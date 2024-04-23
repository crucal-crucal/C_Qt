#pragma once

#include <QDialog>
#include <QMessageBox>
#include <QObject>

#include "uvbasedialog.h"

#ifdef FRAMELESSMESSAGEBOX_LIB
#define FRAMELESSMESSAGEBOX_EXPORT Q_DECL_EXPORT
#else
#define FRAMELESSMESSAGEBOX_EXPORT Q_DECL_IMPORT
#endif

namespace UVMessageBox {
enum class LXRobotMsgBoxType {
	LXRobotMsgBoxType_None [[maybe_unused]],
	LXRobotMsgBoxType_Warn [[maybe_unused]],
	LXRobotMsgBoxType_Information [[maybe_unused]],
	LXRobotMsgBoxType_Error [[maybe_unused]]
};

enum LXRobotMessageButton {
	LXRobotMessageButton_Cannel [[maybe_unused]] = 1,
	LXRobotMessageButton_ok [[maybe_unused]]     = 2,
	LXRobotMessageButton_Yes [[maybe_unused]]    = 4,
	LXRobotMessageButton_No [[maybe_unused]]     = 8
};

class FRAMELESSMESSAGEBOX_EXPORT CUVMessageBox : public CUVBaseDialog {
	Q_OBJECT

public:
	CUVMessageBox(QMessageBox::Icon icon,
	              const QString& title,
	              const QString& text,
	              QMessageBox::StandardButtons buttons = QMessageBox::NoButton,
	              QWidget* parent = Q_NULLPTR,
	              Qt::WindowFlags flags = Qt::Widget | Qt::FramelessWindowHint);
	~CUVMessageBox() override;

public:
	void setDefaultButton(QPushButton* button) const;
	void setDefaultButton(QMessageBox::StandardButton button) const;

	void addButton(QAbstractButton* button, QMessageBox::ButtonRole role) const;
	[[nodiscard]] QPushButton* addButton(const QString& text, QMessageBox::ButtonRole role) const;
	[[nodiscard]] QPushButton* addButton(QMessageBox::StandardButton button) const;
	void removeButton(QAbstractButton* button) const;

	static QMessageBox::ButtonRole information(QWidget* parent,
	                                           const QString& title = QObject::tr("IDS_MSG_TIP"),
	                                           const QString& text = "",
	                                           QMessageBox::StandardButtons buttons = QMessageBox::Ok,
	                                           QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
	static QMessageBox::ButtonRole question(QWidget* parent,
	                                        const QString& title,
	                                        const QString& text,
	                                        QMessageBox::StandardButtons buttons = QMessageBox::StandardButtons(
		                                        QMessageBox::Yes | QMessageBox::No),
	                                        QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
	static QMessageBox::ButtonRole warning(QWidget* parent,
	                                       const QString& title = QObject::tr("IDS_WARN_TITLE"),
	                                       const QString& text = "",
	                                       QMessageBox::StandardButtons buttons = QMessageBox::Ok,
	                                       QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
	static QMessageBox::ButtonRole critical(QWidget* parent,
	                                        const QString& title,
	                                        const QString& text,
	                                        QMessageBox::StandardButtons buttons = QMessageBox::Ok,
	                                        QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);
	static void about(QWidget* parent, const QString& title, const QString& text);

	int exec() override;

protected slots:
	void apply() override;
	void closeDialog() override;
	void onMsgBoxButtonClicked(const QAbstractButton* button);

private:
	static QMessageBox::ButtonRole standardConvertToRole(QMessageBox::StandardButton button);

protected:
	QMessageBox* m_pMessageBox{ nullptr };
	QMessageBox::StandardButtons buttons_;
	Qt::WindowFlags flags_;
};

class FRAMELESSMESSAGEBOX_EXPORT CUVCountdownMessageBox final : public CUVMessageBox {
	Q_OBJECT

public:
	explicit CUVCountdownMessageBox(QMessageBox::Icon icon, const QString& title, const QString& text,
	                                QWidget* parent = Q_NULLPTR);
	~CUVCountdownMessageBox() override;

	int exec(int nSecond);

protected:
	void timerEvent(QTimerEvent* event) override;

private:
	int nCountdown{ 0 };
	static const QRegularExpression regex;
};
}
