#pragma once

#include <QLoggingCategory>
#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QMutex>

#include "global/cglobal.h"

#ifdef LOGGER_LIB
#define LOGGER_EXPORT Q_DECL_EXPORT
#else
#define LOGGER_EXPORT Q_DECL_IMPORT
#endif

class LOGGER_EXPORT Logger {
  public:
	static Logger& instance();

	void logInfo(const QString& message);
	void logWarning(const QString& message);
	void logError(const QString& message);

  private:
	Logger();
	Q_DISABLE_COPY(Logger)
	~Logger();

	void logToFile(const QString& level, const QString& message);

	QFile logFile{};
	QTextStream logStream{};
	QMutex m_mutex{};
};
