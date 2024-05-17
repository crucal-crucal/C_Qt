#include "uvmessagebox.h"

#include <QRegularExpression>

//CUVMessageBox
namespace UVMessageBox {
CUVMessageBox::CUVMessageBox(const QMessageBox::Icon icon, const QString& title, const QString& text,
                             const QMessageBox::StandardButtons buttons, QWidget* parent, const Qt::WindowFlags flags)
: CUVBaseDialog(parent), m_pMessageBox(new QMessageBox(icon, "", text, buttons, this, flags)), buttons_(buttons),
  flags_(flags) {
	setTitle(title);
	setTitleBtnRole(CloseRole);
	m_pMessageBox->setWindowFlags(flags);
	m_pMessageBox->setStyleSheet("");
	setContent(m_pMessageBox);

	QFont curFont = font();
	curFont.setPixelSize(16);
	const QFontMetrics fontMetrics(curFont);
	int nMinWidth [[maybe_unused]] = fontMetrics.horizontalAdvance(title);
	connect(m_pMessageBox, &QMessageBox::buttonClicked, this, &CUVMessageBox::onMsgBoxButtonClicked);
}

CUVMessageBox::~CUVMessageBox() = default;

void CUVMessageBox::setDefaultButton(QPushButton* button) const {
	m_pMessageBox->setDefaultButton(button);
}

void CUVMessageBox::setDefaultButton(const QMessageBox::StandardButton button) const {
	m_pMessageBox->setDefaultButton(button);
}

void CUVMessageBox::addButton(QAbstractButton* button, const QMessageBox::ButtonRole role) const {
	m_pMessageBox->addButton(button, role);
}

QPushButton* CUVMessageBox::addButton(const QString& text, const QMessageBox::ButtonRole role) const {
	return m_pMessageBox->addButton(text, role);
}

QPushButton* CUVMessageBox::addButton(const QMessageBox::StandardButton button) const {
	return m_pMessageBox->addButton(button);
}

void CUVMessageBox::removeButton(QAbstractButton* button) const {
	m_pMessageBox->removeButton(button);
}

QMessageBox::ButtonRole CUVMessageBox::information(QWidget* parent,
                                                   const QString& title,
                                                   const QString& text,
                                                   const QMessageBox::StandardButtons buttons,
                                                   [[maybe_unused]] const QMessageBox::StandardButton defaultButton) {
	CUVMessageBox messageBox(QMessageBox::Information, title, text, buttons, parent);
	messageBox.m_pMessageBox->button(QMessageBox::Ok)->setText(tr("OK"));
	return static_cast<QMessageBox::ButtonRole>(messageBox.exec());
}

QMessageBox::ButtonRole CUVMessageBox::question(QWidget* parent,
                                                const QString& title,
                                                const QString& text,
                                                const QMessageBox::StandardButtons buttons,
                                                [[maybe_unused]] const QMessageBox::StandardButton defaultButton) {
	CUVMessageBox messageBox(QMessageBox::Question, title, text, buttons, parent);
	messageBox.m_pMessageBox->button(QMessageBox::Yes)->setText(tr("Yes"));
	messageBox.m_pMessageBox->button(QMessageBox::No)->setText(tr("No"));
	return static_cast<QMessageBox::ButtonRole>(messageBox.exec());
}

QMessageBox::ButtonRole CUVMessageBox::warning(QWidget* parent,
                                               const QString& title,
                                               const QString& text,
                                               const QMessageBox::StandardButtons buttons,
                                               [[maybe_unused]] const QMessageBox::StandardButton defaultButton) {
	CUVMessageBox messageBox(QMessageBox::Warning, title, text, buttons, parent);
	messageBox.m_pMessageBox->button(QMessageBox::Ok)->setText(tr("OK"));
	return static_cast<QMessageBox::ButtonRole>(messageBox.exec());
}

QMessageBox::ButtonRole CUVMessageBox::critical(QWidget* parent,
                                                const QString& title,
                                                const QString& text,
                                                const QMessageBox::StandardButtons buttons,
                                                [[maybe_unused]] const QMessageBox::StandardButton defaultButton) {
	CUVMessageBox messageBox(QMessageBox::Critical, title, text, buttons, parent);
	messageBox.m_pMessageBox->button(QMessageBox::Ok)->setText(tr("OK"));
	return static_cast<QMessageBox::ButtonRole>(messageBox.exec());
}

void CUVMessageBox::about(QWidget* parent, const QString& title, const QString& text) {
	CUVMessageBox messageBox(QMessageBox::NoIcon, title, text, QMessageBox::NoButton, parent);
	messageBox.exec();
}

int CUVMessageBox::exec() {
	int nRet [[maybe_unused]] = CUVBaseDialog::exec();
	int button = m_pMessageBox->standardButton(m_pMessageBox->clickedButton());
	if (QMessageBox::NoButton == button) {
		button = m_pMessageBox->buttonRole(m_pMessageBox->clickedButton());
	} else {
		button = standardConvertToRole(static_cast<QMessageBox::StandardButton>(button));
	}
	return button;
}

void CUVMessageBox::apply() {
	m_pMessageBox->accept();
	close();
}

void CUVMessageBox::closeDialog() {
	m_pMessageBox->reject();
	close();
}

void CUVMessageBox::onMsgBoxButtonClicked([[maybe_unused]] const QAbstractButton* button) {
	close();
}

QMessageBox::ButtonRole CUVMessageBox::standardConvertToRole(const QMessageBox::StandardButton button) {
	switch (button) {
		case QMessageBox::Cancel:
		case QMessageBox::Abort:
		case QMessageBox::Close: return QMessageBox::RejectRole;
		case QMessageBox::No:
		case QMessageBox::NoToAll: return QMessageBox::NoRole;
		case QMessageBox::Ok:
		case QMessageBox::Yes:
		case QMessageBox::Open: return QMessageBox::AcceptRole;
		default: break;
	}
	return QMessageBox::NRoles;
}

//CLXTimeOutMessageBox
const QRegularExpression CUVCountdownMessageBox::regex("\\d+");

CUVCountdownMessageBox::CUVCountdownMessageBox(const QMessageBox::Icon icon, const QString& title, const QString& text,
                                               QWidget* parent) : CUVMessageBox(
	icon, title, text, QMessageBox::Yes | QMessageBox::No, parent,
	Qt::Widget | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint) {
	setModal(true);
	setWindowModality(Qt::WindowModal);
	setWindowFlags(Qt::Widget | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	QFont curFont = font();
	curFont.setPixelSize(16);
	const QFontMetrics fontMetrics(curFont);
	const int nMinWidth = fontMetrics.horizontalAdvance(title);
	resize(nMinWidth + 100, 100);
}

CUVCountdownMessageBox::~CUVCountdownMessageBox() = default;

int CUVCountdownMessageBox::exec(const int nSecond) {
	nCountdown = nSecond;
	m_pMessageBox->button(QMessageBox::Yes)->setText(
		QString("%1(%2)").arg(m_pMessageBox->button(QMessageBox::Yes)->text()).
		                  arg(nCountdown)
	);
	startTimer(1000);
	return CUVMessageBox::exec();
}

void CUVCountdownMessageBox::timerEvent(QTimerEvent* event) {
	nCountdown--;
	if (nCountdown <= 0) {
		killTimer(event->timerId());
		m_pMessageBox->button(QMessageBox::Yes)->clicked();
	}
	QString strText = m_pMessageBox->button(QMessageBox::Yes)->text();
	strText.replace(regex, QString::number(nCountdown));
	m_pMessageBox->button(QMessageBox::Yes)->setText(strText);
}
}
