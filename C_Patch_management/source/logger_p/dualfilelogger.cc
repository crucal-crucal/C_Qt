#include "dualfilelogger.hpp"

Logger_p::DualFileLogger::DualFileLogger(QSettings* firstSettings, QSettings* secondSettings, const int refreshInterval, QObject* parent)
: Logger(parent) {
	m_firstLogger = new FileLogger(firstSettings, refreshInterval, this);
	m_secondLogger = new FileLogger(secondSettings, refreshInterval, this);
}

Logger_p::DualFileLogger::~DualFileLogger() = default;

void Logger_p::DualFileLogger::log(const QtMsgType type, const QString& message, const QString& file, const QString& function, const int line) {
	m_firstLogger->log(type, message, file, function, line);
	m_secondLogger->log(type, message, file, function, line);
}

void Logger_p::DualFileLogger::clear(const bool buffer, const bool variables) {
	m_firstLogger->clear(buffer, variables);
	m_secondLogger->clear(buffer, variables);
}
