//
// Created by crucal on 2024-03-17.
//

#include "framelesswidget_p.hpp"

framelesswidget_p::framelesswidget_p(QWidget* parent) : FramelessWidget(parent) {
	createCtrl();
	layoutcustom();
	initConnection();
	initStyle();
	resize(600, 300);
}

void framelesswidget_p::createCtrl() {
	m_pLbTitle = new QLabel(this);
	m_pLbTitle->setFixedHeight(50);

	m_pLbTitleText = new QLabel(this);
	m_pLbTitleText->setText(tr("FramelessWidget"));
	this->setWindowTitle(m_pLbTitleText->text());
	this->setTitleBar(m_pLbTitle);

	m_pBtnMin = new QPushButton(this);
	m_pBtnMin->setText(tr("Min"));
	m_pBtnMax = new QPushButton(this);
	m_pBtnMax->setText(tr("Max"));
	m_pBtnClose = new QPushButton(this);
	m_pBtnClose->setText(tr("Close"));

	m_pCenterWidget = new QWidget(this);

	m_pHBoxLayTitle  = new QHBoxLayout;
	m_pVBoxLayCenter = new QVBoxLayout;

	this->setLayout(m_pVBoxLayCenter);
}

void framelesswidget_p::layoutcustom() const {
	m_pHBoxLayTitle->setMargin(0);
	m_pHBoxLayTitle->setSpacing(10);
	m_pHBoxLayTitle->addWidget(m_pLbTitleText);
	m_pHBoxLayTitle->addStretch();
	m_pHBoxLayTitle->addWidget(m_pBtnMin);
	m_pHBoxLayTitle->addWidget(m_pBtnMax);
	m_pHBoxLayTitle->addWidget(m_pBtnClose);

	m_pLbTitle->setLayout(m_pHBoxLayTitle);

	m_pVBoxLayCenter->setMargin(0);
	m_pVBoxLayCenter->setSpacing(0);
	m_pVBoxLayCenter->addWidget(m_pLbTitle);
	m_pVBoxLayCenter->addWidget(m_pCenterWidget);
}

void framelesswidget_p::initConnection() {
	connect(this, &framelesswidget_p::titleDblClick, this, &framelesswidget_p::onBtnMaxClicked);
	connect(this, &framelesswidget_p::windowStateChange, this, [&](const bool bl) {
		m_pBtnMax->setText(bl ? tr("Normal") : tr("Max"));
	});
	connect(m_pBtnMin, &QPushButton::clicked, this, &framelesswidget_p::onBtnMinClicked);
	connect(m_pBtnMax, &QPushButton::clicked, this, &framelesswidget_p::onBtnMaxClicked);
	connect(m_pBtnClose, &QPushButton::clicked, this, &framelesswidget_p::onBtnCloseClicked);
}

void framelesswidget_p::initStyle() const {
	m_pCenterWidget->setStyleSheet("background-color: black;");
	m_pLbTitle->setStyleSheet("background-color: grey; color: white;");
}

void framelesswidget_p::onBtnMinClicked() {
#ifdef Q_OS_MACOS
	this->setWindowFlags(this->windowFlags() & ~Qt::FramelessWindowHint);
#endif
	this->showMinimized();
}

void framelesswidget_p::onBtnMaxClicked() {
	if (this->isFullScreen()) {
		this->showNormal();
		m_pBtnMax->setText(tr("Max"));
	} else {
		this->showFullScreen();
		m_pBtnMax->setText(tr("Normal"));
	}
}

void framelesswidget_p::onBtnCloseClicked() {
	this->close();
}
