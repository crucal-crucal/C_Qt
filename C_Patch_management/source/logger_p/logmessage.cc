#include "logmessage.hpp"

#include <QThread>

Logger_p::LogMessage::LogMessage(const QtMsgType type, const QString& message, const QHash<QString, QString>* logVars, const QString& file,
                                 const QString& function, const int line)
: m_type(type), m_message(message), m_file(file), m_function(function), m_line(line) {
	m_timestamp = QDateTime::currentDateTime();
	m_threadId = QThread::currentThreadId();
	if (logVars) {
		this->m_logVars = *logVars;
	}
}

QString Logger_p::LogMessage::toString(const QString& msgFormat, const QString& timestampFormat) const {
	QString decorated = msgFormat + "\n";
	decorated.replace("{message}", m_message);
	if (decorated.contains("{timestamp}")) {
		decorated.replace("{timestamp}", m_timestamp.toString(timestampFormat));
	}
	QString typeNr{};
	typeNr.setNum(m_type);
	decorated.replace("{typeNr}", typeNr);

	switch (m_type) {
		case QtDebugMsg: {
			decorated.replace("{type}", "DEBUG	 ");
			break;
		}
		case QtWarningMsg: {
			decorated.replace("{type}", "WARNING ");
			break;
		}
		case QtCriticalMsg: {
			decorated.replace("{type}", "CRITICAL");
			break;
		}
		case QtFatalMsg: {
			decorated.replace("{type}", "FATAL   ");
			break;
		}
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		case QtInfoMsg: {
			decorated.replace("{type}", "INFO     ");
			break;
		}
#endif
		default: break;
	}

	decorated.replace("{file}", m_file);
	decorated.replace("{function}", m_function);
	decorated.replace("{line}", QString::number(m_line));

	const QString threadId = QString("0x%1").arg(reinterpret_cast<qulonglong>(QThread::currentThread()), 8, 16, QLatin1Char('0'));
	decorated.replace("{thread}", threadId);

	if (decorated.contains("{") && !m_logVars.isEmpty()) {
		QList<QString> keys = m_logVars.keys();
		foreach(auto key, keys) {
			decorated.replace("{" + key + "}", m_logVars.value(key));
		}
	}

	return decorated;
}

QtMsgType Logger_p::LogMessage::getType() const {
	return m_type;
}
