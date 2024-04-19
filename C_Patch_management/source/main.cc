#include <QApplication>
#include <QResource>
#include <QTranslator>
#include <QObject>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <QStyleHints>
#ifdef Q_OS_LINUX
#include <QTextCodec>
#endif

#include "patch.h"
#include "global/cglobal.h"

QTranslator* g_translator{nullptr};
/*
 * @note: 加载、卸载资源文件，加载样式表，加载、卸载翻译文件
 */
bool loadResources(const QString& strPath);
bool unloadResources(const QString& strPath);
bool loadStyle(QApplication& app, const QString& filePath);
bool loadTranslations(QApplication& app, const QString& filePath);
void unLoadTranslations();
/*
 * @note: 配置文件操作
 */
void initializeConfigFile();
std::tuple<WINDOWLANAGUAGE, WINDOWPROGRESSBARSTYLE, WINDOWTHEMESTYLE> readConf();
void changeConf(WINDOWLANAGUAGE newLanguage, WINDOWPROGRESSBARSTYLE newprogressBarStyle, WINDOWTHEMESTYLE newThemeStyle);

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

#ifdef Q_OS_WIN
	QSettings settings(R"(HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)", QSettings::NativeFormat);
	if (settings.value("AppsUseLightTheme") == 0) {
		// 深色主题，如果第一次启动程序，默认使用系统颜色
		windowThemeStyle = WINDOWTHEMESTYLE::DARK;
	} else {
		// 浅色主题
		windowThemeStyle = WINDOWTHEMESTYLE::LIGHT;
	}
#endif
	QApplication::setFont(QFont("Microsoft Yahei", 9));
	// 设置中文编码
#ifdef Q_OS_LINUX
	QTextCodec *codec = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForLocale(codec);
#endif

	QFileInfo appFile(QApplication::applicationFilePath());
	// 将路径切换到上级目录
	QDir dir(appFile.absolutePath());
	dir.cdUp();
	QString appParPath = dir.absolutePath();
	QString strStyle_light = appParPath + "/style/C_Patch_management_light.qss";
	QString strStyle_dark = appParPath + "/style/C_Patch_management_dark.qss";
	QString strRes = appParPath + "/resource/C_Patch_management.rcc";
	QString strtrans_cn = appParPath + "/translation/C_Patch_management_cn.qm";
	QString strtrans_en = appParPath + "/translation/C_Patch_management_en.qm";
	initializeConfigFile();
	// 加载rcc
	Logger::instance().logInfo(loadResources(strRes) ? "Load Resource Success!" : "Load Resource Failed!");
	auto [language, progressBarStyle, themeStyle] = readConf();
	windowLanguage = language;
	progressbarstyle = progressBarStyle;
	windowThemeStyle = themeStyle;
	QString str = (windowThemeStyle == WINDOWTHEMESTYLE::LIGHT) ? strStyle_light : strStyle_dark;
	// 加载样式表
	Logger::instance().logInfo(loadStyle(app, str) ? "Load Style Success!" : "Load Style Failed!");
	// 加载翻译 & 加载Label大小
	str = (windowLanguage == WINDOWLANAGUAGE::Chinese) ? strtrans_cn : strtrans_en;
	Logger::instance().logInfo(loadTranslations(app, str) ? "Load Translation Success!" : "Load Translation Failed!");

	int LabelWidth = windowLanguage == WINDOWLANAGUAGE::Chinese ? CHINESE_LABEL_WIDTH : ENGLISH_LABEL_WIDTH;
	CPatch w(LabelWidth, windowLanguage, progressbarstyle, windowThemeStyle);
	// 修改配置文件
	QObject::connect(&w, &CPatch::ConfChanged, [&](WINDOWLANAGUAGE lang, WINDOWPROGRESSBARSTYLE prostyle) {
		windowLanguage = lang;
		progressbarstyle = prostyle;
		changeConf(windowLanguage, progressbarstyle, windowThemeStyle);
	});
	// 修改主题
	QObject::connect(&w, &CPatch::ThemeChanged, [&](WINDOWTHEMESTYLE windowthemestyle) {
		windowThemeStyle = windowthemestyle;
		loadStyle(app, (windowThemeStyle == WINDOWTHEMESTYLE::LIGHT) ? strStyle_light : strStyle_dark);
		changeConf(windowLanguage, progressbarstyle, windowThemeStyle);
	});
	QObject::connect(&w, &CPatch::destroyed, [&]() {
		unloadResources(strRes);
		unLoadTranslations();
	});
	w.show();

	int nRet = QApplication::exec();
	if (nRet == RETCODE_RESTART) {
		// 传入 qApp->applicationFilePath()，启动自己
		QProcess::startDetached(qApp->applicationFilePath(), QStringList());
		return 0;
	}
	return nRet;
}

bool loadResources(const QString& strPath) {
	qDebug() << "Resource filePath:\t" << strPath;
	return QResource::registerResource(strPath);
}

bool unloadResources(const QString& strPath) {
	if (QResource::unregisterResource(strPath)) {
		qDebug() << "unregister resource success";
		return true;
	}
	Logger::instance().logError("resource filePath:\t" + strPath);
	Logger::instance().logError("unregister resource failed");
	return false;
}

bool loadStyle(QApplication& app, const QString& filePath) {
	qDebug() << "Style filePath:\t" << filePath;
	QFile file(filePath);
	if (file.open(QFile::ReadOnly)) {
		QString strStyleSheet = QLatin1String(file.readAll());
		app.setStyleSheet(strStyleSheet);
		file.close();
		return true;
	}
	Logger::instance().logError(file.errorString());
	return false;
}

bool loadTranslations(QApplication& app, const QString& filePath) {
	unLoadTranslations();
	qDebug() << "Translation filePath:\t" << filePath;
	if (!g_translator)
		g_translator = new QTranslator(&app);
	if (!g_translator->load(filePath)) {
		return false;
	}
	QApplication::installTranslator(g_translator);
	return true;
}

void unLoadTranslations() {
	QApplication::removeTranslator(g_translator);
	if (g_translator) {
		delete g_translator;
		g_translator = nullptr;
		qDebug() << "unLoadTranslations, g_translator delete success";
	} else {
		qDebug() << "unLoadTranslations, g_translator == nullptr";
	}
}

void initializeConfigFile() {
	int language = static_cast<int>(windowLanguage);
	int progressBarStyle = static_cast<int>(progressbarstyle);
	int themeStyle = static_cast<int>(windowThemeStyle);
	// 检查config文件夹是否存在，如果不存在则创建
	if (!std::filesystem::exists(configDir)) {
		if (!std::filesystem::create_directory(configDir)) {
			Logger::instance().logError("Error: Unable to create directory " + QString::fromStdString(configDir));
			return;
		}
		std::cout << "Directory " << configDir << " created." << std::endl;
	}

	std::ifstream configFile(configName);
	if (!configFile) {
		// 配置文件不存在
		std::ofstream outputFile(configName);
		if (outputFile) {
			// 写入语言和进度条样式
			outputFile << "Language: " << language << "\n";
			outputFile << "ProgressbarStyle: " << progressBarStyle << "\n";
			outputFile << "ThemeStyle: " << themeStyle;
			outputFile.close();
			std::cout << "Config file created and initialized with default language." << std::endl;
		} else {
			Logger::instance().logError("Error: Unable to create config file.");
		}
	} else {
		std::cout << "Config file already exists." << std::endl;
	}
}

std::tuple<WINDOWLANAGUAGE, WINDOWPROGRESSBARSTYLE, WINDOWTHEMESTYLE> readConf() {
	auto language = windowLanguage; // 默认语言
	auto progressBarStyle = progressbarstyle; // 默认进度条样式
	auto themeStyle = windowThemeStyle; // 默认主题样式

	std::ifstream configFile(configName);
	if (configFile) {
		std::string line;
		while (std::getline(configFile, line)) {
			if (line.find("Language:") != std::string::npos) {
				// 读取显示语言
				std::string languageValue = line.substr(line.find(':') + 1);
				int languageint = std::stoi(languageValue);
				language = static_cast<WINDOWLANAGUAGE>(languageint);
			} else if (line.find("ProgressbarStyle:") != std::string::npos) {
				// 读取进度条样式
				std::string styleValue = line.substr(line.find(':') + 1);
				int styleInt = std::stoi(styleValue);
				progressBarStyle = static_cast<WINDOWPROGRESSBARSTYLE>(styleInt);
			} else if (line.find("ThemeStyle:") != std::string::npos) {
				// 主题样式
				std::string themeValue = line.substr(line.find(':') + 1);
				int themeInt = std::stoi(themeValue);
				themeStyle = static_cast<WINDOWTHEMESTYLE>(themeInt);
			}
		}
	}
	return std::make_tuple(language, progressBarStyle, themeStyle);
}

void changeConf(WINDOWLANAGUAGE newLanguage, WINDOWPROGRESSBARSTYLE newprogressBarStyle, WINDOWTHEMESTYLE newThemeStyle) {
	int newLanguageInt = static_cast<int>(newLanguage);
	int newProgressBarStyleInt = static_cast<int>(newprogressBarStyle);
	int newThemeStyleInt = static_cast<int>(newThemeStyle);

	// 读取整个文件内容到内存中
	std::ifstream configFile(configName);
	std::vector<std::string> lines;
	if (configFile) {
		std::string line;
		while (std::getline(configFile, line)) {
			lines.push_back(line);
		}
		configFile.close();
	} else {
		Logger::instance().logError("Error: Unable to open config file for reading.");
		return;
	}

	// 查找并修改 "Language:", "ProgressbarStyle:", "ThemeStyle:"
	bool languageFound = false;
	bool styleFound = false;
	bool themeFound = false;
	for (std::string& line : lines) {
		if (line.find("Language:") != std::string::npos) {
			line = "Language: " + std::to_string(newLanguageInt); // 修改语言值
			languageFound = true;
		} else if (line.find("ProgressbarStyle:") != std::string::npos) {
			line = "ProgressbarStyle: " + std::to_string(newProgressBarStyleInt); // 修改样式值
			styleFound = true;
		} else if (line.find("ThemeStyle:") != std::string::npos) {
			line = "ThemeStyle: " + std::to_string(newThemeStyleInt); // 修改主题值
			themeFound = true;
		}
		if (languageFound && styleFound && themeFound) {
			break;
		}
	}

	// 如果找到了语言和样式行，则写回到文件中
	if (languageFound && styleFound && themeFound) {
		std::ofstream outputFile(configName, std::ios::trunc);
		if (outputFile) {
			for (const std::string& line : lines) {
				outputFile << line << std::endl;
			}
			outputFile.close();
			std::cout << "Language changed to " << (newLanguage == WINDOWLANAGUAGE::English ? "English" : "Chinese") << std::endl;
			std::cout << "Progressbar style changed" << std::endl;
			std::cout << "Theme style changed" << std::endl;
		} else {
			Logger::instance().logError("Error: Unable to open config file for writing.");
		}
	} else {
		Logger::instance().logError("Error: Language or style line not found in config file.");
	}
}
