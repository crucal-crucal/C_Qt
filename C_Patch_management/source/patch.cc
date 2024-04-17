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
		Logger::instance().logInfo(tr("User deselect ditectory"));
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
	m_pPbschedule->reset();
	m_totalProcess = 0;
	QStringList filePaths{};
	QString begin = m_pCbStartTime->currentText();
	QString end = m_pCbEndTime->currentText();
	if (m_pLePatchPath->text().isEmpty()) {
		UVMessageBox::CUVMessageBox::warning(this, tr("Waring"), tr("please open a directory"));
		return;
	}

	auto beginIndex = m_localMap.find(begin);
	auto endIndex = m_localMap.find(end);

	if (beginIndex != m_localMap.end() && endIndex != m_localMap.end()) {
		for (auto& it = beginIndex; it != std::next(endIndex); ++it) {
			QString str = m_pLePatchPath->text() + QDir::separator() + it->second;
			filePaths.append(str);
		}
	}

	QString outDirName = "output" + QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
	m_outDirName = outDirName;
	m_output = qApp->applicationDirPath() + QDir::separator() + outDirName;

	std::reverse(filePaths.begin(), filePaths.end());
	QStringList filesToMerge{};
	getFilesInDirectory(filePaths, filesToMerge);
	m_localProcess = filesToMerge.size();

	auto mp = splitFileList(m_dirname, filesToMerge);
	int threadNum = qMin(static_cast<int>(mp.size()), m_pCbThreadNum->currentText().toInt());
	QThreadPool::globalInstance()->setMaxThreadCount(threadNum);

	std::vector<QStringList> threadFiles{};
	threadFiles.resize(threadNum);
	splitFileListByThread(mp, threadFiles);

	std::vector<CMergeDir*> m_workers;
	for (auto& filesPerThread : threadFiles) {
		auto* worker = new CMergeDir(filesPerThread, m_output, m_dirname);
		connect(worker, &CMergeDir::progressUpdated, this, &CPatch::updateProcess, Qt::QueuedConnection);
		m_workers.emplace_back(worker);
	}

	if (m_pBtnGenerate->isChecked()) {
		m_pBtnGenerate->setText(tr("Generate"));
		m_pLbCopy->setText(tr("Copying..."));
		m_pGenerateTime->start();
		for (auto& worker : m_workers) {
			QThreadPool::globalInstance()->start(worker);
		}

		QString msg = tr("Merge directories from ") + begin + tr(" To ") + end + tr(" for ") + outDirName;
		Logger::instance().logInfo(msg);

		updatePage(begin, end, outDirName);
	} else {
		m_pBtnGenerate->setText(tr("Cancel"));
		m_pLbCopy->setText(tr("Cancel..."));
		m_pGenerateTime->stop();
		for (auto& worker : m_workers) {
			worker->exit();
			bool result = QThreadPool::globalInstance()->tryTake(worker);
			QString msg = tr("try to stop thread ") + (result ? tr("success") : tr("fail"));
			Logger::instance().logInfo(msg);
			delete worker;
		}
	}
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
	auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change language"), tr("reboot applicaion to take effect"));
	if (nRes == QMessageBox::ButtonRole::AcceptRole) {
		emit LanguageChanged(WINDOWLANAGUAGE::Chinese);
	} else {
		Logger::instance().logInfo(tr("Cancel language change"));
	}
}

void CPatch::onActEnglishClicked() {
	auto nRes = UVMessageBox::CUVMessageBox::question(this, tr("Change language"), tr("reboot applicaion to take effect"));
	if (nRes == QMessageBox::ButtonRole::AcceptRole) {
		emit LanguageChanged(WINDOWLANAGUAGE::English);
	} else {
		Logger::instance().logInfo(tr("Cancel language change"));
	}
}

void CPatch::updateProcess(qint64 value) {
	m_totalProcess += value;
	m_pPbschedule->setValue(static_cast<int>(m_totalProcess / m_localProcess) * 100);

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
	m_pBtnGenerate->setChecked(false);
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
	m_pBtnGenerate->setCheckable(true);
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

	QString sheet = "QComboBox{ combobox-popup:0; }";
	m_pCbStartTime->setStyleSheet(sheet);
	m_pCbStartTime->setMaxVisibleItems(10);
	m_pCbEndTime->setStyleSheet(sheet);
	m_pCbEndTime->setMaxVisibleItems(10);
	for (int i = 1; i <= 5; i++) {
		m_pCbThreadNum->addItem(QString::number(i));
	}

//	m_pPbschedule->setRange(0, 100);
//	m_pPbschedule->setMinimum(0);
//	m_pPbschedule->setMaximum(100);
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
			QString relativePath = filePath.mid(directoryPath.length());
			if (!m_set_path_files.contains(relativePath)) {
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
	QStringList files{}; // 存储抛开目录过后的文件
	QString index = "file"; // 最后一次创建的Key
	for (auto& file : filesToMerge) {
		QString fileName{};
		int flagindex = file.lastIndexOf(flag);
		if (flagindex != -1) {
			QString str = file.mid(flagindex + flag.length() + 1);
			int firstSlashIndex = str.indexOf(separator);
			if (firstSlashIndex != -1) {
				int secondSlashIndex = str.indexOf(separator, firstSlashIndex + 1);
				if (secondSlashIndex != -1) {
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
	int numThreads = static_cast<int>(threadFiles.size());
	int avgListPerThread = static_cast<int>(std::ceil(static_cast<double>(mp.size()) / numThreads)); // 向上取整
	int remainingLists = static_cast<int>(mp.size()) % numThreads; // 余下的QStringList

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
