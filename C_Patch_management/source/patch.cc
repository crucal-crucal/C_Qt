#include "patch.h"
#include <QApplication>

CPatch::CPatch(QWidget* parent) : FramelessMainWindow(parent) {
	createCtrl();
	layOut();
	init();
	initConnect();
	resize(900, 600);
}

CPatch::~CPatch() = default;

void CPatch::onBtnOpenClicked() {
	QString dirPath = CUVFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::currentPath());
	if (dirPath.isEmpty()) {
		Logger::instance().logWarning(tr("User deselect ditectory"));
		return;
	}
	QDir dir(dirPath);
	m_dirname = dir.dirName();

	m_pLePatchPath->setText(dirPath);
	Logger::instance().logInfo(tr("open directory ") + dirPath);
	readDirToList(dirPath);
}

void CPatch::showInTextEdit() {
	QString dirName = m_pLwPatchList->currentItem()->text();
	QString basePath = m_pLePatchPath->text() + QDir::separator() + dirName;

	QDir directory(basePath);
	QStringList txtFiles = directory.entryList(QStringList() << "*.txt", QDir::Files);

	m_pTePreviewTxt->clear();

	if (!txtFiles.isEmpty()) {
		QString fileName = basePath + QDir::separator() + txtFiles.first();
		QString codeType = getFileCodec(fileName);
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			Logger::instance().logError(tr("open error ") + file.errorString());
			return;
		}

		try {
			QTextStream in(&file);
			in.setCodec(codeType.toLatin1());

			QString fileContent = in.readAll();
			file.close();

			m_pTePreviewTxt->append(fileContent);
			// 设置光标到开头
			QTextCursor cursor = m_pTePreviewTxt->textCursor();
			cursor.setPosition(QTextCursor::Start);
			m_pTePreviewTxt->setTextCursor(cursor);
		}
		catch (const std::exception& e) {
			Logger::instance().logError(tr("Exception:") + QString::fromLocal8Bit(e.what()));
		}
	} else {
		Logger::instance().logWarning(tr("No .txt files found in the specified directory."));
	}
}

void CPatch::onBtnRefreshClicked() {
	if (m_pLePatchPath->text().isEmpty()) {
		return;
	}
	readDirToList(m_pLePatchPath->text());
	m_pTePreviewTxt->clear();
}

void CPatch::onBtnGenerateClicked() {
	QStringList filePaths{};
	QString begin = m_pCbStartTime->currentText();
	QString end = m_pCbEndTime->currentText();

	auto beginIndex = m_localMap.find(begin);
	auto endIndex = m_localMap.find(end);

	if (beginIndex != m_localMap.end() && endIndex != m_localMap.end()) {
		for (auto& it = beginIndex; it != std::next(endIndex); ++it) {
			QString str = m_pLePatchPath->text() + QDir::separator() + it->second;
			filePaths.append(str);
		}
	}

	QString outDirName = "output" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm");
	m_outDirName = outDirName;
	m_output = qApp->applicationDirPath() + QDir::separator() + outDirName;

	std::reverse(filePaths.begin(), filePaths.end());
	QStringList filesToMerge{};
	getFileCountInDirectory(filePaths, filesToMerge);
	m_localProcess = filesToMerge.size();
//	groupFilesBySecondDirectory(filePaths, m_dirname);

	QThreadPool::globalInstance()->setMaxThreadCount(m_pCbThreadNum->currentText().toInt());

	int numThreads = QThreadPool::globalInstance()->maxThreadCount();
	int numFiles = filesToMerge.size();
	int filesPerThread = numFiles / numThreads;

	std::vector<CMergeDir*> workers;
	for (int i = 0; i < numThreads; ++i) {
		int startIdx = i * filesPerThread;
		int endIdx = (i == numThreads - 1) ? numFiles : (startIdx + filesPerThread);
		QStringList subFilePaths = filesToMerge.mid(startIdx, endIdx - startIdx);
		auto* worker = new CMergeDir(subFilePaths, m_output, m_dirname);
		connect(worker, &CMergeDir::progressUpdated, this, &CPatch::updateProcess, Qt::QueuedConnection);
		workers.emplace_back(worker);
		worker->setAutoDelete(true);
	}

	if (!m_bIsGenerate) {
		m_pBtnGenerate->setText(tr("Generate"));
		m_pLbCopy->setText(tr("Copying..."));
		m_pGenerateTime->start();
		for (auto& worker : workers) {
			QThreadPool::globalInstance()->start(worker);
		}

		QString msg = tr("Merge directories from ") + begin + tr(" To ") + end + tr(" for ") + outDirName;
		Logger::instance().logInfo(msg);

		updatePage(begin, end, outDirName);
	} else {
		m_pBtnGenerate->setText(tr("Cancel"));
		m_pLbCopy->setText(tr("Cancel..."));
		m_pGenerateTime->stop();
		for (auto& worker : workers) {
			worker->exit();
			bool result = QThreadPool::globalInstance()->tryTake(worker);
			QString msg = tr("try to stop thread ") + (result ? tr("success") : tr("fail"));
			Logger::instance().logInfo(msg);
			delete worker;
		}
	}
	m_bIsGenerate = !m_bIsGenerate;
}

void CPatch::onBtnChoosePathCliecked() {
	QString dirPath = CUVFileDialog::getExistingDirectory(this, tr("CHOOSE_PATH"), QDir::currentPath());
	if (dirPath.isEmpty()) {
		Logger::instance().logWarning(tr("User deselect ditectory"));
		return;
	}
	m_pLePatchOutPath->setText(dirPath);
}

void CPatch::onBtnDoneClicked() {
	QString dirPath = m_pLePatchOutPath->text();
	if (dirPath.isEmpty()) {
		m_pFlickerTimer->start();
		return;
	}
	if (QDir(m_output).exists()) {
		QString newDirectoryName = CUVFileDialog::getSaveFileName(this, tr("INPUT_NAME"),
																  dirPath + QDir::separator() + m_outDirName, tr("DIR_NAME"));
		if (!newDirectoryName.isEmpty()) {
			try {
				if (QDir().rename(m_output, newDirectoryName)) {
					Logger::instance().logInfo(tr("Rename ") + m_output + tr(" To ") + newDirectoryName);
				} else {
					Logger::instance().logError(tr("Unable to rename directory"));
				}
			}
			catch (const std::exception& e) {
				Logger::instance().logError(tr("Exception during rename: ") + QString::fromStdString(e.what()));
			}
		}
	} else {
		Logger::instance().logWarning(tr("The source directory does not exist"));
	}
}

void CPatch::onActChineseClicked() {
	auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change language"), tr("Modify the language needs to restart the program, whether to modify"));
	if (nRes == QMessageBox::ButtonRole::AcceptRole) {
		emit LanguageChanged(WINDOWLANAGUAGE::Chinese);
	} else {
		Logger::instance().logInfo(tr("Cancel language change"));
	}
}

void CPatch::onActEnglishClicked() {
	auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change language"), tr("Modify the language needs to restart the program, whether to modify"));
	if (nRes == QMessageBox::ButtonRole::AcceptRole) {
		emit LanguageChanged(WINDOWLANAGUAGE::English);
	} else {
		Logger::instance().logInfo(tr("Cancel language change"));
	}
}

void CPatch::updateProcess(qint64 value) {
	m_totalProcess += value;
	m_pPbschedule->setValue(static_cast<int>(m_totalProcess / m_localProcess));
	if (m_pPbschedule->value() == 100) {
		m_pLbCopy->setText("");
		m_pGenerateTime->stop();
		m_GenerateTime = 0;
		m_pBtnGenerate->setText(tr("Generate"));
	}
}

void CPatch::updateEndTimeOptions(int _index) {
	m_pCbEndTime->clear();
	QString selectedStartTime = m_pCbStartTime->itemText(_index);
	QDateTime startDateTime = GetDateTimeFromString(selectedStartTime);

	for (const auto& [end, full] : m_localMap) {
		QDateTime endDateTime = GetDateTimeFromString(end);

		if (endDateTime >= startDateTime) {
			m_pCbEndTime->addItem(end);
		}
	}
}

QString CPatch::getFileCodec(QString& _fileName) {
	QFile file(_fileName);
	QString codeType = "UTF-8";
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		QByteArray text = file.readAll();
		QTextCodec::ConverterState state;
		QTextCodec* codec = QTextCodec::codecForName("UTF-8");
		codec->toUnicode(text.constData(), text.size(), &state);

		if (state.invalidChars > 0) {
			codeType = "GBK";
		}
		file.close();
	}

	return codeType;
}

void CPatch::readDirToList(const QString& _dirpath) {
	m_pLwPatchList->clear();
	QDir curDir(_dirpath);
	QStringList dirctories = curDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
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
}

QDateTime CPatch::GetDateTimeFromString(const QString& str) {
	return QDateTime::fromString(str, "yyyyMMdd");
}

void CPatch::updatePage(QString& begin, QString& end, const QString& outputDir) {
	m_pLwOutPatchList->clear();
	auto beginIndex = m_localMap.find(begin);
	auto endIndex = m_localMap.find(end);
	if (beginIndex != m_localMap.end() && endIndex != m_localMap.end()) {
		for (auto& it = beginIndex; it != std::next(endIndex); ++it) {
			m_pLwOutPatchList->addItem(it->second);
		}
	}

	m_pLePatchVersion->setText(outputDir);
}

void CPatch::createCtrl() {
	m_pCentralWidget = new QWidget(this);
	m_pCentralWidget->setObjectName("CPatch_CentralWidget");
	m_pTitleBar = new QWidget(m_pCentralWidget);
	this->setTitleBar(m_pTitleBar);

	m_pBtnMin = new QPushButton(m_pTitleBar);
	m_pBtnMin->setObjectName("Dialog_Btn_Min");
	m_pBtnMin->setToolTip(tr("Min"));

	m_pBtnClose = new QPushButton(m_pTitleBar);
	m_pBtnClose->setObjectName("Dialog_Btn_Close");
	m_pBtnClose->setToolTip(tr("Close"));

	m_pMenuBar = new QMenuBar(m_pTitleBar);
	m_pMenuBar->setObjectName("Main_MenuBar");

	QMenu* menu = m_pMenuBar->addMenu(tr("LANGUAGE"));
	m_pActChinese = menu->addAction(tr("CHINESE"));
	m_pActEnglish = menu->addAction(tr("ENGLISH"));

	m_pTabWidget = new QTabWidget(m_pCentralWidget);
	m_pReadWidget = new QWidget(m_pTabWidget);
	m_pRenewalWidget = new QWidget(m_pTabWidget);
	m_pTabWidget->addTab(m_pReadWidget, tr("READ"));
	m_pTabWidget->addTab(m_pRenewalWidget, tr("RENEWAL"));

	m_pLbPatchPath = new QLabel(tr("PATCH_VERSION"), m_pReadWidget);
	m_pLePatchPath = new QLineEdit(m_pReadWidget);
	m_pBtnOpen = new QPushButton(tr("OPEN_FILE"), m_pReadWidget);
	m_pBtnRefresh = new QPushButton(tr("REFRESH"), m_pReadWidget);

	m_pLwPatchList = new QListWidget(m_pReadWidget);
	m_pTePreviewTxt = new QTextEdit(m_pReadWidget);

	m_pLbGeneratePath = new QLabel(tr("GENERATE_PATH"), m_pReadWidget);
	m_pCbStartTime = new QComboBox(m_pReadWidget);
	m_pCbStartTime->setMinimumWidth(150);
	m_pCbEndTime = new QComboBox(m_pReadWidget);
	m_pCbEndTime->setMinimumWidth(150);
	m_pBtnGenerate = new QPushButton(tr("GENERATE"), m_pReadWidget);
	m_pBtnGenerate->setFixedWidth(100);
	m_pLbThreadNum = new QLabel(tr("Thread Num"), m_pReadWidget);
	m_pCbThreadNum = new QComboBox(m_pReadWidget);
	m_pCbThreadNum->setMinimumWidth(70);
	m_pLbTime = new QLabel(tr("TIME: ") + QString::number(m_GenerateTime) + tr(" s"), m_pReadWidget);
	m_pLbTime->setFixedWidth(100);
	m_pLbCopy = new QLabel(m_pReadWidget);
	m_pLbCopy->setFixedWidth(100);
	m_pPbschedule = new QProgressBar(m_pReadWidget);

	m_pLbPatchVersion = new QLabel(tr("PATCH_VERSION"), m_pRenewalWidget);
	m_pLePatchVersion = new QLineEdit(m_pRenewalWidget);

	m_pLePatchOutPath = new QLineEdit(m_pRenewalWidget);
	m_pBtnPatchOutPath = new QPushButton(tr("PATCH_OUT_PATH"), m_pRenewalWidget);

	m_pLwOutPatchList = new QListWidget(m_pRenewalWidget);

	m_pLbVersionPath = new QLabel(tr("LAB_VERSION_PATH"), m_pRenewalWidget);
	m_pBtnVersionPatch = new QPushButton(tr("BTN_VERSION_PATH"), m_pRenewalWidget);

	m_plyHTitle = new QHBoxLayout(m_pTitleBar);
	m_pCentralLayout = new QVBoxLayout(m_pCentralWidget);

	m_pReadWidgetLayout = new QVBoxLayout(m_pReadWidget);
	m_pReadFirstRowLayout = new QHBoxLayout(m_pReadWidget);
	m_pReadSecondRowLayout = new QHBoxLayout(m_pReadWidget);
	m_pReadThirdRowLayout = new QHBoxLayout(m_pReadWidget);

	m_pRenewalWidgetLayout = new QVBoxLayout(m_pRenewalWidget);
	m_pRenewalFirstRowLayout = new QHBoxLayout(m_pRenewalWidget);
	m_pRenewalSecondRowLayout = new QHBoxLayout(m_pRenewalWidget);
	m_pRenewalThirdRowLayout = new QHBoxLayout(m_pRenewalWidget);

	setMenuWidget(m_pTitleBar);
	setCentralWidget(m_pCentralWidget);
}

void CPatch::layOut() {
	m_plyHTitle->addStretch(); // 添加一个可伸缩的空间
	m_plyHTitle->addWidget(m_pBtnMin);
	m_plyHTitle->addWidget(m_pBtnClose);
	m_plyHTitle->setContentsMargins(0, 0, 0, 0);

	m_pTitleBar->setLayout(m_plyHTitle);

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

	m_pReadWidget->setLayout(m_pReadWidgetLayout);

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

	m_pReadWidget->setLayout(m_pRenewalWidgetLayout);
}

void CPatch::init() {
	m_pFlickerTimer = new QTimer(this);
	m_pFlickerTimer->setInterval(100); // 设置定时器间隔为100毫秒
	m_pGenerateTime = new QTimer(this);
	m_pGenerateTime->setInterval(1000);

	m_pLePatchVersion->setReadOnly(true);
	m_pTePreviewTxt->setReadOnly(true);
	m_pLePatchPath->setReadOnly(true);
	m_pLePatchOutPath->setReadOnly(true);

	QString sheet = "QComboBox{combobox-popup:0;}";
	m_pCbStartTime->setStyleSheet(sheet);
	m_pCbStartTime->setMaxVisibleItems(10);
	m_pCbEndTime->setStyleSheet(sheet);
	m_pCbEndTime->setMaxVisibleItems(10);
	for (int i = 1; i <= 5; i++) {
		m_pCbThreadNum->addItem(QString::number(i));
	}
}

void CPatch::initConnect() {
	connect(m_pBtnClose, &QPushButton::clicked, this, &CPatch::close);
	connect(m_pBtnMin, &QPushButton::clicked, this, &CPatch::showMinimized);
	connect(m_pBtnOpen, &QPushButton::clicked, this, &CPatch::onBtnOpenClicked);
	connect(m_pBtnRefresh, &QPushButton::clicked, this, &CPatch::onBtnRefreshClicked);
	connect(m_pBtnGenerate, &QPushButton::clicked, this, &CPatch::onBtnGenerateClicked);
	connect(m_pLwPatchList, &QListWidget::itemSelectionChanged, this, &CPatch::showInTextEdit);
	connect(m_pCbStartTime, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CPatch::updateEndTimeOptions);
	connect(m_pBtnPatchOutPath, &QPushButton::clicked, this, &CPatch::onBtnChoosePathCliecked);
	connect(m_pBtnVersionPatch, &QPushButton::clicked, this, &CPatch::onBtnDoneClicked);
	connect(m_pActChinese, &QAction::triggered, this, &CPatch::onActChineseClicked);
	connect(m_pActEnglish, &QAction::triggered, this, &CPatch::onActEnglishClicked);
	connect(m_pFlickerTimer, &QTimer::timeout, this, [&]() {
		if (m_pBtnPatchOutPath->styleSheet().isEmpty()) {
			m_pBtnPatchOutPath->setStyleSheet("background-color: lightcoral;");
		} else {
			m_pBtnPatchOutPath->setStyleSheet("");
			m_pFlickerTimer->stop();
		}
	});
	connect(m_pGenerateTime, &QTimer::timeout, this, [&]() {
		m_GenerateTime++;
		m_pLbTime->setText(tr("Time: ") + QString::number(m_GenerateTime) + tr(" s"));
	});
}

void CPatch::getFileCountInDirectory(const QStringList& directoryPaths, QStringList& filesToMerge) {
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
			QString relativePath = filePath.mid(directoryPath.length());
			if (!m_set_path_files.contains(relativePath)) {
				m_set_path_files.insert(relativePath);
				filesToMerge.append(filePath);
			}
		}
	}
}

[[maybe_unused]] int CPatch::countFilesRecursively(const QString& directoryPath) {
	QStack<QString> directoriesToProcess;
	directoriesToProcess.push(directoryPath);
	int totalCount = 0;

	while (!directoriesToProcess.isEmpty()) {
		QString currentDirPath = directoriesToProcess.pop();
		QDir currentDir(currentDirPath);

		QStringList files = currentDir.entryList(QDir::Files);
		QStringList subDirs = currentDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

		totalCount += files.size();

		for (const QString& subDir : subDirs) {
			QString subDirPath = currentDir.filePath(subDir);
			directoriesToProcess.push(subDirPath);
		}
	}

	return totalCount;
}

[[maybe_unused]] void CPatch::groupFilesBySecondDirectory(QStringList& filesToMerge, const QString& flag) {
	QMap<QString, QStringList> groupedFiles;
	for (const auto& filePath : filesToMerge) {
		QString curflag = "/" + QString(flag) + "/";
		// 找到第二个目录的位置
		int flagindex = filePath.indexOf(curflag);
		if (flagindex != -1) {
			// 找到第二个目录的结束位置
			int secondDirStartIndex = filePath.indexOf('/', flagindex + curflag.length());
			if (secondDirStartIndex != -1) {
				// 提取第二个目录名
				QString secondDirName = filePath.mid(flagindex + curflag.length(), secondDirStartIndex - flagindex - curflag.length());
				// 将路径添加到相应的组中
				groupedFiles[secondDirName].append(filePath);
			}
		}
	}

	filesToMerge.clear();

	for (auto it = groupedFiles.begin(); it != groupedFiles.end(); ++it) {
		const QStringList& filePaths = it.value();
		for (const QString& filePath : filePaths) {
			filesToMerge.append(filePath);
		}
	}
}