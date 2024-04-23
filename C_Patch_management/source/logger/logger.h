#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QLoggingCategory>
#include <QMutex>
#include <QTextStream>

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
