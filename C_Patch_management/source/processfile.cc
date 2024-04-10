#include "processfile.h"

ProcessFile::ProcessFile(QObject* parent) : QObject(parent) {

}

ProcessFile::~ProcessFile() = default;

bool ProcessFile::copyAFile(const QString& sourceFile, const QString& destinationFile, bool bFailIfExists) {
	QFileInfo srcfile(sourceFile);
	if (!srcfile.exists()) {
		// log
		emit finished(false);
		return false;
	}

	QFileInfo dstfile(destinationFile);
	if (dstfile.exists()) {
		if (destinationFile == sourceFile || bFailIfExists) {
			// log
			emit finished(false);
			return false;
		}
		if (!QFile::remove(destinationFile)) {
			// log
            emit finished(false);
            return false;
		}
	}

	if (!createDirectory(destinationFile, true)) {
		// log
        emit finished(false);
        return false;
	}

	bool bRes{true};
	QFile src(sourceFile);
	QString dest = destinationFile;
	if (!src.copy(dest)) {
		bRes = false;
		// log
	}
	emit finished(bRes);
	return bRes;
}

bool ProcessFile::copyFileSystem(const QString& sourceFile, const QString& destinationFile) {
	bool bRes{true};
#ifdef Q_OS_WIN
	QFile source(sourceFile);
	const QString& dest(destinationFile);
	if (!source.copy(dest)) {
		bRes = false;
        // log
	}
#elif Q_OS_UNIX
	std::string command = "cp \"";
	command += sourceFile.toUtf8().constData();
	command += "\" \"";
	command += destinationFile.toUtf8().constData();
	command += "\"";
	bRes = system((char*)command.c_str()) != -1;
#endif
	return bRes;
}

bool ProcessFile::createDirectory(const QString& directory, bool bFailIfExists) {
	if (directory.isEmpty()) {
		return false;
	}

	QFileInfo dirt(directory);
	if (dirt.isDir()) {
		return true;
	}

	QString strDir(directory);
	if (bFailIfExists) {
		int idx = directory.lastIndexOf("/");
		strDir = directory.mid(0, idx);
	}

	QDir dir;
	return dir.mkpath(strDir);
}

// ThreadProcessFile
ThreadProcessFile::ThreadProcessFile(QObject* parent) : QObject(parent) {
	workerThread = new QThread;

	auto* worker = new ProcessFile();
	worker->moveToThread(workerThread);
	connect(workerThread, &QThread::finished, worker, &ProcessFile::deleteLater);
	connect(this, &ThreadProcessFile::copyFile, worker, &ProcessFile::copyAFile);
	connect(worker, &ProcessFile::finished, this, &ThreadProcessFile::finished);

	// 线程要主动释放
	connect(worker, &ProcessFile::finished, this, &ThreadProcessFile::deleteLater);

	workerThread->start();
}

ThreadProcessFile::~ThreadProcessFile() {
	workerThread->quit();
	workerThread->wait();
}

void ThreadProcessFile::copyAFile(const QString& sourceFile, const QString& destinationFile, bool bFailIfExists) {
	emit copyFile(sourceFile, destinationFile, bFailIfExists);
}

// ThreadProcessList
ThreadProcessList::ThreadProcessList(QObject* parent) : QObject(parent) {
	m_nThreadNumber = 1;
	m_nTaskCount = 0;
	m_nFinishedCount = 0;
	m_bFailIfExists = false;
}

ThreadProcessList::~ThreadProcessList() = default;

void ThreadProcessList::setThreadNumer(int number) {
	m_nThreadNumber = number;
}

void ThreadProcessList::startCopyFiles(const QStringList& srcfiles, const QString& dstfiles, bool bFailIfExists) {
	m_srcfiles = srcfiles;
	m_dstfiles = dstfiles;
	m_bFailIfExists = bFailIfExists;

	m_nAllTaskcount = m_srcfiles.size();
	int nTaskCount = std::min(m_nThreadNumber, m_nAllTaskcount);
	qDebug() << nTaskCount;
	for (int i = 0; i < nTaskCount; i++) {
		auto* tp = new ThreadProcessFile;
		connect(tp, &ThreadProcessFile::finished, this, &ThreadProcessList::updateTaskCount);
		m_mutex.lock();
		++m_nTaskCount;
		tp->copyAFile(m_srcfiles[0], dstfiles, m_bFailIfExists);
		m_srcfiles.pop_front();
//		m_dstfiles.pop_front();
		m_mutex.unlock();
	}
}

void ThreadProcessList::updateTaskCount(bool bSuccess) {
	m_mutex.lock();
	--m_nTaskCount;

	if (bSuccess) {
		++m_nFinishedCount;
	}

	emit processProgress(m_nFinishedCount, m_nAllTaskcount);
	if (m_nFinishedCount < m_nAllTaskcount && !m_srcfiles.empty()) {
		auto* tp = new ThreadProcessFile;
		connect(tp, &ThreadProcessFile::finished, this, &ThreadProcessList::updateTaskCount);
		++m_nTaskCount;
		tp->copyAFile(m_srcfiles[0], m_dstfiles, m_bFailIfExists);
		m_srcfiles.pop_front();
//		m_dstfiles.pop_front();
	} else if (!m_nTaskCount) {
		emit finished(m_nFinishedCount == m_nAllTaskcount);
	}
	m_mutex.unlock();
}
