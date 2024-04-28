#pragma once

/*
 * @breif 重启代码
 */
constexpr static int RETCODE_RESTART = 773;
/*
 * @breif 窗口语言
 * 存储于配置文件中
 */
enum class WINDOWLANAGUAGE {
	Chinese,
	English
};
/*
 * @breif 主题样式
 */
enum class WINDOWTHEMESTYLE {
	DARK,
	LIGHT
};
/*
 * @breif 配置文件
 */
static const std::string configDir = "config";
static const std::string configName = configDir + "/config.ini";
/*
 * @breif 日志文件名称
 */
constexpr static auto logDir = "log";
constexpr static auto logFileName = "user.log";
/*
 * @breif QMenuBar宽度
 */
constexpr static auto ENGLISH_MENUBAR_WIDTH = 120;
constexpr static auto CHINESE_MENUBAR_WIDTH = 90;
/*
 * @breif 窗口显示语言, 默认中文; 进度条样式, 默认块状; 主题样式, 默认亮色
 */
static auto windowLanguage = WINDOWLANAGUAGE::Chinese;
static auto windowThemeStyle = WINDOWTHEMESTYLE::LIGHT;
/*
 * @breif AppID
 */
constexpr static auto AppID = "crucal_app_id";
/*
 * @breif 资源文件路径
 */
constexpr static auto qssFilePathLight = "/style/C_testffmpeg_light.qss";
constexpr static auto qssFilePathDark = "/style/C_testffmpeg_dark.qss";
constexpr static auto rccFilePath = "/resource/C_testffmpeg.rcc";
constexpr static auto translationFilePath_CN = "/translation/C_testffmpeg_cn.qm";
constexpr static auto translationFilePath_EN = "/translation/C_testffmpeg_en.qm";
/*
 * @breif 程序启动传递参数
 */
static std::string App_arg_dir{};
/*
 * @breif 配置文件内容
 */
struct ConfigData {
 WINDOWLANAGUAGE lanaguage{};
 WINDOWTHEMESTYLE themeStyle{};

 ConfigData();
 ConfigData(WINDOWLANAGUAGE lang, WINDOWTHEMESTYLE theme);
 ConfigData& operator=(const ConfigData& other);
 void reset();
};

inline ConfigData::ConfigData() {
 reset();
}

inline ConfigData::ConfigData(WINDOWLANAGUAGE lang, WINDOWTHEMESTYLE theme) :
lanaguage(lang),  themeStyle(theme) {
}

inline ConfigData& ConfigData::operator=(const ConfigData& other) {
 if (this == &other) {
  return *this;
 }
 lanaguage = other.lanaguage;
 themeStyle = other.themeStyle;
 return *this;
}

inline void ConfigData::reset() {
 lanaguage = WINDOWLANAGUAGE::Chinese;
 themeStyle = WINDOWTHEMESTYLE::LIGHT;
}