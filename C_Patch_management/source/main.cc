#include <QApplication>
#include <QResource>
#include <QTranslator>
#include <QObject>
#include <iostream>
#include <fstream>
#include <string>

#include "patch.h"
#include "C_global.h"
#ifdef Q_OS_LINUX
#include <QTextCodec>
#endif

QTranslator* g_translator{nullptr};
std::string configName = "config.ini";

bool loadResources(const QString& strPath);
bool unloadResources(const QString& strPath);
bool loadStyle(QApplication& app, const QString& filePath);
bool loadTranslations(QApplication& app, const QString& filePath);
void unLoadTranslations();
void initializeConfigFile();
WINDOWLANAGUAGE readLanguageFormConfig();
void changeLanguageInConfig(WINDOWLANAGUAGE newLanguage);

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QApplication::setFont(QFont("Microsoft Yahei", 9));
	//设置中文编码
#ifdef Q_OS_LINUX
	QTextCodec *codec = QTextCodec::codecForName("utf-8");
	QTextCodec::setCodecForLocale(codec);
#endif

	QFileInfo appFile(QApplication::applicationFilePath());
	// 将路径切换到上级目录
	QDir dir(appFile.absolutePath());
	dir.cdUp();
	QString appParPath = dir.absolutePath();
	QString strStyle = appParPath + "/style/C_Patch_management.qss";
	QString strRes = appParPath + "/resource/C_Patch_management.rcc";
	QString strtrans_cn = appParPath + "/translation/C_Patch_management_cn.qm";
	QString strtrans_en = appParPath + "/translation/C_Patch_management_en.qm";
	initializeConfigFile();
	// 加载样式表
	qInfo(loadStyle(app, strStyle) ? "Load Style Success!" : "Load Style Failed!");
	// 加载rcc
	qInfo(loadResources(strRes) ? "Load Resource Success!" : "Load Resource Failed!");
	// 加载中文翻译
	QString str = (readLanguageFormConfig() == WINDOWLANAGUAGE::Chinese) ? strtrans_cn : strtrans_en;
	qInfo(loadTranslations(app, str) ? "Load Translation Success!" : "Load Translation Failed!");

	CPatch w;
	QObject::connect(&w, &CPatch::LanguageChanged, [&](WINDOWLANAGUAGE language) {
		changeLanguageInConfig(language);
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
	qDebug() << "resource filePath:\t" << strPath;
	qDebug() << "unregister resource failed";
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
	qDebug() << file.errorString();
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
	std::ifstream configFile(configName);
	if (!configFile) {
		// 配置文件不存在
		std::ofstream outputFile(configName);
		if (outputFile) {
			outputFile << "Language: Chinese";
			outputFile.close();
			std::cout << "Config file created and initialized with default language." << std::endl;
		}
		else {
			std::cerr << "Error: Unable to create config file." << std::endl;
		}
	}
	else {
		std::cout << "Config file already exists." << std::endl;
	}
}

WINDOWLANAGUAGE readLanguageFormConfig() {
	std::ifstream configFile(configName);
	if (configFile) {
		std::string line;
		while (std::getline(configFile, line)) {
			if (line.find("Language:") != std::string::npos) {
				if (line.find("English") != std::string::npos) {
					return WINDOWLANAGUAGE::English;
				}
				else if (line.find("Chinese") != std::string::npos) {
					return WINDOWLANAGUAGE::Chinese;
				}
			}
		}
	}
	return WINDOWLANAGUAGE::Chinese; // 默认返回中文
}

void changeLanguageInConfig(WINDOWLANAGUAGE newLanguage) {
	std::ofstream configFile(configName, std::ios::trunc);
	if (configFile) {
		if (newLanguage == WINDOWLANAGUAGE::English) {
			configFile << "Language: English";
		}
		else {
			configFile << "Language: Chinese";
		}
		std::cout << "Language changed to " << (newLanguage == WINDOWLANAGUAGE::English ? "English" : "Chinese") << std::endl;
	}
	else {
		std::cerr << "Error: Unable to open config file for writing." << std::endl;
	}
	qApp->exit(RETCODE_RESTART);
}
