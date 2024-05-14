#include "logger.hpp"

#include <QDateTime>
#include <QObject>
#include <QThread>
#include <utility>
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QRecursiveMutex>
#endif

Logger_p::Logger* Logger_p::Logger::defaultLogger = nullptr;

QThreadStorage<QHash<QString, QString>*> Logger_p::Logger::logVars{};

QMutex Logger_p::Logger::mutex{};

Logger_p::Logger::Logger(QObject* parent)
: QObject(parent), msgFormat("{timestamp} {type} {message}"), timestampFormat("dd.MM.yyyy hh:mm:ss.zzz"), minLevel(QtDebugMsg) {
}

Logger_p::Logger::Logger(QString msgFormat, QString timestampFormat, const QtMsgType minLevel, const int bufferSize, QObject* parent)
: QObject(parent), msgFormat(msgFormat.isEmpty() ? "{timestamp} {type} {message}" : std::move(msgFormat)),
  timestampFormat(timestampFormat.isEmpty() ? "dd.MM.yyyy hh:mm:ss.zzz" : std::move(timestampFormat)),
  minLevel(minLevel), bufferSize(bufferSize) {
}

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
static QRecursiveMutex recursiveMutex;
static QMutex nonRecursiveMutex;
#else
static QMutex recursiveMutex(QMutex::Recursive);
static QMutex nonRecursiveMutex(QMutex::NonRecursive);
#endif

Logger_p::Logger::~Logger() {
	if (defaultLogger == this) {
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		qInstallMessageHandler(nullptr);
#else
		qInstallMsgHandler(nullptr);
#endif
		defaultLogger = nullptr;
	}
}

void Logger_p::Logger::log(const QtMsgType type, const QString& message, const QString& file, const QString& function, const int line) {
	bool bToPrint{ false };
	switch (type) {
		case QtDebugMsg: {
			if (minLevel == QtDebugMsg) {
				bToPrint = true;
				break;
			}
		}
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
		case QtInfoMsg: {
			if (minLevel == QtDebugMsg || minLevel == QtInfoMsg) {
				bToPrint = true;
				break;
			}
		}
#endif
		case QtWarningMsg: {
			if (minLevel == QtDebugMsg ||
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
				minLevel == QtInfoMsg ||
#endif
				minLevel == QtWarningMsg) {
				bToPrint = true;
				break;
			}
		}
		case QtCriticalMsg: {
			if (minLevel == QtDebugMsg ||
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
				minLevel == QtInfoMsg ||
#endif
				minLevel == QtWarningMsg || minLevel == QtCriticalMsg) {
				bToPrint = true;
				break;
			}
		}
		case QtFatalMsg: {
			bToPrint = true;
			break;
		}
		default: break;
	}

	mutex.lock();
	if (bufferSize > 0) {
		if (!buffers.hasLocalData()) {
			buffers.setLocalData(new QList<LogMessage*>());
		}
		QList<LogMessage*>* buffer = buffers.localData();
		const auto logMessage = new LogMessage(type, message, logVars.localData(), file, function, line);
		buffer->append(logMessage);
		if (buffer->size() > bufferSize) {
			delete buffer->takeFirst();
		}
		if (bToPrint) {
			while (!buffer->isEmpty()) {
				const auto log_message = buffer->takeFirst();
				write(log_message);
				delete log_message;
			}
		}
	} else {
		if (bToPrint) {
			const auto log_message = new LogMessage(type, message, logVars.localData(), file, function, line);
			write(log_message);
			delete log_message;
		}
	}
	mutex.unlock();
}

void Logger_p::Logger::installMsgHandler() {
	defaultLogger = this;
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	qInstallMessageHandler(msgHandler5);
#else
	qInstallMsgHandler(msgHandler4);
#endif
}

void Logger_p::Logger::set(const QString& name, const QString& value) {
	mutex.lock();
	if (!logVars.hasLocalData()) {
		logVars.setLocalData(new QHash<QString, QString>());
	}
	logVars.localData()->insert(name, value);
	mutex.unlock();
}

void Logger_p::Logger::clear(const bool buffer, const bool variables) {
	mutex.lock();
	if (buffer && buffers.hasLocalData()) {
		QList<LogMessage*>* log_messages = buffers.localData();
		while (log_messages && !log_messages->isEmpty()) {
			const auto logMessage = log_messages->takeFirst();
			delete logMessage;
		}
	}
	if (variables && logVars.hasLocalData()) {
		logVars.localData()->clear();
	}
	mutex.unlock();
}

void Logger_p::Logger::write(const LogMessage* logMessage) {
	fputs(qPrintable(logMessage->toString(msgFormat, timestampFormat)), stderr);
	fflush(stderr);
}

void Logger_p::Logger::msgHandler(const QtMsgType type, const QString& message, const QString& file, const QString& function, const int line) {
	// 防止多个线程同时调用这个方法, 但是允许递归调用，这是防止死锁所必需的
	recursiveMutex.lock();
	// 当递归调用此方法时退回到 stderr
	if (defaultLogger && nonRecursiveMutex.tryLock()) {
		defaultLogger->log(type, message, file, function, line);
		nonRecursiveMutex.unlock();
	} else {
		fputs(qPrintable(message), stderr);
		fflush(stderr);
	}

	// 记录一个致命消息后中止程序
	if (type == QtFatalMsg) {
		abort();
	}
	recursiveMutex.unlock();
}

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
void Logger_p::Logger::msgHandler5(const QtMsgType type, const QMessageLogContext& context, const QString& message) {
	Q_UNUSED(context)
	msgHandler(type, message, context.file, context.function, context.line);
}
#else
void Logger_p::Logger::msgHandler4(const QtMsgType type, const char* message) {
	msgHandler(type,message);
}
#endif
