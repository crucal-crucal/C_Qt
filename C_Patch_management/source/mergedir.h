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

class CMergeDir : public QThread, public QRunnable {
  Q_OBJECT

  public:
	CMergeDir(QStringList _filePaths, QString _outputFilePath, QString dirname, QObject* parent = nullptr);
	~CMergeDir() override;

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