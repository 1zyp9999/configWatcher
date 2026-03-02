#include "aiservice.h"
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QDebug>
#include <QtConcurrent>
#include <QFuture>

AiService::AiService(QObject *parent) : QObject(parent)
{
    initSynonymDictionary();
    initDomainKeywords();
}

AiService::~AiService()
{
}

void AiService::initSynonymDictionary()
{
    // ===== 相机/光学相关同义词 =====
    m_synonyms["相机"] = QStringList{"camera", "摄相机", "工业相机", "面阵相机", "线阵相机"};
    m_synonyms["camera"] = QStringList{"相机", "cam", "industrial camera"};
    m_synonyms["曝光"] = QStringList{"exposure", "曝光时间", "积分时间", "integration"};
    m_synonyms["增益"] = QStringList{"gain", "analog gain", "digital gain", "模拟增益", "数字增益"};
    m_synonyms["触发"] = QStringList{"trigger", "软触发", "硬触发", "外触发"};
    m_synonyms["帧率"] = QStringList{"framerate", "fps", "frame rate", "帧频"};
    m_synonyms["分辨率"] = QStringList{"resolution", "width", "height", "宽", "高"};
    m_synonyms["白平衡"] = QStringList{"white balance", "wb", "色温"};
    m_synonyms["伽马"] = QStringList{"gamma", "γ", "灰度"};
    m_synonyms["对比度"] = QStringList{"contrast", "反差"};
    m_synonyms["亮度"] = QStringList{"brightness", "luminance", "明暗"};
    m_synonyms["饱和"] = QStringList{"saturation", "饱和度", "色彩饱和度"};
    m_synonyms["锐度"] = QStringList{"sharpness", "清晰度", "锐化"};
    m_synonyms["镜头"] = QStringList{"lens", "焦距", "focus", "对焦"};
    m_synonyms["光圈"] = QStringList{"aperture", "f 值", "f-number"};
    m_synonyms["roi"] = QStringList{"region of interest", "感兴趣区域", "裁剪区域"};
    m_synonyms["binning"] = QStringList{"像素合并", "合并", "采样"};
    m_synonyms["offset"] = QStringList{"偏移", "黑电平", "black level"};
    m_synonyms["翻转"] = QStringList{"flip", "镜像", "mirror", "rotate", "旋转"};
    m_synonyms["格式"] = QStringList{"format", "pixel format", "像素格式", "输出格式"};
    m_synonyms["压缩"] = QStringList{"compression", "jpeg", "h264", "编码"};
    m_synonyms["传输"] = QStringList{"transfer", "usb", "gige", "cameralink", "协议"};
    m_synonyms["温度"] = QStringList{"temperature", "temp", "传感器温度", "冷却"};
    m_synonyms["风扇"] = QStringList{"fan", "散热", "冷却风扇"};
    m_synonyms["固件"] = QStringList{"firmware", "版本", "version"};
    m_synonyms["序列号"] = QStringList{"serial number", "sn", "设备序列号", "id"};
    m_synonyms["状态"] = QStringList{"status", "state", "连接状态", "在线"};
    m_synonyms["错误"] = QStringList{"error", "错误码", "故障", "exception"};
    m_synonyms["校准"] = QStringList{"calibration", "标定", "校正", "矫正"};
    m_synonyms["畸变"] = QStringList{"distortion", "镜头畸变", "径向畸变", "切向畸变"};
    m_synonyms["内参"] = QStringList{"intrinsic", "内参数", "焦距", "主点"};
    m_synonyms["外参"] = QStringList{"extrinsic", "外参数", "旋转", "平移"};
    m_synonyms["投影"] = QStringList{"projector", "投影仪", "projection", "结构光"};
    m_synonyms["图案"] = QStringList{"pattern", "条纹", "fringe", "编码图案"};
    m_synonyms["相位"] = QStringList{"phase", "相移", "phase shift"};
    m_synonyms["解调"] = QStringList{"demodulation", "解包裹", "unwrapping"};
    m_synonyms["点云"] = QStringList{"point cloud", "3d 点云", "深度图"};
    m_synonyms["深度"] = QStringList{"depth", "距离", "z 值"};
    m_synonyms["坐标"] = QStringList{"coordinate", "coords", "x", "y", "z"};
    m_synonyms["变换"] = QStringList{"transform", "矩阵", "homography", "单应性"};
    m_synonyms["映射"] = QStringList{"mapping", "查找表", "lut", "lookup table"};
    m_synonyms["阈值"] = QStringList{"threshold", "二值化", "分割"};
    m_synonyms["滤波"] = QStringList{"filter", "平滑", "去噪", "中值滤波", "高斯滤波"};
    m_synonyms["边缘"] = QStringList{"edge", "轮廓", "contour", "边界"};
    m_synonyms["特征"] = QStringList{"feature", "角点", "sift", "surf", "orb"};
    m_synonyms["匹配"] = QStringList{"match", "匹配点", "对应点", "correspondence"};
    m_synonyms["重建"] = QStringList{"reconstruction", "三维重建", "立体视觉"};
    m_synonyms["同步"] = QStringList{"synchronization", "sync", "硬同步", "软同步"};
    m_synonyms["延时"] = QStringList{"delay", "latency", "延迟", "时延"};
    m_synonyms["带宽"] = QStringList{"bandwidth", "吞吐量", "throughput"};
    m_synonyms["缓存"] = QStringList{"buffer", "缓存区", "队列"};
    m_synonyms["超时"] = QStringList{"timeout", "超时时间", "等待时间"};
    m_synonyms["重试"] = QStringList{"retry", "重连", "reconnect"};
    m_synonyms["日志"] = QStringList{"log", "日志级别", "debug", "trace"};
    m_synonyms["配置"] = QStringList{"config", "configuration", "settings", "参数"};
    m_synonyms["预设"] = QStringList{"preset", "默认值", "模板"};
    m_synonyms["用户"] = QStringList{"user", "用户名", "权限", "role"};
    m_synonyms["系统"] = QStringList{"system", "操作系统", "platform"};
    m_synonyms["硬件"] = QStringList{"hardware", "设备", "device", "主板"};
    m_synonyms["网络"] = QStringList{"network", "ip", "mac", "subnet", "网关"};
    m_synonyms["存储"] = QStringList{"storage", "硬盘", "ssd", "保存路径"};
    m_synonyms["内存"] = QStringList{"memory", "ram", "占用"};
    m_synonyms["cpu"] = QStringList{"处理器", "核心数", "利用率"};
    m_synonyms["gpu"] = QStringList{"显卡", "图形处理器", "cuda"};
    m_synonyms["电源"] = QStringList{"power", "供电", "电压", "电流"};
    m_synonyms["led"] = QStringList{"光源", "照明", "补光灯", "strobe"};
    m_synonyms["gpio"] = QStringList{"通用 io", "输入输出", "数字 io", "光耦"};
    m_synonyms["pwm"] = QStringList{"脉冲调制", "占空比", "频率"};
    m_synonyms["编码器"] = QStringList{"encoder", "码盘", "位置反馈"};
    m_synonyms["电机"] = QStringList{"motor", "步进电机", "伺服", "servo"};
    m_synonyms["传感器"] = QStringList{"sensor", "感应器", "探测器"};
    m_synonyms["环境"] = QStringList{"environment", "温湿度", "光照"};
    m_synonyms["安全"] = QStringList{"security", "加密", "认证", "password"};
    m_synonyms["备份"] = QStringList{"backup", "还原", "restore", "导出"};
    m_synonyms["更新"] = QStringList{"update", "升级", "patch", "hotfix"};
    m_synonyms["插件"] = QStringList{"plugin", "扩展", "module", "addon"};
    m_synonyms["接口"] = QStringList{"interface", "api", "sdk", "驱动"};
    m_synonyms["协议"] = QStringList{"protocol", "tcp", "udp", "http", "rtsp"};
    m_synonyms["序列化"] = QStringList{"serialization", "json", "xml", "protobuf"};
    m_synonyms["并发"] = QStringList{"concurrent", "多线程", "异步", "async"};
    m_synonyms["性能"] = QStringList{"performance", "优化", "benchmark"};
    m_synonyms["调试"] = QStringList{"debug", "断点", "监视", "inspect"};
    m_synonyms["测试"] = QStringList{"test", "单元测试", "集成测试", "validation"};
    m_synonyms["文档"] = QStringList{"document", "manual", "help", "说明"};
    m_synonyms["帮助"] = QStringList{"help", "support", "faq", "常见问题"};
    m_synonyms["关于"] = QStringList{"about", "版本信息", "author", "版权"};

    // ===== 中文拼音简写映射 =====
    m_synonyms["jq"] = QStringList() << "相机" << "机器" << "机器视觉";
    m_synonyms["gx"] = QStringList() << "光学" << "光纤" << "感光";
    m_synonyms["tj"] = QStringList() << "触发" << "投影" << "推荐";
    m_synonyms["jl"] = QStringList() << "距离" << "精度" << "记录";
    m_synonyms["cs"] = QStringList() << "参数" << "测试" << "传感器";
    m_synonyms["pz"] = QStringList() << "配置" << "品质" << "品质证";
    m_synonyms["zh"] = QStringList() << "中国" << "中文" << "振华";
}

void AiService::initDomainKeywords()
{
    // 相机配置关键词
    m_domainKeywords["camera"] = QStringList{"exposure", "gain", "trigger", "framerate", "resolution", "white balance", "gamma"};
    m_domainKeywords["projector"] = QStringList{"pattern", "phase", "intensity", "wavelength", "focus"};
    m_domainKeywords["calibration"] = QStringList{"intrinsic", "extrinsic", "distortion", "reprojection", "error"};
    m_domainKeywords["hardware"] = QStringList{"temperature", "fan", "voltage", "current", "power"};
    m_domainKeywords["user"] = QStringList{"name", "password", "role", "permission", "level"};
    m_domainKeywords["system"] = QStringList{"version", "platform", "os", "driver", "firmware"};
}

QString AiService::analyzeIntent(const QString& query)
{
    if (query.trimmed().isEmpty()) {
        return "unknown";
    }
    
    QString q = query.trimmed().toLower();
    
    // ===== 规则 1: 包含明确的值特征 =====
    if (q.contains(QRegularExpression("[0-9]+\\.?[0-9]*")) ||  // 数字
        q.contains(QRegularExpression("^[0-9]+$")) ||  // 纯数字
        q.contains("=", Qt::CaseInsensitive) ||
        q.contains(">", Qt::CaseInsensitive) ||
        q.contains("<", Qt::CaseInsensitive)) {
        return "search_value";
    }
    
    // ===== 规则 2: 包含中文描述性词汇 =====
    QStringList chineseIndicators = {"是什么", "什么意思", "含义", "作用", "干嘛", "做什么", "怎么用", "如何"};
    for (const QString& indicator : chineseIndicators) {
        if (q.contains(indicator)) {
            return "search_chinese";  // 用户在询问含义
        }
    }
    
    // ===== 规则 3: 包含导航/操作意图 =====
    QStringList navIndicators = {"打开", "进入", "跳转", "切换到", "显示", "查看"};
    for (const QString& indicator : navIndicators) {
        if (q.contains(indicator)) {
            return "navigate";
        }
    }
    
    // ===== 规则 4: 匹配领域关键词 =====
    for (auto it = m_domainKeywords.constBegin(); it != m_domainKeywords.constEnd(); ++it) {
        if (q.contains(it.key())) {
            return "search_key";  // 用户在搜索特定领域的配置项
        }
        for (const QString& kw : it.value()) {
            if (q.contains(kw)) {
                return "search_key";
            }
        }
    }
    
    // ===== 规则 5: 包含同义词词典中的词 =====
    for (auto it = m_synonyms.constBegin(); it != m_synonyms.constEnd(); ++it) {
        if (q == it.key() || q.contains(it.key())) {
            return "search_key";
        }
        for (const QString& syn : it.value()) {
            if (q.contains(syn)) {
                return "search_key";
            }
        }
    }
    
    // ===== 规则 6: 纯英文/字母组合，可能是配置键名 =====
    if (q.contains(QRegularExpression("^[a-z][a-z0-9_.]*$"))) {
        return "search_key";
    }
    
    // ===== 规则 7: 包含中文名词，可能是中文名搜索 =====
    QRegularExpression chinesePattern("[\\u4e00-\\u9fa5]+");
    if (q.contains(chinesePattern)) {
        return "search_chinese";
    }
    
    return "search_key";  // 默认当作键名搜索
}

double AiService::getIntentConfidence(const QString& query)
{
    QString intent = analyzeIntent(query);
    QString q = query.trimmed().toLower();
    
    // 基于特征数量计算置信度
    int features = 0;
    
    // 数字特征
    if (q.contains(QRegularExpression("[0-9]"))) features++;
    
    // 操作符特征
    if (q.contains('=') || q.contains('>') || q.contains('<')) features++;
    
    // 疑问词特征
    if (q.contains("是什么") || q.contains("含义") || q.contains("作用")) features++;
    
    // 领域词特征
    for (auto it = m_domainKeywords.constBegin(); it != m_domainKeywords.constEnd(); ++it) {
        if (q.contains(it.key())) { features++; break; }
    }
    
    // 同义词特征
    for (auto it = m_synonyms.constBegin(); it != m_synonyms.constEnd(); ++it) {
        if (q.contains(it.key())) { features++; break; }
    }
    
    // 中文特征
    if (q.contains(QRegularExpression("[\\u4e00-\\u9fa5]"))) features++;
    
    // 长度特征（太短降低置信度）
    if (q.length() < 2) features--;
    if (q.length() > 3) features++;
    
    // 归一化到 0-1
    double confidence = 0.5 + (features * 0.1);
    confidence = qBound(0.0, confidence, 1.0);
    
    return confidence;
}

QVariantList AiService::extractEntities(const QString& query)
{
    QVariantList entities;
    QString q = query.trimmed();
    
    if (q.isEmpty()) return entities;
    
    // 提取数字实体
    QRegularExpression numberRe("[0-9]+\\.?[0-9]*");
    QRegularExpressionMatchIterator numIt = numberRe.globalMatch(q);
    while (numIt.hasNext()) {
        QRegularExpressionMatch match = numIt.next();
        QVariantMap entity;
        entity["type"] = "number";
        entity["value"] = match.captured(0);
        entity["position"] = match.capturedStart(0);
        entities.append(entity);
    }
    
    // 提取英文单词实体
    QRegularExpression wordRe("[a-zA-Z][a-zA-Z0-9_]*");
    QRegularExpressionMatchIterator wordIt = wordRe.globalMatch(q);
    while (wordIt.hasNext()) {
        QRegularExpressionMatch match = wordIt.next();
        QVariantMap entity;
        entity["type"] = "keyword";
        entity["value"] = match.captured(0);
        entity["position"] = match.capturedStart(0);
        entities.append(entity);
    }
    
    // 提取中文实体
    QRegularExpression chineseRe("[\\u4e00-\\u9fa5]+");
    QRegularExpressionMatchIterator chineseIt = chineseRe.globalMatch(q);
    while (chineseIt.hasNext()) {
        QRegularExpressionMatch match = chineseIt.next();
        QVariantMap entity;
        entity["type"] = "chinese";
        entity["value"] = match.captured(0);
        entity["position"] = match.capturedStart(0);
        entities.append(entity);
    }
    
    return entities;
}

QStringList AiService::expandKeywords(const QString& query, int maxResults)
{
    QStringList expanded;
    QString q = query.trimmed().toLower();
    
    if (q.isEmpty()) return expanded;
    
    // 1. 添加原始词
    expanded.append(query);
    
    // 2. 查找同义词
    for (auto it = m_synonyms.constBegin(); it != m_synonyms.constEnd(); ++it) {
        if (q.contains(it.key()) || it.value().contains(q)) {
            expanded.append(it.key());
            expanded.append(it.value());
        }
    }
    
    // 3. 查找领域相关词
    for (auto it = m_domainKeywords.constBegin(); it != m_domainKeywords.constEnd(); ++it) {
        if (q.contains(it.key())) {
            expanded.append(it.value());
        }
        for (const QString& kw : it.value()) {
            if (q.contains(kw)) {
                expanded.append(it.key());
                expanded.append(it.value());
            }
        }
    }
    
    // 4. 去重并限制数量
    expanded.removeDuplicates();
    if (expanded.size() > maxResults) {
        expanded = expanded.mid(0, maxResults);
    }
    
    return expanded;
}

QStringList AiService::getSynonyms(const QString& word)
{
    QString w = word.trimmed().toLower();
    return m_synonyms.value(w, QStringList());
}

QStringList AiService::getRelatedWords(const QString& word)
{
    QStringList related;
    QString w = word.trimmed().toLower();
    
    // 查找包含该词的领域
    for (auto it = m_domainKeywords.constBegin(); it != m_domainKeywords.constEnd(); ++it) {
        if (it.key().contains(w) || it.value().contains(w)) {
            related.append(it.key());
            related.append(it.value());
        }
    }
    
    // 查找同义词
    for (auto it = m_synonyms.constBegin(); it != m_synonyms.constEnd(); ++it) {
        if (it.key().contains(w) || it.value().contains(w)) {
            related.append(it.key());
            related.append(it.value());
        }
    }
    
    related.removeDuplicates();
    return related;
}

QVariantList AiService::generateSuggestions(const QString& query, const QString& context, int maxSuggestions)
{
    QVariantList suggestions;
    QString q = query.trimmed();
    
    if (q.isEmpty()) return suggestions;
    
    // 1. 基于意图生成建议
    QString intent = analyzeIntent(q);
    
    QVariantMap suggestion1;
    suggestion1["text"] = q;
    suggestion1["type"] = "exact";
    suggestion1["description"] = "精确匹配";
    suggestions.append(suggestion1);
    
    // 2. 基于同义词生成建议
    QStringList synonyms = expandKeywords(q, 5);
    for (const QString& syn : synonyms) {
        if (syn != q) {
            QVariantMap s;
            s["text"] = syn;
            s["type"] = "synonym";
            s["description"] = "同义词/相关词";
            suggestions.append(s);
        }
    }
    
    // 3. 基于领域词典生成建议
    for (auto it = m_domainDict.constBegin(); it != m_domainDict.constEnd(); ++it) {
        if (it.key().contains(q, Qt::CaseInsensitive) || 
            it.value().contains(q, Qt::CaseInsensitive)) {
            QVariantMap s;
            s["text"] = it.key();
            s["type"] = "domain";
            s["description"] = it.value();
            suggestions.append(s);
            if (suggestions.size() >= maxSuggestions) break;
        }
    }
    
    // 限制数量
    if (suggestions.size() > maxSuggestions) {
        suggestions = suggestions.mid(0, maxSuggestions);
    }
    
    return suggestions;
}

QString AiService::explainQuery(const QString& query)
{
    QString q = query.trimmed();
    if (q.isEmpty()) return "请输入搜索词";
    
    QString intent = analyzeIntent(q);
    double confidence = getIntentConfidence(q);
    
    QString explanation;
    
    if (intent == "search_value") {
        explanation = "您可能在搜索具体的参数值，系统将匹配包含该数值的配置项。";
    } else if (intent == "search_chinese") {
        explanation = "您可能在搜索中文描述或字段含义，系统将匹配相关的中文名称。";
    } else if (intent == "navigate") {
        explanation = "您似乎想要导航到某个配置页面或功能。";
    } else if (intent == "search_key") {
        explanation = "您在搜索配置项的键名，系统将匹配相关的英文键名。";
    } else {
        explanation = "搜索意图不明确，系统将使用模糊匹配进行搜索。";
    }
    
    // 添加同义词提示
    QStringList synonyms = getSynonyms(q);
    if (!synonyms.isEmpty()) {
        explanation += QString(" 相关词：%1").arg(synonyms.join(", "));
    }
    
    return explanation;
}

bool AiService::needsFuzzyMatch(const QString& query)
{
    QString q = query.trimmed();
    
    // 短词使用模糊匹配
    if (q.length() <= 3) return true;
    
    // 包含中文使用模糊匹配
    if (q.contains(QRegularExpression("[\\u4e00-\\u9fa5]"))) return true;
    
    // 纯数字使用精确匹配
    if (q.contains(QRegularExpression("^[0-9]+$"))) return false;
    
    // 包含特殊字符使用精确匹配
    if (q.contains('.') || q.contains('_') || q.contains('-')) return false;
    
    return true;
}

void AiService::loadDomainDictionary(const QVariantMap& terms)
{
    for (auto it = terms.constBegin(); it != terms.constEnd(); ++it) {
        m_domainDict[it.key()] = it.value().toString();
    }
}

void AiService::clearDictionary()
{
    m_domainDict.clear();
}

int AiService::getDictionarySize() const
{
    return m_domainDict.size();
}

void AiService::setEnabled(bool enabled)
{
    if (m_enabled != enabled) {
        m_enabled = enabled;
        emit enabledChanged(enabled);
    }
}

double AiService::calculateSimilarity(const QString& s1, const QString& s2)
{
    if (s1.isEmpty() || s2.isEmpty()) return 0.0;
    if (s1 == s2) return 1.0;
    
    int len1 = s1.length();
    int len2 = s2.length();
    int maxLen = qMax(len1, len2);
    if (maxLen == 0) return 0.0;
    
    int distance = 0;
    for (int i = 0; i < maxLen; ++i) {
        QChar c1 = i < len1 ? s1[i] : QChar();
        QChar c2 = i < len2 ? s2[i] : QChar();
        if (c1 != c2) distance++;
    }
    
    return 1.0 - (double)distance / maxLen;
}

double AiService::pinyinSimilarity(const QString& chinese, const QString& pinyin)
{
    // 简单实现：直接比较字符串相似度
    // 实际项目中可以集成拼音库如 QtPinyin
    return calculateSimilarity(chinese.toLower(), pinyin.toLower());
}

// 添加信号声明到类中需要在头文件中补充，这里先添加 emit 调用
// 在 setEnabled 中已添加 emit enabledChanged
