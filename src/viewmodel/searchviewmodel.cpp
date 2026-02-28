#include "searchviewmodel.h"
#include "databasemanager.h"
#include "configentry.h"
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
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QMutexLocker>

SearchViewModel::SearchViewModel(QObject *parent) 
    : QObject(parent)
    , m_parser(new ConfigParser(this))
{
    connect(m_parser, &ConfigParser::loadFinished, this, [this]() {
        setIsLoading(false);
        updateSearchResults();
    });

    connect(m_parser, &ConfigParser::loadProgress, this, [this](int progress) {
        setLoadProgress(progress);
    });
    
    connect(m_parser, &ConfigParser::errorOccurred, this, &SearchViewModel::onParserError);
}

SearchViewModel::~SearchViewModel()
{
    QMutexLocker locker(&m_resultsMutex);
    m_searchResults.clear();
    m_allSearchResults.clear();
}

void SearchViewModel::setSearchText(const QString& text)
{
    if (m_searchText == text) return;
    m_searchText = text;
    emit searchTextChanged();
    // 不立即搜索，等待用户按回车或点击搜索按钮
}

QVariantList SearchViewModel::searchResults() const
{
    QMutexLocker locker(&m_resultsMutex);
    return m_searchResults;
}

void SearchViewModel::setSearchResults(const QVariantList& results)
{
    QMutexLocker locker(&m_resultsMutex);
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

void SearchViewModel::setSearchMode(int mode)
{
    if (m_searchMode == mode) return;
    m_searchMode = mode;
    emit searchModeChanged();
}

void SearchViewModel::setCurrentPage(int page)
{
    if (m_currentPage == page) return;
    m_currentPage = qMax(0, qMin(page, m_totalPages - 1));
    emit currentPageChanged();
    updatePaginatedResults();
}

void SearchViewModel::setTotalPages(int pages)
{
    if (m_totalPages == pages) return;
    m_totalPages = pages;
    emit totalPagesChanged();
}

void SearchViewModel::nextPage()
{
    if (m_currentPage < m_totalPages - 1) {
        setCurrentPage(m_currentPage + 1);
    }
}

void SearchViewModel::previousPage()
{
    if (m_currentPage > 0) {
        setCurrentPage(m_currentPage - 1);
    }
}

void SearchViewModel::goToPage(int page)
{
    setCurrentPage(page);
}

QString SearchViewModel::selectDirectory()
{
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
    // 优先使用数据库搜索
    DatabaseManager* db = DatabaseManager::instance();
    if (db) {
        QVariantList list = db->searchParameters(m_searchText, m_searchMode);
        m_allSearchResults = list;
        setTotalPages((list.size() + m_pageSize - 1) / m_pageSize);
        setCurrentPage(0);
        return;
    }

    // 回退到内存搜索
    auto results = m_parser->search(m_searchText);
    QVariantList list;
    for (const auto& entry : results) {
        list.append(entryToMap(entry));
    }
    
    m_allSearchResults = list;
    setTotalPages((list.size() + m_pageSize - 1) / m_pageSize);
    setCurrentPage(0);
}

void SearchViewModel::updatePaginatedResults()
{
    int start = m_currentPage * m_pageSize;
    int end = qMin(start + m_pageSize, m_allSearchResults.size());
    
    QVariantList pageResults;
    for (int i = start; i < end; ++i) {
        pageResults.append(m_allSearchResults.at(i));
    }
    
    setSearchResults(pageResults);
}

void SearchViewModel::onParserError(const QString& message)
{
    qWarning() << "ConfigParser error:" << message;
}

QVariantMap SearchViewModel::entryToMap(const QSharedPointer<ConfigEntry>& entry)
{
    QVariantMap m;
    m["key"] = entry->key();
    m["value"] = entry->value();
    m["chinese"] = entry->chineseKey();
    m["filePath"] = entry->filePath();
    m["format"] = entry->format();
    return m;
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

    for (const QString &k : m_allKeys) {
        if (k.toLower().startsWith(p) || k.toLower().contains(p)) {
            out.append(k);
            if (out.size() >= maxResults) return out;
        }
    }

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

    auto tokenize = [](const QString &s) {
        QString t = s;
        t.replace('_', ' ');
        t.replace('-', ' ');
        t.replace('.', ' ');
        QStringList parts = t.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        return parts;
    };

    QMap<QString, QStringList> groups;
    for (const QString &k : m_allKeys) {
        QString kl = k.toLower();
        if (!p.isEmpty() && !kl.contains(p)) continue;
        QStringList tokens = tokenize(k.toLower());
        QString g = tokens.isEmpty() ? QStringLiteral("other") : tokens.first();
        groups[g].append(k);
    }

    if (groups.isEmpty()) {
        for (const QString &k : m_allKeys) {
            QStringList tokens = tokenize(k.toLower());
            QString g = tokens.isEmpty() ? QStringLiteral("other") : tokens.first();
            groups[g].append(k);
        }
    }

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
        return true;
    }
    m_dbManager = new DatabaseManager(this);
    return m_dbManager->openDatabase(dbPath);
}

void SearchViewModel::requestSuggestClusters(const QString &prefix, int maxClusters, int maxPerCluster)
{
    if (!m_keyIndexBuilt) buildKeyIndex();
    QStringList keys = m_allKeys;
    QString p = prefix.trimmed().toLower();

    QFuture<QVariantList> future = QtConcurrent::run([keys, p, maxClusters, maxPerCluster]() -> QVariantList {
        QVariantList out;
        const int MIN_NGRAM = 2;
        const int MAX_NGRAM = 3;
        const int MAX_CANDIDATES = 2000;
        const int MAX_TERMS_PER_DOC = 40;
        const double SIM_THRESHOLD = 0.22;

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

        auto normalize = [](const QString &s)->QString {
            QString t = s;
            t.replace(QRegExp("([a-z])([A-Z])"), "\\1 \\2");
            t.replace('_', ' ');
            t.replace('-', ' ');
            t.replace('.', ' ');
            t.replace(QRegExp("[^A-Za-z0-9 ]+"), " ");
            return t.toLower().trimmed();
        };

        auto makeNgrams = [&](const QString &s){
            QString t = normalize(s);
            QStringList words = t.split(QRegExp("\\s+"), QString::SkipEmptyParts);
            QStringList ngrams;
            for (const QString &w : words) {
                QString ww = w;
                int L = ww.length();
                for (int n = MIN_NGRAM; n <= MAX_NGRAM; ++n) {
                    if (L < n) continue;
                    for (int i = 0; i + n <= L; ++i) ngrams.append(ww.mid(i,n));
                }
            }
            for (const QString &w : words) ngrams.append("w:" + w);
            return ngrams;
        };

        QVector<QHash<QString,int>> docTermCounts; docTermCounts.reserve(N);
        QHash<QString,int> docFreq; docFreq.reserve(N*4);

        for (const QString &k : candidates) {
            QStringList terms = makeNgrams(k);
            QHash<QString,int> counts;
            for (const QString &t : terms) counts[t] += 1;
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
            for (auto it = trimmed.constBegin(); it != trimmed.constEnd(); ++it) {
                docFreq[it.key()] += 1;
            }
        }

        QStringList vocab = docFreq.keys();
        Q_UNUSED(vocab);

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
            double norm = 0.0; for (auto it = vec.constBegin(); it != vec.constEnd(); ++it) norm += it.value()*it.value(); norm = sqrt(norm);
            if (norm > 1e-12) {
                for (auto it = vec.begin(); it != vec.end(); ++it) it.value() /= norm;
            }
            vectors.append(vec);
        }

        QVector<bool> used(N, false);
        int clustersAdded = 0;
        for (int i=0; i<N && clustersAdded < maxClusters; ++i) {
            if (used[i]) continue;
            used[i] = true;
            QVariantMap cluster;
            cluster["cluster"] = candidates[i];
            QVariantList items; items.append(candidates[i]);

            QList<QPair<double,int>> sims;
            for (int j=0;j<N;++j) {
                if (used[j]) continue;
                const QHash<QString,double> &a = vectors[i];
                const QHash<QString,double> &b = vectors[j];
                double dot = 0.0;
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
            std::sort(sims.begin(), sims.end(), [](const QPair<double,int>& a, const QPair<double,int>& b){ return a.first > b.first; });
            int addedToCluster = 0;
            for (const auto &pr : sims) {
                if (addedToCluster >= maxPerCluster - 1) break;
                double score = pr.first;
                int idx = pr.second;
                if (score >= SIM_THRESHOLD) {
                    used[idx] = true;
                    items.append(candidates[idx]);
                    ++addedToCluster;
                } else {
                    if (addedToCluster == 0 && items.size()==1) {
                        used[idx] = true;
                        items.append(candidates[idx]);
                        ++addedToCluster;
                    } else break;
                }
            }

            QVariantList qitems;
            for (const QVariant &v : items) qitems.append(v.toString());
            cluster["items"] = qitems;
            out.append(cluster);
            clustersAdded++;
        }

        return out;
    });

    QFutureWatcher<QVariantList>* watcher = new QFutureWatcher<QVariantList>(this);
    connect(watcher, &QFutureWatcher<QVariantList>::finished, this, [this, watcher]() {
        QVariantList res = watcher->result();
        emit suggestClustersReady(res);
        watcher->deleteLater();
    });
    watcher->setFuture(future);
}

void SearchViewModel::deliverSuggestClusters(const QVariantList &clusters)
{
    Q_UNUSED(clusters);
}

void SearchViewModel::openFileRequested(const QString &filePath)
{
    if (filePath.trimmed().isEmpty()) {
        qWarning() << "openFileRequested called with empty filePath";
        return;
    }
    QString fp = filePath;
    if (!QFile::exists(fp)) {
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
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(data, &error);
        if (error.error == QJsonParseError::NoError && doc.isObject()) {
            QJsonObject obj = doc.object();
            for (auto it = obj.begin(); it != obj.end(); ++it) {
                QVariantMap m; m["key"] = it.key(); m["value"] = it.value().toString(); out.append(m);
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
    QWidget* parentWidget = nullptr;
    QString file = QFileDialog::getOpenFileName(parentWidget, QObject::tr("选择配置文件"), dir, QObject::tr("Config files (*.ini *.json)"));
    return file;
}

bool SearchViewModel::writeConfigFile(const QString &filePath, const QVariantList &entries)
{
    if (filePath.trimmed().isEmpty()) return false;
    QFile f(filePath);
    if (!f.exists()) return false;

    QString bak = filePath + ".bak";
    QFile::remove(bak);
    if (!QFile::copy(filePath, bak)) {
        qWarning() << "Failed to backup file" << filePath;
    }

    QString suffix = QFileInfo(filePath).suffix().toLower();
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return false;

    if (suffix == "ini") {
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
    }

    f.close();

    DatabaseManager* db = DatabaseManager::instance();
    if (db) {
        for (const QVariant &v : entries) {
            QVariantMap m = v.toMap();
            QString key = m.value("key").toString();
            QString val = m.value("value").toString();
            db->saveConfigEntry(key, val, filePath, QFileInfo(filePath).suffix().toLower(), "");
        }
    }
    return true;
}
