#include "cplaybackwidget.h"

#include "codec/codec_p.h"
#include "global/cdefine.h"

CPlayBackWidget::CPlayBackWidget(QWidget* parent) : QWidget(parent) {
	createCtrl();
	layOut();
	initConnect();
}

CPlayBackWidget::~CPlayBackWidget() = default;

void CPlayBackWidget::openFile(const QString& strFile, const bool bLoop, const bool bPicture) {
	if (!m_pCodecThread) {
		m_pCodecThread = new CCodecThread(this);
		connect(m_pCodecThread, &CCodecThread::notifyImage, this, &CPlayBackWidget::onNotifyImage);
		connect(m_pCodecThread, &CCodecThread::notifyAudio, this, &CPlayBackWidget::onNotifyAudio);
		connect(m_pCodecThread, &CCodecThread::notifyClipInfo, this, &CPlayBackWidget::onNotifyClipInfo);
		connect(m_pCodecThread, &CCodecThread::notifyCountDown, this, &CPlayBackWidget::onNotifyCountDown);
		connect(m_pCodecThread, &CCodecThread::notifyAudioPara, this, &CPlayBackWidget::onNotifyAudioPara);
		connect(m_pCodecThread, &CCodecThread::started, this, &CPlayBackWidget::onCodecStarted);
		connect(m_pCodecThread, &CCodecThread::finished, this, &CPlayBackWidget::onCodecFinished);
	}

	//rtmp://172.16.160.34/live/hpx  udp://233.233.233.233:5200
	// m_pCodecThread->open(strFile, m_pLbDisplay->size(), CPushStreamInfo{}, CCodecThread::OpenMode::OpenMode_Play, bLoop);
	// CPushStreamInfo stStream;
	// stStream.eStream = CPushStreamInfo::Video;
	// stStream.eStream = CPushStreamInfo::Audio;
	// stStream.strAddress = "srt://127.0.0.1:22071?mode=listener";
	// stStream.strAddress = "udp://127.0.0.1:5200";
	// stStream.strAddress = "rtmp://192.168.190.130:1935/live/test1";
	// stStream.nWidth = 1920;
	// stStream.nHeight = 1080;
	// stStream.nAudioSampleRate = 44100;
	// stStream.nFrameRateNum = 1;
	// stStream.nFrameRateDen = 50;

	// 打开媒体文件或流
	m_pCodecThread->open(strFile, m_pLbDisplay->size(), CPushStreamInfo(), CCodecThread::OpenMode::OpenMode_Play, bLoop, bPicture);
	// 处理所有当前事件，确保 open 函数执行完成
	qApp->processEvents(QEventLoop::EventLoopExec);
	//m_pCodecThread->open(strFile, m_pLbDisplay->size(), stStream,
	//    /*, "udp://127.0.0.1:5200","srt://127.0.0.1:22071?mode=listener"*/CLXCodecThread::OpenMode(CLXCodecThread::OpenMode::OpenMode_Play |
	//        CLXCodecThread::OpenMode::OpenMode_Push), true, !QImage(strFile).isNull());
}

void CPlayBackWidget::stop() {
	if (m_pCodecThread) {
		m_pCodecThread->stop();
	}
	m_audioByteBuffer.clear();
	m_pSliderDuration->setValue(0);
	m_pSliderDuration->setEnabled(false);
	m_pLbDuration->setText(QTime(0, 0, 0).toString("hh:mm:ss"));
	m_pLbCountDown->setText(QTime(0, 0, 0).toString("hh:mm:ss"));
	m_pLbDisplay->clear();
	if (m_pAudioOutput) {
		m_pAudioOutput->stop();
	}
}

void CPlayBackWidget::pause() {
	m_pCodecThread->pause();
	m_eState = Pause;
	emit notifyState(m_eState);
}

void CPlayBackWidget::resume() {
	m_pCodecThread->resume();
	m_eState = Play;
	emit notifyState(m_eState);
}

void CPlayBackWidget::onNotifyAudio(const QByteArray& data) {
	m_audioByteBuffer.append(data);
}

void CPlayBackWidget::onNotifyClipInfo(const quint64& nDuration) const {
	m_pSliderDuration->setEnabled(true);
	m_pSliderDuration->setRange(0, static_cast<int>(nDuration));
	m_pLbDuration->setText(QTime(0, 0).addSecs(static_cast<int>(nDuration)).toString("hh:mm:ss"));
}

void CPlayBackWidget::onNotifyAudioPara(const quint64& nSampleRate, const quint64& nChannels) {
	QAudioFormat format{};
	format.setCodec("audio/pcm");
	format.setSampleRate(static_cast<int>(nSampleRate));
	format.setSampleSize(16);
	format.setSampleType(QAudioFormat::SignedInt);
	format.setChannelCount(static_cast<int>(nChannels));
	format.setByteOrder(QAudioFormat::LittleEndian);

	QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice()); //选择默认输出设备

	if (!info.isFormatSupported(format)) {
		format = info.nearestFormat(format);
	}
	if (m_pAudioOutput) {
		m_pAudioOutput->stop();
		SAFE_DELETE(m_pAudioOutput);
		m_pAudioDevice = nullptr;
	}
	if (!m_pAudioOutput) {
		m_pAudioOutput = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format, this);
		m_pAudioOutput->setVolume(100);
		m_pAudioDevice = m_pAudioOutput->start();
	}
	if (m_nTimerId != -1) {
		killTimer(m_nTimerId);
		m_nTimerId = -1;
	}
	m_audioByteBuffer.clear();
	m_nTimerId = startTimer(20);
}

void CPlayBackWidget::onNotifyCountDown(const quint64& nCountDown) const {
	m_pSliderDuration->setValue(static_cast<int>(nCountDown));
	const quint64 nCurCountdown = m_pSliderDuration->maximum() - nCountDown;
	m_pLbCountDown->setText(QTime(0, 0).addSecs(static_cast<int>(nCurCountdown)).toString("hh:mm:ss"));
}

void CPlayBackWidget::onNotifyImage(const QPixmap& pixmap) const {
	const QPixmap scaled = pixmap.scaled(m_pLbDisplay->size(), Qt::KeepAspectRatio);
	m_pLbDisplay->setPixmap(scaled);
}

void CPlayBackWidget::onCodecStarted() {
	m_pSliderDuration->setValue(0);
	m_pSliderDuration->setEnabled(true);
	m_pLbDuration->setText(QTime(0, 0, 0).toString("hh:mm:ss"));
	m_pLbCountDown->setText(QTime(0, 0, 0).toString("hh:mm:ss"));
	m_pLbDisplay->clear();
	m_pBtnPlay->setChecked(true);
	m_eState = CPlayBackWidget::State::Play;
	emit notifyState(m_eState);
}

void CPlayBackWidget::onCodecFinished() {
	m_pSliderDuration->setValue(0);
	m_pSliderDuration->setEnabled(false);
	m_pLbDuration->setText(QTime(0, 0, 0).toString("hh:mm:ss"));
	m_pLbCountDown->setText(QTime(0, 0, 0).toString("hh:mm:ss"));
	m_pLbDisplay->clear();
	m_pBtnPlay->setChecked(false);
	if (m_pAudioOutput) {
		m_pAudioOutput->stop();
		SAFE_DELETE(m_pAudioOutput);
		m_pAudioOutput = nullptr;
	}
	if (m_nTimerId != -1) {
		this->killTimer(m_nTimerId);
		m_nTimerId = -1;
	}
	m_audioByteBuffer.clear();
	m_eState = CPlayBackWidget::State::Stop;
	emit notifyState(m_eState);
}

void CPlayBackWidget::enablePlay(const bool bEnable) const {
	m_pBtnPlay->setEnabled(bEnable);
}

CPlayBackWidget::State CPlayBackWidget::state() const {
	return m_eState;
}

QSize CPlayBackWidget::playSize() const {
	return m_pLbDisplay->size();
}

void CPlayBackWidget::setPlayState(const bool bPlay) const {
	m_pBtnPlay->setChecked(bPlay);
}

void CPlayBackWidget::timerEvent(QTimerEvent* event) {
	if (m_audioByteBuffer.length() <= 0) {
		return;
	}
	if (m_pAudioOutput && m_pAudioOutput->state() != QAudio::StoppedState && m_pAudioOutput->state() != QAudio::SuspendedState) {
		const int writeBytes = qMin(m_audioByteBuffer.length(), m_pAudioOutput->bytesFree());
		m_pAudioDevice->write(m_audioByteBuffer.data(), writeBytes);
		m_audioByteBuffer = m_audioByteBuffer.right(m_audioByteBuffer.length() - writeBytes);
	}
}

void CPlayBackWidget::onSliderDurationPressed() const {
	if (m_pCodecThread) {
		m_pCodecThread->pause();
	}
}

void CPlayBackWidget::onSliderDurationMoved(const int nPosition) const {
	const quint64 nCurCountdown = m_pSliderDuration->maximum() - nPosition;
	m_pLbCountDown->setText(QTime(0, 0).addSecs(static_cast<int>(nCurCountdown)).toString("hh:mm:ss"));
}

void CPlayBackWidget::onSliderDurationReleased() {
	if (m_pCodecThread) {
		m_audioByteBuffer.clear();
		m_pCodecThread->seek(m_pSliderDuration->value());
		m_pCodecThread->resume();
	}
}

void CPlayBackWidget::onBtnPlayClicked(const bool bChecked) {
	if (!bChecked) {
		stop();
	}
	emit notifyPlayClicked(bChecked);
}

void CPlayBackWidget::createCtrl() {
	m_pLbDisplay = new QLabel(this);
	QPalette palette{};
	palette.setBrush(QPalette::Window, Qt::black);
	m_pLbDisplay->setPalette(palette);
	m_pLbDisplay->setAutoFillBackground(true);

	m_pBtnPlay = new QPushButton(this);
	m_pBtnPlay->setObjectName("CPlayBackWidget_BtnPlay");
	m_pBtnPlay->setCheckable(true);

	m_pSliderDuration = new QSlider(Qt::Horizontal, this);
	m_pSliderDuration->setSingleStep(1);
	m_pSliderDuration->setEnabled(false);

	m_pLbDuration = new QLabel(this);
	m_pLbDuration->setText(QTime(0, 0, 0).toString("hh:mm:ss"));

	m_pLbCountDown = new QLabel(this);
	m_pLbCountDown->setText(QTime(0, 0, 0).toString("hh:mm:ss"));

	m_pLyFormDuration = new QFormLayout;
	m_pLyHPlay = new QHBoxLayout;
	m_pLyFormCountDown = new QFormLayout;
	m_pLyHDuration = new QHBoxLayout;
	m_pLyVTotal = new QVBoxLayout;

	m_pAspectRatioItem = new CAspectRatioItem(m_pLbDisplay, 16, 9);
}

void CPlayBackWidget::layOut() {
	m_pLyHPlay->addWidget(m_pBtnPlay);
	m_pLyHPlay->addWidget(m_pSliderDuration);

	m_pLyFormDuration->addRow(tr("Duration"), m_pLbDuration);

	m_pLyFormCountDown->addRow(tr("Countdown"), m_pLbCountDown);

	m_pLyHDuration->addLayout(m_pLyFormDuration);
	m_pLyHDuration->addStretch();
	m_pLyHDuration->addLayout(m_pLyFormCountDown);

	m_pLyVTotal->addItem(m_pAspectRatioItem);
	m_pLyVTotal->addLayout(m_pLyHPlay, 0);
	m_pLyVTotal->addLayout(m_pLyHDuration, 0);
	m_pLyVTotal->setStretch(0, 1);

	this->setLayout(m_pLyVTotal);
}

// void CPlayBackWidget::destroy() {
// }

void CPlayBackWidget::initConnect() {
	connect(m_pSliderDuration, &QSlider::sliderPressed, this, &CPlayBackWidget::onSliderDurationPressed);
	connect(m_pSliderDuration, &QSlider::sliderReleased, this, &CPlayBackWidget::onSliderDurationReleased);
	connect(m_pSliderDuration, &QSlider::sliderMoved, this, &CPlayBackWidget::onSliderDurationMoved);
	connect(m_pBtnPlay, &QPushButton::clicked, this, &CPlayBackWidget::onBtnPlayClicked);
}

// CAspectRatioItem
CAspectRatioItem::CAspectRatioItem(QWidget* parent) : QWidgetItem(parent) {
	Q_ASSERT(parent);
}

CAspectRatioItem::CAspectRatioItem(QWidget* parent, const int nWidthAspect, const int nHeightAspect)
: QWidgetItem(parent), m_nWidthAspect(nWidthAspect), m_nHeightAspect(nHeightAspect) {
	Q_ASSERT(parent);
}

CAspectRatioItem::~CAspectRatioItem() = default;

void CAspectRatioItem::setAspectRatio(const int nWidthAspect, const int nHeightAspect) {
	// 设置宽高比, 并通知父组件的布局无效, 以便重新计算布局
	m_nWidthAspect = nWidthAspect;
	m_nHeightAspect = nHeightAspect;
	if (this->widget()->parentWidget()) {
		if (this->widget()->parentWidget()->layout()) {
			this->widget()->parentWidget()->layout()->invalidate();
		}
	}
}

void CAspectRatioItem::setGeometry(const QRect& rect) {
	doLayout(rect);
}

int CAspectRatioItem::widthAspect() const {
	return m_nWidthAspect;
}

int CAspectRatioItem::heightAspect() const {
	return m_nHeightAspect;
}

void CAspectRatioItem::doLayout(const QRect& rect) const {
	auto rtKeepAspectRatio = rect;
	if (rect.width() * m_nHeightAspect > rect.height() * m_nWidthAspect) {
		int nWidth = rect.height() * static_cast<int>(static_cast<double>(m_nWidthAspect) / static_cast<double>(m_nHeightAspect));
		rtKeepAspectRatio.setLeft(rect.left() + (rect.width() - nWidth) / 2);
		rtKeepAspectRatio.setWidth(nWidth);
	} else if (rect.width() * m_nHeightAspect < rect.height() * m_nWidthAspect) {
		int nHeight = rect.width() * static_cast<int>(static_cast<double>(m_nHeightAspect) / static_cast<double>(m_nWidthAspect));
		rtKeepAspectRatio.setTop(rect.top() + (rect.height() - nHeight) / 2);
		rtKeepAspectRatio.setHeight(nHeight);
	}

	wid->setGeometry(rtKeepAspectRatio);
}
