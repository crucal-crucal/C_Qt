//
// Created by crucal on 2024-03-17.
//

#include "test.h"

test::test(QWidget* parent) : QMainWindow(parent) {
	createCtrl();
	layoutcustom();
	initConnection();

	resize(800, 600);
}

test::~test() = default;

void test::createCtrl() {
	m_pBtnDialog = new QPushButton(this);
	m_pBtnDialog->setText(tr("Dialog"));

	m_pBtnWidget = new QPushButton(this);
	m_pBtnWidget->setText(tr("Widget"));

	m_pBtnMainWindow = new QPushButton(this);
	m_pBtnMainWindow->setText(tr("MainWindow"));

	m_pBtnMessageBox_1 = new QPushButton(this);
	m_pBtnMessageBox_1->setText(tr("MessageBox_1"));

	m_pBtnMessageBox_2 = new QPushButton(this);
	m_pBtnMessageBox_2->setText(tr("MessageBox_2"));

	m_pBtnFramelesshelper = new QPushButton(this);
	m_pBtnFramelesshelper->setText(tr("Framelesshelper"));
	m_pBtnFramelesshelper->setCheckable(true);

	m_pFramelessDialog = new framelessdialog_p(this);
	m_pFramelessDialog->setVisible(false);
	m_pFramelessWidget = new framelesswidget_p();
	m_pFramelessWidget->setVisible(false);
	m_pFramelessMainwindow = new framelessmainwindow_p(this);
	m_pFramelessMainwindow->setVisible(false);

	m_pFramelessHelperWidget = new QMainWindow(this);
	m_pFramelessHelperWidget->setVisible(false);
	m_pFramelessHelperWidget->setStyleSheet("background-color: rgb(0, 0, 0);");
	m_pFramelessHelperWidget->resize(400, 400);

	m_pFramelsssHelper = new QxFrameless::FramelessHelper(m_pFramelessHelperWidget);
	// m_pFramelsssHelper->addWidget(m_pFramelsssHelperWidget);

	m_pCenterWidget = new QWidget(this);

	m_pHLayout       = new QHBoxLayout;
	m_pCenterVLayout = new QVBoxLayout;

	this->setCentralWidget(m_pCenterWidget);
}

void test::layoutcustom() const {
	m_pHLayout->addStretch();
	m_pHLayout->addWidget(m_pBtnDialog);
	m_pHLayout->addWidget(m_pBtnWidget);
	m_pHLayout->addWidget(m_pBtnMainWindow);
	m_pHLayout->addWidget(m_pBtnMessageBox_1);
	m_pHLayout->addWidget(m_pBtnMessageBox_2);
	m_pHLayout->addWidget(m_pBtnFramelesshelper);

	m_pCenterVLayout->addLayout(m_pHLayout);
	m_pCenterVLayout->addStretch();

	m_pCenterWidget->setLayout(m_pCenterVLayout);
}

void test::initConnection() {
	connect(m_pBtnWidget, &QPushButton::clicked, [=]() {
		m_pFramelessWidget->show();
	});
	connect(m_pBtnDialog, &QPushButton::clicked, [=]() {
		m_pFramelessDialog->show();
	});
	connect(m_pBtnMainWindow, &QPushButton::clicked, [=]() {
		m_pFramelessMainwindow->show();
	});
	connect(m_pBtnMessageBox_1, &QPushButton::clicked, [=]() {
		UVMessageBox::CUVMessageBox::information(this, "information", "MessageBox_1");
	});
	connect(m_pBtnMessageBox_2, &QPushButton::clicked, [=]() {
		CUVMessageBox::infomation(this, "information", "MessageBox_2");
	});
	connect(m_pBtnFramelesshelper, &QPushButton::clicked, [=](const bool checked) {
		m_pFramelessHelperWidget->setVisible(checked);
	});
}
