#include "test.h"


test::test(QWidget* parent) : QMainWindow(parent) {
	// 必须为此窗口设置 ObjectName，否则会出现闪烁
	this->setObjectName("frmMaskWidget");
	createCtrl();
	layout();
	initConnection();

	this->resize(800, 600);

//	QTimer::singleShot(1000, this, &test::initForm);
}

test::~test() = default;

void test::createCtrl() {
	m_pCenterWidget = new QWidget(this);
	m_pBtn1 = new QPushButton(this);
	m_pBtn1->setText("Pop-up window1");

	m_pBtn2 = new QPushButton(this);
	m_pBtn2->setText("Pop-up window2");

	m_pBtnHLayout = new QHBoxLayout;
	m_pCenterVLayout = new QVBoxLayout;

	m_pCenterWidget->setLayout(m_pCenterVLayout);

	// 通过寻找 ObjectName 的方式不能设置父对象
	d1 = new QDialog();
	// 另一种直接添加一个 Widget 则可以设置父对象
	d2 = new QDialog(this);

	this->setCentralWidget(m_pCenterWidget);
}

void test::layout() {
	m_pBtnHLayout->addWidget(m_pBtn1);
	m_pBtnHLayout->addWidget(m_pBtn2);
	m_pBtnHLayout->setAlignment(Qt::AlignLeft);

	m_pCenterVLayout->addLayout(m_pBtnHLayout);
	m_pCenterVLayout->addStretch();
}

void test::initConnection() {
	connect(m_pBtn1, &QPushButton::clicked, this, &test::btn1_clicked);
	connect(m_pBtn2, &QPushButton::clicked, this, &test::btn2_clicked);
}

void test::initForm() {
	MaskWidget::Instance()->setMainWidget(this->topLevelWidget());
	MaskWidget::Instance()->setDialogNames(QStringList() << "formTest");
}

void test::btn1_clicked() {
	initForm();
	d1->setObjectName("formTest");
	d1->setWindowTitle("Test Mask Widget");
	d1->resize(400, 300);
	d1->exec();
}

void test::btn2_clicked() {
	// 遮罩
	QScopedPointer<QWidget> shadow(new QWidget(this));
	shadow->setFixedSize(this->size());
	QPalette pal(shadow->palette());
	pal.setColor(QPalette::Window, QColor(0, 0, 0, 90));
	// 设置阴影层自动填充背景，以使颜色生效
	shadow->setAutoFillBackground(true);
	shadow->setPalette(pal);
	// 将阴影层放置在当前窗口的下方，使阴影层处于当前窗口的后面
	shadow->stackUnder(this);
	shadow->setVisible(true);

	d2->setWindowTitle("Test Mask Widget");
	d2->resize(400, 300);
	d2->exec();

	shadow->deleteLater();
}
