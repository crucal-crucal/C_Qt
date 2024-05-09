#pragma once

#include <QCheckBox>
#include <QDebug>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QTimer>

#ifdef FRAMELESSMESSAGEBOX_LIB
#define FRAMELESSMESSAGEBOX_EXPORT Q_DECL_EXPORT
#else
#define FRAMELESSMESSAGEBOX_EXPORT Q_DECL_IMPORT
#endif

/*
 * @brief 消息框基类
 */
class FRAMELESSMESSAGEBOX_EXPORT CUVMessageBase : public QDialog {
	Q_OBJECT

public:
	enum E_BUTTON_STATUS {
		OK     = 0,
		CANCEL = 1,
	};

	explicit CUVMessageBase(QWidget* parent = nullptr, QString title = tr("device remove"), QString text = tr(""), QString okButtonText = tr("OK"),
	                        QString cancelButtonText = tr("Cancel"), QString iconPath = "", bool showWarn = true, bool showOKBtn = true,
	                        bool showCancelBtn = true);
	~CUVMessageBase() override;

	void setTitle(const QString& title) const;
	void setText(const QString& text) const;
	void setOkButtonText(const QString& okButtonText) const;
	void setCancelButtonText(const QString& cancelButtonText) const;
	void setIcon(const QString& iconPath, bool fill = false);
	void setShowWarn(bool showWarn) const;
	void setMoveEnable(bool bEnable);
	void setEscEnable(bool bEnable);
	void setEnterEnable(bool bEnable);

signals:
	void okClicked();
	void checkBoxState(int);

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;

public slots:
	void onBtnOkClicked();

private:
	QPoint m_PressTitlePoint;
	QRect m_rtTitle;
	bool m_bPressTitle{ false };
	bool m_bMoveEnable{ true };
	bool m_bEscEnable{ true };
	bool m_bEnterEnable{ false };

	void createCtrl();
	void layOut();
	void initConnection();

	const QString m_title{};
	const QString m_text{};
	const QString m_okButtonText{};
	const QString m_cancelButtonText{};
	const QString m_iconPath{};
	bool m_showWarn{};
	bool m_showOKBtn{};
	bool m_showCancelBtn{};

	QLabel* m_pLbTitle{ nullptr };
	QPushButton* m_pBtnClose{ nullptr };
	QLabel* m_pLbIcon{ nullptr };
	QPixmap m_pixmap{};
	QLabel* m_pLbText{ nullptr };

	QPushButton* m_pBtnOk{ nullptr };
	QPushButton* m_pBtnCancel{ nullptr };

	QCheckBox* m_pCbWarn{ nullptr };

	QVBoxLayout* m_pCenterVLayout{ nullptr };

	QHBoxLayout* m_pTitleHLayout{ nullptr };
	QHBoxLayout* m_pBtnHLayout{ nullptr };
};

/*
 * @brief 消息框
 */
class FRAMELESSMESSAGEBOX_EXPORT CUVMessageBox final : public QObject {
	Q_OBJECT

public:
	// Create a new CUVMessageBox object
	explicit CUVMessageBox(QWidget* parent = nullptr);
	// Destroy the CUVMessageBox object
	~CUVMessageBox() override;

	//static variable for show again
	static bool showAgain;

	/*
	 * @parma parent 父对象
	 * @parma title 标题
	 * @parma text 文本
	 * @parma showWarn 是否显示警告图标
	 * @parma showOkBtn 是否显示确定按钮
	 * @parma showCancelBtn 是否显示取消按钮
	 * @parma iconPath 警告图标路径
	 * @parma okButtonText 确定按钮文本
	 * @parma cancelButtonText 取消按钮文本
	 * @return CUVMessageBase::E_BUTTON_STATUS
	 * @note 根据参数显示消息框
	 */
	static CUVMessageBase::E_BUTTON_STATUS showMessage(QWidget* parent             = nullptr, const QString& title = tr("device remove"),
	                                                   const QString& text         = tr("select"),
	                                                   bool showWarn               = true, bool showOkBtn = true, bool showCancelBtn = true,
	                                                   const QString& iconPath     = ":icon/control/delete_icon.png",
	                                                   const QString& okButtonText = tr("OK"), const QString& cancelButtonText = tr("Cancel"));
	/*
	 * @parma parent 父对象
	 * @parma title 标题
	 * @parma text 内容
	 * @return CUVMessageBase::E_BUTTON_STATUS
	 * @note about 没有按钮
	 */
	static CUVMessageBase::E_BUTTON_STATUS about(QWidget* parent, const QString& title, const QString& text);
	/*
	 * @parma parent 父对象
	 * @parma title 标题
	 * @parma text 内容
	 * @return CUVMessageBase::E_BUTTON_STATUS
	 * @note critical, 含有确定按钮
	 */
	static CUVMessageBase::E_BUTTON_STATUS critical(QWidget* parent, const QString& title, const QString& text);
	/*
	 * @parma parent 父对象
	 * @parma title 标题
	 * @parma text 内容
	 * @return CUVMessageBase::E_BUTTON_STATUS
	 * @note infomation, 含有确定按钮
	 */
	static CUVMessageBase::E_BUTTON_STATUS infomation(QWidget* parent, const QString& title = tr("infomation"), const QString& text = "",
	                                                  const QString& okButtonText           = tr("OK"));
	/*
	 * @parma parent 父对象
	 * @parma title 标题
	 * @parma text 内容
	 * @return CUVMessageBase::E_BUTTON_STATUS
	 * @note warning, 含有确定按钮
	 */
	static CUVMessageBase::E_BUTTON_STATUS waring(QWidget* parent, const QString& title = tr("waring"), const QString& text = "",
	                                              const QString& okButtonText           = tr("OK"));
	/*
	 * @parma parent 父对象
	 * @parma title 标题
	 * @parma text 内容
	 * @parma okButtonText 确定按钮文本
	 * @parma cancelButtonText 取消按钮文本
	 * @return CUVMessageBase::E_BUTTON_STATUS
	 * @note question, 含有确定和取消按钮
	 */
	static CUVMessageBase::E_BUTTON_STATUS question(QWidget* parent, const QString& title, const QString& text,
	                                                const QString& okButtonText     = tr("OK"),
	                                                const QString& cancelButtonText = tr("Cancel"));
};

/*
 * @brief 定时关闭消息框
 */
class FRAMELESSMESSAGEBOX_EXPORT CUVCountdownMessageBox final : public CUVMessageBase {
	Q_OBJECT

public:
	explicit CUVCountdownMessageBox(QWidget* parent             = nullptr, const QString& title = tr("Countdown"), const QString& text = tr(""),
	                                const QString& okButtonText = tr("OK"), const QString& cancelButtonText = tr("Cancel"),
	                                const QString& iconPath     = "", bool showWarn = false, bool showOKBtn = true, bool showCancelBtn = false);
	~CUVCountdownMessageBox() override;

	int exec(int nSecond);

protected:
	void timerEvent(QTimerEvent* event) override;

private:
	int nCountdown{ 0 };
};
