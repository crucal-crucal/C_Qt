#pragma once

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QRunnable>
#include <QDir>
#include <QDateTime>
#include <QMutex>
#include <QStack>
#include <QWaitCondition>
#include <utility>

#include "logger/Logger.h"

#ifdef MERGEDIR_P_LIB
#define MERGEDIR_P_EXPORT Q_DECL_EXPORT
#else
#define MERGEDIR_P_EXPORT Q_DECL_IMPORT
#endif

class MERGEDIR_P_EXPORT CMergeDir_p : public QThread, public QRunnable {
  Q_OBJECT

  public:
	CMergeDir_p(QStringList _filePaths, QString _outputFilePath, QString dirname, QObject* parent = nullptr);
	~CMergeDir_p() override;

  signals:
	void progressUpdated(qint64 value);

  protected:
	void run() override;

  private:
	QMutex m_mutex{};
	QStringList m_sourcefilePaths;
	QString m_outputFilePath{};
	QString m_dirname{};

	QMutex m_mutexProcess{};
};