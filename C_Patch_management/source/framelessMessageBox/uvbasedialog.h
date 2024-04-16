#pragma once

#include <QDialog>
#include <QDialogButtonBox>
#include <QDesktopServices>
#ifdef Q_OS_WIN
#include <Windowsx.h>
#include <Windows.h>
#include <WinUser.h>
#endif
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QApplication>
#include <utility>
#include <cmath>

/*
 * @brief ÎÞ±ß¿ò´øÒõÓ°Dialog
 */
#define TITLE_HEIGHT            30
#define BORDER_SHADOW_WIDTH        6

#ifdef FRAMELESSBASEDIALOG_LIB
#define FRAMELESSBASEDIALOG_EXPORT Q_DECL_EXPORT
#else
#define FRAMELESSBASEDIALOG_EXPORT Q_DECL_IMPORT
#endif

class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QPainter;

class FRAMELESSBASEDIALOG_EXPORT CUVBaseDialog : public QDialog {
  Q_OBJECT
	Q_DISABLE_COPY(CUVBaseDialog)
  public:
	enum TitleButtonRole {
		NoButtonRole = 0x00000000,
		CloseRole = 0x000001,
		MaxRole = 0x000002,
		MinRole = 0x000004,
		SettingRole [[maybe_unused]] = 0x000008,
		HelpRole = 0x000010,
	};
	Q_DECLARE_FLAGS(TitleButtonRoles, TitleButtonRole)
	Q_FLAG(TitleButtonRoles)
  public:
	explicit CUVBaseDialog(QWidget* parent = nullptr);
	~CUVBaseDialog() override;

  public:
	void setTitle(QString strTitle);
	[[maybe_unused]] [[nodiscard]] QRect getTilteRect() const;
	[[maybe_unused]] [[nodiscard]] QList<QAbstractButton*> getTitleButton() const;
	[[maybe_unused]] void setIcon(const QString& strPath, bool bScale, QSize scaleSize = QSize());
	[[maybe_unused]] void setResizeable(bool bResizeable);
	[[maybe_unused]] void setEscEnable(bool bEnable);
	[[maybe_unused]] void setMoveEnable(bool bEnable);
	[[maybe_unused]] void setTitleVisible(bool bVisible);
	[[maybe_unused]] void setEnterEnable(bool bEnable);
	[[maybe_unused]] void setShadowVisible(bool bVisible);

	void setTitleBtnRole(TitleButtonRoles emTitleButtonRoles);
	[[maybe_unused]] void setDialogBtnRole(QDialogButtonBox::StandardButtons emBtns = (QDialogButtonBox::Ok | QDialogButtonBox::Cancel));
	void setContent(QWidget* pContentWidget);
	[[maybe_unused]] void setContent(QLayout* pLayout);
	[[maybe_unused]] QPushButton* button(QDialogButtonBox::StandardButton emBtn);

  protected:
	void paintEvent(QPaintEvent* event) override;
	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event) override;
	void resizeEvent(QResizeEvent* event) override;

  protected slots:
	virtual void apply();
	virtual void closeDialog();

  protected:
	[[maybe_unused]] void addTitleButton(QAbstractButton* pButton, TitleButtonRole emButtonRole);
	QPushButton* addTitleButton(TitleButtonRole emButtonRole);
	QPushButton* insertTitleButton(int nIndex, TitleButtonRole emButtonRole);
	void insertTitleButton(QAbstractButton* pButton, int nIndex, TitleButtonRole emButtonRole);

  private slots:
	void switchSize();

  private:
	QDialogButtonBox* m_pDialogBtnBox{nullptr};
	QVBoxLayout* m_plyVTotal{nullptr};
	QHBoxLayout* m_plyHTitle{nullptr};
	QHBoxLayout* m_plyHContent{nullptr};

  private:
	QString m_strTitle;
	QString m_strIconPath;
	QPixmap m_icon;
	QPoint m_PressTitlePoint;
	QRect m_rtTitle;
	bool m_bPressTitle{false};
	bool m_bResizeable{false};
	bool m_bIconScaled{false};
	bool m_bEscEnable{false};
	bool m_bMoveEnable{true};
	bool m_bTitleVisible{true};
	bool m_bShadowVisible{true};
	bool m_bEnterEnable{true};
	QHash<TitleButtonRole, QAbstractButton*> m_hashTitleButtons;
};
