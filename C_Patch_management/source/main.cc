#include <filesystem>
#include <fstream>
#include <iostream>
#include <QApplication>
#include <QCommandLineParser>
#include <QObject>
#include <QProcess>
#include <QResource>
#include <QSettings>
#include <QSharedMemory>
#include <QTranslator>
#include <string>
#ifdef Q_OS_LINUX
#include <QTextCodec>
#endif

#include "patch.h"
#include "global/cglobal.h"
#include "logger/logger.h"

QTranslator* g_translator{ nullptr };
QSharedMemory g_sharedMemory{ nullptr };
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
void changeConf(WINDOWLANAGUAGE newLanguage, WINDOWPROGRESSBARSTYLE newprogressBarStyle,
                WINDOWTHEMESTYLE newThemeStyle);
/*
 * @note: Linux 通过系统命令判断是否为深色主题
 */
#ifdef Q_OS_LINUX
std::string exec(const char* cmd); // 执行系统命令并返回其输出
bool isDarkTheme();                // 检查当前主题模式
#endif
/*
 * @note: 第一次启动程序，默认使用系统颜色
 */
void checkWindowThemeStyle();
/*
 * @note: 程序唯一性检查
 */
inline bool checkSingleInstance(QSharedMemory& shared_memory);
/*
 * @note: 创建命令行参数
 */
void createCommandLineParser(const QApplication& app);

int main(int argc, char* argv[]) {
#ifdef Q_OS_LINUX
	QTextCodec* codec = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForLocale(codec);
#endif
	QApplication app(argc, argv);
	createCommandLineParser(app);
	checkWindowThemeStyle();

	const QFileInfo appFile(QApplication::applicationFilePath());
	// 将路径切换到上级目录
	QDir dir(appFile.absolutePath());
	dir.cdUp();
	const QString appParPath = dir.absolutePath();
	const QString strStyle_light = appParPath + QString::fromLatin1(qssFilePathLight);
	const QString strStyle_dark = appParPath + QString::fromLatin1(qssFilePathDark);
	const QString strRcc = appParPath + QString::fromLatin1(rccFilePath);
	const QString strtrans_cn = appParPath + QString::fromLatin1(translationFilePath_CN);
	const QString strtrans_en = appParPath + QString::fromLatin1(translationFilePath_EN);

	initializeConfigFile();
	auto [language, progressBarStyle, themeStyle] = readConf();
	windowLanguage = language;
	progressbarstyle = progressBarStyle;
	windowThemeStyle = themeStyle;
	// 加载rcc
	Logger::instance().logInfo(loadResources(strRcc) ? "Load Resource Success!" : "Load Resource Failed!");
	// 加载样式表
	QString str = (windowThemeStyle == WINDOWTHEMESTYLE::LIGHT) ? strStyle_light : strStyle_dark;
	Logger::instance().logInfo(loadStyle(app, str) ? "Load Style Success!" : "Load Style Failed!");
	// 加载翻译 & 加载Label大小
	str = (windowLanguage == WINDOWLANAGUAGE::Chinese) ? strtrans_cn : strtrans_en;
	Logger::instance().logInfo(loadTranslations(app, str) ? "Load Translation Success!" : "Load Translation Failed!");

	const int LabelWidth = windowLanguage == WINDOWLANAGUAGE::Chinese ? CHINESE_LABEL_WIDTH : ENGLISH_LABEL_WIDTH;
	CPatch w(LabelWidth, windowLanguage, progressbarstyle, windowThemeStyle, App_arg_dir);
	// 修改配置文件
	QObject::connect(&w, &CPatch::ConfChanged, [&](const WINDOWLANAGUAGE lang, const WINDOWPROGRESSBARSTYLE prostyle) {
		windowLanguage = lang;
		progressbarstyle = prostyle;
		changeConf(windowLanguage, progressbarstyle, windowThemeStyle);
	});
	// 修改主题
	QObject::connect(&w, &CPatch::ThemeChanged, [&](const WINDOWTHEMESTYLE windowthemestyle) {
		windowThemeStyle = windowthemestyle;
		loadStyle(app, (windowThemeStyle == WINDOWTHEMESTYLE::LIGHT) ? strStyle_light : strStyle_dark);
		changeConf(windowLanguage, progressbarstyle, windowThemeStyle);
	});
	// 释放资源
	QObject::connect(&w, &CPatch::destroyed, [&]() {
		unloadResources(strRcc);
		unLoadTranslations();
		g_sharedMemory.detach();
	});
	// 程序唯一性检查
	if (!checkSingleInstance(g_sharedMemory)) {
		w.getTrayIcon()->showMessage(QObject::tr("InfoMation"),
		                             QObject::tr("The program already exists, do not start again!"),
		                             QSystemTrayIcon::Information, 1000);
		qDebug() << QObject::tr("The program already exists, do not start again!");
		return -1;
	}

	w.show();
	const int nRet = QApplication::exec();
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
		const QString strStyleSheet = QLatin1String(file.readAll());
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
	const int language = static_cast<int>(windowLanguage);
	const int progressBarStyle = static_cast<int>(progressbarstyle);
	const int themeStyle = static_cast<int>(windowThemeStyle);
	// 检查config文件夹是否存在，如果不存在则创建
	if (!std::filesystem::exists(configDir)) {
		if (!std::filesystem::create_directory(configDir)) {
			Logger::instance().logError("Error: Unable to create directory " + QString::fromStdString(configDir));
			return;
		}
		std::cout << "Directory " << configDir << " created." << std::endl;
	}

	if (const std::ifstream configFile(configName); !configFile) {
		// 配置文件不存在
		if (std::ofstream outputFile(configName); outputFile) {
			// 写入语言和进度条样式
			outputFile << "Language: " << language << "\n";
			outputFile << "ProgressbarStyle: " << progressBarStyle << "\n";
			outputFile << "ThemeStyle: " << themeStyle;
			outputFile.close();
			std::cout << "Config file created." << std::endl;
		} else {
			Logger::instance().logError("Error: Unable to create config file.");
		}
	} else {
		std::cout << "Config file already exists." << std::endl;
	}
}

std::tuple<WINDOWLANAGUAGE, WINDOWPROGRESSBARSTYLE, WINDOWTHEMESTYLE> readConf() {
	auto language = windowLanguage;           // 默认语言
	auto progressBarStyle = progressbarstyle; // 默认进度条样式
	auto themeStyle = windowThemeStyle;       // 默认主题样式

	if (std::ifstream configFile(configName); configFile) {
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

void changeConf(WINDOWLANAGUAGE newLanguage, WINDOWPROGRESSBARSTYLE newprogressBarStyle,
                WINDOWTHEMESTYLE newThemeStyle) {
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
		if (std::ofstream outputFile(configName, std::ios::trunc); outputFile) {
			for (const std::string& line : lines) {
				outputFile << line << std::endl;
			}
			outputFile.close();
			std::cout << "Language changed to " << (newLanguage == WINDOWLANAGUAGE::English ? "English" : "Chinese") <<
				std::endl;
			std::cout << "Progressbar style changed" << std::endl;
			std::cout << "Theme style changed" << std::endl;
		} else {
			Logger::instance().logError("Error: Unable to open config file for writing.");
		}
	} else {
		Logger::instance().logError("Error: Language or style line not found in config file.");
	}
}

#ifdef Q_OS_LINUX
std::string exec(const char* cmd) {
	std::array<char, 128> buffer{};
	std::string result{};
	const std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		// 将buffer中的内容从尾部插入到result中
		std::copy(buffer.begin(), buffer.end(), std::back_inserter(result));
	}
	return result;
}

bool isDarkTheme() {
	const std::string output = exec("gsettings get org.gnome.desktop.interface gtk-theme");
	return output.find("dark") != std::string::npos;
}
#endif

void checkWindowThemeStyle() {
#ifdef Q_OS_WIN
	const QSettings settings(R"(HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)", QSettings::NativeFormat);
	windowThemeStyle = settings.value("AppsUseLightTheme").toBool() ? WINDOWTHEMESTYLE::LIGHT : WINDOWTHEMESTYLE::DARK;
#elif defined(Q_OS_LINUX)
	windowThemeStyle = isDarkTheme() ? WINDOWTHEMESTYLE::DARK : WINDOWTHEMESTYLE::LIGHT;
#endif
}

inline bool checkSingleInstance(QSharedMemory& shared_memory) {
	shared_memory.setKey(QString::fromLatin1(AppID));
	if (shared_memory.attach()) {
		return false;
	}
	if (shared_memory.create(1)) {
		return true;
	}
	return false;
}

void createCommandLineParser(const QApplication& app) {
	// 命令行参数
	QCoreApplication::setApplicationName("C_Patch_management");
	QCoreApplication::setApplicationVersion("1.0.0");
	QCommandLineParser parser;
	parser.addHelpOption();
	parser.addVersionOption();
	const QString optionShort = "d";
	const QString optionLong = "directory";
	parser.addOption(QCommandLineOption({ optionShort, optionLong }, "Specify the directory to open", "directory"));
	parser.process(app);
	if (parser.isSet(optionShort) || parser.isSet(optionLong)) {
		QString directory;
		if (parser.isSet(optionShort))
			directory = parser.value(optionShort);
		else
			directory = parser.value(optionLong);
		App_arg_dir = directory.toStdString();
		qDebug() << "Directory option is set. Directory:" << directory;
	} else {
		qDebug() << "Directory option is not set.";
	}
}
