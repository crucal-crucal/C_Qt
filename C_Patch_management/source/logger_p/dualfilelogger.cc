#include "dualfilelogger.hpp"

Logger_p::DualFileLogger::DualFileLogger(QSettings* firstSettings, QSettings* secondSettings, const int refreshInterval, QObject* parent) {
}

Logger_p::DualFileLogger::~DualFileLogger() {
}

void Logger_p::DualFileLogger::log(QtMsgType type, const QString& message, const QString& file, const QString& function, int line) {
    Logger::log(type, message, file, function, line);
}

void Logger_p::DualFileLogger::clear(bool buffer, bool variables) {
    Logger::clear(buffer, variables);
}
