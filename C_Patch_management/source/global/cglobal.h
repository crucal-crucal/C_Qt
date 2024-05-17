#pragma once

#include <QDebug>
#include <QString>

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
 * @breif 进度条样式
 */
enum class WINDOWPROGRESSBARSTYLE {
	NORMAL,        // Qt默认样式
	BLOCK,         // 块状显示
	BORDER_RED,    // 红色边框
	BORDER_RADIUS, // 圆形边框
	GRADATION      // 渐变色
};
/*
 * @breif 主题样式
 */
enum class WINDOWTHEMESTYLE {
	DARK,
	LIGHT
};
/*
 * @breif 配置文件内容
 */
struct InterfaceConfigData {
	WINDOWLANAGUAGE lanaguage{};               // 界面语言
	WINDOWPROGRESSBARSTYLE progressbarstyle{}; // 界面进度条样式
	WINDOWTHEMESTYLE themeStyle{};             // 界面主题样式

	InterfaceConfigData();
	InterfaceConfigData(WINDOWLANAGUAGE lang, WINDOWPROGRESSBARSTYLE style, WINDOWTHEMESTYLE theme);
	InterfaceConfigData& operator=(const InterfaceConfigData& other);
	friend QDebug operator<<(QDebug debug, const InterfaceConfigData& data);
	static QString getLanaguageName(const WINDOWLANAGUAGE& lanaguage);                      // 获取语言名称
	static QString getProgressbarStyleName(const WINDOWPROGRESSBARSTYLE& progressbarstyle); // 获取进度条样式名称
	static QString getThemeStyleName(const WINDOWTHEMESTYLE& themestyle);                   // 获取主题样式名称
	void reset();
};

inline InterfaceConfigData::InterfaceConfigData() {
	reset();
}

inline InterfaceConfigData::InterfaceConfigData(const WINDOWLANAGUAGE lang, const WINDOWPROGRESSBARSTYLE style, const WINDOWTHEMESTYLE theme)
: lanaguage(lang), progressbarstyle(style), themeStyle(theme) {
}

inline InterfaceConfigData& InterfaceConfigData::operator=(const InterfaceConfigData& other) {
	if (this == &other) {
		return *this;
	}
	lanaguage = other.lanaguage;
	progressbarstyle = other.progressbarstyle;
	themeStyle = other.themeStyle;
	return *this;
}

inline QDebug operator<<(QDebug debug, const InterfaceConfigData& data) {
	const QString info = QString("current lanaguage:%1, current progressbarstyle:%2, current themeStyle:%3")
		.arg(InterfaceConfigData::getLanaguageName(data.lanaguage),
		     InterfaceConfigData::getProgressbarStyleName(data.progressbarstyle),
		     InterfaceConfigData::getThemeStyleName(data.themeStyle));
	debug << info;
	return debug;
}

inline QString InterfaceConfigData::getLanaguageName(const WINDOWLANAGUAGE& lanaguage) {
	QString result{};
	switch (lanaguage) {
		case WINDOWLANAGUAGE::Chinese: {
			result = "Chinese";
			break;
		}
		case WINDOWLANAGUAGE::English: {
			result = "English";
			break;
		}
		default: break;
	}
	return result;
}

inline QString InterfaceConfigData::getProgressbarStyleName(const WINDOWPROGRESSBARSTYLE& progressbarstyle) {
	QString result{};
	switch (progressbarstyle) {
		case WINDOWPROGRESSBARSTYLE::NORMAL: {
			result = "NORMAL";
			break;
		}
		case WINDOWPROGRESSBARSTYLE::BLOCK: {
			result = "BLOCK";
			break;
		}
		case WINDOWPROGRESSBARSTYLE::BORDER_RED: {
			result = "BORDER_RED";
			break;
		}
		case WINDOWPROGRESSBARSTYLE::BORDER_RADIUS: {
			result = "BORDER_RADIUS";
			break;
		}
		case WINDOWPROGRESSBARSTYLE::GRADATION: {
			result = "GRADATION";
			break;
		}
		default: break;
	}
	return result;
}

inline QString InterfaceConfigData::getThemeStyleName(const WINDOWTHEMESTYLE& themestyle) {
	QString result{};
	switch (themestyle) {
		case WINDOWTHEMESTYLE::DARK: {
			result = "DARK";
			break;
		}
		case WINDOWTHEMESTYLE::LIGHT: {
			result = "LIGHT";
			break;
		}
		default: break;
	}
	return result;
}

inline void InterfaceConfigData::reset() {
	lanaguage = WINDOWLANAGUAGE::Chinese;
	progressbarstyle = WINDOWPROGRESSBARSTYLE::BLOCK;
	themeStyle = WINDOWTHEMESTYLE::LIGHT;
}
/*
 * @breif 全局界面配置，备份
 */
inline static InterfaceConfigData g_configData;
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
 * @breif Label宽度, QMenuBar宽度
 */
constexpr static auto ENGLISH_LABEL_WIDTH = 110;
constexpr static auto CHINESE_LABEL_WIDTH = 60;
constexpr static auto ENGLISH_MENUBAR_WIDTH = 120;
constexpr static auto CHINESE_MENUBAR_WIDTH = 90;
/*
 * @breif AppID
 */
constexpr static auto AppID = "crucal_app_id";
/*
 * @breif 资源文件路径
 */
constexpr static auto qssFilePathLight = "/style/C_Patch_management_light.qss";
constexpr static auto qssFilePathDark = "/style/C_Patch_management_dark.qss";
constexpr static auto rccFilePath = "/resource/C_Patch_management.rcc";
constexpr static auto translationFilePath_CN = "/translation/C_Patch_management_cn.qm";
constexpr static auto translationFilePath_EN = "/translation/C_Patch_management_en.qm";
/*
 * @breif 程序启动传递参数
 */
static std::string App_arg_dir{};
