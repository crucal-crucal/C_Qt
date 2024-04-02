#include "uvmessagebox.h"

#include <utility>

CUVMessageBase::CUVMessageBase(QWidget* parent, QString title, QString text, QString okButtonText, QString cancelButtonText,
							   QString iconPath, bool showWarn, bool showOKBtn, bool showCancelBtn)
	: QDialog(parent), m_title(std::move(title)), m_text(std::move(text)), m_okButtonText(std::move(okButtonText)),
	  m_cancelButtonText(std::move(cancelButtonText)), m_iconPath(std::move(iconPath)), m_showWarn(showWarn), m_showOKBtn(showOKBtn), m_showCancelBtn(showCancelBtn) {
	setObjectName("CUVDeleteBase");
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::Dialog);
	setAttribute(Qt::WA_DeleteOnClose);
	createCtrl();
	layOut();
	initConnection();
	QSize newSize = !m_iconPath.isEmpty() ? QSize(450, 292) : QSize(300, 100);
	resize(newSize);
}

CUVMessageBase::~CUVMessageBase() = default;

void CUVMessageBase::createCtrl() {
	m_pLbTitle = new QLabel(m_title, this);
	m_pLbTitle->setObjectName("CUVDeleteWidget_LbTitle");

	m_pBtnClose = new QPushButton(this);
	m_pBtnClose->setObjectName("CUVDeleteWidget_BtnClose");
	m_pBtnClose->setFixedSize(QSize(20, 20));

	m_pixmap.load(m_iconPath);
	m_pLbIcon = new QLabel(this);
	m_pLbIcon->setPixmap(m_pixmap);
	m_pLbIcon->setObjectName("CUVDeleteWidget_LbIcon");
	m_pLbIcon->setVisible(!m_iconPath.isEmpty());

	m_pLbText = new QLabel(m_text, this);
	m_pLbText->setObjectName("CUVDeleteWidget_LbText");
	m_pLbText->setAlignment(Qt::AlignCenter);

	m_pBtnOk = new QPushButton(m_okButtonText, this);
	m_pBtnOk->setObjectName("CUVDeleteWidget_BtnOk");
	m_pBtnOk->setVisible(m_showOKBtn);

	m_pBtnCancel = new QPushButton(m_cancelButtonText, this);
	m_pBtnCancel->setObjectName("CUVDeleteWidget_BtnCancel");
	m_pBtnCancel->setVisible(m_showCancelBtn);

	m_pCbWarn = new QCheckBox(this);
	m_pCbWarn->setText(tr("No Prompt"));
	m_pCbWarn->setObjectName("CUVDeleteWidget_CbWarn");
	m_pCbWarn->setVisible(m_showWarn);

	m_pCenterVLayout = new QVBoxLayout;
	m_pTitleHLayout = new QHBoxLayout;
	m_pBtnHLayout = new QHBoxLayout;
}

void CUVMessageBase::layOut() {
	m_pTitleHLayout->setMargin(0);
	m_pTitleHLayout->addWidget(m_pLbTitle);
	m_pTitleHLayout->addStretch();
	m_pTitleHLayout->addWidget(m_pBtnClose);

	m_pBtnHLayout->setMargin(0);
	m_pBtnHLayout->addStretch();
	m_pBtnHLayout->addWidget(m_pBtnOk);
	m_pBtnHLayout->addSpacing(m_showOKBtn && m_showCancelBtn ? 50 : 0);
	m_pBtnHLayout->addWidget(m_pBtnCancel);
	m_pBtnHLayout->addStretch();
	m_pBtnHLayout->setAlignment(Qt::AlignHCenter);

	m_pCenterVLayout->setContentsMargins(20, 20, 20, 20);
	m_pCenterVLayout->addLayout(m_pTitleHLayout);
	auto* LbIconHLayout = new QHBoxLayout;
	LbIconHLayout->setMargin(0);
	LbIconHLayout->setSpacing(0);
	LbIconHLayout->addWidget(m_pLbIcon);
	LbIconHLayout->setAlignment(Qt::AlignCenter);
	m_pCenterVLayout->addSpacing(20);
	m_pCenterVLayout->addLayout(LbIconHLayout);
	m_pCenterVLayout->addSpacing(m_iconPath.isEmpty() ? 0 : 10);
	m_pCenterVLayout->addWidget(m_pLbText);
	m_pCenterVLayout->addSpacing(10);
	m_pCenterVLayout->addLayout(m_pBtnHLayout);
	auto* CbWarnHLayout = new QHBoxLayout;
	CbWarnHLayout->setMargin(0);
	CbWarnHLayout->setSpacing(0);
	CbWarnHLayout->addWidget(m_pCbWarn);
	CbWarnHLayout->setAlignment(Qt::AlignCenter);
	m_pCenterVLayout->addLayout(CbWarnHLayout);

	setLayout(m_pCenterVLayout);
}

void CUVMessageBase::initConnection() {
	connect(m_pBtnClose, &QPushButton::clicked, this, &CUVMessageBase::close);
	connect(m_pBtnOk, &QPushButton::clicked, this, &CUVMessageBase::onBtnOkClicked);
	connect(m_pBtnCancel, &QPushButton::clicked, this, &CUVMessageBase::close);
	connect(m_pCbWarn, &QCheckBox::stateChanged, this, [&](int state) {
		emit checkBoxState(state);
	});
}

void CUVMessageBase::mousePressEvent(QMouseEvent* event) {
	if (m_bMoveEnable && event->button() == Qt::LeftButton && m_rtTitle.contains(event->pos())) {
		m_PressTitlePoint = event->pos();
		m_bPressTitle = true;
	}
	QDialog::mousePressEvent(event);
}

void CUVMessageBase::mouseReleaseEvent(QMouseEvent* event) {
	if (m_bPressTitle) {
		m_bPressTitle = false;
	}
	QDialog::mouseReleaseEvent(event);
}

void CUVMessageBase::mouseMoveEvent(QMouseEvent* event) {
	if (m_bPressTitle) {
		move(event->globalPos() - m_PressTitlePoint);
	}
	QDialog::mouseMoveEvent(event);
}

void CUVMessageBase::resizeEvent(QResizeEvent* event) {
	m_rtTitle = rect().adjusted(1, 2, -2, 0);
	m_rtTitle.setBottom(m_rtTitle.top() + m_pLbTitle->height());
	QDialog::resizeEvent(event);
}

void CUVMessageBase::keyPressEvent(QKeyEvent* event) {
	if (!m_bEscEnable && Qt::Key_Escape == event->key()) {
		return;
	} else if (!m_bEnterEnable && (Qt::Key_Return == event->key() || Qt::Key_Enter == event->key())) {
		auto key = Qt::Key(event->key());
		emit okClicked();
		return;
	} else {
		QDialog::keyPressEvent(event);
	}
}

void CUVMessageBase::setTitle(const QString& title) const {
	m_pLbTitle->setText(title);
}

void CUVMessageBase::setText(const QString& text) const {
	m_pLbText->setText(text);
}

void CUVMessageBase::setOkButtonText(const QString& okButtonText) const {
	m_pBtnOk->setText(okButtonText);
}

void CUVMessageBase::setCancelButtonText(const QString& cancelButtonText) const {
	m_pBtnCancel->setText(cancelButtonText);
}

void CUVMessageBase::setIcon(const QString& iconPath, bool fill) {
	m_pixmap.load(iconPath);
	m_pLbIcon->setPixmap(m_pixmap);
	m_pLbIcon->setScaledContents(fill);
}

void CUVMessageBase::setShowWarn(bool showWarn) const {
	m_pCbWarn->setVisible(showWarn);
}

void CUVMessageBase::setMoveEnable(bool bEnable) {
	m_bMoveEnable = bEnable;
}

void CUVMessageBase::setEscEnable(bool bEnable) {
	m_bEscEnable = bEnable;
}

void CUVMessageBase::setEnterEnable(bool bEnable) {
	m_bEnterEnable = bEnable;
}

void CUVMessageBase::onBtnOkClicked() {
	emit okClicked();
	this->close();
}

// CUVMessageBox
bool CUVMessageBox::showAgain = true;

CUVMessageBox::CUVMessageBox(QWidget* parent) : QObject(parent) {
}

CUVMessageBox::~CUVMessageBox() = default;

CUVMessageBase::E_BUTTON_STATUS CUVMessageBox::showMessage(QWidget* parent, const QString& title, const QString& text, bool showWarn,
														   bool showOkBtn, bool showCancelBtn, const QString& iconPath, const QString& okButtonText,
														   const QString& cancelButtonText) {
	auto res = CUVMessageBase::E_BUTTON_STATUS::CANCEL;
	if (!showAgain && showWarn) {
		return CUVMessageBase::E_BUTTON_STATUS::OK;
	}
	QPointer<CUVMessageBase> ptr = new CUVMessageBase(parent, title, text, okButtonText, cancelButtonText, iconPath, showWarn, showOkBtn, showCancelBtn);
	connect(ptr, &CUVMessageBase::okClicked, [&]() {
		res = CUVMessageBase::E_BUTTON_STATUS::OK;
	});
	connect(ptr, &CUVMessageBase::checkBoxState, [&](int state) {
		showAgain = state != Qt::CheckState::Checked;
	});
	ptr->exec();
	return res;
}

CUVMessageBase::E_BUTTON_STATUS CUVMessageBox::about(QWidget* parent, const QString& title, const QString& text) {
	return showMessage(parent, title, text, false, false, false, "", "", "");
}

CUVMessageBase::E_BUTTON_STATUS CUVMessageBox::critical(QWidget* parent, const QString& title, const QString& text) {
	return showMessage(parent, title, text, false, true, false, "", "", "");
}

CUVMessageBase::E_BUTTON_STATUS CUVMessageBox::infomation(QWidget* parent, const QString& title, const QString& text, const QString& okButtonText) {
	return showMessage(parent, title, text, false, true, false, "", okButtonText, "");
}

CUVMessageBase::E_BUTTON_STATUS CUVMessageBox::waring(QWidget* parent, const QString& title, const QString& text, const QString& okButtonText) {
	return showMessage(parent, title, text, false, true, false, "", okButtonText, "");
}

CUVMessageBase::E_BUTTON_STATUS CUVMessageBox::question(QWidget* parent, const QString& title, const QString& text, const QString& okButtonText, const QString& cancelButtonText) {
	return showMessage(parent, title, text, false, true, true, "", okButtonText, cancelButtonText);
}

// CUVCountdownMessageBox
CUVCountdownMessageBox::CUVCountdownMessageBox(QWidget* parent, const QString& title, const QString& text, const QString& okButtonText, const QString& cancelButtonText,
											   const QString& iconPath, bool showWarn, bool showOKBtn, bool showCancelBtn)
	: CUVMessageBase(parent, title, text, okButtonText, cancelButtonText, iconPath, showWarn, showOKBtn, showCancelBtn) {

}

CUVCountdownMessageBox::~CUVCountdownMessageBox() = default;

int CUVCountdownMessageBox::exec(int nSecond) {
	nCountdown = nSecond;
	this->startTimer(1000);
	return CUVMessageBase::exec();
}

void CUVCountdownMessageBox::timerEvent(QTimerEvent* event) {
	nCountdown--;
	if (nCountdown <= 0) {
		this->killTimer(event->timerId());
		this->onBtnOkClicked();
	}
}
