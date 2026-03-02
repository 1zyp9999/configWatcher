#ifndef AISERVICE_H
#define AISERVICE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QMap>

/**
 * @brief AI 服务 - 用于意图识别和搜索增强
 * 
 * 功能：
 * 1. 意图识别：分析用户搜索关键词的真实意图
 * 2. 关键词扩展：基于同义词、相关词扩展搜索范围
 * 3. 搜索建议：生成智能化的搜索建议
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

signals:
    /**
     * @brief AI 服务启用状态变化信号
     */
    void enabledChanged(bool enabled);

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

private:
    bool m_enabled = true;
    
    // 同义词词典：key -> [synonym1, synonym2, ...]
    QMap<QString, QStringList> m_synonyms;
    
    // 领域词典：配置 key -> 中文名
    QMap<QString, QString> m_domainDict;
    
    // 意图置信度阈值
    double m_confidenceThreshold = 0.6;
    
    // 领域关键词映射（用于意图识别）
    QMap<QString, QStringList> m_domainKeywords;
};

#endif // AISERVICE_H
