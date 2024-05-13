#pragma once

#include <QSettings>
#include "logger_p_global.hpp"
#include "logger.hpp"
#include "filelogger.hpp"

namespace Logger_p {
class LOGGER_P_EXPORT DualFileLogger final : public Logger {
	Q_OBJECT
	Q_DISABLE_COPY(DualFileLogger)

public:
	explicit DualFileLogger(QSettings* firstSettings, QSettings* secondSettings, int refreshInterval = 10000, QObject* parent = nullptr);
	~DualFileLogger() override;

	void log(QtMsgType type, const QString& message, const QString& file, const QString& function, int line) override;
	void clear(bool buffer, bool variables) override;

private:
	FileLogger* m_firstLogger{ nullptr };
	FileLogger* m_seconfLogger{ nullptr };
};
}
