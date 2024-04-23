﻿#include "Logger.h"

Logger& Logger::instance() {
	static Logger instance;
	return instance;
}

void Logger::logInfo(const QString& message) {
	logToFile("INFO", message);
}

void Logger::logWarning(const QString& message) {
	logToFile("WARNING", message);
}

void Logger::logError(const QString& message) {
	logToFile("ERROR", message);
}

Logger::Logger() {
	QString appDirPath = QCoreApplication::applicationDirPath();
	QDir log_dir(appDirPath + QDir::separator() + QString::fromStdString(logDir));
	if (!log_dir.exists()) {
		if (!log_dir.mkpath(".")) {
			qWarning() << "Failed to create log directory.";
			return;
		}
	}
	logFile.setFileName(log_dir.filePath(QString::fromStdString(logFileName)));
	if (logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
		logStream.setDevice(&logFile);
	}
}

Logger::~Logger() {
	logFile.close();
}

void Logger::logToFile(const QString& level, const QString& message) {
	QMutexLocker locker(&m_mutex);
	if (logStream.device()) {
		logStream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << " [" << level << "] " << message << Qt::endl;
	}
}
