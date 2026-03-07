#include "aiservice.h"
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantMap>
#include <QDebug>
#include <QtConcurrent>
#include <QFuture>
#include <QFile>
#include <QDir>
#include <QDateTime>

AiService::AiService(QObject *parent) : QObject(parent)
{
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataDir);
    m_userDictPath = dataDir + "/user_dictionary.json";
    m_searchHistoryPath = dataDir + "/search_history.json";
    
    loadUserDictionary();
    loadSearchHistory();
}

void AiService::ensureSynonymsLoaded()
{
    if (m_synonymsLoaded) return;
    initSynonymDictionary();
    m_synonymsLoaded = true;
}

void AiService::ensureDomainKeywordsLoaded()
{
    if (m_domainKeywordsLoaded) return;
    initDomainKeywords();
    m_domainKeywordsLoaded = true;
}

void AiService::buildReverseIndex()
{
    if (m_reverseIndexBuilt) return;
    ensureDomainKeywordsLoaded();
    
    for (auto it = m_domainKeywords.constBegin(); it != m_domainKeywords.constEnd(); ++it) {
        const QString& domain = it.key();
        const QStringList& keywords = it.value();
        for (const QString& kw : keywords) {
            m_keywordToDomain[kw.toLower()] = domain;
        }
    }
    m_reverseIndexBuilt = true;
}

AiService::~AiService()
{
    saveUserDictionary();
    saveSearchHistory();
}

void AiService::initSynonymDictionary()
{
    // ===== 相机/光学核心参数 =====
    m_synonyms["相机"] = QStringList{"camera", "摄相机", "工业相机", "面阵相机", "线阵相机", "cam", "cameralist", "cameratype", "cameraplugin", "cameraconfigname"};
    m_synonyms["camera"] = QStringList{"相机", "cam", "industrial camera", "area scan", "line scan", "cameralist", "cameratype", "cameraplugin"};
    m_synonyms["曝光"] = QStringList{"exposure", "曝光时间", "积分时间", "integration", "exposure time", "shutter", "exposuretime"};
    m_synonyms["增益"] = QStringList{"gain", "analog gain", "digital gain", "模拟增益", "数字增益", "db"};
    m_synonyms["触发"] = QStringList{"trigger", "软触发", "硬触发", "外触发", "内触发", "strobe", "triggerwidth", "triggerboradorder"};
    m_synonyms["帧率"] = QStringList{"framerate", "fps", "frame rate", "帧频", "frames per second"};
    m_synonyms["分辨率"] = QStringList{"resolution", "width", "height", "宽", "高", "像素", "megapixel", "actualresolution", "actualobliqueresolution", "capturesize"};
    m_synonyms["白平衡"] = QStringList{"white balance", "wb", "色温", "color temperature", "gain red", "gain blue"};
    m_synonyms["伽马"] = QStringList{"gamma", "γ", "灰度", "tone mapping", "曲线"};
    m_synonyms["对比度"] = QStringList{"contrast", "反差", "dynamic range"};
    m_synonyms["亮度"] = QStringList{"brightness", "luminance", "明暗", "black level", "offset", "averagebrightness", "brightnessmax", "brightnessmin", "brightnessrange", "calbrightnessblue", "calbrightnessgreen", "calbrightnessred"};
    m_synonyms["饱和"] = QStringList{"saturation", "饱和度", "色彩饱和度", "color"};
    m_synonyms["锐度"] = QStringList{"sharpness", "清晰度", "锐化", "edge enhancement"};
    m_synonyms["镜头"] = QStringList{"lens", "焦距", "focus", "对焦", "focal length", "镜头焦距"};
    m_synonyms["光圈"] = QStringList{"aperture", "f 值", "f-number", "f stop", "光圈值"};
    m_synonyms["roi"] = QStringList{"region of interest", "感兴趣区域", "裁剪区域", "window", "感兴趣区"};
    m_synonyms["binning"] = QStringList{"像素合并", "合并", "采样", "bin", "2x2", "4x4"};
    m_synonyms["offset"] = QStringList{"偏移", "黑电平", "black level", "dark current", "暗电流"};
    m_synonyms["翻转"] = QStringList{"flip", "镜像", "mirror", "rotate", "旋转", "reverse", "invert"};
    m_synonyms["格式"] = QStringList{"format", "pixel format", "像素格式", "输出格式", "color format", "mono", "bayer"};
    m_synonyms["压缩"] = QStringList{"compression", "jpeg", "h264", "编码", "encode", "quality", "mjpeg"};
    m_synonyms["传输"] = QStringList{"transfer", "usb", "gige", "cameralink", "协议", "interface", "genicam"};

    // ===== 光源/颜色（基于数据库实际数据扩展）=====
    m_synonyms["光源"] = QStringList{"light", "照明", "补光灯", "lightsource", "illumination", "lighttype", "lightenablelist", "lightlevelhighlimit", "lightlevellowlimit"};
    m_synonyms["红光"] = QStringList{"red light", "620nm", "红色光源", "upperbottomred", "uppertopred", "calbrightnessred"};
    m_synonyms["绿光"] = QStringList{"green light", "530nm", "绿色光源", "upperbottomgreen", "uppermidgreen", "calbrightnessgreen"};
    m_synonyms["蓝光"] = QStringList{"blue light", "470nm", "蓝色光源", "upperbottomblue", "calbrightnessblue"};
    m_synonyms["白光"] = QStringList{"white light", "自然光", "diffuse", "漫射", "upperbottomwhite", "uppermidwhite", "uppertopwhite"};
    m_synonyms["同轴光"] = QStringList{"coaxial", "同轴光", "coax"};
    m_synonyms["背光"] = QStringList{"backlight", "背光源", "透射"};
    m_synonyms["环形光"] = QStringList{"ring light", "环形光源", "round"};
    m_synonyms["条形光"] = QStringList{"bar light", "条形光源", "line light"};
    m_synonyms["点光源"] = QStringList{"spot light", "点光", "focused"};
    m_synonyms["颜色"] = QStringList{"color", "colour", "red", "green", "blue", "white", "颜色", "色彩"};
    m_synonyms["颜色通道"] = QStringList{"channel", "通道", "channelvalues", "channeldiffvalue", "triggerchannel"};
    m_synonyms["投影亮度"] = QStringList{"projectionbrightness", "projection", "brightness"};
    m_synonyms["均匀光度"] = QStringList{"uniformluminance", "luminance", "uniformluminancestandardvalue"};
    m_synonyms["LSC 校正"] = QStringList{"lsc", "lscparam", "lsccorrectionresult", "lsccapturesetting"};

    // ===== 温度/散热 =====
    m_synonyms["温度"] = QStringList{"temperature", "temp", "传感器温度", "冷却", "摄氏度", "celsius"};
    m_synonyms["风扇"] = QStringList{"fan", "散热", "冷却风扇", "fan speed", "转速", "cooling"};
    m_synonyms["过热"] = QStringList{"overheat", "高温", "thermal", "温度保护"};

    // ===== 设备信息（基于数据库实际数据扩展）=====
    m_synonyms["设备"] = QStringList{"device", "equipment", "equip", "machine", "aoimachine", "deviceid", "devicename", "deviceserialnumber", "devicesn", "devicetype", "devno", "equipcode", "equipid", "equipmodel", "equipname", "equipmentid", "factory", "workstation"};
    m_synonyms["设备型号"] = QStringList{"devmodel", "equipmodel", "model", "product", "type", "devicetype", "devicetype2"};
    m_synonyms["设备编号"] = QStringList{"devno", "deviceno", "equipid", "deviceid", "deviceserialnumber", "devicesn", "equipcode"};
    m_synonyms["固件"] = QStringList{"firmware", "版本", "version", "fw", "build", "appversion", "autotestversion"};
    m_synonyms["序列号"] = QStringList{"serial number", "sn", "设备序列号", "id", "device id", "uuid", "barcode", "barcodinfid", "checkbarcode", "assignbarcode"};
    m_synonyms["型号"] = QStringList{"model", "产品型号", "product", "type", "devmodel", "equipmodel"};
    m_synonyms["制造商"] = QStringList{"manufacturer", "vendor", "厂家", "brand"};
    m_synonyms["状态"] = QStringList{"status", "state", "连接状态", "在线", "offline", "connected", "focusstatus"};
    m_synonyms["错误"] = QStringList{"error", "错误码", "故障", "exception", "alarm", "warning", "err", "errortype", "errortable", "boarddroperror"};
    m_synonyms["日志"] = QStringList{"log", "日志级别", "debug", "trace", "info", "记录", "elapsedtime"};
    m_synonyms["创建时间"] = QStringList{"createtime", "createprojecttime", "calibrationdate"};
    m_synonyms["作者"] = QStringList{"author", "account", "user", "calibrationuser"};

    // ===== 标定/校准（基于数据库实际数据扩展）=====
    m_synonyms["校准"] = QStringList{"calibration", "标定", "校正", "矫正", "calib", "calibrationcalsetting", "calibrationdatas", "calibrationdate", "calibrationzaxis"};
    m_synonyms["畸变"] = QStringList{"distortion", "镜头畸变", "径向畸变", "切向畸变", "k1", "k2", "p1", "p2"};
    m_synonyms["内参"] = QStringList{"intrinsic", "内参数", "焦距", "主点", "fx", "fy", "cx", "cy"};
    m_synonyms["外参"] = QStringList{"extrinsic", "外参数", "旋转", "平移", "rotation", "translation", "pose"};
    m_synonyms["标定板"] = QStringList{"calibration board", "棋盘格", "checkerboard", "dot pattern", "标定靶", "targetinfo", "targetname", "targetposlist"};
    m_synonyms["重投影"] = QStringList{"reprojection", "重投影误差", "error", "rms"};
    m_synonyms["手眼"] = QStringList{"hand eye", "眼在手外", "eye to hand", "机器人标定"};
    m_synonyms["3D 标定"] = QStringList{"cal3d", "3dcalibration", "projectionbrightnesssetting", "projectioninspectionsetting", "projectionzscalesetting"};
    m_synonyms["相机标定"] = QStringList{"calcamerasetting", "calcamerafocussetting", "camerazoriginsetting"};
    m_synonyms["光源标定"] = QStringList{"callightsetting", "light2dsetting", "light2dstandard"};
    m_synonyms["机械标定"] = QStringList{"calmechanismsetting", "mechanismcameraoriginsetting", "mechanismmotionoriginsetting"};
    m_synonyms["验证"] = QStringList{"verification", "calverificationsetting", "cmksetting"};
    m_synonyms["焦点"] = QStringList{"focus", "对焦", "diffocus", "standardfocus", "focusstatus"};
    m_synonyms["Z 轴"] = QStringList{"zaxis", "z 轴", "zpos", "calibrationzaxis", "zstep", "zorigin"};

    // ===== 投影/结构光 =====
    m_synonyms["投影"] = QStringList{"projector", "投影仪", "projection", "结构光", "sl", "pattern projection", "projectiontype", "projectionbrightness", "projectioninspection", "projectionzscale"};
    m_synonyms["图案"] = QStringList{"pattern", "条纹", "fringe", "编码图案", "grating", "正弦条纹"};
    m_synonyms["相位"] = QStringList{"phase", "相移", "phase shift", "psp", "相位展开"};
    m_synonyms["解调"] = QStringList{"demodulation", "解包裹", "unwrapping", "phase unwrapping"};
    m_synonyms["强度"] = QStringList{"intensity", "亮度", "光强", "brightness", "power", "led intensity"};
    m_synonyms["波长"] = QStringList{"wavelength", "光谱", "spectrum", "nm", "红外", "紫外"};
    m_synonyms["曝光序列"] = QStringList{"exposure sequence", "多曝光", "hdr", "high dynamic range"};
    m_synonyms["周期参数"] = QStringList{"cyclesparameter", "cycle", "period"};
    m_synonyms["均值范围"] = QStringList{"meanrange", "mean", "standarddeviationrange"};
    m_synonyms["高度标定"] = QStringList{"heightcalib", "heightcalibstandardmean", "heightcalibstandardstd"};

    // ===== 3D/点云 =====
    m_synonyms["点云"] = QStringList{"point cloud", "3d 点云", "深度图", "depth map", "pcl"};
    m_synonyms["深度"] = QStringList{"depth", "距离", "z 值", "distance", "depth map", "z buffer"};
    m_synonyms["三维"] = QStringList{"3d", "三维重建", "stereo", "binocular", "双目"};
    m_synonyms["坐标"] = QStringList{"coordinate", "coords", "x", "y", "z", "坐标系", "world", "camera", "posx", "posy", "position"};
    m_synonyms["变换"] = QStringList{"transform", "矩阵", "homography", "单应性", "matrix", "4x4"};
    m_synonyms["映射"] = QStringList{"mapping", "查找表", "lut", "lookup table", "remap", "校正映射"};
    m_synonyms["配准"] = QStringList{"registration", "对齐", "align", "icp", "点云配准"};
    m_synonyms["滤波"] = QStringList{"filter", "平滑", "去噪", "中值滤波", "高斯滤波", "pass through", "voxel"};
    m_synonyms["倾斜分辨率"] = QStringList{"obliqueresolution", "actualobliqueresolution"};

    // ===== 图像处理 =====
    m_synonyms["阈值"] = QStringList{"threshold", "二值化", "分割", "binarize", "otsu", "自适应阈值"};
    m_synonyms["边缘"] = QStringList{"edge", "轮廓", "contour", "边界", "canny", "sobel", "laplacian"};
    m_synonyms["特征"] = QStringList{"feature", "角点", "sift", "surf", "orb", "keypoint", "descriptor"};
    m_synonyms["匹配"] = QStringList{"match", "匹配点", "对应点", "correspondence", "feature match"};
    m_synonyms["分割"] = QStringList{"segmentation", "分割", "region", "watershed", "聚类"};
    m_synonyms["形态学"] = QStringList{"morphology", "膨胀", "腐蚀", "open", "close", "dilate", "erode"};
    m_synonyms["模板"] = QStringList{"template", "模板匹配", "match template", "pattern match"};
    m_synonyms["相关性"] = QStringList{"correlation", "correlationlimit", "相关"};
    m_synonyms["灰度"] = QStringList{"gray", "grey", "灰度", "grayhighlimit", "graylowlimit"};

    // ===== 运动控制/机械（基于数据库实际数据扩展）=====
    m_synonyms["运动"] = QStringList{"motion", "运动控制", "mechanismmotion", "motionorigin"};
    m_synonyms["轴"] = QStringList{"axis", "轴", "axiscontroltype", "axistopyreverse", "bottomx", "bottomy", "bottomz"};
    m_synonyms["速度"] = QStringList{"speed", "速度", "speedlevel", "conveyorcarryoutspeed", "bottomxyspeedrate", "accel", "decel"};
    m_synonyms["加速度"] = QStringList{"acceleration", "accel", "加速", "bottomxaccelspeedrate", "bottomyaccelspeedrate", "bottomzaccelspeedrate", "xyaccelspeedrate"};
    m_synonyms["减速度"] = QStringList{"deceleration", "decel", "减速", "bottomxdecelspeedrate", "bottomydecelspeedrate", "bottomzdecelspeedrate"};
    m_synonyms["电机"] = QStringList{"motor", "步进电机", "伺服", "servo", "stepper", "驱动器"};
    m_synonyms["传感器"] = QStringList{"sensor", "感应器", "探测器", "detector", "proximity"};
    m_synonyms["编码器"] = QStringList{"encoder", "码盘", "位置反馈", "rotary", "linear"};
    m_synonyms["原点"] = QStringList{"origin", "原点", "originoffset", "cameraorigin", "motionorigin", "zorigin"};
    m_synonyms["偏移"] = QStringList{"offset", "偏移", "originoffsetx", "originoffsety", "originoffsetz", "originoffsetw"};
    m_synonyms["平台"] = QStringList{"stage", "平台", "扫描平台", "scanstage"};
    m_synonyms["扫描边"] = QStringList{"scanside", "scan", "扫描侧"};

    // ===== 传送带/轨道（基于数据库实际数据扩展）=====
    m_synonyms["传送带"] = QStringList{"conveyor", "传送带", "输送带", "conveyorcalsize", "conveyorcarryout", "conveyoruser", "conveyorwait"};
    m_synonyms["轨道"] = QStringList{"lane", "轨道", "laneindex", "track", "supportreflowtrack"};
    m_synonyms["进板"] = QStringList{"carryin", "进板", "carryindirection", "carryintimeout", "carrytoentry"};
    m_synonyms["出板"] = QStringList{"carryout", "出板", "carryouttimeout", "conveyorcarryout"};
    m_synonyms["夹板"] = QStringList{"clamp", "clamped", "夹板", "clampeddelay", "clampedenabled"};
    m_synonyms["板"] = QStringList{"board", "pcb", "板卡", "boardcount", "boardtable", "boardexport", "boarddrop"};
    m_synonyms["板宽"] = QStringList{"boardwidth", "maxlength", "maxwidth", "minlength", "minwidth"};
    m_synonyms["速度等级"] = QStringList{"speedlevel", "outboardspeedlevel"};
    m_synonyms["NG 输出"] = QStringList{"ngoutput", "ngoutputmethods"};
    m_synonyms["轨道宽度"] = QStringList{"trackwidth", "autotrackwidthadjustment"};
    m_synonyms["进板方向"] = QStringList{"carrydirection", "carryindirection"};
    m_synonyms["基线"] = QStringList{"baseline", "基线"};
    m_synonyms["位置"] = QStringList{"position", "位置", "pos"};

    // ===== 数据库/网络/通信（基于数据库实际数据扩展）=====
    m_synonyms["数据库"] = QStringList{"database", "db", "sql", "dbaccount", "dbname", "dbpassword", "dbusername", "dbpassword", "exportimportdatabase", "databasecleanthreshold", "keepdatabaserecent", "isclearhistorydatabase"};
    m_synonyms["服务器"] = QStringList{"server", "服务器", "serverip", "serverport", "servername", "serveraddress", "eaphost"};
    m_synonyms["IP 地址"] = QStringList{"ip", "ipaddress", "ip", "ftpip", "plcip", "pcip", "repairip", "workstationip", "serverip", "addressip"};
    m_synonyms["端口"] = QStringList{"port", "端口", "portname", "ftpport", "plcport", "repairport", "serverport", "addressport", "flashcomport", "modbuscomport"};
    m_synonyms["网络"] = QStringList{"network", "网络", "networkpath", "savepicturenetworkpath", "mac", "subnet", "网关", "dhcp", "static"};
    m_synonyms["FTP"] = QStringList{"ftp", "ftppath", "ftpimageport", "ftptxtport", "ftpip", "ftpport"};
    m_synonyms["TCP"] = QStringList{"tcp", "tcpip", "tcpport", "uploadcheck", "uploaddata"};
    m_synonyms["PLC"] = QStringList{"plc", "plcip", "plcport", "modbus", "modbuscom", "modbuscombaud", "modbuscomport"};
    m_synonyms["MODBUS"] = QStringList{"modbus", "modbuscom", "modbuscombaud", "modbuscomport"};
    m_synonyms["账户"] = QStringList{"account", "账户", "dbaccount", "dbusername", "dbpassword", "password", "user"};
    m_synonyms["上传"] = QStringList{"upload", "上传", "uploadcheck", "uploaddata", "sendserver", "sendfailed"};
    m_synonyms["MES"] = QStringList{"mes", "制造执行系统", "checkurl", "checksnurl", "checkmacurl", "checkbarcodeurl", "testreporturl"};
    m_synonyms["EAP"] = QStringList{"eap", "企业应用集成", "eaphost"};

    // ===== 检测/扫描/结果（基于数据库实际数据扩展）=====
    m_synonyms["检测"] = QStringList{"inspection", "inspect", "检测", "projectioninspection", "autojudge"};
    m_synonyms["扫描"] = QStringList{"scan", "扫描", "scanside", "scanstage"};
    m_synonyms["结果"] = QStringList{"result", "结果", "compresult", "checkresult", "focusstatus", "lscorrectionresult", "reviewresult"};
    m_synonyms["NG"] = QStringList{"ng", "不良", "ngoutput", "ngcompontvoicetip"};
    m_synonyms["通过"] = QStringList{"pass", "ok", "通过", "合格"};
    m_synonyms["捕获场景"] = QStringList{"capturescene", "capturescenetype", "capture"};
    m_synonyms["重复次数"] = QStringList{"repeatcnt", "repeat", "cycles"};
    m_synonyms["完成标志"] = QStringList{"completedflag", "completed", "finish"};
    m_synonyms["相机类型"] = QStringList{"cameratype", "cameratype", "stage"};

    // ===== 导出/导入/文件（基于数据库实际数据扩展）=====
    m_synonyms["导出"] = QStringList{"export", "导出", "exportmethod", "exportname", "exportpicture", "exporttimeout", "boardexport", "compexport", "projectexport", "exportalgorithmparam"};
    m_synonyms["导入"] = QStringList{"import", "导入", "importdatabase", "import"};
    m_synonyms["文件"] = QStringList{"file", "文件", "filepath", "choosefile", "openfile", "deleteboard", "removeboard"};
    m_synonyms["项目"] = QStringList{"project", "项目", "projectpath", "mainprojectpath", "createprojecttime", "projectexport"};
    m_synonyms["路径"] = QStringList{"path", "路径", "backupsavepath", "diskpath", "copyPath", "savepicturenetworkpath"};
    m_synonyms["保存"] = QStringList{"save", "保存", "backupsavepath", "savepicture"};
    m_synonyms["备份"] = QStringList{"backup", "备份", "backupsavepath", "copyfile"};
    m_synonyms["复制"] = QStringList{"copy", "复制", "copyfile", "copypath"};

    // ===== 条码/RFID（基于数据库实际数据扩展）=====
    m_synonyms["条码"] = QStringList{"barcode", "条码", "barcodeinfid", "checkbarcode", "assignbarcode", "bindboardcode", "bindchildboardcode", "bothsidecode"};
    m_synonyms["RFID"] = QStringList{"rfid", "射频识别", "rfidbrand", "rfidbrandlane"};
    m_synonyms["二维码"] = QStringList{"qrcode", "qr", "二维码", "datamatrix", "dm"};
    m_synonyms["绑定"] = QStringList{"bind", "绑定", "bindboardcode", "bindchildboardcode"};

    // ===== 声音/提示（基于数据库实际数据扩展）=====
    m_synonyms["声音"] = QStringList{"voice", "声音", "buzzer", "badboardvoicetip", "ngcompontvoicetip"};
    m_synonyms["提示"] = QStringList{"tip", "提示", "tips", "sendfailedshowtips", "recicemestip", "reviewresultwindowtip", "badboardwindowtip"};
    m_synonyms["蜂鸣器"] = QStringList{"buzzer", "蜂鸣器", "alarm"};
    m_synonyms["窗口"] = QStringList{"window", "窗口", "showchildboard", "windowtip"};

    // ===== 维修/重测（基于数据库实际数据扩展）=====
    m_synonyms["维修"] = QStringList{"repair", "维修", "repairip", "repairport"};
    m_synonyms["重测"] = QStringList{"retest", "重测", "recicemes"};
    m_synonyms["脚本"] = QStringList{"script", "脚本", "script"};

    // ===== WIP/夹具/工位（基于数据库实际数据扩展）=====
    m_synonyms["WIP"] = QStringList{"wip", "在制品", "wipid"};
    m_synonyms["夹具"] = QStringList{"fixture", "夹具", "fixturenum"};
    m_synonyms["工位"] = QStringList{"workstation", "工位", "workstationip", "station"};
    m_synonyms["设施"] = QStringList{"facility", "设施", "facshortcode"};
    m_synonyms["PCBA"] = QStringList{"pcba", "pcb 组装", "pcb", "selectchildboard", "childboardvisible"};
    m_synonyms["SMT"] = QStringList{"smt", "表面贴装技术", "贴片机"};
    m_synonyms["回流焊"] = QStringList{"reflow", "回流焊", "supportreflowtrack"};
    m_synonyms["波峰焊"] = QStringList{"wave", "波峰焊"};
    m_synonyms["SPI"] = QStringList{"spi", "锡膏检测"};
    m_synonyms["AXI"] = QStringList{"axi", "自动 X 射线检测"};

    // ===== 系统/硬件 =====
    m_synonyms["配置"] = QStringList{"config", "configuration", "settings", "参数", "prefs", "preferences"};
    m_synonyms["预设"] = QStringList{"preset", "默认值", "模板", "profile", "scheme"};
    m_synonyms["用户"] = QStringList{"user", "用户名", "权限", "role", "admin", "operator", "guest"};
    m_synonyms["系统"] = QStringList{"system", "操作系统", "platform", "os", "linux", "windows"};
    m_synonyms["硬件"] = QStringList{"hardware", "设备", "device", "主板", "pcie", "fpga"};
    m_synonyms["网络"] = QStringList{"network", "ip", "mac", "subnet", "网关", "dhcp", "static"};
    m_synonyms["存储"] = QStringList{"storage", "硬盘", "ssd", "保存路径", "path", "directory"};
    m_synonyms["内存"] = QStringList{"memory", "ram", "占用", "usage", "available"};
    m_synonyms["cpu"] = QStringList{"处理器", "核心数", "利用率", "core", "thread", "load"};
    m_synonyms["gpu"] = QStringList{"显卡", "图形处理器", "cuda", "opengl", "compute", "vram"};
    m_synonyms["电源"] = QStringList{"power", "供电", "电压", "电流", "voltage", "ampere", "watt"};
    m_synonyms["gpio"] = QStringList{"通用 io", "输入输出", "数字 io", "光耦", "input", "output", "pin"};
    m_synonyms["pwm"] = QStringList{"脉冲调制", "占空比", "频率", "pulse width", "hz"};
    m_synonyms["环境"] = QStringList{"environment", "温湿度", "光照", "humidity", "ambient"};

    // ===== 安全/维护 =====
    m_synonyms["安全"] = QStringList{"security", "加密", "认证", "password", "token", "license"};
    m_synonyms["备份"] = QStringList{"backup", "还原", "restore", "导出", "import", "export"};
    m_synonyms["更新"] = QStringList{"update", "升级", "patch", "hotfix", "upgrade", "migrate"};
    m_synonyms["插件"] = QStringList{"plugin", "扩展", "module", "addon", "extension", "dll", "so", "cameraplugin", "cameraconfigname"};
    m_synonyms["接口"] = QStringList{"interface", "api", "sdk", "驱动", "driver", "binding", "checkintfname"};
    m_synonyms["协议"] = QStringList{"protocol", "tcp", "udp", "http", "rtsp", "onvif", "modbus", "conntype"};

    // ===== 开发/调试 =====
    m_synonyms["调试"] = QStringList{"debug", "断点", "监视", "inspect", "console", "trace"};
    m_synonyms["测试"] = QStringList{"test", "单元测试", "集成测试", "validation", "verify", "benchmark", "autotest"};
    m_synonyms["性能"] = QStringList{"performance", "优化", "benchmark", "speed", "fps", "latency"};
    m_synonyms["并发"] = QStringList{"concurrent", "多线程", "异步", "async", "thread", "parallel"};
    m_synonyms["序列化"] = QStringList{"serialization", "json", "xml", "protobuf", "yaml", "marshal"};

    // ===== 文档/帮助 =====
    m_synonyms["文档"] = QStringList{"document", "manual", "help", "说明", "guide", "tutorial", "wiki"};
    m_synonyms["帮助"] = QStringList{"help", "support", "faq", "常见问题", "question", "issue"};
    m_synonyms["关于"] = QStringList{"about", "版本信息", "author", "版权", "copyright", "contact"};

    // ===== LED/光源 =====
    m_synonyms["led"] = QStringList{"光源", "照明", "补光灯", "strobe", "light source", "illumination"};
    m_synonyms["红光"] = QStringList{"red light", "620nm", "红色光源"};
    m_synonyms["蓝光"] = QStringList{"blue light", "470nm", "蓝色光源"};
    m_synonyms["白光"] = QStringList{"white light", "自然光", "diffuse", "漫射"};
    m_synonyms["同轴"] = QStringList{"coaxial", "同轴光", "coax"};
    m_synonyms["背光"] = QStringList{"backlight", "背光源", "透射"};
    m_synonyms["环形"] = QStringList{"ring light", "环形光源", "round"};
    m_synonyms["条形"] = QStringList{"bar light", "条形光源", "line light"};
    m_synonyms["点光源"] = QStringList{"spot light", "点光", "focused"};
    m_synonyms["偏振"] = QStringList{"polarizer", "偏光", "polarization", "偏振片"};

    // ===== 中文拼音简写映射 =====
    m_synonyms["jq"] = QStringList() << "相机" << "机器" << "机器视觉" << "camera";
    m_synonyms["gx"] = QStringList() << "光学" << "光纤" << "感光" << "optical";
    m_synonyms["tj"] = QStringList() << "触发" << "投影" << "推荐" << "trigger";
    m_synonyms["jl"] = QStringList() << "距离" << "精度" << "记录" << "distance";
    m_synonyms["cs"] = QStringList() << "参数" << "测试" << "传感器" << "config";
    m_synonyms["pz"] = QStringList() << "配置" << "品质" << "品质证" << "preset";
    m_synonyms["zh"] = QStringList() << "中国" << "中文" << "振华" << "chinese";
    m_synonyms["bd"] = QStringList() << "标定" << "标定板" << "校准" << "calibration";
    m_synonyms["ty"] = QStringList() << "投影" << "投影仪" << "pattern" << "projector";
    m_synonyms["yj"] = QStringList() << "硬件" << "硬件配置" << "hardware" << "device";
    m_synonyms["yh"] = QStringList() << "用户" << "用户配置" << "user" << "username";
    m_synonyms["tz"] = QStringList() << "调整" << "调整配置" << "adjust" << "tuning";
    m_synonyms["jd"] = QStringList() << "精度" << "精度校准" << "accuracy" << "precision";
    m_synonyms["sb"] = QStringList() << "设备" << "设备信息" << "device" << "equipment";
    m_synonyms["cw"] = QStringList() << "错误" << "错误码" << "error" << "fault";
    m_synonyms["rz"] = QStringList() << "日志" << "运行日志" << "log" << "record";
    m_synonyms["gy"] = QStringList() << "光源" << "光学" << "light" << "optical";
    m_synonyms["dd"] = QStringList() << "轨道" << "传送带" << "lane" << "conveyor";
    m_synonyms["yb"] = QStringList() << "板子" << "PCB" << "board" << "pcb";
    m_synonyms["sj"] = QStringList() << "数据" << "数据库" << "database" << "db";
    m_synonyms["fw"] = QStringList() << "服务器" << "服务" << "server" << "service";
    m_synonyms["dz"] = QStringList() << "电子" << "电子厂" << "electronics";
    m_synonyms["azz"] = QStringList() << "aoi" << "自动光学检测" << "aoimachine";
    m_synonyms["gg"] = QStringList() << "光光" << "光源" << "light" << "brightness";
}

void AiService::initDomainKeywords()
{
    // 相机配置关键词
    m_domainKeywords["camera"] = QStringList{"exposure", "gain", "trigger", "framerate", "resolution", "white balance", "gamma", 
        "cameralist", "cameratype", "cameraplugin", "cameraconfigname", "capturesize", "actualresolution", 
        "focus", "diffocus", "standardfocus", "focusstatus", "averagebrightness"};
    
    // 投影/结构光关键词
    m_domainKeywords["projector"] = QStringList{"pattern", "phase", "intensity", "wavelength", "focus", 
        "projectionbrightness", "projectioninspection", "projectionzscale", "projectiontype",
        "cyclesparameter", "meanrange", "standarddeviationrange"};
    
    // 标定/校准关键词
    m_domainKeywords["calibration"] = QStringList{"intrinsic", "extrinsic", "distortion", "reprojection", "error",
        "calibrationcalsetting", "calibrationdatas", "calibrationdate", "calibrationzaxis",
        "cal3d", "calcamerasetting", "callightsetting", "calmechanismsetting", "calverificationsetting",
        "targetinfo", "targetname", "targetposlist", "completedflag", "cmksetting"};
    
    // 光源/光学关键词
    m_domainKeywords["light"] = QStringList{"brightness", "lighttype", "lightenablelist", "lightlevel",
        "calbrightnessblue", "calbrightnessgreen", "calbrightnessred", "light2dsetting",
        "uniformluminance", "lsccorrectionresult", "channelvalues", "channeldiffvalue",
        "correlationlimit", "grayhighlimit", "graylowlimit"};
    
    // 运动控制/机械关键词
    m_domainKeywords["motion"] = QStringList{"origin", "offset", "axis", "speed", "accel", "decel",
        "mechanismmotion", "motionorigin", "originoffsetx", "originoffsety", "originoffsetz",
        "axiscontroltype", "axistopyreverse", "scanside"};
    
    // 传送带/轨道关键词
    m_domainKeywords["conveyor"] = QStringList{"lane", "carryin", "carryout", "clamp", "board",
        "conveyorcalsize", "conveyorcarryout", "conveyoruser", "conveyorwait",
        "carrydirection", "carryindirection", "baseline", "position", "stage",
        "speedlevel", "outboardspeedlevel", "ngoutputmethods", "clampeddelay", "clampedenabled"};
    
    // 数据库/网络关键词
    m_domainKeywords["database"] = QStringList{"db", "sql", "server", "ip", "port", "account", "password",
        "dbaccount", "dbname", "dbpassword", "dbusername", "exportimportdatabase",
        "serverip", "serverport", "ftpip", "ftpport", "plcip", "plcport"};
    
    // 设备信息关键词
    m_domainKeywords["device"] = QStringList{"equipment", "deviceid", "devicename", "deviceserialnumber",
        "devicetype", "equipcode", "equipid", "equipmodel", "equipname", "equipmentid",
        "appversion", "autotestversion", "factory", "workstation", "devno", "deviceno"};
    
    // 检测/结果关键词
    m_domainKeywords["inspection"] = QStringList{"result", "scan", "check", "ng", "pass",
        "compresult", "checkresult", "lscorrectionresult", "reviewresult",
        "autojudge", "projectioninspection", "capturescene", "repeatcnt"};
    
    // 条码/RFID 关键词
    m_domainKeywords["barcode"] = QStringList{"barcode", "qrcode", "rfid", "bind", "sn",
        "barcodeinfid", "checkbarcode", "assignbarcode", "bindboardcode", "bindchildboardcode",
        "rfidbrand", "bothsidecode"};
    
    // 导出/文件关键词
    m_domainKeywords["export"] = QStringList{"file", "path", "save", "backup", "copy",
        "exportmethod", "exportname", "exportpicture", "exporttimeout", "boardexport",
        "compexport", "projectexport", "backupsavepath", "diskpath", "copyfile"};
    
    // 硬件/系统关键词
    m_domainKeywords["hardware"] = QStringList{"temperature", "fan", "voltage", "current", "power",
        "buzzer", "gpio", "pwm", "sensor", "encoder", "motor"};
    
    // 用户/权限关键词
    m_domainKeywords["user"] = QStringList{"name", "password", "role", "permission", "level",
        "account", "calibrationuser", "author"};
    
    // 系统/版本关键词
    m_domainKeywords["system"] = QStringList{"version", "platform", "os", "driver", "firmware",
        "appversion", "autotestversion", "createprojecttime", "elapsedtime"};
    
    // MES/EAP集成关键词
    m_domainKeywords["mes"] = QStringList{"eap", "upload", "check", "test", "report",
        "checkurl", "checksnurl", "checkmacurl", "testreporturl", "eaphost",
        "uploadcheck", "uploaddata", "sendserver", "sendfailed"};
    
    // SMT/PCBA 关键词
    m_domainKeywords["smt"] = QStringList{"pcba", "pcb", "reflow", "wave", "spi", "axi",
        "fixture", "wip", "workstation", "selectchildboard", "childboardvisible"};
}

QString AiService::analyzeIntent(const QString& query)
{
    if (query.trimmed().isEmpty()) {
        return "unknown";
    }
    
    ensureSynonymsLoaded();
    ensureDomainKeywordsLoaded();
    
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
    
    // ===== 规则 4: 使用反向索引快速匹配领域关键词 =====
    buildReverseIndex();
    for (auto it = m_keywordToDomain.constBegin(); it != m_keywordToDomain.constEnd(); ++it) {
        if (q.contains(it.key())) {
            return "search_key";
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
    ensureSynonymsLoaded();
    ensureDomainKeywordsLoaded();
    
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

void AiService::adjustSuggestionsByHistory(QVariantList& suggestions)
{
    if (!m_learningEnabled || m_searchFrequency.isEmpty()) return;
    
    // 基于搜索频率调整建议顺序
    std::sort(suggestions.begin(), suggestions.end(), [this](const QVariant& a, const QVariant& b) {
        QVariantMap ma = a.toMap();
        QVariantMap mb = b.toMap();
        int freqA = m_searchFrequency.value(ma.value("text", "").toString(), 0);
        int freqB = m_searchFrequency.value(mb.value("text", "").toString(), 0);
        return freqA > freqB;
    });
}

// ========== 用户自定义词典方法 ==========

void AiService::addUserTerm(const QString& key, const QString& chinese, const QStringList& synonyms)
{
    if (key.trimmed().isEmpty()) return;
    
    UserTerm term;
    term.chinese = chinese;
    term.synonyms = synonyms;
    m_userDict[key] = term;
    
    // 同时添加到同义词词典
    m_synonyms[key] = QStringList() << chinese << synonyms;
    m_synonyms[chinese] = QStringList() << key << synonyms;
    for (const QString& syn : synonyms) {
        m_synonyms[syn] = QStringList() << key << chinese;
    }
    
    emit userDictionaryChanged();
    saveUserDictionary();
}

void AiService::removeUserTerm(const QString& key)
{
    if (m_userDict.contains(key)) {
        m_userDict.remove(key);
        emit userDictionaryChanged();
        saveUserDictionary();
    }
}

QVariantList AiService::getUserTerms() const
{
    QVariantList result;
    for (auto it = m_userDict.constBegin(); it != m_userDict.constEnd(); ++it) {
        QVariantMap item;
        item["key"] = it.key();
        item["chinese"] = it.value().chinese;
        item["synonyms"] = it.value().synonyms;
        result.append(item);
    }
    return result;
}

QString AiService::getUserDictionaryPath() const
{
    return m_userDictPath;
}

bool AiService::saveUserDictionary()
{
    QFile file(m_userDictPath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to save user dictionary:" << m_userDictPath;
        return false;
    }
    
    QJsonObject root;
    QJsonArray terms;
    for (auto it = m_userDict.constBegin(); it != m_userDict.constEnd(); ++it) {
        QJsonObject term;
        term["key"] = it.key();
        term["chinese"] = it.value().chinese;
        term["synonyms"] = QJsonArray::fromStringList(it.value().synonyms);
        terms.append(term);
    }
    root["terms"] = terms;
    root["version"] = 1;
    root["updated"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    
    file.write(QJsonDocument(root).toJson());
    file.close();
    return true;
}

bool AiService::loadUserDictionary()
{
    QFile file(m_userDictPath);
    if (!file.exists()) return false;
    
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    file.close();
    
    if (!doc.isObject()) return false;
    
    QJsonObject root = doc.object();
    QJsonArray terms = root["terms"].toArray();
    
    m_userDict.clear();
    for (const QJsonValue& val : terms) {
        QJsonObject term = val.toObject();
        UserTerm userTerm;
        userTerm.chinese = term["chinese"].toString();
        QVariantList synVars = QJsonArray(term["synonyms"].toArray()).toVariantList();
        QStringList synList;
        for (const QVariant& v : synVars) synList.append(v.toString());
        userTerm.synonyms = synList;
        m_userDict[term["key"].toString()] = userTerm;
        
        // 加载时同步到同义词词典
        QString key = term["key"].toString();
        m_synonyms[key] = QStringList() << userTerm.chinese << userTerm.synonyms;
        m_synonyms[userTerm.chinese] = QStringList() << key << userTerm.synonyms;
    }
    
    emit userDictionaryChanged();
    return true;
}

// ========== 搜索历史方法 ==========

void AiService::recordSearchHistory(const QString& query, int resultCount, bool selected)
{
    if (query.trimmed().isEmpty()) return;
    
    SearchHistoryItem item;
    item.query = query;
    item.intent = analyzeIntent(query);
    item.timestamp = QDateTime::currentDateTime();
    item.resultCount = resultCount;
    item.selected = selected;
    
    m_searchHistory.prepend(item);
    m_searchFrequency[query]++;
    
    // 限制历史记录数量
    if (m_searchHistory.size() > 500) {
        m_searchHistory = m_searchHistory.mid(0, 500);
    }
    
    emit searchHistoryChanged();
    
    // 定期保存
    if (m_searchHistory.size() % 10 == 0) {
        saveSearchHistory();
    }
}

QVariantList AiService::getSearchHistory(int limit)
{
    QVariantList result;
    int count = qMin(limit, m_searchHistory.size());
    
    for (int i = 0; i < count; ++i) {
        const SearchHistoryItem& item = m_searchHistory[i];
        QVariantMap map;
        map["query"] = item.query;
        map["intent"] = item.intent;
        map["timestamp"] = item.timestamp;
        map["resultCount"] = item.resultCount;
        map["selected"] = item.selected;
        result.append(map);
    }
    
    return result;
}

void AiService::clearSearchHistory()
{
    m_searchHistory.clear();
    m_searchFrequency.clear();
    emit searchHistoryChanged();
    saveSearchHistory();
}

bool AiService::deleteSearchHistory(const QString& query)
{
    bool found = false;
    // 从历史列表中删除
    for (int i = m_searchHistory.size() - 1; i >= 0; --i) {
        if (m_searchHistory[i].query == query) {
            m_searchHistory.removeAt(i);
            found = true;
        }
    }
    // 从频率统计中删除
    if (m_searchFrequency.contains(query)) {
        m_searchFrequency.remove(query);
    }
    emit searchHistoryChanged();
    saveSearchHistory();
    return found;
}

QVariantList AiService::getHotSearches(int limit)
{
    QVariantList result;
    
    // 按频率排序
    QList<QPair<QString, int>> sorted;
    for (auto it = m_searchFrequency.constBegin(); it != m_searchFrequency.constEnd(); ++it) {
        sorted.append(qMakePair(it.key(), it.value()));
    }
    std::sort(sorted.begin(), sorted.end(), [](const QPair<QString,int>& a, const QPair<QString,int>& b) {
        return a.second > b.second;
    });
    
    int count = qMin(limit, sorted.size());
    for (int i = 0; i < count; ++i) {
        QVariantMap item;
        item["query"] = sorted[i].first;
        item["frequency"] = sorted[i].second;
        result.append(item);
    }
    
    return result;
}

QString AiService::getSearchHistoryPath() const
{
    return m_searchHistoryPath;
}

bool AiService::saveSearchHistory()
{
    QFile file(m_searchHistoryPath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    
    QJsonObject root;
    QJsonArray history;
    for (const SearchHistoryItem& item : m_searchHistory) {
        QJsonObject obj;
        obj["query"] = item.query;
        obj["intent"] = item.intent;
        obj["timestamp"] = item.timestamp.toString(Qt::ISODate);
        obj["resultCount"] = item.resultCount;
        obj["selected"] = item.selected;
        history.append(obj);
    }
    root["history"] = history;
    
    // 保存频率统计
    QJsonObject freq;
    for (auto it = m_searchFrequency.constBegin(); it != m_searchFrequency.constEnd(); ++it) {
        freq[it.key()] = it.value();
    }
    root["frequency"] = freq;
    
    file.write(QJsonDocument(root).toJson());
    file.close();
    return true;
}

bool AiService::loadSearchHistory()
{
    QFile file(m_searchHistoryPath);
    if (!file.exists()) return false;
    
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    file.close();
    
    if (!doc.isObject()) return false;
    
    QJsonObject root = doc.object();
    QJsonArray history = root["history"].toArray();
    
    m_searchHistory.clear();
    for (const QJsonValue& val : history) {
        QJsonObject obj = val.toObject();
        SearchHistoryItem item;
        item.query = obj["query"].toString();
        item.intent = obj["intent"].toString();
        item.timestamp = QDateTime::fromString(obj["timestamp"].toString(), Qt::ISODate);
        item.resultCount = obj["resultCount"].toInt();
        item.selected = obj["selected"].toBool();
        m_searchHistory.append(item);
    }
    
    // 加载频率统计
    QJsonObject freq = root["frequency"].toObject();
    m_searchFrequency.clear();
    for (auto it = freq.constBegin(); it != freq.constEnd(); ++it) {
        m_searchFrequency[it.key()] = it.value().toInt();
    }
    
    emit searchHistoryChanged();
    return true;
}

void AiService::setLearningEnabled(bool enabled)
{
    if (m_learningEnabled != enabled) {
        m_learningEnabled = enabled;
        emit enabledChanged(enabled);
    }
}

// 添加信号声明到类中需要在头文件中补充，这里先添加 emit 调用
// 在 setEnabled 中已添加 emit enabledChanged
