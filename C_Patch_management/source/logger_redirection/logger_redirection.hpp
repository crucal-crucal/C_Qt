#pragma once

#include <QDebug>
#include <QFile>
#include <QMutexLocker>
#include <QObject>
#include <QtWidgets/QApplication>

#ifdef LOGGER_REDIRECTION_LIB
#define LOGGER_REDIRECTIONEXPORT Q_DECL_EXPORT
#else
#define LOGGER_REDIRECTIONEXPORT Q_DECL_IMPORT
#endif

/*
 * @brief: 用于重定向qDebug, qWarning, qInfo等函数的输出，将输出信息保存到日志文件
 */
class LOGGER_REDIRECTIONEXPORT LoggerRedirection final : public QObject {
public:
	static LoggerRedirection* getInstance();

	void install(const QString& logDirpath = QApplication::applicationDirPath() + "/log"); // 安装信息处理函数
	static void uninstall();                                                               // 卸载信息处理函数
	void deletelog() const;                                                                // 删除过期日志

protected:
	// 此函数用于注册
	static void customMessageHandler(QtMsgType msgType, const QMessageLogContext& context, const QString& message);

private:
	explicit LoggerRedirection(QObject* parent = nullptr);
	~LoggerRedirection() override;

public:
	LoggerRedirection(const LoggerRedirection& sig) = delete;
	LoggerRedirection& operator=(const LoggerRedirection& sig) = delete;

private:
	static LoggerRedirection* m_instance;
	static QMutex m_mutex;

	QString m_logdirpath{};
	QFile m_curLogFile{};
	QString m_curLogFileDate{}; // 当前日志所属时间，防止在午夜24点刚过，需要更换日志输出文件

public:
	/*
	 * @note: 通过调试信息保存到日志文件
	 * @param: type 调试信息类型或级别( qdebug, qwaring, qinfo...
	 * @param: context 调试信息所处文本，可使用context.file和context.line获取文本所处行数及所处文件路径，以及使用context.function获取文本所处函数名
	 * @param: message 调试信息内容
	 */
	void outPutMsg(QtMsgType msgType, const QMessageLogContext& context, const QString& message);

	/*
	 * @note: 根据调试信息以及日期，保存到相应的文件，在保存文件前需要判断文件大小是否大于自定义值，如果大于，则按照序号从小到大新建一个
	 */
	void saveLog(const QString& message);

	/*
	 * @note: 打开日志文件
	 */
	void openTheLogFile();
};
