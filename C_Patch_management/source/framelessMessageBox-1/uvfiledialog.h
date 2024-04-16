#pragma once

#include <QFileDialog>
#include <QApplication>
#include <QSettings>
#include <QDebug>
#include "uvbasedialog.h"

#ifdef FRAMELESSFILEDIALOG_LIB
#define FRAMELESSFILEDIALOG_EXPORT Q_DECL_EXPORT
#else
#define FRAMELESSFILEDIALOG_EXPORT Q_DECL_IMPORT
#endif

class FRAMELESSFILEDIALOG_EXPORT CUVFileBase : public CUVBaseDialog {
  Q_OBJECT
  public:
	explicit CUVFileBase(QString strRegisterName, QWidget* parent = Q_NULLPTR,
						 const QString& caption = QString(),
						 const QString& directory = QString(),
						 const QString& filter = QString());
	~CUVFileBase() override;
  public:
	[[maybe_unused]] void setLabelText(QFileDialog::DialogLabel label, const QString& strText);
	[[maybe_unused]] void setFilter(QDir::Filters filters = QDir::AllEntries | QDir::NoDotAndDotDot);
	void setFileMode(QFileDialog::FileMode mode = QFileDialog::ExistingFile);

	void setAcceptMode(QFileDialog::AcceptMode mode = QFileDialog::AcceptOpen);
	[[maybe_unused]] [[nodiscard]] QFileDialog::AcceptMode acceptMode() const;

	[[maybe_unused]] void setDefaultSuffix(const QString& suffix);
	[[maybe_unused]] [[nodiscard]] QString defaultSuffix() const;

	[[maybe_unused]] void setDirectory(const QString& directory);
	[[maybe_unused]] inline void setDirectory(const QDir& directory);
	[[maybe_unused]] [[nodiscard]] QDir directory() const;

	void setDirectoryUrl(const QUrl& directory);
	[[maybe_unused]] [[nodiscard]] QUrl directoryUrl() const;

	[[maybe_unused]] void setViewMode(QFileDialog::ViewMode mode = QFileDialog::Detail);

	[[maybe_unused]] void selectFile(const QString& filename);
	[[nodiscard]] QStringList selectedFiles() const;

	QString getOpenFileName(QString* selectedFilter = nullptr,
							QFileDialog::Options options = QFileDialog::Options());

	QUrl getOpenFileUrl(const QUrl& dir = QUrl(),
						QString* selectedFilter = nullptr,
						QFileDialog::Options options = QFileDialog::Options(),
						const QStringList& supportedSchemes = QStringList());

	QString getSaveFileName(QString* selectedFilter = nullptr,
							QFileDialog::Options options = QFileDialog::Options());

	QUrl getSaveFileUrl(const QUrl& dir = QUrl(),
						QString* selectedFilter = nullptr,
						QFileDialog::Options options = QFileDialog::Options(),
						const QStringList& supportedSchemes = QStringList());

	QString getExistingDirectory(QFileDialog::Options options = QFileDialog::ShowDirsOnly);

	QString getExistingDirectoryUrl(const QUrl& dir = QUrl(),
									QFileDialog::Options options = QFileDialog::ShowDirsOnly,
									const QStringList& supportedSchemes = QStringList());

	QStringList getOpenFileNames(QString* selectedFilter = nullptr,
								 QFileDialog::Options options = QFileDialog::Options());

	QList<QUrl> getOpenFileUrls(const QUrl& dir = QUrl(),
								QString* selectedFilter = nullptr,
								QFileDialog::Options options = QFileDialog::Options(),
								const QStringList& supportedSchemes = QStringList());

	void getOpenFileContent(const QString& nameFilter,
							const std::function<void(const QString&, const QByteArray&)>& fileContentsReady);

	void saveFileContent(const QByteArray& fileContent, const QString& fileNameHint = QString());

  private:
	void init();
  private:
	QFileDialog* m_pFileDialog{nullptr};
	QString m_strRegisterName{""};
};

class FRAMELESSFILEDIALOG_EXPORT CUVFileDialog : CUVBaseDialog {
  Q_OBJECT
  public:
	[[maybe_unused]] explicit CUVFileDialog(QWidget* parent = nullptr);
	~CUVFileDialog() override;

	[[maybe_unused]] static QString getOpenFileName(QWidget* parent = nullptr,
													const QString& caption = QString(),
													const QString& dir = QString(),
													const QString& filter = QString(),
													QString* selectedFilter = nullptr,
													QFileDialog::Options options = QFileDialog::Options());

	[[maybe_unused]] static QUrl getOpenFileUrl(QWidget* parent = nullptr,
												const QString& caption = QString(),
												const QUrl& dir = QUrl(),
												const QString& filter = QString(),
												QString* selectedFilter = nullptr,
												QFileDialog::Options options = QFileDialog::Options(),
												const QStringList& supportedSchemes = QStringList());

	static QString getSaveFileName(QWidget* parent = nullptr,
								   const QString& caption = QString(),
								   const QString& dir = QString(),
								   const QString& filter = QString(),
								   QString* selectedFilter = nullptr,
								   QFileDialog::Options options = QFileDialog::Options());

	[[maybe_unused]] static QUrl getSaveFileUrl(QWidget* parent = nullptr,
												const QString& caption = QString(),
												const QUrl& dir = QUrl(),
												const QString& filter = QString(),
												QString* selectedFilter = nullptr,
												QFileDialog::Options options = QFileDialog::Options(),
												const QStringList& supportedSchemes = QStringList());

	static QString getExistingDirectory(QWidget* parent = nullptr,
										const QString& caption = QString(),
										const QString& dir = QString(),
										QFileDialog::Options options = QFileDialog::ShowDirsOnly);

	[[maybe_unused]] static QUrl getExistingDirectoryUrl(QWidget* parent = nullptr,
														 const QString& caption = QString(),
														 const QUrl& dir = QUrl(),
														 QFileDialog::Options options = QFileDialog::ShowDirsOnly,
														 const QStringList& supportedSchemes = QStringList());

	[[maybe_unused]] static QStringList getOpenFileNames(QWidget* parent = nullptr,
														 const QString& caption = QString(),
														 const QString& dir = QString(),
														 const QString& filter = QString(),
														 QString* selectedFilter = nullptr,
														 QFileDialog::Options options = QFileDialog::Options());

	[[maybe_unused]] static QList<QUrl> getOpenFileUrls(QWidget* parent = nullptr,
														const QString& caption = QString(),
														const QUrl& dir = QUrl(),
														const QString& filter = QString(),
														QString* selectedFilter = nullptr,
														QFileDialog::Options options = QFileDialog::Options(),
														const QStringList& supportedSchemes = QStringList());

	[[maybe_unused]] static void getOpenFileContent(const QString& nameFilter,
													const std::function<void(const QString&, const QByteArray&)>& fileContentsReady);

	[[maybe_unused]] static void saveFileContent(const QByteArray& fileContent, const QString& fileNameHint = QString());
};

