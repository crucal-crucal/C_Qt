#include "test.h"

#include "codec/codec_p.h"

Test::Test(const WINDOWLANAGUAGE Lanaguage, const WINDOWTHEMESTYLE ThemeStyle, QWidget* parent)
: FramelessMainWindow(parent), m_language(Lanaguage), m_ThemeStyle(ThemeStyle) {
	createCtrl();
	customLayout();
	init();
	initConnection();
	this->resize(800, 600);
}

Test::~Test() = default;

void Test::createCtrl() {
	m_pCentralWidget = this->createWidget<QWidget>(this, "CPatch_CentralWidget");
	m_pTitleBar = this->createWidget<QWidget>(m_pCentralWidget);
	this->setTitleBar(m_pTitleBar);

	m_pBtnStyle = this->createWidget<QPushButton>(m_pTitleBar, "CPatch_BtnStyle");
	m_pBtnStyle->setCheckable(true);
	m_pBtnStyle->setToolTip(tr("Change Style"));

	m_pBtnMin = this->createWidget<QPushButton>(m_pTitleBar, "Dialog_Btn_Min");
	m_pBtnMin->setToolTip(tr("Min"));

	m_pBtnClose = this->createWidget<QPushButton>(m_pTitleBar, "Dialog_Btn_Close");
	m_pBtnClose->setToolTip(tr("Close"));

	m_pMenuBar = this->createWidget<QMenuBar>(m_pTitleBar, "Main_MenuBar");

	m_menuPreference = m_pMenuBar->addMenu(tr("Preference"));

	m_menuLanguage = m_menuPreference->addMenu(tr("Language"));
	m_pActGroupLanguage = this->createWidget<QActionGroup>(m_menuLanguage);
	m_pActChinese = m_pActGroupLanguage->addAction(tr("CHINESE"));
	m_pActEnglish = m_pActGroupLanguage->addAction(tr("ENGLISH"));
	m_pActChinese->setCheckable(true);
	m_pActEnglish->setCheckable(true);

	m_menuLanguage->addActions(m_pActGroupLanguage->actions());
	m_pActGroupLanguage->setExclusive(true); // 设置互斥

	m_plyHTitle = this->createWidget<QHBoxLayout>(m_pTitleBar);
	m_pCentralLayout = this->createWidget<QVBoxLayout>(m_pCentralWidget);

	this->setMenuWidget(m_pTitleBar);
	this->setCentralWidget(m_pCentralWidget);
}

void Test::customLayout() const {
	m_plyHTitle->addWidget(m_pMenuBar);
	m_plyHTitle->addStretch();
	m_plyHTitle->addWidget(m_pBtnStyle);
	m_plyHTitle->addWidget(m_pBtnMin);
	m_plyHTitle->addWidget(m_pBtnClose);
	m_plyHTitle->setContentsMargins(0, 0, 0, 0);

	m_pTitleBar->setLayout(m_plyHTitle);

	m_pCentralLayout->addWidget(m_pTitleBar);
}

void Test::init() {
	recoveryStateWithAct();
	m_pMenuBar->setFixedWidth(m_language == WINDOWLANAGUAGE::Chinese ? CHINESE_MENUBAR_WIDTH : ENGLISH_MENUBAR_WIDTH);

	m_pBtnStyle->setChecked(m_ThemeStyle == WINDOWTHEMESTYLE::LIGHT);
}

void Test::initConnection() {
	connect(m_pBtnClose, &QPushButton::clicked, this, &Test::close);
	connect(m_pBtnMin, &QPushButton::clicked, this, &Test::showMinimized);
	connect(m_pActQuit, &QAction::triggered, this, &Test::close);
	connect(m_pActShow, &QAction::triggered, this, &Test::show);
	connect(m_ptrayIcon, &QSystemTrayIcon::activated, this, &Test::onSystemTrayIconActivated);
	connect(m_pBtnStyle, &QPushButton::clicked, this, &Test::onBtnStyleClicked);
}

void Test::restart() {
	qApp->exit(RETCODE_RESTART);
}

void Test::recoveryStateWithAct() const {
	m_pActChinese->setChecked(m_language == WINDOWLANAGUAGE::Chinese);
	m_pActEnglish->setChecked(m_language == WINDOWLANAGUAGE::English);
}

void Test::setSystemTrayIcon() {
	if (m_ptrayIcon) {
		return;
	}

	m_ptrayIcon = new QSystemTrayIcon(this);
	m_ptrayMenu = std::make_unique<QMenu>();
	m_pActShow = new QAction(QObject::tr("Show"), m_ptrayMenu.get());
	m_pActQuit = new QAction(QObject::tr("Exit"), m_ptrayMenu.get());
	m_ptrayMenu->addAction(m_pActShow);
	m_ptrayMenu->addAction(m_pActQuit);
	m_ptrayMenu->setWindowFlag(Qt::FramelessWindowHint);
	m_ptrayMenu->setAttribute(Qt::WA_TranslucentBackground);
	m_ptrayIcon->setToolTip(QObject::tr("C_testffmpeg"));
	m_ptrayIcon->setIcon(QIcon(":/icon/start.png"));

	m_ptrayIcon->setContextMenu(m_ptrayMenu.get());
	m_ptrayIcon->show();
}

void Test::onBtnStyleClicked() {
	m_ThemeStyle = m_pBtnStyle->isChecked() ? WINDOWTHEMESTYLE::LIGHT : WINDOWTHEMESTYLE::DARK;
	emit ThemeChanged(m_ThemeStyle);
}

void Test::onActChineseClicked() {
	if (const auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change language"),
	                                                            tr("reboot applicaion to take effect")); nRes ==
		QMessageBox::ButtonRole::AcceptRole) {
		m_language = WINDOWLANAGUAGE::Chinese;
		emit ConfChanged(m_language, m_ThemeStyle);
		Test::restart();
	} else {
		recoveryStateWithAct();
	}
}

void Test::onActEnglishClicked() {
	if (const auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change language"),
	                                                            tr("reboot applicaion to take effect")); nRes ==
		QMessageBox::ButtonRole::AcceptRole) {
		m_language = WINDOWLANAGUAGE::English;
		emit ConfChanged(m_language, m_ThemeStyle);
		Test::restart();
	} else {
		recoveryStateWithAct();
	}
}

void Test::onSystemTrayIconActivated(const QSystemTrayIcon::ActivationReason reason) {
	if (reason == QSystemTrayIcon::DoubleClick) {
		// 双击显示
		this->isMinimized() ? this->showNormal() : this->showMinimized(); // 将主窗口显示出来
		this->activateWindow();                                           // 激活主窗口，确保它位于顶部
	} else if (reason == QSystemTrayIcon::Context) {
		// 右键菜单
		// 调整显示始终在鼠标之上
		const auto pos = QCursor::pos();
		const int offsetY = m_ptrayMenu->sizeHint().height();
		m_ptrayMenu->move(pos.x(), pos.y() - offsetY);
		m_ptrayMenu->exec();
	}
}
