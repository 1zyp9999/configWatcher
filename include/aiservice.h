#ifndef AISERVICE_H
#define AISERVICE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QMap>
#include <QStandardPaths>
#include <QJsonDocument>

/**
 * @brief 搜索历史记录
 */
struct SearchHistoryItem {
    QString query;
    QString intent;
    QDateTime timestamp;
    int resultCount;
    bool selected;  // 用户是否点击了结果
};

/**
 * @brief AI 服务 - 用于意图识别和搜索增强
 * 
 * 功能：
 * 1. 意图识别：分析用户搜索关键词的真实意图
 * 2. 关键词扩展：基于同义词、相关词扩展搜索范围
 * 3. 搜索建议：生成智能化的搜索建议
 * 4. 用户词典：支持用户自定义术语映射
 * 5. 搜索历史：记录并学习用户搜索习惯
 */
class AiService : public QObject
{
    Q_OBJECT

public:
    explicit AiService(QObject *parent = nullptr);
    ~AiService();

    // ========== 意图识别 ==========
    
    /**
     * @brief 分析搜索意图
     * @param query 用户输入的搜索词
     * @return 意图类型：search_key, search_value, search_chinese, navigate, unknown
     */
    Q_INVOKABLE QString analyzeIntent(const QString& query);
    
    /**
     * @brief 获取意图的置信度
     * @param query 用户输入的搜索词
     * @return 置信度 0.0-1.0
     */
    Q_INVOKABLE double getIntentConfidence(const QString& query);
    
    /**
     * @brief 提取搜索词中的实体（如配置项名称、值等）
     * @param query 用户输入的搜索词
     * @return 提取的实体列表
     */
    Q_INVOKABLE QVariantList extractEntities(const QString& query);

    // ========== 关键词扩展 ==========
    
    /**
     * @brief 扩展搜索关键词
     * @param query 原始搜索词
     * @param maxResults 最大返回数量
     * @return 扩展后的关键词列表
     */
    Q_INVOKABLE QStringList expandKeywords(const QString& query, int maxResults = 10);
    
    /**
     * @brief 获取同义词
     * @param word 原始词
     * @return 同义词列表
     */
    Q_INVOKABLE QStringList getSynonyms(const QString& word);
    
    /**
     * @brief 获取相关词
     * @param word 原始词
     * @return 相关词列表
     */
    Q_INVOKABLE QStringList getRelatedWords(const QString& word);

    // ========== 搜索建议 ==========
    
    /**
     * @brief 生成搜索建议
     * @param query 用户输入的部分搜索词
     * @param context 上下文信息（如当前配置类型）
     * @param maxSuggestions 最大建议数量
     * @return 搜索建议列表
     */
    Q_INVOKABLE QVariantList generateSuggestions(const QString& query, const QString& context = "", int maxSuggestions = 5);
    
    /**
     * @brief 解释搜索词的可能含义
     * @param query 搜索词
     * @return 解释说明
     */
    Q_INVOKABLE QString explainQuery(const QString& query);
    
    /**
     * @brief 判断搜索词是否需要模糊匹配
     * @param query 搜索词
     * @return 是否需要模糊匹配
     */
    Q_INVOKABLE bool needsFuzzyMatch(const QString& query);

    // ========== 配置管理 ==========
    
    /**
     * @brief 加载领域词典（针对特定配置文件的术语）
     * @param terms 术语列表，格式：{"key": "中文名", ...}
     */
    Q_INVOKABLE void loadDomainDictionary(const QVariantMap& terms);
    
    /**
     * @brief 清空词典
     */
    Q_INVOKABLE void clearDictionary();
    
    /**
     * @brief 获取词典大小
     * @return 词典中的词条数量
     */
    Q_INVOKABLE int getDictionarySize() const;

    // ========== 用户自定义词典 ==========
    
    /**
     * @brief 添加用户自定义词条
     * @param key 英文键名
     * @param chinese 中文名/别名
     * @param synonyms 同义词列表（可选）
     */
    Q_INVOKABLE void addUserTerm(const QString& key, const QString& chinese, const QStringList& synonyms = QStringList());
    
    /**
     * @brief 删除用户自定义词条
     * @param key 英文键名
     */
    Q_INVOKABLE void removeUserTerm(const QString& key);
    
    /**
     * @brief 获取所有用户自定义词条
     * @return 用户词条列表
     */
    Q_INVOKABLE QVariantList getUserTerms() const;
    
    /**
     * @brief 保存用户词典到文件
     * @return 是否成功
     */
    Q_INVOKABLE bool saveUserDictionary();
    
    /**
     * @brief 从文件加载用户词典
     * @return 是否成功
     */
    Q_INVOKABLE bool loadUserDictionary();
    
    /**
     * @brief 获取用户词典文件路径
     * @return 文件路径
     */
    Q_INVOKABLE QString getUserDictionaryPath() const;

    // ========== 搜索历史 ==========
    
    /**
     * @brief 记录搜索历史
     * @param query 搜索词
     * @param resultCount 结果数量
     * @param selected 用户是否点击了结果
     */
    Q_INVOKABLE void recordSearchHistory(const QString& query, int resultCount = 0, bool selected = false);
    
    /**
     * @brief 获取搜索历史
     * @param limit 最大返回数量
     * @return 搜索历史列表
     */
    Q_INVOKABLE QVariantList getSearchHistory(int limit = 20);

    /**
     * @brief 清除搜索历史
     */
    Q_INVOKABLE void clearSearchHistory();

    /**
     * @brief 删除单条搜索历史
     * @param query 搜索词
     */
    Q_INVOKABLE bool deleteSearchHistory(const QString& query);

    /**
     * @brief 获取热门搜索（基于历史统计）
     * @param limit 最大返回数量
     * @return 热门搜索列表
     */
    Q_INVOKABLE QVariantList getHotSearches(int limit = 10);
    
    /**
     * @brief 保存搜索历史到文件
     * @return 是否成功
     */
    Q_INVOKABLE bool saveSearchHistory();
    
    /**
     * @brief 从文件加载搜索历史
     * @return 是否成功
     */
    Q_INVOKABLE bool loadSearchHistory();
    
    /**
     * @brief 获取搜索历史文件路径
     * @return 文件路径
     */
    Q_INVOKABLE QString getSearchHistoryPath() const;

    // ========== 设置 ==========
    
    /**
     * @brief 设置是否启用 AI 增强
     * @param enabled 是否启用
     */
    Q_INVOKABLE void setEnabled(bool enabled);
    
    /**
     * @brief 检查 AI 服务是否启用
     * @return 是否启用
     */
    Q_INVOKABLE bool isEnabled() const { return m_enabled; }
    
    /**
     * @brief 设置是否启用搜索历史学习
     * @param enabled 是否启用
     */
    Q_INVOKABLE void setLearningEnabled(bool enabled);
    
    /**
     * @brief 检查学习功能是否启用
     * @return 是否启用
     */
    Q_INVOKABLE bool isLearningEnabled() const { return m_learningEnabled; }

signals:
    /**
     * @brief AI 服务启用状态变化信号
     */
    void enabledChanged(bool enabled);
    
    /**
     * @brief 用户词典变化信号
     */
    void userDictionaryChanged();
    
    /**
     * @brief 搜索历史变化信号
     */
    void searchHistoryChanged();

private:
    /**
     * @brief 初始化内置的同义词词典
     */
    void initSynonymDictionary();
    
    /**
     * @brief 初始化领域关键词映射
     */
    void initDomainKeywords();
    
    /**
     * @brief 计算两个字符串的相似度（0-1）
     */
    double calculateSimilarity(const QString& s1, const QString& s2);
    
    /**
     * @brief 拼音相似度（简单实现：基于字符串相似度）
     */
    double pinyinSimilarity(const QString& chinese, const QString& pinyin);
    
    /**
     * @brief 基于搜索历史调整建议权重
     */
    void adjustSuggestionsByHistory(QVariantList& suggestions);

private:
    bool m_enabled = true;
    bool m_learningEnabled = true;
    bool m_synonymsLoaded = false;
    bool m_domainKeywordsLoaded = false;
    
    void ensureSynonymsLoaded();
    void ensureDomainKeywordsLoaded();
    
    // 同义词词典：key -> [synonym1, synonym2, ...]
    QMap<QString, QStringList> m_synonyms;
    
    // 领域词典：配置 key -> 中文名
    QMap<QString, QString> m_domainDict;
    
    // 用户自定义词典：key -> {chinese, synonyms}
    struct UserTerm {
        QString chinese;
        QStringList synonyms;
    };
    QMap<QString, UserTerm> m_userDict;
    
    // 搜索历史
    QList<SearchHistoryItem> m_searchHistory;
    QMap<QString, int> m_searchFrequency;  // 搜索词频统计
    
    // 意图置信度阈值
    double m_confidenceThreshold = 0.6;
    
    // 领域关键词映射（用于意图识别）
    QMap<QString, QStringList> m_domainKeywords;
    
    // 反向索引：关键词 -> 领域
    QMap<QString, QString> m_keywordToDomain;
    bool m_reverseIndexBuilt = false;
    void buildReverseIndex();
    
    // 文件路径
    QString m_userDictPath;
    QString m_searchHistoryPath;
};

#endif // AISERVICE_H
