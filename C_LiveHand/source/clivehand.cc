#include "clivehand.h"

#include <QSettings>
#include <QDomElement>
#include <QHeaderView>

#include "codec/codec_p.h"
#include "framelessMessageBox/uvfiledialog.h"

CLiveHand::CLiveHand(const WINDOWLANAGUAGE Lanaguage, const WINDOWTHEMESTYLE ThemeStyle, QWidget* parent)
: FramelessMainWindow(parent), m_language(Lanaguage), m_ThemeStyle(ThemeStyle) {
	QString strConfigIniPath = qApp->applicationDirPath() + "/config/watchProcess.ini";
	QSettings setting(strConfigIniPath, QSettings::IniFormat);
	m_pProcessName = setting.value("process/name").toString();
	m_strTitle = QString("%1 Watchman").arg(m_pProcessName);

	createCtrl();
	customLayout();
	init();
	initConnection();
	initData();
	this->resize(800, 600);
}

CLiveHand::~CLiveHand() {
	destroy();
}

void CLiveHand::readConfig() {
	QString strSavePath = qApp->applicationDirPath() + "/config/clips.xml";
	if (QFile::exists(strSavePath)) {
		QFile file(strSavePath);
		if (file.open(QFile::ReadOnly | QFile::Text)) {
			QDomDocument xmldoc{};
			if (xmldoc.setContent(&file)) {
				auto infoNode = xmldoc.documentElement();
				int nCurPending = infoNode.attribute("pendingFillerPiece").toInt();
				if (!infoNode.isNull()) {
					auto clipEle = infoNode.firstChildElement("Clip");
					while (!clipEle.isNull()) {
						QString strPath = clipEle.attribute("path");
						appendItem(strPath);
						clipEle = clipEle.nextSiblingElement("Clop");
					}
				}
				if (auto item = m_pFillerPieceTable->item(nCurPending, 0)) {
					for (int i = 0; i < m_pFillerPieceTable->rowCount(); i++) {
						if (auto item1 = m_pFillerPieceTable->item(i, 0)) {
							if (item1->data(Qt::UserRole + 3).value<bool>()) {
								item->setData(Qt::UserRole + 3, false);
								m_pFillerPieceTable->item(item1->row(), 2)->setIcon(QIcon());
								m_pFillerPieceTable->item(item1->row(), 2)->setToolTip("");
								break;
							}
						}
					}
					item->setData(Qt::UserRole + 3, true);
					m_pFillerPieceTable->item(item->row(), 2)->setIcon(QIcon(":/icon/blue_dot.png"));
					m_pFillerPieceTable->item(item->row(), 2)->setToolTip(tr("Pending Fillerpiece"));
				}
			}
		}
	}
}

void CLiveHand::saveConfig() {
	QDomDocument doc{};
	QDomElement infoElement = doc.createElement("ClipInfo");
	for (int i = 0; i < m_pFillerPieceTable->rowCount(); i++) {
		if (auto item = m_pFillerPieceTable->item(i, 0)) {
			if (item->data(Qt::UserRole + 3).value<bool>()) {
				infoElement.setAttribute("pendingFillerPiece", i);
				break;
			}
		}
	}
	for (int i = 0; i < m_pFillerPieceTable->rowCount(); i++) {
		if (auto item = m_pFillerPieceTable->item(i, 0)) {
			if (!m_pFillerPieceTable->item(item->row(), 0)->data(Qt::UserRole + 1).value<bool>()) {
				QDomElement clipEle = doc.createElement("Clip");
				QString strFilePath = item->text();
				clipEle.setAttribute("path", strFilePath);
				infoElement.appendChild(clipEle);
			}
		}
	}
	doc.appendChild(infoElement);

	QString strSavePath = qApp->applicationDirPath() + "/config/clips.xml";
	QFile file(strSavePath);
	if (file.open(QFile::WriteOnly)) {
		QTextStream out(&file);
		out.setCodec("UTF-8");
		doc.save(out, 4, QDomNode::EncodingFromTextStream);
	}
}

void CLiveHand::appendItem(const QString& strFile, bool bLock, bool bCurrent) {
	auto* item = new QTableWidgetItem(strFile);
	item->setText(strFile);
	item->setToolTip(strFile);
	int nRow = m_pFillerPieceTable->rowCount();
	m_pFillerPieceTable->insertRow(m_pFillerPieceTable->rowCount());
	m_pFillerPieceTable->setItem(nRow, 0, item);
	auto* lockItem = new QTableWidgetItem();
	if (bLock) {
		item->setData(Qt::UserRole + 1, true);
		lockItem->setIcon(QIcon(":/icon/lock.png"));
		lockItem->setToolTip(tr("Clip_Lock"));
	}
	m_pFillerPieceTable->setItem(nRow, 1, lockItem);
	auto* stateItem = new QTableWidgetItem();
	if (bCurrent) {
		item->setData(Qt::UserRole + 3, true);
		stateItem->setIcon(QIcon(":/icon/blue_dot.png"));
		stateItem->setToolTip(tr("Pending Fillerpiece"));
	}
	m_pFillerPieceTable->setItem(nRow, 2, stateItem);
	if (m_pBtnFillerPieceSwitch->isChecked()) {
		m_pLbFillerPieceTip->setText(tr("Fillerpiece Tip Except").arg(m_pProcessName));
		m_pLbFillerPieceTip->setStyleSheet("color:white");
	}
}

void CLiveHand::removeItem(QTableWidgetItem* item) {
	if (item->data(Qt::UserRole + 3).value<bool>()) {
		if (m_pFillerPieceTable->rowCount() > 0) {
			m_pFillerPieceTable->item(0, 0)->setData(Qt::UserRole + 3, true);
			m_pFillerPieceTable->item(0, 2)->setIcon(QIcon(":/icon/blue_dot.png"));
			m_pFillerPieceTable->item(0, 2)->setToolTip(tr("Pending Fillerpiece"));
		}
	}
	m_pFillerPieceTable->removeRow(item->row());
	if (m_pFillerPieceTable->rowCount() == 0) {
		m_pLbFillerPieceTip->setText(tr("Fillerpiece Tip Empty").arg(m_pProcessName));
		m_pLbFillerPieceTip->setStyleSheet("color:red");
	}
}

void CLiveHand::createCtrl() {
	m_pCentralWidget = new QWidget(this);
	m_pCentralWidget->setObjectName("CLiveHand_CentralWidget");
	m_pTitleBar = new QWidget(m_pCentralWidget);
	this->setTitleBar(m_pTitleBar);

	m_pBtnStyle = new QPushButton(m_pTitleBar);
	m_pBtnStyle->setCheckable(true);
	m_pBtnStyle->setObjectName("CLiveHand_BtnStyle");
	m_pBtnStyle->setToolTip(tr("Change Style"));

	m_pBtnMin = new QPushButton(m_pTitleBar);
	m_pBtnMin->setObjectName("CLiveHand_Btn_Min");
	m_pBtnMin->setToolTip(tr("Min"));

	m_pBtnClose = new QPushButton(m_pTitleBar);
	m_pBtnClose->setObjectName("CLiveHand_Btn_Close");
	m_pBtnClose->setToolTip(tr("Close"));

	m_pMenuBar = new QMenuBar(m_pTitleBar);
	m_pMenuBar->setObjectName("Main_MenuBar");

	m_menuPreference = m_pMenuBar->addMenu(tr("Preference"));

	m_menuLanguage = m_menuPreference->addMenu(tr("Language"));
	m_pActGroupLanguage = new QActionGroup(m_menuLanguage);
	m_pActChinese = m_pActGroupLanguage->addAction(tr("CHINESE"));
	m_pActEnglish = m_pActGroupLanguage->addAction(tr("ENGLISH"));
	m_pActChinese->setCheckable(true);
	m_pActEnglish->setCheckable(true);

	m_menuLanguage->addActions(m_pActGroupLanguage->actions());
	m_pActGroupLanguage->setExclusive(true); // 设置互斥

	m_pLbHostStatus = new QLabel(tr("Status Unknown"), m_pCentralWidget);
	m_pLbFillerPieceStatus = new QLabel(tr("Status_Enable"), m_pCentralWidget);
	m_pBtnFillerPieceSwitch = new QPushButton(m_pCentralWidget);
	m_pBtnFillerPieceSwitch->setObjectName("CLiveHand_SwitchBtn");
	m_pBtnFillerPieceSwitch->setCheckable(true);
	m_pBtnFillerPieceSwitch->setChecked(true);

	m_pBtnFillerPieceStop = new QPushButton(tr("Stop"), m_pCentralWidget);
	m_pBtnFillerPieceStop->setFixedWidth(100);
	m_pBtnFillerPieceStop->setEnabled(false);
	m_pPlayWidget = new CPlayBackWidget(m_pCentralWidget);

	m_pBtnAppendFillerPiece = new QPushButton(tr("Append Fillerpiece"), m_pCentralWidget);
	m_pBtnAppendFillerPiece->setFixedWidth(100);

	m_pFillerPieceTable = new QTableWidget(m_pCentralWidget);
	m_pFillerPieceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pFillerPieceTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
	m_pFillerPieceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pFillerPieceTable->horizontalHeader()->setStretchLastSection(true);
	m_pFillerPieceTable->horizontalHeader()->hide();
	m_pFillerPieceTable->verticalHeader()->hide();
	m_pFillerPieceTable->setColumnCount(3);
	m_pFillerPieceTable->setColumnWidth(0, 480);
	m_pFillerPieceTable->setColumnWidth(1, 40);
	m_pFillerPieceTable->setColumnWidth(2, 20);
	m_pFillerPieceTable->setShowGrid(false);
	m_pFillerPieceTable->setContextMenuPolicy(Qt::CustomContextMenu);
	m_pFillerPieceTable->setFocusPolicy(Qt::NoFocus);

	m_pLbFillerPieceTip = new QLabel(tr("Fillerpiece Tip Empty").arg(m_pProcessName), m_pCentralWidget);
	m_pLbFillerPieceTip->setStyleSheet("color:red");

	m_pLyFormStatus = new QFormLayout;
	m_pLyHFillerPiece = new QHBoxLayout;
	m_pLyVStatus = new QVBoxLayout;
	m_pLyHPlay = new QHBoxLayout;

	m_pLyHFillerPieceListTitle = new QHBoxLayout;
	m_pLyVFillerPieceTotal = new QVBoxLayout;

	m_pLyHTitle = new QHBoxLayout(m_pTitleBar);
	m_pCentralLayout = new QVBoxLayout(m_pCentralWidget);

	this->setMenuWidget(m_pTitleBar);
	this->setCentralWidget(m_pCentralWidget);
}

void CLiveHand::customLayout() {
	m_pLyHTitle->addWidget(m_pMenuBar);
	m_pLyHTitle->addStretch();
	m_pLyHTitle->addWidget(m_pBtnStyle);
	m_pLyHTitle->addWidget(m_pBtnMin);
	m_pLyHTitle->addWidget(m_pBtnClose);
	m_pLyHTitle->setContentsMargins(0, 0, 0, 0);

	m_pTitleBar->setLayout(m_pLyHTitle);

	m_pLyFormStatus->addRow(tr("IDS_HOST_STATUS").arg(m_pProcessName), m_pLbHostStatus);
	m_pLyFormStatus->addRow(tr("IDS_FILLERPIECE_STATUS"), m_pLbFillerPieceStatus);
	m_pLyFormStatus->addRow(tr("IDS_FILLERPIECE_SWITCH"), m_pBtnFillerPieceSwitch);
	m_pLyFormStatus->setLabelAlignment(Qt::AlignRight);

	m_pLyHFillerPiece->addStretch();
	m_pLyHFillerPiece->addWidget(m_pBtnFillerPieceStop);
	m_pLyHFillerPiece->addStretch();

	m_pLyVStatus->addLayout(m_pLyFormStatus);
	m_pLyVStatus->addLayout(m_pLyHFillerPiece);
	m_pLyVStatus->addStretch();
	m_pLyVStatus->setContentsMargins(20, 0, 0, 0);
	m_pLyVStatus->setSpacing(20);

	m_pLyHPlay->addLayout(m_pLyVStatus);
	m_pLyHPlay->addStretch();
	m_pLyHPlay->addWidget(m_pPlayWidget);
	m_pLyHPlay->setContentsMargins(0, 20, 0, 0);

	m_pLyHFillerPieceListTitle->addWidget(new QLabel(tr("Fillerpiece Table"), this));
	m_pLyHFillerPieceListTitle->addWidget(m_pBtnAppendFillerPiece);

	m_pLyVFillerPieceTotal->addLayout(m_pLyHFillerPieceListTitle);
	m_pLyVFillerPieceTotal->addWidget(m_pFillerPieceTable);
	m_pLyVFillerPieceTotal->addWidget(m_pLbFillerPieceTip);

	m_pCentralLayout->addWidget(m_pTitleBar);
	m_pCentralLayout->addLayout(m_pLyHPlay, 1);
	m_pCentralLayout->addLayout(m_pLyVFillerPieceTotal, 2);
}

void CLiveHand::init() {
	recoveryStateWithAct();
	// m_pMenuBar->setFixedWidth(m_language == WINDOWLANAGUAGE::Chinese ? CHINESE_MENUBAR_WIDTH : ENGLISH_MENUBAR_WIDTH);
	m_pMenuBar->setFixedWidth(ENGLISH_MENUBAR_WIDTH);
	m_pBtnStyle->setChecked(m_ThemeStyle == WINDOWTHEMESTYLE::LIGHT);
}

void CLiveHand::initConnection() {
	connect(m_pBtnClose, &QPushButton::clicked, this, &CLiveHand::onBtnCloseClicked);
	connect(m_pBtnMin, &QPushButton::clicked, this, &CLiveHand::showMinimized);
	connect(m_pActQuit, &QAction::triggered, this, &CLiveHand::close);
	connect(m_pActShow, &QAction::triggered, this, &CLiveHand::show);
	connect(m_ptrayIcon, &QSystemTrayIcon::activated, this, &CLiveHand::onSystemTrayIconActivated);
	connect(m_pBtnStyle, &QPushButton::clicked, this, &CLiveHand::onBtnStyleClicked);
	connect(m_pBtnFillerPieceSwitch, &QPushButton::clicked, this, &CLiveHand::onBtnFillerPieceSwitchClicked);
	connect(m_pBtnFillerPieceStop, &QPushButton::clicked, this, &CLiveHand::onBtnStopFillerPieceClicked);
	connect(m_pBtnAppendFillerPiece, &QPushButton::clicked, this, &CLiveHand::onBtnAppendFillerPieceClicked);
	connect(m_pFillerPieceTable, &QTableWidget::itemDoubleClicked, this, &CLiveHand::onItemDoubleClicked);
	connect(m_pFillerPieceTable, &QTableWidget::itemSelectionChanged, this, &CLiveHand::onItemSelectChanged);
	connect(m_pFillerPieceTable, &QWidget::customContextMenuRequested, this, &CLiveHand::onTableCustomContextMenuRequested);
	connect(m_pPlayWidget, &CPlayBackWidget::notifyState, this, &CLiveHand::onNotifyPlayStateChanged);
	connect(m_pPlayWidget, &CPlayBackWidget::notifyPlayClicked, this, &CLiveHand::onNotifyPlayClicked);
}

void CLiveHand::initData() {
	readConfig();
	if (m_pFillerPieceTable->rowCount() > 0) {
		m_pFillerPieceTable->selectRow(0);
	}
}

void CLiveHand::destroy() {
	saveConfig();
}

void CLiveHand::help() {
}

void CLiveHand::version() {
}

void CLiveHand::restart() {
	qApp->exit(RETCODE_RESTART);
}

void CLiveHand::recoveryStateWithAct() const {
	m_pActChinese->setChecked(m_language == WINDOWLANAGUAGE::Chinese);
	m_pActEnglish->setChecked(m_language == WINDOWLANAGUAGE::English);
}

void CLiveHand::setSystemTrayIcon() {
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

void CLiveHand::onBtnStyleClicked() {
	m_ThemeStyle = m_pBtnStyle->isChecked() ? WINDOWTHEMESTYLE::LIGHT : WINDOWTHEMESTYLE::DARK;
	emit ThemeChanged(m_ThemeStyle);
}

void CLiveHand::onActChineseClicked() {
	if (const auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change language"),
	                                                            tr("reboot applicaion to take effect")); nRes ==
		QMessageBox::ButtonRole::AcceptRole) {
		m_language = WINDOWLANAGUAGE::Chinese;
		emit ConfChanged(m_language, m_ThemeStyle);
		CLiveHand::restart();
	} else {
		recoveryStateWithAct();
	}
}

void CLiveHand::onActEnglishClicked() {
	if (const auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change language"),
	                                                            tr("reboot applicaion to take effect")); nRes ==
		QMessageBox::ButtonRole::AcceptRole) {
		m_language = WINDOWLANAGUAGE::English;
		emit ConfChanged(m_language, m_ThemeStyle);
		CLiveHand::restart();
	} else {
		recoveryStateWithAct();
	}
}

void CLiveHand::onSystemTrayIconActivated(const QSystemTrayIcon::ActivationReason reason) {
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

void CLiveHand::onBtnFillerPieceSwitchClicked(bool bChecked) {
	if (bChecked) {
		m_pLbFillerPieceStatus->setText(tr("status enable"));
		if (m_pFillerPieceTable->rowCount() == 0) {
			m_pLbFillerPieceTip->setText(tr("fillerpiece tip empty").arg(m_pProcessName));
			m_pLbFillerPieceTip->setStyleSheet("color:red");
		} else {
			m_pLbFillerPieceTip->setText(tr("fillerpiece tip except").arg(m_pProcessName));
			m_pLbFillerPieceTip->setStyleSheet("color:white");
		}
	} else {
		m_pLbFillerPieceTip->setText("");
		m_pLbFillerPieceTip->setStyleSheet("color:white");
		m_pLbFillerPieceStatus->setText(tr("status disable"));
	}
}

void CLiveHand::onBtnStopFillerPieceClicked() {
	// 检查全局线程池中是否有活动的线程
	if (QThreadPool::globalInstance()->activeThreadCount() > 0) {
		// 如果有接收线程在其中，停止并删除这些线程
		if (m_recvThreadPool.activeThreadCount() > 0) {
			for (auto i : m_recvThreadPool.children()) {
				if (auto* thread = qobject_cast<CRecvThread*>(i)) {
					thread->stop();
					delete thread;
				}
			}
		}
		// 停止主线程中的编解码线程
		for (auto i : children()) {
			if (auto* thread = qobject_cast<CCodecThread*>(i)) {
				thread->stop();
			}
		}
		// 清空当前垫片剪辑的路径，禁用停止按钮
		m_strCurrentFillerPieceClip = "";
		m_pBtnFillerPieceStop->setEnabled(false);
		// 遍历垫片表，找到正在处理的垫片，将其背景颜色设置为透明
		for (int i = 0; i < m_pFillerPieceTable->rowCount(); i++) {
			if (QTableWidgetItem* item = m_pFillerPieceTable->item(i, 0)) {
				if (item->data(Qt::UserRole + 2).value<bool>()) {
					item->setBackground(Qt::transparent);
					// 恢复相邻项的背景色
					if (QTableWidgetItem* siblingItem = m_pFillerPieceTable->item(item->row(), 1)) {
						siblingItem->setBackground(Qt::transparent);
					}
					if (QTableWidgetItem* siblingItem = m_pFillerPieceTable->item(item->row(), 2)) {
						siblingItem->setBackground(Qt::transparent);
					}
					item->setData(Qt::UserRole + 2, false);
					break;
				}
			}
		}
		// 等待全局线程池中的任务完成
		QThreadPool::globalInstance()->waitForDone();
		// 通知播放组件，编解码完成
		m_pPlayWidget->onCodecFinished();
	}
}

void CLiveHand::onBtnAppendFillerPieceClicked() {
	auto files = CUVFileDialog::getOpenFileNames(this, tr("Append Path"), "",
	                                             QString("%1(*.avi *.wmv *.mov *.mp4 *.mpg *.ts);;%2(*.bmp *.png *.jpg *.jpeg)")
	                                             .arg(tr("Video")).arg(tr("Image")));
	for (const auto& i : files) {
		// 加入到垫片列表
		appendItem(i);
	}
	// 保存到配置文件
	saveConfig();
}

bool CLiveHand::onItemDoubleClicked(QTableWidgetItem* item) {
	bool bRet = false;
	if (QThreadPool::globalInstance()->activeThreadCount() > 0) {
		UVMessageBox::CUVMessageBox::warning(this, tr("IDS_WARNING"), tr("IDS_PUSING_CAN_NOT_PLAY"), QMessageBox::Ok);
		return bRet;
	} else {
		QTableWidgetItem* clipItem = m_pFillerPieceTable->item(item->row(), 0);
		QString strFile = clipItem->text();
		if (QFile::exists(strFile)) {
			m_pPlayWidget->openFile(strFile, !QImage(strFile).isNull(), !QImage(strFile).isNull());
			m_strCurrentFillerPieceClip = strFile;
			for (int i = 0; i < m_pFillerPieceTable->rowCount(); i++) {
				if (QTableWidgetItem* widget_item = m_pFillerPieceTable->item(i, 0)) {
					if (widget_item->data(Qt::UserRole + 2).value<bool>()) {
						widget_item->setBackground(Qt::transparent);
						if (QTableWidgetItem* siblingItem = m_pFillerPieceTable->item(widget_item->row(), 1)) {
							siblingItem->setBackground(Qt::transparent);
						}
						if (QTableWidgetItem* siblingItem = m_pFillerPieceTable->item(widget_item->row(), 2)) {
							siblingItem->setBackground(Qt::transparent);
						}
						widget_item->setData(Qt::UserRole + 2, false);
						break;
					}
				}
			}
			clipItem->setBackground(QColor(200, 150, 30));
			if (QTableWidgetItem* siblingItem = m_pFillerPieceTable->item(clipItem->row(), 1)) {
				siblingItem->setBackground(QColor(200, 150, 30));
			}
			if (QTableWidgetItem* siblingItem = m_pFillerPieceTable->item(clipItem->row(), 2)) {
				siblingItem->setBackground(QColor(200, 150, 30));
			}
			clipItem->setData(Qt::UserRole + 2, true);
			bRet = true;
		} else {
			// 文件不存在
			if (QMessageBox::AcceptRole == UVMessageBox::CUVMessageBox::warning(this, tr("IDS_WARNING"), tr("IDS_FILE_NOT_EXISTS"),
			                                                                    QMessageBox::Ok | QMessageBox::Cancel)) {
				removeItem(item);
				saveConfig();
			}
			bRet = false;
		}
	}
	return bRet;
}

void CLiveHand::onItemSelectChanged() {
}

void CLiveHand::onTableCustomContextMenuRequested(const QPoint& pos) {
}

void CLiveHand::onBtnCloseClicked() {
	CQuitDialog quitDialog(this);
	if (quitDialog.exec()) {
		int nMode = quitDialog.selectMode();
		if (nMode == 0) {
			hide();
		} else {
			qApp->quit();
		}
	}
}

void CLiveHand::onSysTrayCloseTriggered() {
}

void CLiveHand::onBtnMinClicked() {
}

void CLiveHand::onSystemTrayActived(QSystemTrayIcon::ActivationReason reason) {
}

void CLiveHand::onNotifyPlayStateChanged(CPlayBackWidget::State eState) {
}

void CLiveHand::onNotifyPlayClicked(bool bChecked) {
}

void CLiveHand::onNotifyProcessState(eProcessState state, QVector<CPushStreamInfo> vecStreamInfo) {
}

// CQuitDialog
CQuitDialog::CQuitDialog(QWidget* parent) : CUVBaseDialog(parent) {
	setTitle(CLiveHand::tr("IDS_INFORMATION"));
	setTitleBtnRole(CUVBaseDialog::CloseRole);
	setDialogBtnRole();
	createCtrl();
	layOut();

	QSettings defaultConfig("Sobey", "LiveWatchman");
	int nDefault = defaultConfig.value("client/mode", 0).toInt();
	nDefault == 0 ? m_pBtnToTray->setChecked(true) : m_pBtnExit->setChecked(true);
}

CQuitDialog::~CQuitDialog() = default;

int CQuitDialog::selectMode() const {
	return m_pBtnToTray->isChecked() ? 0 : 1;
}

void CQuitDialog::accept() {
	QSettings defaultConfig("Sobey", "LiveWatchman");
	int nDefault = m_pBtnToTray->isChecked() ? 0 : 1;
	defaultConfig.setValue("client/mode", nDefault);
	CUVBaseDialog::accept();
}

void CQuitDialog::createCtrl() {
	m_pLbTip = new QLabel(tr("IDS_SELECT_OPERATE"), this);
	m_pBtnToTray = new QRadioButton(tr("IDS_TO_TRAY"), this);
	m_pBtnExit = new QRadioButton(tr("IDS_QUIT"), this);

	m_pLyHTip = new QHBoxLayout;
	m_pLyVChk = new QVBoxLayout;
	m_pLyHChk = new QHBoxLayout;
	m_pLyVTotal = new QVBoxLayout;
}

void CQuitDialog::layOut() {
	m_pLyHTip->addWidget(m_pLbTip);
	m_pLyHTip->addStretch();

	m_pLyVChk->addWidget(m_pBtnToTray);
	m_pLyVChk->addWidget(m_pBtnExit);

	m_pLyHChk->addStretch();
	m_pLyHChk->addLayout(m_pLyVChk);

	m_pLyVTotal->addLayout(m_pLyHTip);
	m_pLyVTotal->addLayout(m_pLyHChk);

	m_pLyVTotal->setContentsMargins(6, 6, 6, 6);

	setContent(m_pLyVTotal);
}

void CQuitDialog::destroy() {
}
