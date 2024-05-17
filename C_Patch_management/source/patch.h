#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMenuBar>
#include <QProgressBar>
#include <QSystemTrayIcon>
#include <QTextEdit>
#include <QTimer>
#include <set>
#include <utility>

#include "framelessmainwindow/framelessmainwindow.h"
#include "framelessMessageBox/uvfiledialog.h"
#include "framelessMessageBox/uvmessagebox.h"
#include "global/cglobal.h"
#include "mergedir/mergedir_p.h"

class CPatch final : public FramelessMainWindow {
	Q_OBJECT

public:
	explicit CPatch(WINDOWLANAGUAGE Lanaguage = WINDOWLANAGUAGE::Chinese,
	                WINDOWPROGRESSBARSTYLE ProgressbarStyle = WINDOWPROGRESSBARSTYLE::BLOCK,
	                WINDOWTHEMESTYLE ThemeStyle = WINDOWTHEMESTYLE::LIGHT,
	                std::string dirPath = "", QWidget* parent = nullptr);
	~CPatch() override;

	[[nodiscard]] QSystemTrayIcon* getTrayIcon() const { return m_ptrayIcon; }

signals:
	void ConfChanged(WINDOWLANAGUAGE, WINDOWPROGRESSBARSTYLE, WINDOWTHEMESTYLE);
	void ThemeChanged(WINDOWTHEMESTYLE);

private slots:
	void onBtnOpenClicked();
	void showInTextEdit() const;
	void onBtnRefreshClicked();
	void onBtnGenerateClicked();
	void updateEndTimeOptions(int _index);
	void onBtnChoosePathCliecked();
	void onBtnDoneClicked();
	void onBtnStyleClicked();
	void onActChineseClicked();
	void onActEnglishClicked();
	void onActProgressbar_normalClicked();
	void onActProgressbar_borderClicked();
	void onActProgressbar_border_radiusClicked();
	void onActProgressbar_blockClicked();
	void onActProgressbar_gradationClicked();
	void updateProcess(qint64 value);
	void onSystemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
	/*
	 * @note: 获取文件编码格式
	 * @param: _fileName 文件名
	*/
	static QString getFileCodec(const QString& _fileName);
	/*
	 * @note: 读取目录内容到列表
	 * @param: _dir 目录
	 */
	void readDirToList(const QDir& _dir);
	/*
	 * @note: 读取文件内容到文本框
	 */
	void updateCombox();
	/*
	 * @note: 获取当前时间
	 * @param: str 当前ComboBox选中时间
	 * @return: QDateTime 当前时间
	 */
	static QDateTime GetDateTimeFromString(const QString& str);
	/*
	 * @note: 更新到第二页面
	 * @param: begin 起始目录, end 终止目录, outputDir 输出目录
	 */
	void updatePage(const QString& begin, const QString& end, const QString& outputDir);
	/*
	 * @note: 获取文件夹下所需要合并的文件
	 * @param: directoryPaths ComboBox中选中时间对应的文件夹, filesToMerge& 需要合并的文件
	 */
	static void getFilesInDirectory(const QStringList& directoryPaths, QStringList& filesToMerge);
	/*
	 * @note: 分割文件，使得所有文件按照文件夹分类装在 map 的Value中，map以文件夹名为Key，如果分割时仅剩文件，则在最后插入map
	 * @param: flag 文件夹名，filesToMerge 筛选出需要 Copy 的文件
	 * @return: std::map<QString, QStringList> 文件夹名与文件列表的映射关系
	 */
	static std::map<QString, QStringList> splitFileList(const QString& flag, const QStringList& filesToMerge);
	/*
	 * @note: 通过用户选择的线程分割文件
	 * @parma: mp 文件夹名与文件列表的映射关系, threadFiles 线程分割后的文件列表
	 * @reurn: bool 是否分割成功
	 */
	static bool splitFileListByThread(const std::map<QString, QStringList>& mp, std::vector<QStringList>& threadFiles);
	/*
	 * @note: 重启程序
	 */
	static void restart();
	/*
	 * @note: 恢复按钮状态
	 */
	void recoveryStateWithAct() const;
	/*
 	* @note: 设置系统托盘图标
 	*/
	void setSystemTrayIcon();
	/*
	 * @note: 打开目录并传递到界面
	 */
	void openDir(const QString& _dirpath);

	/*
	 * @note: 构建模板
	 */
	template<typename T>
	T* createWidget(QWidget* parent = nullptr, const QString& objName = "") {
		QScopedPointer<T> widget(new T(parent));
		widget->setObjectName(objName);
		return widget.take();
	}

	template<typename T>
	T* createWidget(const QString& text, QWidget* parent = nullptr, const QString& objName = "") {
		QScopedPointer<T> widget(new T(text, parent));
		widget->setObjectName(objName);
		return widget.take();
	}

	void createCtrl();
	void layOut() const;
	void init();
	void initConnect();

	QWidget* m_pCentralWidget{ nullptr };

	QWidget* m_pTitleBar{ nullptr };
	QPushButton* m_pBtnStyle{ nullptr };
	QPushButton* m_pBtnClose{ nullptr };
	QPushButton* m_pBtnMin{ nullptr };

	QMenuBar* m_pMenuBar{ nullptr };
	QMenu* m_menuPreference{ nullptr };
	QMenu* m_menuLanguage{ nullptr };
	QActionGroup* m_pActGroupLanguage{ nullptr };
	QAction* m_pActChinese{ nullptr };
	QAction* m_pActEnglish{ nullptr };
	QMenu* m_menuProgressbar{ nullptr };
	QActionGroup* m_pActGroupProgressbar{ nullptr };
	QAction* m_pActProgressbar_normal{ nullptr };
	QAction* m_pActProgressbar_border{ nullptr };
	QAction* m_pActProgressbar_border_radius{ nullptr };
	QAction* m_pActProgressbar_block{ nullptr };
	QAction* m_pActProgressbar_gradation{ nullptr };

	QTabWidget* m_pTabWidget{ nullptr };

	QWidget* m_pReadWidget{ nullptr };
	QWidget* m_pRenewalWidget{ nullptr };

	QLabel* m_pLbPatchPath{ nullptr };
	QLineEdit* m_pLePatchPath{ nullptr };
	QPushButton* m_pBtnOpen{ nullptr };
	QPushButton* m_pBtnRefresh{ nullptr };

	QListWidget* m_pLwPatchList{ nullptr };
	QTextEdit* m_pTePreviewTxt{ nullptr };

	QLabel* m_pLbGeneratePath{ nullptr };
	QComboBox* m_pCbStartTime{ nullptr };
	QComboBox* m_pCbEndTime{ nullptr };
	QPushButton* m_pBtnGenerate{ nullptr };
	QLabel* m_pLbThreadNum{ nullptr };
	QComboBox* m_pCbThreadNum{ nullptr };
	QLabel* m_pLbTime{ nullptr };
	QLabel* m_pLbCopy{ nullptr };

	QProgressBar* m_pPbschedule{ nullptr };

	QLabel* m_pLbPatchVersion{ nullptr };
	QLineEdit* m_pLePatchVersion{ nullptr };

	QLineEdit* m_pLePatchOutPath{ nullptr };
	QPushButton* m_pBtnPatchOutPath{ nullptr };

	QListWidget* m_pLwOutPatchList{ nullptr };

	QLabel* m_pLbVersionPath{ nullptr };
	QPushButton* m_pBtnVersionPatch{ nullptr };

	QHBoxLayout* m_plyHTitle{ nullptr };
	QVBoxLayout* m_pCentralLayout{ nullptr };

	QVBoxLayout* m_pReadWidgetLayout{ nullptr };
	QHBoxLayout* m_pReadFirstRowLayout{ nullptr };
	QHBoxLayout* m_pReadSecondRowLayout{ nullptr };
	QHBoxLayout* m_pReadThirdRowLayout{ nullptr };

	QVBoxLayout* m_pRenewalWidgetLayout{ nullptr };
	QHBoxLayout* m_pRenewalFirstRowLayout{ nullptr };
	QHBoxLayout* m_pRenewalSecondRowLayout{ nullptr };
	QHBoxLayout* m_pRenewalThirdRowLayout{ nullptr };

	std::map<QString, QString> m_localMap{};       // 时间，完整路径
	QString m_output{};                            // 记录上一次输出路径
	QString m_dirname{};                           // 记录合并的文件夹名
	QString m_outDirName{};                        // 记录上一次输出路径的文件夹名
	QTimer* m_pFlickerTimer{ nullptr };            // 闪烁定时器
	int m_GenerateTime{ 0 };                       // 生成时间
	QTimer* m_pGenerateTime{ nullptr };            // 生成时间定时器
	qint64 m_localProcess{ 0 };                    // 当前进度
	qint64 m_totalProcess{ 0 };                    // 总进度
	WINDOWLANAGUAGE m_language{};                  // 语言
	WINDOWPROGRESSBARSTYLE m_ProgressbarStyle{};   // 进度条样式
	WINDOWTHEMESTYLE m_ThemeStyle{};               // 主题
	QSystemTrayIcon* m_ptrayIcon{ nullptr };       // 系统托盘图标
	std::unique_ptr<QMenu> m_ptrayMenu{ nullptr }; // 系统托盘菜单
	QAction* m_pActShow{ nullptr };                // 显示主界面按钮
	QAction* m_pActQuit{ nullptr };                // 退出按钮
	std::string m_dirPath{};                       // 记录上一次打开的目录路径，方便使用命令行直接打开控制
};
