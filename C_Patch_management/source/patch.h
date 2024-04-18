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
#include <set>

#include "C_global.h"
#include "framelessmainwindow/framelessmainwindow.h"
#include "framelessMessageBox/uvmessagebox.h"
#include "framelessMessageBox/uvfiledialog.h"
#include "mergedir.h"
#include "logger/Logger.h"


class CPatch : public FramelessMainWindow {
  Q_OBJECT
  public:

	explicit CPatch(int LabelWidth, WINDOWLANAGUAGE Lanaguage = WINDOWLANAGUAGE::Chinese,
					WINDOWPROGRESSBARSTYLE ProgressbarStyle = WINDOWPROGRESSBARSTYLE::BLOCK,
					QWidget* parent = nullptr);
	~CPatch() override;

  signals:
	void ConfChanged(WINDOWLANAGUAGE, WINDOWPROGRESSBARSTYLE);

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
	void onActProgressbar_normalClicked();
	void onActProgressbar_borderClicked();
	void onActProgressbar_border_radiusClicked();
	void onActProgressbar_blockClicked();
	void onActProgressbar_gradationClicked();
	void updateProcess(qint64 value);

  private:
	// 获取文件编码格式
	static QString getFileCodec(QString& _fileName);
	void readDirToList(const QString& _dirpath);
	void updateCombox();
	static QDateTime GetDateTimeFromString(const QString& str);
	void updatePage(QString& begin, QString& end, const QString& outputDir);
	static void getFilesInDirectory(const QStringList& directoryPaths, QStringList& filesToMerge);
	/*
	 * @note: 分割文件，使得所有文件按照文件夹分类装在 map 的Value中，map以文件夹名为Key，如果分割时仅剩文件，则在最后插入map
	 * @param: flag 文件夹名，filesToMerge 筛选出需要 Copy 的文件
	 */
	static std::map<QString, QStringList> splitFileList(const QString& flag, const QStringList& filesToMerge);
	/*
	 * @note: 通过用户选择的线程分割文件
	 */
	static bool splitFileListByThread(const std::map<QString, QStringList>& mp, std::vector<QStringList>& threadFiles);

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
	QMenu* m_menuPreference{nullptr};
	QMenu* m_menuLanguage{nullptr};
	QAction* m_pActChinese{nullptr};
	QAction* m_pActEnglish{nullptr};
	QMenu* m_menuProgressbar{nullptr};
	QAction* m_pActProgressbar_normal{nullptr};
	QAction* m_pActProgressbar_border{nullptr};
	QAction* m_pActProgressbar_border_radius{nullptr};
	QAction* m_pActProgressbar_block{nullptr};
	QAction* m_pActProgressbar_gradation{nullptr};

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
	int m_LabelWidth{};
	WINDOWLANAGUAGE m_language{};
	WINDOWPROGRESSBARSTYLE m_ProgressbarStyle{};
};
