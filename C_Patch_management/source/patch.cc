#include "patch.h"

#include <cmath>
#include <QDateTime>
#include <QTextCodec>
#include <QThreadPool>

#include "logger/logger.h"

CPatch::CPatch(const InterfaceConfigData& interfaceconfigdata, std::string dirPath, QWidget* parent)
: FramelessMainWindow(parent), m_language(interfaceconfigdata.lanaguage), m_ProgressbarStyle(interfaceconfigdata.progressbarstyle),
  m_ThemeStyle(interfaceconfigdata.themeStyle), m_dirPath(std::move(dirPath)) {
	createCtrl();
	layOut();
	init();
	setSystemTrayIcon();
	initConnect();
	resize(900, 600);
}

CPatch::~CPatch() = default;

void CPatch::onBtnOpenClicked() {
	const QString dirPath = CUVFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::currentPath());
	if (dirPath.isEmpty()) {
		Logger::instance().logInfo(tr("User deselect ditectory"));
		return;
	}
	openDir(dirPath);
}

void CPatch::showInTextEdit() const {
	const QString dirName = m_pLwPatchList->currentItem()->text();
	const QString basePath = m_pLePatchPath->text() + QDir::separator() + dirName;

	const QDir directory(basePath);
	QStringList txtFiles = directory.entryList(QStringList() << "*.txt", QDir::Files);

	m_pTePreviewTxt->clear();

	if (!txtFiles.isEmpty()) {
		const QString fileName = basePath + QDir::separator() + txtFiles.first();
		const QString codeType = getFileCodec(fileName);
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			Logger::instance().logError(tr("open error ") + file.errorString());
			qCritical() << tr("open error ") + file.errorString();
			return;
		}

		try {
			QTextStream in(&file);
			in.setCodec(codeType.toLatin1());

			const QString fileContent = in.readAll();
			file.close();

			m_pTePreviewTxt->append(fileContent);
			// 设置光标到开头
			QTextCursor cursor = m_pTePreviewTxt->textCursor();
			cursor.setPosition(QTextCursor::Start);
			m_pTePreviewTxt->setTextCursor(cursor);
		} catch (const std::exception& e) {
			Logger::instance().logError(tr("Exception:") + QString::fromLocal8Bit(e.what()));
			qCritical() << tr("Exception:") + QString::fromLocal8Bit(e.what());
		}
	} else {
		Logger::instance().logWarning(tr("No .txt files found in the specified directory."));
		qCritical() << tr("No .txt files found in the specified directory.");
	}
}

void CPatch::onBtnRefreshClicked() {
	if (m_pLePatchPath->text().isEmpty()) {
		return;
	}
	readDirToList(QDir(m_pLePatchPath->text()));
	m_pTePreviewTxt->clear();
}

void CPatch::onBtnGenerateClicked() {
	m_pPbschedule->reset();
	m_totalProcess = 0;
	QStringList filePaths{};
	const QString begin = m_pCbStartTime->currentText();
	const QString end = m_pCbEndTime->currentText();
	if (m_pLePatchPath->text().isEmpty()) {
		UVMessageBox::CUVMessageBox::warning(this, tr("Waring"), tr("please open a directory"));
		return;
	}

	auto beginIndex = m_localMap.find(begin);
	if (const auto endIndex = m_localMap.find(end); beginIndex != m_localMap.end() && endIndex != m_localMap.end()) {
		for (auto& it = beginIndex; it != std::next(endIndex); ++it) {
			QString str = m_pLePatchPath->text() + QDir::separator() + it->second;
			filePaths.append(str);
		}
	}

	const QString outDirName = "output" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
	m_outDirName = outDirName;
	m_output = qApp->applicationDirPath() + QDir::separator() + outDirName; // NOLINT

	std::reverse(filePaths.begin(), filePaths.end());
	QStringList filesToMerge{};
	getFilesInDirectory(filePaths, filesToMerge);
	m_localProcess = filesToMerge.size();

	const auto mp = splitFileList(m_dirname, filesToMerge);
	const int threadNum = qMin(static_cast<int>(mp.size()), m_pCbThreadNum->currentText().toInt());
	QThreadPool::globalInstance()->setMaxThreadCount(threadNum);

	std::vector<QStringList> threadFiles{};
	threadFiles.resize(threadNum);
	splitFileListByThread(mp, threadFiles);

	std::vector<CMergeDir_p*> m_workers;
	for (const auto& filesPerThread : threadFiles) {
		auto* worker = new CMergeDir_p(filesPerThread, m_output, m_dirname);
		connect(worker, &CMergeDir_p::progressUpdated, this, &CPatch::updateProcess, Qt::QueuedConnection);
		m_workers.emplace_back(worker);
	}

	if (m_pBtnGenerate->isChecked()) {
		m_pBtnGenerate->setText(tr("Generate"));
		m_pLbCopy->setText(tr("Copying..."));
		m_pGenerateTime->start();
		for (const auto& worker : m_workers) {
			QThreadPool::globalInstance()->start(worker);
		}

		const QString msg = tr("Merge directories from ") + begin + tr(" To ") + end + tr(" for ") + outDirName;
		Logger::instance().logInfo(msg);
		qInfo() << msg;

		updatePage(begin, end, outDirName);
	} else {
		m_pBtnGenerate->setText(tr("Cancel"));
		m_pLbCopy->setText(tr("Cancel..."));
		m_pGenerateTime->stop();
		for (const auto& worker : m_workers) {
			worker->exit();
			const bool result = QThreadPool::globalInstance()->tryTake(worker);
			const QString msg = tr("try to stop thread ") + (result ? tr("success") : tr("fail"));
			Logger::instance().logInfo(msg);
			delete worker;
		}
	}
}

void CPatch::onBtnChoosePathCliecked() {
	const QString dirPath = CUVFileDialog::getExistingDirectory(this, tr("CHOOSE_PATH"), QDir::currentPath());
	if (dirPath.isEmpty()) {
		Logger::instance().logWarning(tr("User deselect ditectory"));
		return;
	}
	m_pLePatchOutPath->setText(dirPath);
}

void CPatch::onBtnDoneClicked() {
	const QString dirPath = m_pLePatchOutPath->text();
	if (dirPath.isEmpty()) {
		m_pFlickerTimer->start();
		return;
	}
	if (QDir(m_output).exists()) {
		if (const QString newDirectoryName = CUVFileDialog::getSaveFileName(
			this, tr("INPUT_NAME"), dirPath + QDir::separator() + m_outDirName,
			tr("DIR_NAME")); !newDirectoryName.isEmpty()) {
			try {
				if (QDir().rename(m_output, newDirectoryName)) {
					Logger::instance().logInfo(tr("Rename ") + m_output + tr(" To ") + newDirectoryName);
				} else {
					Logger::instance().logError(tr("Unable to rename directory"));
				}
			} catch (const std::exception& e) {
				Logger::instance().logError(tr("Exception during rename: ") + QString::fromStdString(e.what()));
			}
		}
	} else {
		Logger::instance().logWarning(tr("The source directory does not exist"));
	}
}

void CPatch::onBtnStyleClicked() {
	m_ThemeStyle = m_pBtnStyle->isChecked() ? WINDOWTHEMESTYLE::LIGHT : WINDOWTHEMESTYLE::DARK;
	emit ThemeChanged(m_ThemeStyle);
}

void CPatch::onActChineseClicked() {
	if (const auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change language"),
	                                                            tr("reboot applicaion to take effect")); nRes ==
		QMessageBox::ButtonRole::AcceptRole) {
		m_language = WINDOWLANAGUAGE::Chinese;
		emit ConfChanged(m_language, m_ProgressbarStyle, m_ThemeStyle);
		CPatch::restart();
	} else {
		recoveryStateWithAct();
	}
}

void CPatch::onActEnglishClicked() {
	if (const auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change language"),
	                                                            tr("reboot applicaion to take effect")); nRes ==
		QMessageBox::ButtonRole::AcceptRole) {
		m_language = WINDOWLANAGUAGE::English;
		emit ConfChanged(m_language, m_ProgressbarStyle, m_ThemeStyle);
		CPatch::restart();
	} else {
		recoveryStateWithAct();
	}
}

void CPatch::onActProgressbar_normalClicked() {
	if (const auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change Progressbar Style"),
	                                                            tr("reboot applicaion to take effect")); nRes ==
		QMessageBox::ButtonRole::AcceptRole) {
		m_ProgressbarStyle = WINDOWPROGRESSBARSTYLE::NORMAL;
		emit ConfChanged(m_language, m_ProgressbarStyle, m_ThemeStyle);
		CPatch::restart();
	} else {
		recoveryStateWithAct();
	}
}

void CPatch::onActProgressbar_borderClicked() {
	if (const auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change Progressbar Style"),
	                                                            tr("reboot applicaion to take effect")); nRes ==
		QMessageBox::ButtonRole::AcceptRole) {
		m_ProgressbarStyle = WINDOWPROGRESSBARSTYLE::BORDER_RED;
		emit ConfChanged(m_language, m_ProgressbarStyle, m_ThemeStyle);
		CPatch::restart();
	} else {
		recoveryStateWithAct();
	}
}

void CPatch::onActProgressbar_border_radiusClicked() {
	if (const auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change Progressbar Style"),
	                                                            tr("reboot applicaion to take effect")); nRes ==
		QMessageBox::ButtonRole::AcceptRole) {
		m_ProgressbarStyle = WINDOWPROGRESSBARSTYLE::BORDER_RADIUS;
		emit ConfChanged(m_language, m_ProgressbarStyle, m_ThemeStyle);
		CPatch::restart();
	} else {
		recoveryStateWithAct();
	}
}

void CPatch::onActProgressbar_blockClicked() {
	if (const auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change Progressbar Style"),
	                                                            tr("reboot applicaion to take effect")); nRes ==
		QMessageBox::ButtonRole::AcceptRole) {
		m_ProgressbarStyle = WINDOWPROGRESSBARSTYLE::BLOCK;
		emit ConfChanged(m_language, m_ProgressbarStyle, m_ThemeStyle);
		CPatch::restart();
	} else {
		recoveryStateWithAct();
	}
}

void CPatch::onActProgressbar_gradationClicked() {
	if (const auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change Progressbar Style"),
	                                                            tr("reboot applicaion to take effect")); nRes ==
		QMessageBox::ButtonRole::AcceptRole) {
		m_ProgressbarStyle = WINDOWPROGRESSBARSTYLE::GRADATION;
		emit ConfChanged(m_language, m_ProgressbarStyle, m_ThemeStyle);
		CPatch::restart();
	} else {
		recoveryStateWithAct();
	}
}

void CPatch::updateProcess(const qint64 value) {
	m_totalProcess += value;
	m_pPbschedule->setValue(static_cast<int>(m_totalProcess / m_localProcess) * 100);

	if (m_pPbschedule->value() == 100) {
		m_pLbCopy->setText("");
		m_pGenerateTime->stop();
		m_GenerateTime = 0;
		m_pBtnGenerate->setText(tr("Generate"));
	}
}

void CPatch::onSystemTrayIconActivated(const QSystemTrayIcon::ActivationReason reason) {
	if (reason == QSystemTrayIcon::DoubleClick) {
		// 双击显示
		this->isMinimized() ? this->showNormal() : this->showMinimized(); // 将主窗口显示出来
		this->activateWindow();                                           // 激活主窗口，确保它位于顶部
	} else if (reason == QSystemTrayIcon::Context) {                      // 右键菜单
		// 调整显示始终在鼠标之上
		const auto pos = QCursor::pos();
		const int offsetY = m_ptrayMenu->sizeHint().height();
		m_ptrayMenu->move(pos.x(), pos.y() - offsetY);
		m_ptrayMenu->exec();
	}
}

void CPatch::updateEndTimeOptions(const int _index) {
	m_pCbEndTime->clear();
	const QString selectedStartTime = m_pCbStartTime->itemText(_index);
	const QDateTime startDateTime = GetDateTimeFromString(selectedStartTime);

	for (const auto& [end, full] : m_localMap) {
		if (const QDateTime endDateTime = GetDateTimeFromString(end); endDateTime >= startDateTime) {
			m_pCbEndTime->addItem(end);
		}
	}
}

QString CPatch::getFileCodec(const QString& _fileName) {
	QFile file(_fileName);
	QString codeType = "UTF-8";
#if 0
	if (file.open(QIODevice::ReadOnly)) {
		const QByteArray text = file.readAll();
		QTextCodec::ConverterState state;
		const QTextCodec* codec = QTextCodec::codecForName("UTF-8");
		codec->toUnicode(text.constData(), text.size(), &state);

		if (state.invalidChars > 0) {
			codeType = "GBK";
		}
		file.close();
	}
#else
	if (file.open(QIODevice::ReadOnly)) {
		// 读取3字节用于判断
		if (QByteArray buffer = file.read(3); buffer.startsWith("\xFF\xFE")) {
			codeType = "UTF-16LE";
		} else if (buffer.startsWith("\xFE\xFF")) {
			codeType = "UTF-16BE";
		} else if (buffer.startsWith("\xEF\xBB\xBF")) {
			codeType = "UTF-8BOM";
		} else {
			buffer = file.readAll();
			// 尝试用 utf-8 转换，如果可用字数大于0，表示是 ANSI 编码
			QTextCodec::ConverterState state;
			const QTextCodec* codec = QTextCodec::codecForName("UTF-8");
			codec->toUnicode(buffer.constData(), buffer.size(), &state);
			codeType = state.invalidChars > 0 ? "GBK" : codeType;
		}
		file.close();
	}
#endif
	return codeType;
}

void CPatch::readDirToList(const QDir& _dir) {
	m_pLwPatchList->clear();
	QStringList dirctories = _dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	std::sort(dirctories.begin(), dirctories.end(), [&](const QString& a, const QString& b) {
		return GetDateTimeFromString(a.right(8)) < GetDateTimeFromString(b.right(8));
	});

	for (const QString& dirName : dirctories) {
		m_pLwPatchList->addItem(dirName);
		m_localMap[dirName.right(8)] = dirName;
	}

	updateCombox();
}

void CPatch::updateCombox() {
	m_pCbStartTime->clear();
	m_pCbEndTime->clear();
	for (const auto& [str, fullstr] : m_localMap) {
		m_pCbStartTime->addItem(str);
	}
	updateEndTimeOptions(m_pCbStartTime->currentIndex());
}

QDateTime CPatch::GetDateTimeFromString(const QString& str) {
	return QDateTime::fromString(str, "yyyyMMdd");
}

void CPatch::updatePage(const QString& begin, const QString& end, const QString& outputDir) {
	m_pBtnGenerate->setChecked(false);
	m_pLwOutPatchList->clear();
	auto beginIndex = m_localMap.find(begin);
	if (const auto endIndex = m_localMap.find(end); beginIndex != m_localMap.end() && endIndex != m_localMap.end()) {
		for (auto& it = beginIndex; it != std::next(endIndex); ++it) {
			m_pLwOutPatchList->addItem(it->second);
		}
	}

	m_pLePatchVersion->setText(outputDir);
}

void CPatch::createCtrl() {
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

	m_menuProgressbar = m_menuPreference->addMenu(tr("ProgressBar Style"));
	m_pActGroupProgressbar = this->createWidget<QActionGroup>(m_menuProgressbar);
	m_pActProgressbar_normal = m_pActGroupProgressbar->addAction(tr("Normal"));
	m_pActProgressbar_block = m_pActGroupProgressbar->addAction(tr("Block"));
	m_pActProgressbar_border = m_pActGroupProgressbar->addAction(tr("Border_Red"));
	m_pActProgressbar_border_radius = m_pActGroupProgressbar->addAction(tr("Border Radius"));
	m_pActProgressbar_gradation = m_pActGroupProgressbar->addAction(tr("Gradation"));
	m_pActProgressbar_normal->setCheckable(true);
	m_pActProgressbar_block->setCheckable(true);
	m_pActProgressbar_border->setCheckable(true);
	m_pActProgressbar_border_radius->setCheckable(true);
	m_pActProgressbar_gradation->setCheckable(true);

	m_menuProgressbar->addActions(m_pActGroupProgressbar->actions());
	m_pActGroupProgressbar->setExclusive(true); // 设置互斥

	m_pTabWidget = this->createWidget<QTabWidget>(m_pCentralWidget);
	m_pTabWidget->tabBar()->setObjectName("CPatch_TabBar");
	m_pReadWidget = this->createWidget<QWidget>(m_pTabWidget);
	m_pRenewalWidget = this->createWidget<QWidget>(m_pTabWidget);
	m_pTabWidget->addTab(m_pReadWidget, tr("READ"));
	m_pTabWidget->addTab(m_pRenewalWidget, tr("RENEWAL"));

	m_pLbPatchPath = this->createWidget<QLabel>(tr("PATCH_VERSION"), m_pReadWidget);
	m_pLePatchPath = this->createWidget<QLineEdit>(m_pReadWidget);
	m_pBtnOpen = this->createWidget<QPushButton>(tr("OPEN_FILE"), m_pReadWidget);
	m_pBtnRefresh = this->createWidget<QPushButton>(tr("REFRESH"), m_pReadWidget);

	m_pLwPatchList = this->createWidget<QListWidget>(m_pReadWidget);
	m_pTePreviewTxt = this->createWidget<QTextEdit>(m_pReadWidget);

	m_pLbGeneratePath = this->createWidget<QLabel>(tr("GENERATE_PATH"), m_pReadWidget);
	m_pCbStartTime = this->createWidget<QComboBox>(m_pReadWidget);
	m_pCbStartTime->setView(this->createWidget<QListView>(m_pCbStartTime));
	m_pCbStartTime->setMinimumWidth(150);
	m_pCbEndTime = this->createWidget<QComboBox>(m_pReadWidget);
	m_pCbEndTime->setView(this->createWidget<QListView>(m_pCbEndTime));
	m_pCbEndTime->setMinimumWidth(150);
	m_pBtnGenerate = this->createWidget<QPushButton>(tr("GENERATE"), m_pReadWidget);
	m_pBtnGenerate->setFixedWidth(100);
	m_pBtnGenerate->setCheckable(true);
	m_pLbThreadNum = this->createWidget<QLabel>(tr("Thread Num"), m_pReadWidget);
	m_pCbThreadNum = this->createWidget<QComboBox>(m_pReadWidget);
	m_pCbThreadNum->setView(this->createWidget<QListView>(m_pCbThreadNum));
	m_pCbThreadNum->setMinimumWidth(70);
	m_pLbTime = this->createWidget<QLabel>(tr("TIME: ") + QString::number(m_GenerateTime) + tr(" s"), m_pReadWidget);
	m_pLbTime->setFixedWidth(100);
	m_pLbCopy = this->createWidget<QLabel>(m_pReadWidget);
	m_pLbCopy->setFixedWidth(100);
	m_pPbschedule = this->createWidget<QProgressBar>(m_pReadWidget);

	m_pLbPatchVersion = this->createWidget<QLabel>(tr("PATCH_VERSION"), m_pRenewalWidget);
	m_pLePatchVersion = this->createWidget<QLineEdit>(m_pRenewalWidget);

	m_pLePatchOutPath = this->createWidget<QLineEdit>(m_pRenewalWidget);
	m_pBtnPatchOutPath = this->createWidget<QPushButton>(tr("PATCH_OUT_PATH"), m_pRenewalWidget);

	m_pLwOutPatchList = this->createWidget<QListWidget>(m_pRenewalWidget);

	m_pLbVersionPath = this->createWidget<QLabel>(tr("LAB_VERSION_PATH"), m_pRenewalWidget);
	m_pBtnVersionPatch = this->createWidget<QPushButton>(tr("BTN_VERSION_PATH"), m_pRenewalWidget);

	m_plyHTitle = this->createWidget<QHBoxLayout>(m_pTitleBar);
	m_pCentralLayout = this->createWidget<QVBoxLayout>(m_pCentralWidget);

	m_pReadWidgetLayout = this->createWidget<QVBoxLayout>(m_pReadWidget);
	m_pReadFirstRowLayout = this->createWidget<QHBoxLayout>();
	m_pReadSecondRowLayout = this->createWidget<QHBoxLayout>();
	m_pReadThirdRowLayout = this->createWidget<QHBoxLayout>();

	m_pRenewalWidgetLayout = this->createWidget<QVBoxLayout>(m_pRenewalWidget);
	m_pRenewalFirstRowLayout = this->createWidget<QHBoxLayout>();
	m_pRenewalSecondRowLayout = this->createWidget<QHBoxLayout>();
	m_pRenewalThirdRowLayout = this->createWidget<QHBoxLayout>();

	setMenuWidget(m_pTitleBar);
	setCentralWidget(m_pCentralWidget);
}

void CPatch::layOut() const {
	m_plyHTitle->addWidget(m_pMenuBar);
	m_plyHTitle->addStretch();
	m_plyHTitle->addWidget(m_pBtnStyle);
	m_plyHTitle->addWidget(m_pBtnMin);
	m_plyHTitle->addWidget(m_pBtnClose);
	m_plyHTitle->setContentsMargins(0, 0, 0, 0);

	m_pCentralLayout->addWidget(m_pTitleBar);
	m_pCentralLayout->addWidget(m_pTabWidget);

	m_pReadFirstRowLayout->addWidget(m_pLbPatchPath);
	m_pReadFirstRowLayout->addWidget(m_pLePatchPath);
	m_pReadFirstRowLayout->addWidget(m_pBtnOpen);
	m_pReadFirstRowLayout->addWidget(m_pBtnRefresh);

	m_pReadSecondRowLayout->addWidget(m_pLwPatchList);
	m_pReadSecondRowLayout->addWidget(m_pTePreviewTxt);

	m_pReadThirdRowLayout->addWidget(m_pLbGeneratePath);
	m_pReadThirdRowLayout->addWidget(m_pCbStartTime);
	m_pReadThirdRowLayout->addWidget(m_pCbEndTime);
	m_pReadThirdRowLayout->addWidget(m_pBtnGenerate);
	m_pReadThirdRowLayout->addWidget(m_pLbThreadNum);
	m_pReadThirdRowLayout->addWidget(m_pCbThreadNum);
	m_pReadThirdRowLayout->addWidget(m_pLbTime);

	m_pReadThirdRowLayout->addWidget(m_pLbCopy);

	m_pReadWidgetLayout->addLayout(m_pReadFirstRowLayout);
	m_pReadWidgetLayout->addLayout(m_pReadSecondRowLayout);
	m_pReadWidgetLayout->addLayout(m_pReadThirdRowLayout);
	m_pReadWidgetLayout->addWidget(m_pPbschedule);

	m_pRenewalFirstRowLayout->addWidget(m_pLbPatchVersion);
	m_pRenewalFirstRowLayout->addWidget(m_pLePatchVersion);

	m_pRenewalSecondRowLayout->addWidget(m_pLePatchOutPath);
	m_pRenewalSecondRowLayout->addWidget(m_pBtnPatchOutPath);

	m_pRenewalThirdRowLayout->addWidget(m_pLbVersionPath);
	m_pRenewalThirdRowLayout->addStretch();
	m_pRenewalThirdRowLayout->addWidget(m_pBtnVersionPatch);

	m_pRenewalWidgetLayout->addLayout(m_pRenewalFirstRowLayout);
	m_pRenewalWidgetLayout->addLayout(m_pRenewalSecondRowLayout);
	m_pRenewalWidgetLayout->addWidget(m_pLwOutPatchList);
	m_pRenewalWidgetLayout->addLayout(m_pRenewalThirdRowLayout);
}

void CPatch::init() {
	m_pFlickerTimer = this->createWidget<QTimer>(this);
	m_pFlickerTimer->setInterval(100); // 设置定时器间隔为100毫秒
	m_pGenerateTime = this->createWidget<QTimer>(this);
	m_pGenerateTime->setInterval(1000);

	m_pLePatchVersion->setReadOnly(true);
	m_pTePreviewTxt->setReadOnly(true);
	m_pLePatchPath->setReadOnly(true);
	m_pLePatchOutPath->setReadOnly(true);

	m_pCbStartTime->setMaxVisibleItems(7);
	m_pCbEndTime->setMaxVisibleItems(7);

	for (int i = 1; i <= 5; i++) {
		m_pCbThreadNum->addItem(QString::number(i));
	}

	recoveryStateWithAct();
	m_pLbGeneratePath->setFixedWidth(m_language == WINDOWLANAGUAGE::Chinese ? CHINESE_LABEL_WIDTH : ENGLISH_LABEL_WIDTH);
	m_pLbThreadNum->setFixedWidth(m_language == WINDOWLANAGUAGE::Chinese ? CHINESE_LABEL_WIDTH : ENGLISH_LABEL_WIDTH);
	m_pMenuBar->setFixedWidth(m_language == WINDOWLANAGUAGE::Chinese ? CHINESE_MENUBAR_WIDTH : ENGLISH_MENUBAR_WIDTH);

	m_pBtnStyle->setChecked(m_ThemeStyle == WINDOWTHEMESTYLE::LIGHT);

	const int progressbarStyle = static_cast<int>(m_ProgressbarStyle);
	m_pPbschedule->setProperty("customProgressBar", progressbarStyle);

	if (!m_dirPath.empty()) {
		openDir(QString::fromStdString(m_dirPath));
	}
}

void CPatch::initConnect() {
	connect(m_pBtnClose, &QPushButton::clicked, this, &CPatch::close);
	connect(m_pBtnMin, &QPushButton::clicked, this, &CPatch::showMinimized);
	connect(m_pActQuit, &QAction::triggered, this, &CPatch::close);
	connect(m_pActShow, &QAction::triggered, this, &CPatch::showNormal);
	connect(m_ptrayIcon, &QSystemTrayIcon::activated, this, &CPatch::onSystemTrayIconActivated);
	connect(m_pBtnStyle, &QPushButton::clicked, this, &CPatch::onBtnStyleClicked);
	connect(m_pBtnOpen, &QPushButton::clicked, this, &CPatch::onBtnOpenClicked);
	connect(m_pBtnRefresh, &QPushButton::clicked, this, &CPatch::onBtnRefreshClicked);
	connect(m_pBtnGenerate, &QPushButton::clicked, this, &CPatch::onBtnGenerateClicked);
	connect(m_pLwPatchList, &QListWidget::itemSelectionChanged, this, &CPatch::showInTextEdit);
	connect(m_pCbStartTime, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CPatch::updateEndTimeOptions);
	connect(m_pBtnPatchOutPath, &QPushButton::clicked, this, &CPatch::onBtnChoosePathCliecked);
	connect(m_pBtnVersionPatch, &QPushButton::clicked, this, &CPatch::onBtnDoneClicked);
	connect(m_pActChinese, &QAction::triggered, this, &CPatch::onActChineseClicked);
	connect(m_pActEnglish, &QAction::triggered, this, &CPatch::onActEnglishClicked);
	connect(m_pActProgressbar_normal, &QAction::triggered, this, &CPatch::onActProgressbar_normalClicked);
	connect(m_pActProgressbar_border, &QAction::triggered, this, &CPatch::onActProgressbar_borderClicked);
	connect(m_pActProgressbar_border_radius, &QAction::triggered, this, &CPatch::onActProgressbar_border_radiusClicked);
	connect(m_pActProgressbar_block, &QAction::triggered, this, &CPatch::onActProgressbar_blockClicked);
	connect(m_pActProgressbar_gradation, &QAction::triggered, this, &CPatch::onActProgressbar_gradationClicked);
	connect(m_pFlickerTimer, &QTimer::timeout, this, [=]() {
		if (m_pBtnPatchOutPath->styleSheet().isEmpty()) {
			m_pBtnPatchOutPath->setStyleSheet("background-color: lightcoral;");
		} else {
			m_pBtnPatchOutPath->setStyleSheet("");
			m_pFlickerTimer->stop();
		}
	});
	connect(m_pGenerateTime, &QTimer::timeout, this, [=]() {
		m_GenerateTime++;
		m_pLbTime->setText(tr("Time: ") + QString::number(m_GenerateTime) + tr(" s"));
	});
}

void CPatch::getFilesInDirectory(const QStringList& directoryPaths, QStringList& filesToMerge) {
	QSet<QString> m_set_path_files{};
	for (const auto& directoryPath : directoryPaths) {
		// 存储所有文件的完整路径
		QStringList allFilePaths;
		// 待处理的目录列表
		QStringList pendingDirs;
		pendingDirs.append(directoryPath);
		// 遍历目录及其子目录，获取所有文件的完整路径
		while (!pendingDirs.isEmpty()) {
			QString currentDir = pendingDirs.takeFirst();
			QDir directory(currentDir);
			// 获取当前目录下的所有文件
			QStringList files = directory.entryList(QDir::Files);
			for (auto& file : files) {
				allFilePaths.append(directory.filePath(file));
			}
			// 获取当前目录下的所有子目录，并加入待处理列表
			QStringList subDirs = directory.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
			for (const QString& subDir : subDirs) {
				QString subDirPath = directory.filePath(subDir);
				pendingDirs.append(subDirPath);
			}
		}
		// 将文件路径添加到 filesToMerge 列表中，并排除重复的文件
		for (auto& filePath : allFilePaths) {
			// 移除目录路径部分，只保留相对路径
			if (QString relativePath = filePath.mid(directoryPath.length()); !m_set_path_files.contains(relativePath)) {
				m_set_path_files.insert(relativePath);
				filesToMerge.append(filePath);
			}
		}
	}
}

std::map<QString, QStringList> CPatch::splitFileList(const QString& flag, const QStringList& filesToMerge) {
#ifdef Q_OS_WIN
	QString separator = "/";
#else
	QString separator = QDir::separator();
#endif
	std::map<QString, QStringList> mp{};
	QStringList files{};    // 存储抛开目录过后的文件
	QString index = "file"; // 最后一次创建的Key
	for (auto& file : filesToMerge) {
		QString fileName{};
		if (const int flagindex = file.lastIndexOf(flag); flagindex != -1) {
			QString str = file.mid(flagindex + flag.length() + 1);
			if (const int firstSlashIndex = str.indexOf(separator); firstSlashIndex != -1) {
				if (const int secondSlashIndex = str.indexOf(separator, firstSlashIndex + 1); secondSlashIndex != -1) {
					fileName = str.mid(firstSlashIndex + 1, secondSlashIndex - firstSlashIndex - 1);
				} else {
					files.append(file);
				}
			}
		}
		if (!fileName.isEmpty()) {
			index = fileName;
			mp[fileName].append(file);
		}
	}
	for (auto& file : files) {
		mp[index].append(file);
	}
	return mp;
}

bool CPatch::splitFileListByThread(const std::map<QString, QStringList>& mp, std::vector<QStringList>& threadFiles) {
	bool bRet = false;
	// 如果mp为空或者threadFiles的大小为0，则返回false
	if (mp.empty() || threadFiles.empty()) {
		return bRet;
	}

	// 计算每个线程应该分配的QStringList数量
	const int numThreads = static_cast<int>(threadFiles.size());
	const int avgListPerThread = static_cast<int>(std::ceil(static_cast<double>(mp.size()) / numThreads)); // 向上取整
	int remainingLists = static_cast<int>(mp.size()) %
		numThreads; // 余下的QStringList

	auto iter = mp.begin();
	for (size_t i = 0; i < numThreads; ++i) {
		// 将QStringList平均分配给每个线程
		for (int j = 0; j < avgListPerThread && iter != mp.end(); ++j) {
			threadFiles[i].append(iter->second);
			++iter;
		}
		// 将余下的QStringList放入最后一个线程中
		if (i == numThreads - 1 && remainingLists > 0 && iter != mp.end()) {
			threadFiles[i].append(iter->second);
			++iter;
			--remainingLists;
		}
	}
	bRet = true;
	return bRet;
}

void CPatch::restart() {
	qApp->exit(RETCODE_RESTART); // NOLINT
}

void CPatch::recoveryStateWithAct() const {
	m_pActChinese->setChecked(m_language == WINDOWLANAGUAGE::Chinese);
	m_pActEnglish->setChecked(m_language == WINDOWLANAGUAGE::English);

	m_pActProgressbar_normal->setChecked(m_ProgressbarStyle == WINDOWPROGRESSBARSTYLE::NORMAL);
	m_pActProgressbar_block->setChecked(m_ProgressbarStyle == WINDOWPROGRESSBARSTYLE::BLOCK);
	m_pActProgressbar_border->setChecked(m_ProgressbarStyle == WINDOWPROGRESSBARSTYLE::BORDER_RED);
	m_pActProgressbar_border_radius->setChecked(m_ProgressbarStyle == WINDOWPROGRESSBARSTYLE::BORDER_RADIUS);
	m_pActProgressbar_gradation->setChecked(m_ProgressbarStyle == WINDOWPROGRESSBARSTYLE::GRADATION);
}

void CPatch::setSystemTrayIcon() {
	if (m_ptrayIcon) {
		return;
	}

	m_ptrayIcon = this->createWidget<QSystemTrayIcon>(this);
	m_ptrayMenu = std::make_unique<QMenu>();
	m_pActShow = this->createWidget<QAction>(QObject::tr("Show"), m_ptrayMenu.get());
	m_pActQuit = this->createWidget<QAction>(QObject::tr("Exit"), m_ptrayMenu.get());
	m_ptrayMenu->addAction(m_pActShow);
	m_ptrayMenu->addAction(m_pActQuit);
	m_ptrayMenu->setWindowFlag(Qt::FramelessWindowHint);
	m_ptrayMenu->setAttribute(Qt::WA_TranslucentBackground);
	m_ptrayIcon->setToolTip(QObject::tr("C_Patch_management"));
	m_ptrayIcon->setIcon(QIcon(":/icon/Patch.jpg"));

	m_ptrayIcon->setContextMenu(m_ptrayMenu.get());
	m_ptrayIcon->show();
}

void CPatch::openDir(const QString& _dirpath) {
	const QDir dir(_dirpath);
	m_dirname = dir.dirName();
	m_pLePatchPath->setText(dir.absolutePath());
	Logger::instance().logInfo(tr("open directory ") + dir.absolutePath());
	readDirToList(dir);
}
