#include <filesystem>
#include <fstream>
#include <iostream>
#include <QApplication>
#include <QCommandLineParser>
#include <QObject>
#include <QProcess>
#include <QResource>
#include <QSharedMemory>
#include <QTranslator>
#include <string>
#ifdef Q_OS_LINUX
#include <QTextCodec>
#endif

#include "patch.h"
#include "global/cglobal.h"
#include "logger/logger.h"
#include "logger_p/filelogger.hpp"
#include "logger_redirection/logger_redirection.hpp"
#include "splashscreen/splashscreen.h"

QTranslator* g_translator{ nullptr };
QSharedMemory g_sharedMemory{ nullptr };
SplashScreen* g_splashScreen{ nullptr };
/*
 * @note: 加载、卸载资源文件，加载样式表，加载、卸载翻译文件
 * @return: 返回true表示加载成功，返回false表示加载失败
 */
bool loadResources(const QString& strPath);
bool unloadResources(const QString& strPath);
bool loadStyle(QApplication& app, const QString& filePath);
bool loadTranslations(QApplication& app, const QString& filePath);
void unLoadTranslations();
/*
 * @note: 配置文件操作
 */
QString initializeConfigFile(const LoggerConfigData& loggerConfigData);
InterfaceConfigData readConf();
void readConf(const QString& configFilePath, std::vector<std::string>& lines);
void writeConf(const QString& configFilePath, const std::vector<std::string>& lines, const std::vector<std::string>& newLines);
void changeConf(const QString& configFilePath, const InterfaceConfigData& interfaceConfigData);
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
 * @note: 程序唯一性检查, 利用共享内存机制，设置一个唯一的Key，尝试将共享内存附加到当前进程，如果共享内存存在，则说明程序已存在，返回false；如果共享内存不存在，则说明程序唯一，返回true
 * @param: 共享内存
 * @return: 返回true表示程序唯一, 返回false表示程序已存在
 */
inline bool checkSingleInstance(QSharedMemory& shared_memory);
/*
 * @note: 创建命令行参数, -d 指定程序打开的目录, -v 版本, -h 帮助
 */
void createCommandLineParser(const QApplication& app);
/*
 * @note: 创建程序启动页面
 */
SplashScreen* createSplashScreen(const QPixmap& pixmap, int w = 400, int h = 400, Qt::AspectRatioMode mode = Qt::IgnoreAspectRatio);

int main(int argc, char* argv[]) {
#ifdef Q_OS_LINUX
	QTextCodec* codec = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForLocale(codec);
#endif
	QApplication app(argc, argv);
	const LoggerConfigData loggerConfigData;
	// 初始化配置文件
	const QString configFilePath = initializeConfigFile(loggerConfigData);
	// 初始化命令行参数
	createCommandLineParser(app);
	// 获取系统主题颜色
	checkWindowThemeStyle();
	const QFileInfo appFile(QApplication::applicationFilePath());
	// 将路径切换到上级目录
	QDir dir(appFile.absolutePath());
	dir.cdUp();
	const QString appParpath = dir.absolutePath();
	const QString style_light = appParpath + QString::fromLatin1(qssFilePathLight);
	const QString style_dark = appParpath + QString::fromLatin1(qssFilePathDark);
	const QString rcc_path = appParpath + QString::fromLatin1(rccFilePath);
	const QString trans_cn = appParpath + QString::fromLatin1(translationFilePath_CN);
	const QString trans_en = appParpath + QString::fromLatin1(translationFilePath_EN);
	// 加载rcc
	Logger::instance().logInfo(loadResources(rcc_path) ? "Load Resource Success!" : "Load Resource Failed!");
	/*
	 * @note: 加载重定向日志, 写入文件前需要将文件夹创建好, 因为Logger::instance()会创建好log文件夹，所以此处不再创建
	 */
	const auto logSettings = new QSettings(configFilePath, QSettings::IniFormat, &app);
	logSettings->beginGroup(QString::fromStdWString(loggerConfigData.group));
	const auto logger = new Logger_p::FileLogger(logSettings, 10000, &app);
	logger->installMsgHandler();
	// 加载开始界面
	g_splashScreen = createSplashScreen(QPixmap(":/icon/start.png"));
	// 加载界面配置
	g_configData = readConf();
	// 加载样式表
	QString str = (g_configData.themeStyle == WINDOWTHEMESTYLE::LIGHT) ? style_light : style_dark;
	g_splashScreen->showMessage(loadStyle(app, str) ? "Load Style Success!" : "Load Style Failed!", Qt::AlignBottom);
	QThread::sleep(1);
	// 加载翻译 & 加载Label大小
	str = (g_configData.lanaguage == WINDOWLANAGUAGE::Chinese) ? trans_cn : trans_en;
	g_splashScreen->showMessage(loadTranslations(app, str) ? "Load Translation Success!" : "Load Translation Failed!", Qt::AlignBottom);
	QThread::sleep(1);

	CPatch w(g_configData, App_arg_dir);
	// 修改配置文件
	QObject::connect(&w, &CPatch::ConfChanged, [&](const InterfaceConfigData& configData) {
		g_configData.lanaguage = configData.lanaguage;
		g_configData.progressbarstyle = configData.progressbarstyle;
		changeConf(configFilePath, g_configData);
	});
	// 修改主题
	QObject::connect(&w, &CPatch::ThemeChanged, [&](const WINDOWTHEMESTYLE windowthemestyle) {
		g_configData.themeStyle = windowthemestyle;
		loadStyle(app, (g_configData.themeStyle == WINDOWTHEMESTYLE::LIGHT) ? style_light : style_dark);
		changeConf(configFilePath, g_configData);
	});
	// 释放资源
	QObject::connect(&w, &CPatch::destroyed, [&]() {
		unloadResources(rcc_path);
		unLoadTranslations();
		g_sharedMemory.detach();
		g_splashScreen->deleteLater();
	});
	// 程序唯一性检查
	if (!checkSingleInstance(g_sharedMemory)) {
		w.getTrayIcon()->showMessage(QObject::tr("InfoMation"),
		                             QObject::tr("The program already exists, do not start again!"),
		                             QSystemTrayIcon::Information, 1000);
		qDebug() << QObject::tr("The program already exists, do not start again!");
		return -1;
	}

	g_splashScreen->hide();
	w.show();
	const int nRet = QApplication::exec();
	if (nRet == RETCODE_RESTART) {
		// 传入 qApp->applicationFilePath()，启动自己
		QProcess::startDetached(qApp->applicationFilePath(), QStringList()); // NOLINT
		return 0;
	}
	return nRet;
}

bool loadResources(const QString& strPath) {
	qDebug() << ("Resource filePath:\t" + strPath);
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
	qDebug() << ("Style filePath:\t" + filePath);
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

QString initializeConfigFile(const LoggerConfigData& loggerConfigData) {
	const int language = static_cast<int>(g_configData.lanaguage);
	const int progressBarStyle = static_cast<int>(g_configData.progressbarstyle);
	const int themeStyle = static_cast<int>(g_configData.themeStyle);

	const QString appPath = QApplication::applicationDirPath();
	const QString configDirPath = appPath + QDir::separator() + QString::fromStdString(configDir);
	if (const QDir configDir(configDirPath); !configDir.exists() && !configDir.mkpath(".")) {
		qDebug() << "Unable to create directory " << configDirPath;
		return "";
	}

	const QString configFilePath = appPath + QDir::separator() + QString::fromStdString(configName);
	QFile configFile(configFilePath);
	if (!configFile.exists()) {
		if (configFile.open(QFile::WriteOnly | QFile::Text)) {
			QTextStream output(&configFile);
			output << "[" << QString::fromStdWString(loggerConfigData.group) << "]" << "\n";
			output << "fileName=" << QString::fromStdWString(loggerConfigData.fileName) << "\n";
			output << "maxSize=" << QString::number(loggerConfigData.maxSize) << "\n";
			output << "maxBackups=" << QString::number(loggerConfigData.maxBackups) << "\n";
			output << "bufferSize=" << QString::number(loggerConfigData.bufferSize) << "\n";
			output << "minLevel=" << QString::fromStdWString(loggerConfigData.minLevel) << "\n";
			output << "msgFormat=" << QString::fromStdString(loggerConfigData.msgFormat) << "\n";
			output << "timestampFormat=" << QString::fromStdString(loggerConfigData.timestampFormat) << "\n";
			output << "[interface]\n";
			output << "Language: " << language << "\n";
			output << "ProgressbarStyle: " << progressBarStyle << "\n";
			output << "ThemeStyle: " << themeStyle << "\n";
			configFile.close();
		} else {
			qDebug() << "Error: Unable to create config file.";
		}
	}

	return configFilePath;
}

InterfaceConfigData readConf() {
	auto language = g_configData.lanaguage;                // 默认语言
	auto progressBarStyle = g_configData.progressbarstyle; // 默认进度条样式
	auto themeStyle = g_configData.themeStyle;             // 默认主题样式

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
	return { language, progressBarStyle, themeStyle };
}

void readConf(const QString& configFilePath, std::vector<std::string>& lines) {
	bool bInterfaceSection{ false };
	// 读取整个文件内容到内存中
	if (std::ifstream configFile(configFilePath.toStdString()); configFile) {
		std::string line;
		while (std::getline(configFile, line)) {
			if (line == "[interface]") {
				bInterfaceSection = true;
			} else if (line.empty() || line[0] == '[') {
				bInterfaceSection = false;
			}

			if (bInterfaceSection && !line.empty() && line[0] != '[') {
				lines.emplace_back(line);
			}
		}
		configFile.close();
	} else {
		Logger::instance().logError("Error: Unable to open config file for reading.");
	}

	for (auto& line : lines) {
		qDebug() << QString::fromStdString(line);
	}
}

void writeConf(const QString& configFilePath, const std::vector<std::string>& lines, const std::vector<std::string>& newLines) {
	QFile file(configFilePath);
	if (file.open(QIODevice::ReadWrite)) {
		QTextStream stream(&file);
		QString content = stream.readAll();
		if (lines.size() != newLines.size()) {
			qDebug() << "Error: The number of lines in the config file and the number of lines in the new config file do not match.";
			file.close();
			return;
		}
		for (int i = 0; i < newLines.size(); ++i) {
			content.replace(QString::fromStdString(lines[i]), QString::fromStdString(newLines[i]));
		}
		file.seek(0);
		stream << content;
		file.close();
	}
}

void changeConf(const QString& configFilePath, const InterfaceConfigData& interfaceConfigData) {
	const int newLanguageInt = static_cast<int>(interfaceConfigData.lanaguage);
	const int newProgressBarStyleInt = static_cast<int>(interfaceConfigData.progressbarstyle);
	const int newThemeStyleInt = static_cast<int>(interfaceConfigData.themeStyle);

	std::vector<std::string> lines;
	readConf(configFilePath, lines);
	std::vector<std::string> newlines;
	newlines.emplace_back("Language: " + std::to_string(newLanguageInt));
	newlines.emplace_back("ProgressbarStyle: " + std::to_string(newProgressBarStyleInt));
	newlines.emplace_back("ThemeStyle: " + std::to_string(newThemeStyleInt));
	writeConf(configFilePath, lines, newlines);
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
	g_configData.themeStyle = settings.value("AppsUseLightTheme").toBool() ? WINDOWTHEMESTYLE::LIGHT : WINDOWTHEMESTYLE::DARK;
#elif defined(Q_OS_LINUX)
	g_configData.themeStyle = isDarkTheme() ? WINDOWTHEMESTYLE::DARK : WINDOWTHEMESTYLE::LIGHT;
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
	parser.addOption(QCommandLineOption({ "d", "directory" }, "Specify the directory to open", "directory"));
	parser.process(app);
	if (const QString directory = parser.value("d"); !directory.isEmpty()) {
		App_arg_dir = directory.toStdString();
		std::cout << "Directory option is set. Directory:" << directory.toStdString() << std::endl;
	} else {
		std::cout << "Directory option is not set." << std::endl;
	}
}

SplashScreen* createSplashScreen(const QPixmap& pixmap, const int w, const int h, const Qt::AspectRatioMode mode) {
	auto* splash = new SplashScreen(pixmap.scaled(w, h, mode));
	splash->show();
	QApplication::processEvents();
	return splash;
}
