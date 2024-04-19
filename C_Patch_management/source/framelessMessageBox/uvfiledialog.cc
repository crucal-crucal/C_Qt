#include "uvfiledialog.h"

CUVFileBase::CUVFileBase(QString strRegisterName, QWidget* parent, const QString& caption, const QString& directory, const QString& filter) :
	CUVBaseDialog(parent), m_pFileDialog(new QFileDialog(this, caption, directory, filter)), m_strRegisterName(std::move(strRegisterName)) {
	setTitle(caption);
	init();
	setObjectName("CUVFileBase");
}

CUVFileBase::~CUVFileBase() {
	if (!m_strRegisterName.isEmpty()) {
		QSettings fileDialogState("crucal", "C_Patch_management");
		QByteArray byState = m_pFileDialog->saveState().toBase64();
		fileDialogState.setValue(QString("client/%1").arg(m_strRegisterName), byState);
	}
}

// 设置文件对话框中的指定标签的文本内容
[[maybe_unused]] void CUVFileBase::setLabelText(QFileDialog::DialogLabel label, const QString& strText) {
	m_pFileDialog->setLabelText(label, strText);
}

// 设置文件对话框过滤器，限制显示的文件类型
[[maybe_unused]] void CUVFileBase::setFilter(QDir::Filters filters) {
	m_pFileDialog->setFilter(filters);
}

// 设置对话框的工作模式
void CUVFileBase::setFileMode(QFileDialog::FileMode mode) {
	m_pFileDialog->setFileMode(mode);
}

// 设置对话框的接受模式
void CUVFileBase::setAcceptMode(QFileDialog::AcceptMode mode) {
	m_pFileDialog->setAcceptMode(mode);
}

[[maybe_unused]] QFileDialog::AcceptMode CUVFileBase::acceptMode() const {
	return m_pFileDialog->acceptMode();
}

// 设置默认文件后缀
[[maybe_unused]] void CUVFileBase::setDefaultSuffix(const QString& suffix) {
	m_pFileDialog->setDefaultSuffix(suffix);
}

[[maybe_unused]] QString CUVFileBase::defaultSuffix() const {
	return m_pFileDialog->defaultSuffix();
}

[[maybe_unused]] void CUVFileBase::setDirectory(const QString& directory) {
	m_pFileDialog->setDirectory(directory);
}

[[maybe_unused]] inline void CUVFileBase::setDirectory(const QDir& directory) {
	m_pFileDialog->setDirectory(directory);
}

[[maybe_unused]] QDir CUVFileBase::directory() const {
	return m_pFileDialog->directory();
}

void CUVFileBase::setDirectoryUrl(const QUrl& directory) {
	m_pFileDialog->setDirectoryUrl(directory);
}

[[maybe_unused]] void CUVFileBase::setViewMode(QFileDialog::ViewMode mode) {
	m_pFileDialog->setViewMode(mode);
}

[[maybe_unused]] QUrl CUVFileBase::directoryUrl() const {
	return m_pFileDialog->directoryUrl();
}

// 指定选中默认文件
[[maybe_unused]] void CUVFileBase::selectFile(const QString& filename) {
	m_pFileDialog->selectFile(filename);
}

QStringList CUVFileBase::selectedFiles() const {
	return m_pFileDialog->selectedFiles();
}

void CUVFileBase::init() {
	setTitleBtnRole(CUVBaseDialog::CloseRole);
	m_pFileDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
	m_pFileDialog->setOption(QFileDialog::DontUseNativeDialog);
	m_pFileDialog->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
	m_pFileDialog->setLabelText(QFileDialog::Accept, tr("IDS_SELECT"));
	m_pFileDialog->setLabelText(QFileDialog::Reject, tr("IDS_CANCEL"));
	m_pFileDialog->setLabelText(QFileDialog::LookIn, tr("IDS_DIRECTORY"));
	m_pFileDialog->setLabelText(QFileDialog::FileName, tr("IDS_NAME"));
	m_pFileDialog->setLabelText(QFileDialog::FileType, tr("IDS_TYPE"));

	connect(m_pFileDialog, &QFileDialog::accepted, this, &CUVFileBase::accept);
	connect(m_pFileDialog, &QFileDialog::rejected, this, &CUVFileBase::reject);
	setContent(m_pFileDialog);

	QSettings fileDialogState("crucal", "C_Patch_management");
	QByteArray byHistoryState = QByteArray::fromBase64(fileDialogState.value(QString("client/%1").arg(m_strRegisterName)).toByteArray());
	m_pFileDialog->restoreState(byHistoryState);
}

QString CUVFileBase::getOpenFileName(QString* selectedFilter, QFileDialog::Options options) {
	m_pFileDialog->setOptions(options);
	if (selectedFilter) {
		m_pFileDialog->selectNameFilter(*selectedFilter);
	}
	if (this->exec()) {
		if (selectedFilter) {
			*selectedFilter = m_pFileDialog->selectedNameFilter();
		}
		return this->selectedFiles().first();
	}

	return {};
}

QUrl CUVFileBase::getOpenFileUrl(const QUrl& dir, QString* selectedFilter,
								 QFileDialog::Options options, const QStringList& supportedSchemes) {
	this->setDirectoryUrl(dir);
	m_pFileDialog->setOptions(options);
	m_pFileDialog->setSupportedSchemes(supportedSchemes);
	if (selectedFilter) {
		m_pFileDialog->selectNameFilter(*selectedFilter);
	}
	if (this->exec()) {
		if (selectedFilter) {
			*selectedFilter = m_pFileDialog->selectedNameFilter();
		}
		return m_pFileDialog->selectedUrls().first();
	}
	return {};
}

QString CUVFileBase::getSaveFileName(QString* selectedFilter, QFileDialog::Options options) {
	m_pFileDialog->setAcceptMode(QFileDialog::AcceptSave);
	m_pFileDialog->setOptions(options);
	if (selectedFilter) {
		m_pFileDialog->selectNameFilter(*selectedFilter);
	}
	if (this->exec()) {
		if (selectedFilter) {
			*selectedFilter = m_pFileDialog->selectedNameFilter();
		}
		return this->selectedFiles().first();
	}

	return {};
}

QUrl CUVFileBase::getSaveFileUrl(const QUrl& dir, QString* selectedFilter,
								 QFileDialog::Options options, const QStringList& supportedSchemes) {
	this->setDirectoryUrl(dir);
	m_pFileDialog->setAcceptMode(QFileDialog::AcceptSave);
	m_pFileDialog->setOptions(options);
	m_pFileDialog->setSupportedSchemes(supportedSchemes);
	if (selectedFilter) {
		m_pFileDialog->selectNameFilter(*selectedFilter);
	}
	if (this->exec()) {
		if (selectedFilter) {
			*selectedFilter = m_pFileDialog->selectedNameFilter();
		}
		return this->selectedFiles().first();
	}

	return {};
}

QString CUVFileBase::getExistingDirectory(QFileDialog::Options options) {
	/*
	 * @note
	 * 设置目录模式必须在前，因为默认设置 QFileDialog::ShowDirsOnly 为 Options时，默认同时显示文件和目录
	 * 仅显示目录仅在目录模式下有效
	 */
	this->setFileMode(QFileDialog::Directory);
	m_pFileDialog->setOptions(options);
	if (this->exec()) {
		return this->selectedFiles().first();
	}
	return {};
}

QString CUVFileBase::getExistingDirectoryUrl(const QUrl& dir, QFileDialog::Options options, const QStringList& supportedSchemes) {
	this->setFileMode(QFileDialog::Directory);
	m_pFileDialog->setOptions(options);
	m_pFileDialog->setSupportedSchemes(supportedSchemes);
	this->setDirectoryUrl(dir);
	if (this->exec()) {
		return this->selectedFiles().first();
	}
	return {};
}

QStringList CUVFileBase::getOpenFileNames(QString* selectedFilter, QFileDialog::Options options) {
	m_pFileDialog->setOptions(options);
	if (selectedFilter) {
		m_pFileDialog->selectNameFilter(*selectedFilter);
	}
	if (this->exec()) {
		if (selectedFilter) {
			*selectedFilter = m_pFileDialog->selectedNameFilter();
		}
		return this->selectedFiles();
	}

	return {};
}

QList<QUrl> CUVFileBase::getOpenFileUrls(const QUrl& dir, QString* selectedFilter,
										 QFileDialog::Options options, const QStringList& supportedSchemes) {
	this->setDirectoryUrl(dir);
	m_pFileDialog->setOptions(options);
	m_pFileDialog->setSupportedSchemes(supportedSchemes);
	if (selectedFilter) {
		m_pFileDialog->selectNameFilter(*selectedFilter);
	}
	if (this->exec()) {
		if (selectedFilter) {
			*selectedFilter = m_pFileDialog->selectedNameFilter();
		}
		return m_pFileDialog->selectedUrls();
	}
	return {};
}

void CUVFileBase::getOpenFileContent(const QString& nameFilter,
									 const std::function<void(const QString&, const QByteArray&)>& fileContentsReady) {
	this->setFileMode(QFileDialog::ExistingFile);
	m_pFileDialog->setNameFilter(nameFilter);

	connect(m_pFileDialog, &QFileDialog::fileSelected, [=](const QString& filePath) {
		QFile file(filePath);
		if (file.open(QIODevice::ReadOnly)) {
			QByteArray content = file.readAll();
			file.close();
			fileContentsReady(filePath, content);
		} else {
			fileContentsReady(filePath, QByteArray()); // Pass an empty QByteArray to indicate failure
		}
	});
	this->exec();
}

void CUVFileBase::saveFileContent(const QByteArray& fileContent, const QString& fileNameHint) {
	m_pFileDialog->setWindowTitle(tr("Save File"));
	this->setAcceptMode(QFileDialog::AcceptSave);
	m_pFileDialog->selectFile(fileNameHint);
	if (this->exec() == QDialog::Accepted) {
		QString fileName = m_pFileDialog->selectedFiles().first();
		QFile file(fileName);
		if (file.open(QIODevice::WriteOnly)) {
			file.write(fileContent);
			file.close();
		}
	}
}

// CUVFileDialog
[[maybe_unused]] CUVFileDialog::CUVFileDialog(QWidget* parent) : CUVBaseDialog(parent) {
}

CUVFileDialog::~CUVFileDialog() = default;

[[maybe_unused]] QString CUVFileDialog::getOpenFileName(QWidget* parent, const QString& caption,
														const QString& dir, const QString& filter,
														QString* selectedFilter,
														QFileDialog::Options options) {
	CUVFileBase file_base(tr("C_Patch_management"), parent, caption, dir, filter);
	return file_base.getOpenFileName(selectedFilter, options);
}

[[maybe_unused]] QUrl CUVFileDialog::getOpenFileUrl(QWidget* parent, const QString& caption,
													const QUrl& dir, const QString& filter,
													QString* selectedFilter,
													QFileDialog::Options options,
													const QStringList& supportedSchemes) {
	CUVFileBase file_base(tr("C_Patch_management"), parent, caption, "", filter);
	return file_base.getOpenFileUrl(dir, selectedFilter, options, supportedSchemes);
}

QString CUVFileDialog::getSaveFileName(QWidget* parent, const QString& caption,
									   const QString& dir, const QString& filter,
									   QString* selectedFilter,
									   QFileDialog::Options options) {
	CUVFileBase file_base(tr("C_Patch_management"), parent, caption, dir, filter);
	return file_base.getSaveFileName(selectedFilter, options);
}

[[maybe_unused]] QUrl CUVFileDialog::getSaveFileUrl(QWidget* parent, const QString& caption,
													const QUrl& dir, const QString& filter,
													QString* selectedFilter,
													QFileDialog::Options options,
													const QStringList& supportedSchemes) {
	CUVFileBase file_base(tr("C_Patch_management"), parent, caption, "", filter);
	return file_base.getSaveFileUrl(dir, selectedFilter, options, supportedSchemes);
}

QString CUVFileDialog::getExistingDirectory(QWidget* parent, const QString& caption,
											const QString& dir,
											QFileDialog::Options options) {
	CUVFileBase file_base(tr("C_Patch_management"), parent, caption, dir);
	return file_base.getExistingDirectory(options);
}

[[maybe_unused]] QUrl CUVFileDialog::getExistingDirectoryUrl(QWidget* parent, const QString& caption,
															 const QUrl& dir,
															 QFileDialog::Options options,
															 const QStringList& supportedSchemes) {
	CUVFileBase file_base(tr("C_Patch_management"), parent, caption);
	return file_base.getExistingDirectoryUrl(dir, options, supportedSchemes);
}

[[maybe_unused]] QStringList CUVFileDialog::getOpenFileNames(QWidget* parent, const QString& caption,
															 const QString& dir, const QString& filter,
															 QString* selectedFilter,
															 QFileDialog::Options options) {
	CUVFileBase file_base(tr("C_Patch_management"), parent, caption, dir, filter);
	return file_base.getOpenFileNames(selectedFilter, options);
}

[[maybe_unused]] QList<QUrl> CUVFileDialog::getOpenFileUrls(QWidget* parent, const QString& caption,
															const QUrl& dir, const QString& filter,
															QString* selectedFilter,
															QFileDialog::Options options,
															const QStringList& supportedSchemes) {
	CUVFileBase file_base(tr("C_Patch_management"), parent, caption, "", filter);
	return file_base.getOpenFileUrls(dir, selectedFilter, options, supportedSchemes);
}

[[maybe_unused]] void CUVFileDialog::getOpenFileContent(const QString& nameFilter,
														const std::function<void(const QString&, const QByteArray&)>& fileContentsReady) {
	CUVFileBase file_base(tr("C_Patch_management"));
	return file_base.getOpenFileContent(nameFilter, fileContentsReady);
}

[[maybe_unused]] void CUVFileDialog::saveFileContent(const QByteArray& fileContent,
													 const QString& fileNameHint) {
	CUVFileBase file_base(tr("C_Patch_management"));
	return file_base.saveFileContent(fileContent, fileNameHint);
}