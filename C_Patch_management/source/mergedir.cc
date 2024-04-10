#include "mergedir.h"

#include <utility>
#include "logger/Logger.h"

CMergeDir::CMergeDir(QStringList _filePaths, QString _outputFilePath, QString dirname, QObject* parent)
	: QRunnable(), QObject(parent), m_sourcefilePaths(std::move(_filePaths)), m_dirname(std::move(dirname)),
	  m_outputFilePath(std::move(_outputFilePath)) {}

CMergeDir::~CMergeDir() = default;

void CMergeDir::run() {
	QDir output(m_outputFilePath);
	if (!output.exists() && !output.mkpath(".")) {
		QString msg = tr("Unable to create directory ") + m_outputFilePath;
		Logger::instance().logError(msg);
		return;
	}

	QMutexLocker locker_file(&m_mutexFile);
	for (auto& filePath : m_sourcefilePaths) {
		// 截取包含“Patch”的位置后的目录路径
		int patchIndex = filePath.indexOf("/" + m_dirname);
		if (patchIndex != -1) {
			// 获取子目录的长度
			int startIndex = patchIndex + QString("/" + m_dirname + "/").length();
			int endIndex = filePath.indexOf('/', startIndex);
			if (endIndex == -1) {
				endIndex = filePath.size();
			}
			int subindex = filePath.midRef(startIndex, endIndex - startIndex).length();
			// 截取子目录路径
			QString relativePath = filePath.mid(patchIndex + subindex + QString("/" + m_dirname).length() + 2);
			// 构建目标文件路径
			QString destFilePath = output.filePath(relativePath);
			// 确保目标文件所在的目录已存在
			QDir destDir(QFileInfo(destFilePath).absolutePath());

			if (!destDir.exists()) {
				if (!destDir.mkpath(".")) {
					QString msg = tr("Unable to create directory ") + destDir.path();
					Logger::instance().logError(msg);
					continue;
				}
			}
			// 将文件复制到目标文件夹中
			if (!QFile::copy(filePath, destFilePath)) {
				QString msg = tr("Unable to copy file ") + filePath + tr(" to ") + destFilePath;
				Logger::instance().logError(msg);
			}
			++currentFile;
			emit progressUpdated(currentFile);
		}
	}
}
