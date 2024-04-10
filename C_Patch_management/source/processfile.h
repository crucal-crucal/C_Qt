#pragma once

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

class ProcessFile : public QObject {
  Q_OBJECT
  public:
	explicit ProcessFile(QObject* parent = nullptr);
	~ProcessFile() override;

  signals:
	void finished(bool);

  public slots:
	bool copyAFile(const QString& sourceFile, const QString& destinationFile, bool bFailIfExists = false);

  private:
	static bool copyFileSystem(const QString& sourceFile, const QString& destinationFile);
	static bool createDirectory(const QString& directory, bool bFailIfExists = false);
};

class ThreadProcessFile : public QObject {
  Q_OBJECT
  public:
	explicit ThreadProcessFile(QObject* parent = nullptr);
	~ThreadProcessFile() override;

	void copyAFile(const QString& sourceFile, const QString& destinationFile, bool bFailIfExists = false);

  signals:
	void copyFile(const QString& sourceFile, const QString& destinationFile, bool bFailIfExists);
	void finished(bool);

  private:
	QThread* workerThread{nullptr};
};

class ThreadProcessList : public QObject {
	Q_OBJECT
  public:
	explicit ThreadProcessList(QObject* parent = nullptr);
	~ThreadProcessList() override;

	void setThreadNumer(int number);
	void startCopyFiles(const QStringList& srcfiles, const QString& dstfiles, bool bFailIfExists = false);

  public slots:
	void updateTaskCount(bool bSuccess);

  signals:
	void processProgress(qint64 nFinishedcount, qint64 nAllTaskcount);
	void finished(bool bSuccess);

  private:
	int m_nThreadNumber{1};
	int m_nTaskCount{};
	int m_nFinishedCount{};
	int m_nAllTaskcount{};
	bool m_bFailIfExists{false};
	QMutex m_mutex{};
	QStringList m_srcfiles{};
	QString m_dstfiles{};
};