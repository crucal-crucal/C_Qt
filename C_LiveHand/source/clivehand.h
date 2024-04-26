#pragma once

#include <QActionGroup>
#include <QMenuBar>
#include <QRadioButton>
#include <QSystemTrayIcon>
#include <QTableWidget>
#include <QThreadPool>

#include "cplaybackwidget.h"
#include "framelessmainwindow/framelessmainwindow.h"
#include "framelessMessageBox/uvmessagebox.h"
#include "global/cdefine.h"
#include "global/interface_global.h"

class CLXPlaybackWidget;
struct AVFormatContext;

class CLiveHand final : public FramelessMainWindow {
	Q_OBJECT

public:
	explicit CLiveHand(WINDOWLANAGUAGE Lanaguage = WINDOWLANAGUAGE::Chinese,
	                   WINDOWTHEMESTYLE ThemeStyle = WINDOWTHEMESTYLE::LIGHT,
	                   QWidget* parent = nullptr);
	~CLiveHand() override;

	[[nodiscard]] QSystemTrayIcon* getTrayIcon() const { return m_ptrayIcon; }

signals:
	void ConfChanged(WINDOWLANAGUAGE, WINDOWTHEMESTYLE);
	void ThemeChanged(WINDOWTHEMESTYLE);

private:
	void readConfig();
	void saveConfig();
	void appendItem(const QString& strFile, bool bLock = false, bool bCurrent = false);
	void removeItem(QTableWidgetItem* item);

private:
	void createCtrl();
	void customLayout();
	void init();
	void initConnection();
	void initData();
	void destroy();
	void help();
	void version();
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

private slots:
	void onBtnStyleClicked();
	void onActChineseClicked();
	void onActEnglishClicked();
	void onSystemTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
	void onBtnFillerPieceSwitchClicked(bool bChecked);
	void onBtnStopFillerPieceClicked();
	void onBtnAppendFillerPieceClicked();
	bool onItemDoubleClicked(QTableWidgetItem* item);
	void onItemSelectChanged();
	void onTableCustomContextMenuRequested(const QPoint& pos);
	void onBtnCloseClicked();
	void onSysTrayCloseTriggered();
	void onBtnMinClicked();
	void onSystemTrayActived(QSystemTrayIcon::ActivationReason reason);
	void onNotifyPlayStateChanged(CPlayBackWidget::State eState);
	void onNotifyPlayClicked(bool bChecked);
	void onNotifyProcessState(eProcessState state, QVector<CPushStreamInfo> vecStreamInfo);

private:
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

	QLabel* m_pLbHostStatus{ nullptr };
	QLabel* m_pLbFillerPieceStatus{ nullptr };
	QPushButton* m_pBtnFillerPieceSwitch{ nullptr };
	QPushButton* m_pBtnFillerPieceStop{ nullptr };
	CPlayBackWidget* m_pPlayWidget{ nullptr };

	QPushButton* m_pBtnAppendFillerPiece{ nullptr };
	QTableWidget* m_pFillerPieceTable{ nullptr };
	QLabel* m_pLbFillerPieceTip{ nullptr };

	QWidget* m_pCenterWidget{ nullptr };
	QFormLayout* m_pLyFormStatus{ nullptr };
	QHBoxLayout* m_pLyHFillerPiece{ nullptr };
	QVBoxLayout* m_pLyVStatus{ nullptr };
	QHBoxLayout* m_pLyHPlay{ nullptr };

	QHBoxLayout* m_pLyHFillerPieceListTitle{ nullptr };
	QVBoxLayout* m_pLyVFillerPieceTotal{ nullptr };

	QHBoxLayout* m_pLyHTitle{ nullptr };
	QVBoxLayout* m_pCentralLayout{ nullptr };

	WINDOWLANAGUAGE m_language{};                  // 语言
	WINDOWTHEMESTYLE m_ThemeStyle{};               // 主题
	QSystemTrayIcon* m_ptrayIcon{ nullptr };       // 系统托盘图标
	std::unique_ptr<QMenu> m_ptrayMenu{ nullptr }; // 系统托盘菜单
	QAction* m_pActShow{ nullptr };                // 显示主界面按钮
	QAction* m_pActQuit{ nullptr };                // 退出按钮

private:
	QString m_strTitle;
	QString m_strIconPath;
	QPixmap m_icon;
	QPoint m_PressTitlePoint;
	QRect m_rtTitle;
	bool m_bPressTitle{ false };

	QString m_pProcessName;
	QString m_strCurrentFillerPieceClip;
	QThreadPool m_recvThreadPool;
};

class CQuitDialog final : public CUVBaseDialog {
	Q_OBJECT

public:
	explicit CQuitDialog(QWidget* parent = nullptr);
	~CQuitDialog() override;

public:
	[[nodiscard]] int selectMode() const;

protected:
	void accept() override;

private:
	void createCtrl();
	void layOut();
	void destroy();

private:
	QLabel* m_pLbTip{ nullptr };
	QRadioButton* m_pBtnToTray{ nullptr };
	QRadioButton* m_pBtnExit{ nullptr };

	QHBoxLayout* m_pLyHTip{ nullptr };
	QVBoxLayout* m_pLyVChk{ nullptr };
	QHBoxLayout* m_pLyHChk{ nullptr };
	QVBoxLayout* m_pLyVTotal{ nullptr };
};
