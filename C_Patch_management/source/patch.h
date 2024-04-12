#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QHeaderView>
#include <QSystemTrayIcon>
#include <QRadioButton>
#include <QCheckBox>
#include <QTabWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QComboBox>
#include <QProgressBar>
#include <QLineEdit>
#include <QMenuBar>
#include <QTimer>
#include <QFileDialog>
#include <QTextCodec>
#include <QTextCursor>
#include <QThreadPool>
#include <QDir>
#include <QComboBox>
#include <QSet>
#include <QDirIterator>
#include <QProcess>

#include "C_global.h"
#include "framelessmainwindow/framelessmainwindow.h"
#include "framelessMessageBox-1/uvmessagebox.h"
#include "framelessMessageBox-1/uvfiledialog.h"
#include "mergedir.h"
#include "logger/Logger.h"


class CPatch : public FramelessMainWindow {
  Q_OBJECT
  public:

	explicit CPatch(QWidget* parent = Q_NULLPTR);
	~CPatch() override;

  signals:
	void LanguageChanged(WINDOWLANAGUAGE);

  private slots:
	void onBtnOpenClicked();
	void showInTextEdit();
	void onBtnRefreshClicked();
	void onBtnGenerateClicked();
	void updateEndTimeOptions(int _index);
	void onBtnChoosePathCliecked();
	void onBtnDoneClicked();
	void onActChineseClicked();
	void onActEnglishClicked();
	void updateProcess(qint64 value);

  private:
	// 获取文件编码格式
	static QString getFileCodec(QString& _fileName);
	void readDirToList(const QString& _dirpath);
	void updateCombox();
	static QDateTime GetDateTimeFromString(const QString& str);
	void updatePage(QString& begin, QString& end, const QString& outputDir);
	static void getFileCountInDirectory(const QStringList& directoryPaths, QStringList& filesToMerge);
	[[maybe_unused]] static int countFilesRecursively(const QString& directoryPath);
	[[maybe_unused]] static void groupFilesBySecondDirectory(QStringList& filesToMerge, const QString& flag);

  private:
	void createCtrl();
	void layOut();
	void init();
	void initConnect();

  private:
	QWidget* m_pCentralWidget{nullptr};

	QWidget* m_pTitleBar{nullptr};
	QPushButton* m_pBtnClose{nullptr};
	QPushButton* m_pBtnMin{nullptr};

	QMenuBar* m_pMenuBar{nullptr};
	QAction* m_pActChinese{nullptr};
	QAction* m_pActEnglish{nullptr};

	QTabWidget* m_pTabWidget{nullptr};

	QWidget* m_pReadWidget{nullptr};
	QWidget* m_pRenewalWidget{nullptr};

	QLabel* m_pLbPatchPath{nullptr};
	QLineEdit* m_pLePatchPath{nullptr};
	QPushButton* m_pBtnOpen{nullptr};
	QPushButton* m_pBtnRefresh{nullptr};

	QListWidget* m_pLwPatchList{nullptr};
	QTextEdit* m_pTePreviewTxt{nullptr};

	QLabel* m_pLbGeneratePath{nullptr};
	QComboBox* m_pCbStartTime{nullptr};
	QComboBox* m_pCbEndTime{nullptr};
	QPushButton* m_pBtnGenerate{nullptr};
	QLabel* m_pLbThreadNum{nullptr};
	QComboBox* m_pCbThreadNum{nullptr};
	QLabel* m_pLbTime{nullptr};
	QLabel* m_pLbCopy{nullptr};

	QProgressBar* m_pPbschedule{nullptr};

	QLabel* m_pLbPatchVersion{nullptr};
	QLineEdit* m_pLePatchVersion{nullptr};

	QLineEdit* m_pLePatchOutPath{nullptr};
	QPushButton* m_pBtnPatchOutPath{nullptr};

	QListWidget* m_pLwOutPatchList{nullptr};

	QLabel* m_pLbVersionPath{nullptr};
	QPushButton* m_pBtnVersionPatch{nullptr};

	QHBoxLayout* m_plyHTitle{nullptr};
	QVBoxLayout* m_pCentralLayout{nullptr};

	QVBoxLayout* m_pReadWidgetLayout{nullptr};
	QHBoxLayout* m_pReadFirstRowLayout{nullptr};
	QHBoxLayout* m_pReadSecondRowLayout{nullptr};
	QHBoxLayout* m_pReadThirdRowLayout{nullptr};

	QVBoxLayout* m_pRenewalWidgetLayout{nullptr};
	QHBoxLayout* m_pRenewalFirstRowLayout{nullptr};
	QHBoxLayout* m_pRenewalSecondRowLayout{nullptr};
	QHBoxLayout* m_pRenewalThirdRowLayout{nullptr};

  private:
	QPoint m_PressTitlePoint;

  private:
	// 时间，完整路径
	std::map<QString, QString> m_localMap{};
//	CMergeDir* m_pMergeDir{nullptr};
	QString m_output{};
	QString m_dirname{};
	QString m_outDirName{};
	QTimer* m_pFlickerTimer{nullptr};
	int m_GenerateTime{0};
	QTimer* m_pGenerateTime{nullptr};

	qint64 m_localProcess{0};
	qint64 m_totalProcess{0};

	bool m_bIsGenerate{false};
};
