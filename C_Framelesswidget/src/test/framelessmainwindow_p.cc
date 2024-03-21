//
// Created by crucal on 2024-03-17.
//

#include "framelessmainwindow_p.h"

framelessmainwindow_p::framelessmainwindow_p(QWidget* parent) : FramelessMainWindow(parent) {
	createCtrl();
	layout();
	initConnection();
	initStyle();
	resize(600, 300);
}

void framelessmainwindow_p::createCtrl() {
	m_pLbTitle = new QLabel(this);
	m_pLbTitle->setFixedHeight(50);

	m_pLbTitleText = new QLabel(this);
	m_pLbTitleText->setText(tr("FramelessMainwindow"));
	this->setWindowTitle(m_pLbTitleText->text());
	this->setTitleBar(m_pLbTitle);

	m_pBtnMin = new QPushButton(this);
	m_pBtnMin->setText(tr("Min"));
	m_pBtnMax = new QPushButton(this);
	m_pBtnMax->setText(tr("Max"));
	m_pBtnClose = new QPushButton(this);
	m_pBtnClose->setText(tr("Close"));

	m_pCenterWidget = new QWidget(this);

	m_pHBoxLayTitle = new QHBoxLayout;
	m_pVBoxLayCenter = new QVBoxLayout;

	this->setCentralWidget(m_pCenterWidget);
}

void framelessmainwindow_p::layout() {
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
	m_pVBoxLayCenter->addStretch();

	m_pCenterWidget->setLayout(m_pVBoxLayCenter);
}

void framelessmainwindow_p::initConnection() {
	connect(this, &framelessmainwindow_p::titleDblClick, this, &framelessmainwindow_p::on_btnMax_clicked);
	connect(this, &framelessmainwindow_p::windowStateChange, this, [&](bool bl) {
		m_pBtnMax->setText(bl ? tr("Normal") : tr("Max"));
	});
	connect(m_pBtnMin, &QPushButton::clicked, this, &framelessmainwindow_p::on_btnMin_clicked);
	connect(m_pBtnMax, &QPushButton::clicked, this, &framelessmainwindow_p::on_btnMax_clicked);
	connect(m_pBtnClose, &QPushButton::clicked, this, &framelessmainwindow_p::on_btnClose_clicked);
}

void framelessmainwindow_p::initStyle() {
	m_pCenterWidget->setStyleSheet("background-color: black;");
	m_pLbTitle->setStyleSheet("background-color: grey; color: white;");
}

void framelessmainwindow_p::on_btnMin_clicked() {
#ifdef Q_OS_MACOS
	this->setWindowFlags(this->windowFlags() & ~Qt::FramelessWindowHint);
#endif
	this->showMinimized();
}

void framelessmainwindow_p::on_btnMax_clicked() {
	if (this->isFullScreen()) {
		this->showNormal();
		m_pBtnMax->setText(tr("Max"));
	} else {
		this->showFullScreen();
		m_pBtnMax->setText(tr("Normal"));
	}
}

void framelessmainwindow_p::on_btnClose_clicked() {
	this->close();
}
