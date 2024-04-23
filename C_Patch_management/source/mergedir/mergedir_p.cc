#include "mergedir_p.h"

CMergeDir_p::CMergeDir_p(QStringList _filePaths, QString _outputFilePath, QString dirname, QObject* parent)
: QThread(parent), m_sourcefilePaths(std::move(_filePaths)), m_outputFilePath(std::move(_outputFilePath)),
m_dirname(std::move(dirname)) {
	this->setAutoDelete(true);
}

CMergeDir_p::~CMergeDir_p() = default;

void CMergeDir_p::run() {
	const QDir output(m_outputFilePath);
	if (!output.exists() && !output.mkpath(".")) {
		const QString msg = tr("Unable to create directory ") + m_outputFilePath;
		Logger::instance().logError(msg);
		return;
	}

	qint64 currentFile{ 0 };
	for (auto& filePath : m_sourcefilePaths) {
		// 截取包含 m_dirname 的位置后的目录路径
		if (const int patchIndex = filePath.indexOf("/" + m_dirname); patchIndex != -1) {
			// 获取子目录的长度
			const int startIndex = patchIndex + QString("/" + m_dirname + "/").length();
			int endIndex = filePath.indexOf('/', startIndex);
			if (endIndex == -1) {
				endIndex = filePath.size();
			}
			const int subindex = filePath.midRef(startIndex, endIndex - startIndex).length();
			// 截取子目录路径
			QString relativePath = filePath.mid(patchIndex + subindex + QString("/" + m_dirname).length() + 2);
			// 构建目标文件路径
			QString destFilePath = output.filePath(relativePath);

			QMutexLocker locker(&m_mutex);
			// 确保目标文件所在的目录已存在
			if (QDir destDir(QFileInfo(destFilePath).absolutePath()); !destDir.exists()) {
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
