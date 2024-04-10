#pragma once
#include <QDialog>
#include <QObject>
#include <QMessageBox>
#include <QPushButton>
#include <QStyleOption>
#include <QPainter>
#include <QTextOption>
#include <QFontMetrics>
#include <QMouseEvent>
#include <QFont>
#include "uvbasedialog.h"

#ifdef FRAMELESSMESSAGEBOX_LIB
#define FRAMELESSMESSAGEBOX_EXPORT Q_DECL_EXPORT
#else
#define FRAMELESSMESSAGEBOX_EXPORT Q_DECL_IMPORT
#endif

namespace UVMessageBox {
enum class LXRobotMsgBoxType {
	LXRobotMsgBoxType_None,
	LXRobotMsgBoxType_Warn,
	LXRobotMsgBoxType_Information,
	LXRobotMsgBoxType_Error
};

enum LXRobotMessageButton {
	LXRobotMessageButton_Cannel = 1,
	LXRobotMessageButton_ok = 2,
	LXRobotMessageButton_Yes = 4,
	LXRobotMessageButton_No = 8
};

class FRAMELESSMESSAGEBOX_EXPORT CUVMessageBox : public CUVBaseDialog {
  Q_OBJECT
  public:
	CUVMessageBox(QMessageBox::Icon icon, const QString& title, const QString& text,
				  QMessageBox::StandardButtons buttons = QMessageBox::NoButton, QWidget* parent = Q_NULLPTR,
				  Qt::WindowFlags flags = Qt::Widget | Qt::FramelessWindowHint);
	~CUVMessageBox() override;
  public:
	void setDefaultButton(QPushButton* button);
	void setDefaultButton(QMessageBox::StandardButton button);

	void addButton(QAbstractButton* button, QMessageBox::ButtonRole role);
	QPushButton* addButton(const QString& text, QMessageBox::ButtonRole role);
	QPushButton* addButton(QMessageBox::StandardButton button);
	void removeButton(QAbstractButton* button);

	static QMessageBox::ButtonRole information(QWidget* parent, const QString& title = QObject::tr("IDS_MSG_TIP"),
											   const QString& text = "", QMessageBox::StandardButtons buttons = QMessageBox::Ok,
											   QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
	static QMessageBox::ButtonRole question(QWidget* parent, const QString& title,
											const QString& text, QMessageBox::StandardButtons buttons = QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No),
											QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
	static QMessageBox::ButtonRole warning(QWidget* parent, const QString& title = QObject::tr("IDS_WARN_TITLE"),
										   const QString& text = "", QMessageBox::StandardButtons buttons = QMessageBox::Ok,
										   QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
	static QMessageBox::ButtonRole critical(QWidget* parent, const QString& title,
											const QString& text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
											QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
	static void about(QWidget* parent, const QString& title, const QString& text);

	int exec() override;
  protected slots:
	void apply() override;
	void closeDialog() override;
	void onMsgBoxButtonClicked(QAbstractButton* button);
  private:
	static QMessageBox::ButtonRole standardConvertToRole(QMessageBox::StandardButton button);
  protected:
	QMessageBox* m_pMessageBox{nullptr};
};

class FRAMELESSMESSAGEBOX_EXPORT CUVCountdownMessageBox : public CUVMessageBox {
  Q_OBJECT
  public:
	explicit CUVCountdownMessageBox(QMessageBox::Icon icon, const QString& title, const QString& text,
									QWidget* parent = Q_NULLPTR);
	~CUVCountdownMessageBox() override;
  public:
	int exec(int nSecond);
  protected:
	void timerEvent(QTimerEvent* event) override;
  private:
	int nCountdown{0};
};
}