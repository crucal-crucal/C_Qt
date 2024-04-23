#pragma once

/*
 * @breif 重启代码
 */
static const int RETCODE_RESTART = 773;
/*
 * @breif 窗口语言
 * 存储于配置文件中
 */
enum class WINDOWLANAGUAGE {
	Chinese,
	English
};
/*
 * @breif 进度条样式
 */
enum class WINDOWPROGRESSBARSTYLE {
	NORMAL,                // Qt默认样式
	BLOCK,                // 块状显示
	BORDER_RED,        // 红色边框
	BORDER_RADIUS,        // 圆形边框
	GRADATION            // 渐变色
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
static const std::string logDir = "log";
static const std::string logFileName = "user.log";
/*
 * @breif Label大小
 */
static const int ENGLISH_LABEL_WIDTH = 110;
static const int CHINESE_LABEL_WIDTH = 60;
/*
 * @breif 窗口显示语言, 默认中文; 进度条样式, 默认块状; 主题样式, 默认亮色
 */
static WINDOWLANAGUAGE windowLanguage = WINDOWLANAGUAGE::Chinese;
static WINDOWPROGRESSBARSTYLE progressbarstyle = WINDOWPROGRESSBARSTYLE::BLOCK;
static WINDOWTHEMESTYLE windowThemeStyle = WINDOWTHEMESTYLE::LIGHT;
/*
 * @breif AppID
 */
static const std::string AppID = "crucal_app_id";
/*
 * @breif 资源文件路径
 */
static const std::string qssFilePathLight = "/style/C_Patch_management_light.qss";
static const std::string qssFilePathDark = "/style/C_Patch_management_dark.qss";
static const std::string rccFilePath = "/resource/C_Patch_management.rcc";
static const std::string translationFilePath_CN = "/translation/C_Patch_management_cn.qm";
static const std::string translationFilePath_EN = "/translation/C_Patch_management_en.qm";