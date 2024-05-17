#pragma once

#include <QDateTime>
#include <QHash>
#include "logger_p_global.hpp"

namespace Logger_p {
/*
 * @brief: 一条日志消息
 * 以下变量可以在消息和 msgFormat 中使用:
 * - {timestamp} 创建日期和时间
 * - {typeNr} 数字格式的消息类型(0-3)
 * - {type} 字符串格式的消息类型(DEBUG, WARNING, CRITICAL, FATAL)
 * - {thread} 线程ID号
 * - {message} 消息文本
 * - {xxx} 用于任何用户定义的记录器变量
 * - {file} 文件名
 * - {function} 函数名
 * - {line} 行号
 */
class LOGGER_P_EXPORT LogMessage {
	Q_DISABLE_COPY(LogMessage)

public:
	/*
	 * @param: type 消息类型
	 * @param: message 消息文本
	 * @param: logVars 用户定义的记录器变量，允许为0
	 * @param: file 文件名
	 * @param: function 函数名
	 * @param: line 行号
	 */
	LogMessage(QtMsgType type, QString message, const QHash<QString, QString>* logVars, QString file, QString function, int line);
	/*
	 * @note: 将消息转换为字符串
	 * @param: msgFormat装饰格式，可能包含变量和静态文本
	 * @param: timestampFormat时间戳格式。
	 * @return: 格式化后的字符串
	 */
	[[nodiscard]] QString toString(const QString& msgFormat, const QString& timestampFormat) const;
	/*
	 * @note: 获取消息类型
	 */
	[[nodiscard]] QtMsgType getType() const;

private:
	QHash<QString, QString> m_logVars{}; // 用户定义的记录器变量
	QDateTime m_timestamp{};             // 创建日期和时间
	QtMsgType m_type{};                  // 消息类型
	Qt::HANDLE m_threadId{};             // 线程ID号
	QString m_message{};                 // 消息文本
	QString m_file{};                    // 文件名
	QString m_function{};                // 函数名
	int m_line{};                        // 行号
};
}
