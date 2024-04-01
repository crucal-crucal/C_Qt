#include "test.h"


test::test(QWidget* parent) : QMainWindow(parent) {
	// 必须为此窗口设置 ObjectName，否则会出现闪烁
	this->setObjectName("frmMaskWidget");
	createCtrl();
	layout();
	initConnection();

	this->resize(800, 600);

	QTimer::singleShot(1000, this, &test::initForm);
}

test::~test() = default;

void test::createCtrl() {
	m_pCenterWidget = new QWidget(this);
	m_pBtn = new QPushButton(this);
	m_pBtn->setText("Pop-up window");

	m_pBtnHLayout = new QHBoxLayout;
	m_pCenterVLayout = new QVBoxLayout;

	m_pCenterWidget->setLayout(m_pCenterVLayout);

	// 弹窗不能设置父对象，否则不会有阴影效果
	d = new QDialog();

	this->setCentralWidget(m_pCenterWidget);
}

void test::layout() {
	m_pBtnHLayout->addWidget(m_pBtn);
	m_pBtnHLayout->setAlignment(Qt::AlignLeft);

	m_pCenterVLayout->addLayout(m_pBtnHLayout);
	m_pCenterVLayout->addStretch();
}

void test::initConnection() {
	connect(m_pBtn, &QPushButton::clicked, this, &test::btn_clicked);
}

void test::initForm() {
	MaskWidget::Instance()->setMainWidget(this->topLevelWidget());
	MaskWidget::Instance()->setDialogNames(QStringList() << "formTest");
}

void test::btn_clicked() {
	d->setObjectName("formTest");
	d->setWindowTitle("Test Mask Widget");
	d->resize(400, 300);
	d->exec();
}
