#include "uvmessagebox.h"

//CUVMessageBox
namespace UVMessageBox {
CUVMessageBox::CUVMessageBox(QMessageBox::Icon icon, const QString& title, const QString& text, QMessageBox::StandardButtons buttons,
							 QWidget* parent, Qt::WindowFlags flags) : CUVBaseDialog(parent), m_pMessageBox(new QMessageBox(icon, "", text, buttons, this, flags)) {
	setTitle(title);
	setTitleBtnRole(CloseRole);
	m_pMessageBox->setWindowFlags(flags);
	m_pMessageBox->setStyleSheet("");
	setContent(m_pMessageBox);

	QFont curFont = font();
	curFont.setPixelSize(16);
	QFontMetrics fontMetrics(curFont);
	int nMinWidth = fontMetrics.width(title);
	connect(m_pMessageBox, &QMessageBox::buttonClicked, this, &CUVMessageBox::onMsgBoxButtonClicked);
}

CUVMessageBox::~CUVMessageBox() = default;

void CUVMessageBox::setDefaultButton(QPushButton* button) {
	m_pMessageBox->setDefaultButton(button);
}

void CUVMessageBox::setDefaultButton(QMessageBox::StandardButton button) {
	m_pMessageBox->setDefaultButton(button);
}

void CUVMessageBox::addButton(QAbstractButton* button, QMessageBox::ButtonRole role) {
	m_pMessageBox->addButton(button, role);
}

QPushButton* CUVMessageBox::addButton(const QString& text, QMessageBox::ButtonRole role) {
	return m_pMessageBox->addButton(text, role);
}

QPushButton* CUVMessageBox::addButton(QMessageBox::StandardButton button) {
	return m_pMessageBox->addButton(button);
}

void CUVMessageBox::removeButton(QAbstractButton* button) {
	m_pMessageBox->removeButton(button);
}

QMessageBox::ButtonRole CUVMessageBox::information(QWidget* parent, const QString& title, const QString& text,
												   QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton) {
	CUVMessageBox messageBox(QMessageBox::Information, title, text, buttons, parent);
	return QMessageBox::ButtonRole(messageBox.exec());
}

QMessageBox::ButtonRole CUVMessageBox::question(QWidget* parent, const QString& title, const QString& text,
												QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton) {
	CUVMessageBox messageBox(QMessageBox::Question, title, text, buttons, parent);
	return QMessageBox::ButtonRole(messageBox.exec());
}

QMessageBox::ButtonRole CUVMessageBox::warning(QWidget* parent, const QString& title, const QString& text,
											   QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton) {
	CUVMessageBox messageBox(QMessageBox::Warning, title, text, buttons, parent);
	return QMessageBox::ButtonRole(messageBox.exec());
}

QMessageBox::ButtonRole CUVMessageBox::critical(QWidget* parent, const QString& title, const QString& text,
												QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton) {
	CUVMessageBox messageBox(QMessageBox::Critical, title, text, buttons, parent);
	return QMessageBox::ButtonRole(messageBox.exec());
}

void CUVMessageBox::about(QWidget* parent, const QString& title, const QString& text) {
	CUVMessageBox messageBox(QMessageBox::NoIcon, title, text, QMessageBox::NoButton, parent);
	messageBox.exec();
}

int CUVMessageBox::exec() {
	int nRet = CUVBaseDialog::exec();
	int button = m_pMessageBox->standardButton(m_pMessageBox->clickedButton());
	if (QMessageBox::NoButton == button) {
		button = m_pMessageBox->buttonRole(m_pMessageBox->clickedButton());
	} else {
		button = standardConvertToRole(QMessageBox::StandardButton(button));
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

void CUVMessageBox::onMsgBoxButtonClicked(QAbstractButton* button) {
	close();
}

QMessageBox::ButtonRole CUVMessageBox::standardConvertToRole(QMessageBox::StandardButton button) {
	switch (button) {
		case QMessageBox::Cancel:
		case QMessageBox::Abort:
		case QMessageBox::Close:return QMessageBox::RejectRole;
		case QMessageBox::No:
		case QMessageBox::NoToAll:return QMessageBox::NoRole;
		case QMessageBox::Ok:
		case QMessageBox::Yes:
		case QMessageBox::Open:return QMessageBox::AcceptRole;
		default:break;
	}
	return QMessageBox::NRoles;
}

//CLXTimeOutMessageBox
CUVCountdownMessageBox::CUVCountdownMessageBox(QMessageBox::Icon icon, const QString& title, const QString& text, QWidget* parent)
	: CUVMessageBox(icon, title, text, QMessageBox::Yes | QMessageBox::No, parent, Qt::Widget | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint) {
	setModal(true);
	setWindowModality(Qt::WindowModal);
	setWindowFlags(Qt::Widget | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	QFont curFont = font();
	curFont.setPixelSize(16);
	QFontMetrics fontMetrics(curFont);
	int nMinWidth = fontMetrics.width(title);
	resize(nMinWidth + 100, 100);
}

CUVCountdownMessageBox::~CUVCountdownMessageBox() = default;

int CUVCountdownMessageBox::exec(int nSecond) {
	nCountdown = nSecond;
	m_pMessageBox->button(QMessageBox::Yes)->setText(QString("%1(%2)").arg(m_pMessageBox->button(QMessageBox::Yes)->text()).
		arg(nCountdown));
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
	strText.replace(QRegularExpression(R"(\d+)"), QString::number(nCountdown));
	m_pMessageBox->button(QMessageBox::Yes)->setText(strText);
}
}