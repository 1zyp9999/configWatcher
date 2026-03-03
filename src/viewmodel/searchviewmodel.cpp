#include "searchviewmodel.h"
#include "databasemanager.h"
#include "configentry.h"
#include "aiservice.h"
#include <QQmlEngine>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QJsonDocument>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDateTime>
#include <QSettings>
#include <QJsonObject>
#include <QCoreApplication>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

SearchViewModel::SearchViewModel(QObject *parent) : QObject(parent)
{
    m_parser = new ConfigParser(this);
    m_aiService = new AiService(this);

    connect(m_parser, &ConfigParser::loadFinished, this, [=]() {
        setIsLoading(false);
        updateSearchResults();
    });

    connect(m_parser, &ConfigParser::loadProgress, this, [=](int progress) {
        setLoadProgress(progress);
    });
}

void SearchViewModel::setSearchText(const QString& text)
{
    if (m_searchText == text) return;
    m_searchText = text;
    emit searchTextChanged();
    updateSearchResults();
}

void SearchViewModel::setFormatFilter(const QString& filter)
{
    if (m_formatFilter == filter) return;
    m_formatFilter = filter;
    emit formatFilterChanged();
    updateSearchResults();
}

void SearchViewModel::setSearchResults(const QList<QObject*>& results)
{
    m_searchResults = results;
    emit searchResultsChanged();
}

void SearchViewModel::setIsLoading(bool loading)
{
    if (m_isLoading == loading) return;
    m_isLoading = loading;
    emit isLoadingChanged();
}

void SearchViewModel::setLoadProgress(int progress)
{
    if (m_loadProgress == progress) return;
    m_loadProgress = progress;
    emit loadProgressChanged();
}

QString SearchViewModel::selectDirectory()
{
    // 固定搜索路径为 $HOME/.config/Leichen
    QString home = QString::fromLocal8Bit(qgetenv("HOME"));
    return home + "/.config/Leichen";
}

void SearchViewModel::loadConfigFiles(const QStringList& filePaths)
{
    setIsLoading(true);
    setLoadProgress(0);
    m_parser->loadConfigFiles(filePaths);
}

void SearchViewModel::openConfigFile(const QString& filePath)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

void SearchViewModel::updateSearchResults()
{
    // Prefer database-backed search if DB is initialized
    DatabaseManager* db = DatabaseManager::instance();
    if (db) {
        QVariantList list = db->searchParameters(m_searchText, 0, m_formatFilter);
        QList<QObject*> objResults;
        for (const QVariant& item : list) {
            // If DatabaseManager already returned QObject wrapped in QVariant, use it
            if (item.canConvert<QObject*>()) {
                QObject* obj = item.value<QObject*>();
                if (obj) {
                    objResults.append(obj);
                    continue;
                }
            }
            QVariantMap m = item.toMap();
            ConfigEntry* e = new ConfigEntry(this);
            // Fill fields with fallbacks
            e->setKey(m.value("key").toString());
            e->setValue(m.value("value").toString());
            e->setChineseKey(m.value("chinese").toString());
            e->setFilePath(m.value("filePath").toString());
            // optional fields
            if (!m.value("format").toString().isEmpty()) e->setFormat(m.value("format").toString());
            objResults.append(e);
        }
        setSearchResults(objResults);
        return;
    }

    // Fallback to in-memory parser search
    QList<ConfigEntry*> results = m_parser->search(m_searchText);
    QList<QObject*> objResults;

    for (ConfigEntry* entry : results) {
        // ensure parent ownership so QML can access
        if (!entry->parent()) entry->setParent(this);
        objResults.append(entry);
    }

    setSearchResults(objResults);

    // Save entries into DB if initialized
    if (!m_dbManager) return;
    for (ConfigEntry* e : results) {
        // Defensive checks
        QString k = e->key();
        QString v = e->value();
        QString fp = e->filePath();
        QString fmt = e->format();
        QString ck = e->chineseKey();
        m_dbManager->saveConfigEntry(k, v, fp, fmt, ck);
    }
}

void SearchViewModel::buildKeyIndex()
{
    if (m_keyIndexBuilt) return;
    DatabaseManager* db = DatabaseManager::instance();
    if (!db) return;
    m_allKeys = db->listAllKeys();
    m_keyIndexBuilt = true;
}

static int levenshteinDistance(const QString &a, const QString &b)
{
    int n = a.length();
    int m = b.length();
    if (n == 0) return m;
    if (m == 0) return n;
    QVector<int> v0(m+1), v1(m+1);
    for (int j=0;j<=m;j++) v0[j]=j;
    for (int i=1;i<=n;i++) {
        v1[0]=i;
        for (int j=1;j<=m;j++) {
            int cost = (a[i-1]==b[j-1])?0:1;
            v1[j] = qMin(qMin(v1[j-1]+1, v0[j]+1), v0[j-1]+cost);
        }
        v0 = v1;
    }
    return v1[m];
}

QStringList SearchViewModel::suggestKeys(const QString &prefix, int maxResults)
{
    if (!m_keyIndexBuilt) buildKeyIndex();
    QStringList out;
    if (prefix.trimmed().isEmpty()) return out;
    QString p = prefix.toLower();

    // 1) prefix/substring exact match first
    for (const QString &k : m_allKeys) {
        if (k.toLower().startsWith(p) || k.toLower().contains(p)) {
            out.append(k);
            if (out.size() >= maxResults) return out;
        }
    }

    // 2) compute small Levenshtein distance for remaining keys
    QVector<QPair<int,QString>> scored;
    for (const QString &k : m_allKeys) {
        if (out.contains(k)) continue;
        int d = levenshteinDistance(p, k.toLower());
        scored.append(qMakePair(d, k));
    }
    std::sort(scored.begin(), scored.end(), [](const QPair<int,QString>& a, const QPair<int,QString>& b){ return a.first < b.first; });
    for (const auto &pr : scored) {
        out.append(pr.second);
        if (out.size() >= maxResults) break;
    }
    return out;
}

QVariantList SearchViewModel::suggestClusters(const QString &prefix, int maxClusters, int maxPerCluster)
{
    if (!m_keyIndexBuilt) buildKeyIndex();
    QVariantList out;
    QString p = prefix.toLower();

    // simple tokenization: split by ., _, - and camelCase boundaries
    auto tokenize = [](const QString &s) {
        QString t = s;
        t.replace('_', ' ');
        t.replace('-', ' ');
        t.replace('.', ' ');
        QStringList parts = t.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        return parts;
    };

    // score keys by whether they match prefix; group by first token
    QMap<QString, QStringList> groups;
    for (const QString &k : m_allKeys) {
        QString kl = k.toLower();
        if (!p.isEmpty() && !kl.contains(p)) continue; // filter to relevant ones
        QStringList tokens = tokenize(k.toLower());
        QString g = tokens.isEmpty() ? QStringLiteral("other") : tokens.first();
        groups[g].append(k);
    }

    // If no filtered groups (prefix empty or no match), fallback to grouping all by first token
    if (groups.isEmpty()) {
        for (const QString &k : m_allKeys) {
            QStringList tokens = tokenize(k.toLower());
            QString g = tokens.isEmpty() ? QStringLiteral("other") : tokens.first();
            groups[g].append(k);
        }
    }

    // sort groups by size descending
    QList<QPair<int,QString>> order;
    for (auto it = groups.constBegin(); it != groups.constEnd(); ++it) {
        order.append(qMakePair(it.value().size(), it.key()));
    }
    std::sort(order.begin(), order.end(), [](const QPair<int,QString>& a, const QPair<int,QString>& b){ return a.first > b.first; });

    int added = 0;
    for (const auto &pr : order) {
        if (added >= maxClusters) break;
        QString gname = pr.second;
        QVariantMap gm;
        gm["cluster"] = gname;
        QStringList items = groups.value(gname);
        // limit items per cluster, sort alphabetically
        std::sort(items.begin(), items.end(), [](const QString &a, const QString &b){ return a.toLower() < b.toLower(); });
        QVariantList iv;
        int cnt = 0;
        for (const QString &it : items) {
            iv.append(it);
            if (++cnt >= maxPerCluster) break;
        }
        gm["items"] = iv;
        out.append(gm);
        added++;
    }

    return out;
}

bool SearchViewModel::initializeDatabase(const QString& dbPath)
{
    if (m_dbManager) {
        // already initialized
        return true;
    }
    m_dbManager = new DatabaseManager(this);
    return m_dbManager->openDatabase(dbPath);
}

void SearchViewModel::requestSuggestClusters(const QString &prefix, int maxClusters, int maxPerCluster)
{
    if (!m_keyIndexBuilt) buildKeyIndex();
    // copy keys for thread-safety
    QStringList keys = m_allKeys;
    QString p = prefix.trimmed().toLower();

    // Run heavy clustering in background
    QFuture<QVariantList> future = QtConcurrent::run([keys, p, maxClusters, maxPerCluster]() -> QVariantList {
        QVariantList out;
        // Parameters
        const int MIN_NGRAM = 2;
        const int MAX_NGRAM = 3;
        const int MAX_CANDIDATES = 2000; // cap for performance
        const int MAX_TERMS_PER_DOC = 40; // trim per-doc terms
        const double SIM_THRESHOLD = 0.22; // cosine similarity threshold for grouping

        // 1) Build candidate list (filter by prefix if provided)
        QStringList candidates;
        candidates.reserve(keys.size());
        for (const QString &k : keys) {
            if (!p.isEmpty()) {
                if (k.toLower().contains(p)) candidates.append(k);
            } else {
                candidates.append(k);
            }
            if ((int)candidates.size() >= MAX_CANDIDATES) break;
        }
        if (candidates.isEmpty()) return out;

        int N = candidates.size();

        // Helpers: normalize and generate n-grams
        auto normalize = [](const QString &s)->QString {
            QString t = s;
            // insert spaces before camelCase boundaries
            t.replace(QRegExp("([a-z])([A-Z])"), "\\1 \\\\2");
            // replace separators with space
            t.replace('_', ' ');
            t.replace('-', ' ');
            t.replace('.', ' ');
            // remove non-alnum except space
            t.replace(QRegExp("[^A-Za-z0-9 ]+"), " ");
            return t.toLower().trimmed();
        };

        auto makeNgrams = [&](const QString &s){
            QString t = normalize(s);
            QStringList words = t.split(QRegExp("\\s+"), QString::SkipEmptyParts);
            QStringList ngrams;
            // for each word generate char n-grams across MIN..MAX
            for (const QString &w : words) {
                QString ww = w;
                int L = ww.length();
                for (int n = MIN_NGRAM; n <= MAX_NGRAM; ++n) {
                    if (L < n) continue;
                    for (int i = 0; i + n <= L; ++i) ngrams.append(ww.mid(i,n));
                }
            }
            // also add whole words as terms
            for (const QString &w : words) ngrams.append("w:" + w);
            return ngrams;
        };

        // 2) Build term frequencies and document frequencies
        QVector<QHash<QString,int>> docTermCounts; docTermCounts.reserve(N);
        QHash<QString,int> docFreq; docFreq.reserve(N*4);

        for (const QString &k : candidates) {
            QStringList terms = makeNgrams(k);
            QHash<QString,int> counts;
            for (const QString &t : terms) counts[t] += 1;
            // trim to top terms by count to limit vector size
            QList<QPair<int,QString>> pairs;
            for (auto it = counts.constBegin(); it != counts.constEnd(); ++it) pairs.append(qMakePair(it.value(), it.key()));
            std::sort(pairs.begin(), pairs.end(), [](const QPair<int,QString>& a, const QPair<int,QString>& b){ return a.first > b.first; });
            QHash<QString,int> trimmed;
            int added = 0;
            for (const auto &pr : pairs) {
                trimmed.insert(pr.second, pr.first);
                if (++added >= MAX_TERMS_PER_DOC) break;
            }
            docTermCounts.append(trimmed);
            // update DF
            for (auto it = trimmed.constBegin(); it != trimmed.constEnd(); ++it) {
                docFreq[it.key()] += 1;
            }
        }

        // Vocabulary
        QStringList vocab = docFreq.keys();

        // 3) Build TF-IDF vectors (sparse maps)
        QVector<QHash<QString,double>> vectors; vectors.reserve(N);
        for (int i=0;i<N;++i) {
            const QHash<QString,int> &cnts = docTermCounts[i];
            double total = 0.0;
            for (auto it = cnts.constBegin(); it != cnts.constEnd(); ++it) total += it.value();
            QHash<QString,double> vec;
            for (auto it = cnts.constBegin(); it != cnts.constEnd(); ++it) {
                double tf = (total>0.0) ? (it.value() / total) : 0.0;
                double idf = log( (double)(N + 1) / (1.0 + docFreq.value(it.key(),1)) );
                vec.insert(it.key(), tf * idf);
            }
            // optional: normalize vector length
            double norm = 0.0; for (auto it = vec.constBegin(); it != vec.constEnd(); ++it) norm += it.value()*it.value(); norm = sqrt(norm);
            if (norm > 1e-12) {
                for (auto it = vec.begin(); it != vec.end(); ++it) it.value() /= norm;
            }
            vectors.append(vec);
        }

        // 4) Greedy clustering using cosine similarity
        QVector<bool> used(N, false);
        int clustersAdded = 0;
        for (int i=0; i<N && clustersAdded < maxClusters; ++i) {
            if (used[i]) continue;
            // make i as seed
            used[i] = true;
            QVariantMap cluster;
            cluster["cluster"] = candidates[i];
            QVariantList items; items.append(candidates[i]);

            // compute similarity of seed to all others
            QList<QPair<double,int>> sims;
            for (int j=0;j<N;++j) {
                if (used[j]) continue;
                // cosine between vectors[i] and vectors[j]
                const QHash<QString,double> &a = vectors[i];
                const QHash<QString,double> &b = vectors[j];
                double dot = 0.0;
                // iterate smaller map
                if (a.size() < b.size()) {
                    for (auto it = a.constBegin(); it != a.constEnd(); ++it) {
                        double bv = b.value(it.key(), 0.0);
                        if (bv != 0.0) dot += it.value() * bv;
                    }
                } else {
                    for (auto it = b.constBegin(); it != b.constEnd(); ++it) {
                        double av = a.value(it.key(), 0.0);
                        if (av != 0.0) dot += it.value() * av;
                    }
                }
                if (dot > 0.0) sims.append(qMakePair(dot, j));
            }
            // sort descending
            std::sort(sims.begin(), sims.end(), [](const QPair<double,int>& a, const QPair<double,int>& b){ return a.first > b.first; });
            int addedToCluster = 0;
            for (const auto &pr : sims) {
                if (addedToCluster >= maxPerCluster - 1) break; // -1 because seed already included
                double score = pr.first;
                int idx = pr.second;
                if (score >= SIM_THRESHOLD) {
                    used[idx] = true;
                    items.append(candidates[idx]);
                    ++addedToCluster;
                } else {
                    // if nothing matched threshold, we still may want a few nearest neighbors
                    if (addedToCluster == 0 && items.size()==1) {
                        used[idx] = true;
                        items.append(candidates[idx]);
                        ++addedToCluster;
                    } else break;
                }
            }

            // build QVariantList for items to ensure QML receives plain string array
            QVariantList qitems;
            for (const QVariant &v : items) qitems.append(v.toString());
            cluster["items"] = qitems;
            out.append(cluster);
            clustersAdded++;
        }

        // write debug log to file (attempt) with timestamp
        try {
            QJsonDocument doc = QJsonDocument::fromVariant(QVariant(out));
            QString json = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
            // use user home directory instead of root to avoid permission issues
            QString logDir = QDir::homePath() + "/.aoi/log";
            QDir().mkpath(logDir);
            QFile f(logDir + "/configwatcher.log");
            if (f.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream ts(&f);
                ts << QDateTime::currentDateTime().toString(Qt::ISODate) << " PREFIX=" << p << " CANDIDATES=" << candidates.size() << " CLUSTERS=" << out.size() << "\n";
                ts << json << "\n---\n";
                f.close();
            }
        } catch (...) {
            // swallow logging errors
        }

        return out;
    });

    // Watcher to emit signal when ready
    QFutureWatcher<QVariantList>* watcher = new QFutureWatcher<QVariantList>(this);
    connect(watcher, &QFutureWatcher<QVariantList>::finished, this, [this, watcher]() {
        QVariantList res = watcher->result();
        // log delivered result briefly
        try {
            QJsonDocument doc = QJsonDocument::fromVariant(QVariant(res));
            QString json = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
            QString logDir = QDir::homePath() + "/.aoi/log";
            QDir().mkpath(logDir);
            QFile f(logDir + "/configwatcher.log");
            if (f.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream ts(&f);
                ts << QDateTime::currentDateTime().toString(Qt::ISODate) << " DELIVERED_CLUSTERS=" << res.size() << "\n";
                ts << json.left(2000) << "\n---\n"; // cap large dumps
                f.close();
            }
        } catch (...) {}

        qDebug() << "suggestClustersReady: size=" << res.size();
        emit suggestClustersReady(res);
        watcher->deleteLater();
    });
    watcher->setFuture(future);
}

void SearchViewModel::deliverSuggestClusters(const QVariantList &clusters)
{
    // This slot can be used by QML connected signal to directly deliver clusters
    Q_UNUSED(clusters);
}

void SearchViewModel::openFileRequested(const QString &filePath)
{
    if (filePath.trimmed().isEmpty()) {
        qWarning() << "openFileRequested called with empty filePath";
        return;
    }
    // 防御性：如果路径不是绝对路径，尝试构造为相对于HOME的路径
    QString fp = filePath;
    if (!QFile::exists(fp)) {
        // 尝试直接用 home 路径前缀
        QString alt = QDir::homePath() + "/" + filePath;
        if (QFile::exists(alt)) fp = alt;
    }
    qDebug() << "Opening config file:" << fp;
    openConfigFile(fp);
}

QVariantList SearchViewModel::readConfigFile(const QString &filePath)
{
    QVariantList out;
    if (filePath.trimmed().isEmpty()) return out;
    QFile f(filePath);
    if (!f.exists()) return out;
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return out;

    QString suffix = QFileInfo(filePath).suffix().toLower();
    if (suffix == "ini") {
        QTextStream in(&f);
        QString section;
        while (!in.atEnd()) {
            QString line = in.readLine();
            QString t = line.trimmed();
            if (t.isEmpty() || t.startsWith(';') || t.startsWith('#')) continue;
            if (t.startsWith('[') && t.endsWith(']')) { section = t.mid(1, t.size()-2).trimmed(); continue; }
            int eq = line.indexOf('=');
            if (eq > 0) {
                QString key = line.left(eq).trimmed();
                QString val = line.mid(eq+1).trimmed();
                QVariantMap m; m["key"] = section.isEmpty() ? key : section + "." + key; m["value"] = val; out.append(m);
            }
        }
    } else if (suffix == "json") {
        QByteArray data = f.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            for (auto it = obj.begin(); it != obj.end(); ++it) {
                QVariantMap m; m["key"] = it.key(); m["value"] = it.value().toString(); out.append(m);
            }
        }
    } else if (suffix == "xml") {
        QXmlStreamReader xml(&f);
        QStringList sectionStack;
        while (!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement) {
                QString elemName = xml.name().toString();
                sectionStack.append(elemName);

                // 属性作为键值对
                QXmlStreamAttributes attrs = xml.attributes();
                for (const QXmlStreamAttribute& attr : attrs) {
                    QString prefix = sectionStack.join(".");
                    QVariantMap m;
                    m["key"] = prefix + "[@" + attr.name().toString() + "]";
                    m["value"] = attr.value().toString();
                    out.append(m);
                }

                // 文本内容
                QString text = xml.readElementText(QXmlStreamReader::SkipChildElements).trimmed();
                if (!text.isEmpty()) {
                    QString key = sectionStack.join(".");
                    QVariantMap m;
                    m["key"] = key;
                    m["value"] = text;
                    out.append(m);
                    // readElementText 已消费了 EndElement，需手动弹出
                    if (!sectionStack.isEmpty()) sectionStack.removeLast();
                }
            } else if (token == QXmlStreamReader::EndElement) {
                if (!sectionStack.isEmpty()) sectionStack.removeLast();
            }
        }
    }
    f.close();
    return out;
}

QString SearchViewModel::pickConfigFile()
{
    QString home = QString::fromLocal8Bit(qgetenv("HOME"));
    QString dir = home + "/.config/Leichen";
    QString file = QFileDialog::getOpenFileName(nullptr, QObject::tr("选择配置文件"), dir, QObject::tr("Config files (*.ini *.json *.xml)"));
    return file;
}

bool SearchViewModel::writeConfigFile(const QString &filePath, const QVariantList &entries)
{
    if (filePath.trimmed().isEmpty()) return false;
    QFile f(filePath);
    if (!f.exists()) return false;

    // 先读取旧值用于记录修改
    QVariantList oldEntries = readConfigFile(filePath);
    QMap<QString, QString> oldMap;
    for (const QVariant &v : oldEntries) {
        QVariantMap m = v.toMap();
        oldMap[m.value("key").toString()] = m.value("value").toString();
    }

    // 备份原文件
    QString bak = filePath + ".bak";
    QFile::remove(bak);
    if (!QFile::copy(filePath, bak)) {
        qWarning() << "Failed to backup file" << filePath;
    }

    QString suffix = QFileInfo(filePath).suffix().toLower();
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return false;

    if (suffix == "ini") {
        // 简单实现：把 entries 中的 key 包含 '.' 的视为 section.key，按 section 聚合然后写入
        QMap<QString, QMap<QString,QString>> sections;
        for (const QVariant &v : entries) {
            QVariantMap m = v.toMap();
            QString k = m.value("key").toString();
            QString val = m.value("value").toString();
            QString section = "";
            QString name = k;
            int dot = k.indexOf('.');
            if (dot > 0) { section = k.left(dot); name = k.mid(dot+1); }
            sections[section][name] = val;
        }
        QTextStream out(&f);
        for (auto sit = sections.constBegin(); sit != sections.constEnd(); ++sit) {
            QString sname = sit.key();
            if (!sname.isEmpty()) out << "[" << sname << "]\n";
            QMap<QString,QString> map = sit.value();
            for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
                out << it.key() << "=" << it.value() << "\n";
            }
            out << "\n";
        }
    } else if (suffix == "json") {
        QJsonObject obj;
        for (const QVariant &v : entries) {
            QVariantMap m = v.toMap();
            obj.insert(m.value("key").toString(), QJsonValue::fromVariant(m.value("value")));
        }
        QJsonDocument doc(obj);
        f.write(doc.toJson());
    } else if (suffix == "xml") {
        QXmlStreamWriter xml(&f);
        xml.setAutoFormatting(true);
        xml.writeStartDocument();
        xml.writeStartElement("config");
        for (const QVariant &v : entries) {
            QVariantMap m = v.toMap();
            QString key = m.value("key").toString();
            QString val = m.value("value").toString();
            // 跳过属性条目 ([@attr] 格式)，只写元素
            if (key.contains("[@")) continue;
            // 取最后一个点号后面的名称作为元素名
            QString elemName = key.contains(".") ? key.mid(key.lastIndexOf('.') + 1) : key;
            if (elemName.isEmpty()) elemName = "item";
            xml.writeTextElement(elemName, val);
        }
        xml.writeEndElement(); // </config>
        xml.writeEndDocument();
    }

    f.close();

    // 同步到数据库：逐条保存，并记录修改
    DatabaseManager* db = DatabaseManager::instance();
    if (db) {
        for (const QVariant &v : entries) {
            QVariantMap m = v.toMap();
            QString key = m.value("key").toString();
            QString val = m.value("value").toString();
            db->saveConfigEntry(key, val, filePath, QFileInfo(filePath).suffix().toLower(), "");

            // 记录修改历史
            QString oldVal = oldMap.value(key);
            if (oldVal != val) {
                db->addChangeLog(filePath, key, oldVal, val);
            }
        }
    }
    return true;
}

// ========== AI 相关方法实现 ==========

void SearchViewModel::setAiEnabled(bool enabled)
{
    if (m_aiEnabled != enabled) {
        m_aiEnabled = enabled;
        if (m_aiService) {
            m_aiService->setEnabled(enabled);
        }
        emit aiEnabledChanged(enabled);
    }
}

void SearchViewModel::analyzeSearchQuery(const QString& query)
{
    if (!m_aiEnabled || !m_aiService) return;
    
    m_aiIntent = m_aiService->analyzeIntent(query);
    m_aiConfidence = m_aiService->getIntentConfidence(query);
    m_aiSuggestions = m_aiService->generateSuggestions(query);
    m_aiExplanation = m_aiService->explainQuery(query);
    
    emit aiIntentChanged();
    emit aiConfidenceChanged();
    emit aiSuggestionsChanged();
    emit aiExplanationChanged();
}

void SearchViewModel::applyAiSuggestion(const QString& suggestion)
{
    if (suggestion.trimmed().isEmpty()) return;
    
    setSearchText(suggestion);
    updateSearchResults();
}

void SearchViewModel::expandSearchWithAi(const QString& query)
{
    if (!m_aiEnabled || !m_aiService) return;
    
    QStringList expanded = m_aiService->expandKeywords(query, 10);
    
    // 使用扩展的关键词进行搜索
    QVariantList allResults;
    for (const QString& keyword : expanded) {
        DatabaseManager* db = DatabaseManager::instance();
        if (db) {
            QVariantList results = db->searchParameters(keyword, 0);
            allResults.append(results);
        }
    }
    
    // 去重并转换为 QObject 列表
    QList<QObject*> objResults;
    QSet<QString> seenKeys;
    for (const QVariant& item : allResults) {
        if (item.canConvert<QObject*>()) {
            QObject* obj = item.value<QObject*>();
            if (obj) {
                ConfigEntry* entry = qobject_cast<ConfigEntry*>(obj);
                if (entry && !seenKeys.contains(entry->key())) {
                    seenKeys.insert(entry->key());
                    if (!entry->parent()) entry->setParent(this);
                    objResults.append(entry);
                }
            }
        }
    }
    
    setSearchResults(objResults);
}

QString SearchViewModel::getAiExplanation(const QString& query)
{
    if (!m_aiService) return QString();
    return m_aiService->explainQuery(query);
}

// ========== 用户词典方法 ==========

void SearchViewModel::addUserTerm(const QString& key, const QString& chinese, const QVariantList& synonyms)
{
    if (m_aiService) {
        QStringList synList;
        for (const QVariant& v : synonyms) {
            synList.append(v.toString());
        }
        m_aiService->addUserTerm(key, chinese, synList);
    }
}

void SearchViewModel::removeUserTerm(const QString& key)
{
    if (m_aiService) {
        m_aiService->removeUserTerm(key);
    }
}

QVariantList SearchViewModel::getUserTerms() const
{
    if (!m_aiService) return QVariantList();
    return m_aiService->getUserTerms();
}

// ========== 搜索历史方法 ==========

void SearchViewModel::recordSearch(const QString& query, int resultCount, bool selected)
{
    if (m_aiService && m_learningEnabled) {
        m_aiService->recordSearchHistory(query, resultCount, selected);
    }
}

QVariantList SearchViewModel::getSearchHistory(int limit)
{
    if (!m_aiService) return QVariantList();
    return m_aiService->getSearchHistory(limit);
}

void SearchViewModel::clearSearchHistory()
{
    if (m_aiService) {
        m_aiService->clearSearchHistory();
    }
}

QVariantList SearchViewModel::getHotSearches(int limit)
{
    if (!m_aiService) return QVariantList();
    return m_aiService->getHotSearches(limit);
}

void SearchViewModel::setLearningEnabled(bool enabled)
{
    if (m_learningEnabled != enabled) {
        m_learningEnabled = enabled;
        if (m_aiService) {
            m_aiService->setLearningEnabled(enabled);
        }
        emit learningEnabledChanged(enabled);
    }
}

bool SearchViewModel::isLearningEnabled() const
{
    return m_learningEnabled;
}
