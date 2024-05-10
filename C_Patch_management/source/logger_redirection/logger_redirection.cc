#include "logger_redirection.hpp"

#include <QDateTime>
#include <QDir>
#include <QMutexLocker>
#include <global/cglobal.h>

LoggerRedirection* LoggerRedirection::m_instance = nullptr;
QMutex LoggerRedirection::m_mutex;

LoggerRedirection* LoggerRedirection::getInstance() {
	QMutexLocker locker(&m_mutex);
	if (!m_instance) {
		m_instance = new LoggerRedirection();
	}
	return m_instance;
}

void LoggerRedirection::install(const QString& logDirpath) {
	m_logdirpath = logDirpath;
	if (const QDir dir(logDirpath); !dir.exists() && !dir.mkpath(".")) {
		qDebug() << QString("create log dir success: %1").arg(logDirpath);
	}

	// 打开日志输出文件（不存在则创建并打开
	this->openTheLogFile();
	// 安装消息处理函数
	// 此句执行后，qDebug,qInfo等才会输出到文件
	qInstallMessageHandler(customMessageHandler);

	qInfo() << "____________________________ log output device create success ____________________________";
}

void LoggerRedirection::uninstall() {
	qInstallMessageHandler(nullptr);
}

void LoggerRedirection::deletelog() const {
	if (m_logdirpath.isEmpty()) {
		return;
	}
	const QDir dir(m_logdirpath);
	QFileInfoList infoList = dir.entryInfoList(QDir::Files);
	for (auto& info : infoList) {
		// 将文件创建时间与过期时间作比较，如果创建时间小于过期时间，则删除（代码是一个月期限）
		if (info.birthTime() <= QDateTime::currentDateTime().addMonths(-1)) {
			QFile::setPermissions(m_logdirpath + QDir::separator() + info.fileName(), QFileDevice::ReadOwner | QFileDevice::WriteOwner);
			if (QFile::remove(m_logdirpath + QDir::separator() + info.fileName())) {
				qDebug() << "delete log file success! --> " << info.fileName();
			} else {
				qDebug() << "delete log file fail! --> " << info.fileName();
			}
		}
	}
}

void LoggerRedirection::customMessageHandler(const QtMsgType msgType, const QMessageLogContext& context, const QString& message) {
	getInstance()->outPutMsg(msgType, context, message);
}

LoggerRedirection::LoggerRedirection(QObject* parent) : QObject(parent) {
}

LoggerRedirection::~LoggerRedirection() {
	if (m_curLogFile.isOpen()) {
		m_curLogFile.close();
	}
	qInfo() << "Log device free";
}

void LoggerRedirection::outPutMsg(const QtMsgType msgType, const QMessageLogContext& context, const QString& message) {
	QString type{};
	switch (msgType) {
		case QtDebugMsg: {
			type = QString("Debug");
			break;
		}
		case QtWarningMsg: {
			type = QString("Warning");
			break;
		}
		case QtCriticalMsg: {
			type = QString("Critical");
			break;
		}
		case QtFatalMsg: {
			type = QString("Fatal");
			break;
		}
		case QtInfoMsg: {
			type = QString("Info");
			break;
		}
		default: break;
	}

	m_mutex.lock();
	auto contextInfo = QString("[File:(%1), Line:(%2), Function:(%3)]:").arg(context.file).arg(context.line).arg(context.function);
	const auto curdatetime = QDateTime::currentDateTime();
	auto curdate = curdatetime.date().toString("yyyy-MM-dd");
	auto curtime = curdatetime.time().toString("hh:mm:ss");

	if (m_curLogFile.isOpen()) {
		const bool bFileSizeLarge = m_curLogFile.size() >= LOG_MAXSIZE;

		// 当前时间过了今天的24点到达另一天，或者超过单个日志文件最大值，切换日志输出文件
		if (const bool bNextDate = curdate.compare(m_curLogFileDate, Qt::CaseInsensitive) == 0; bFileSizeLarge || bNextDate) {
			m_curLogFile.close();
			this->openTheLogFile();
		}
	}

	const auto logMsg = QString("[%1 %2] %3: %4 %5").arg(curdate, curtime, type, contextInfo, message);
	this->saveLog(logMsg);
	m_mutex.unlock();
}

void LoggerRedirection::saveLog(const QString& message) {
	if (m_curLogFile.isOpen()) {
		QTextStream out(&m_curLogFile);
		out << message << "\r\n";
		m_curLogFile.flush();
	}
}

void LoggerRedirection::openTheLogFile() {
	int i = 1;
	m_curLogFileDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
	if (m_logdirpath.isEmpty()) {
		return qDebug() << "Log dir path is empty", void();
	}

	const QString fileName = m_logdirpath + QDir::separator() + m_curLogFileDate + "_log"; // 以天为单位给文件命名
	QString fileNameRight{};                                                               // 文件名右侧的序号
	QString fileNameLast = fileName + ".log";                                              // 最后生成的文件名
	m_curLogFile.setFileName(fileNameLast);
	while (m_curLogFile.size() >= LOG_MAXSIZE) {
		fileNameRight = QString("_%1.log").arg(i);
		fileNameLast = fileName + fileNameRight;
		m_curLogFile.setFileName(fileNameLast);
		i++;
	}

	if (!m_curLogFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
		return qDebug() << "Open log file failed", void();
	}
}
