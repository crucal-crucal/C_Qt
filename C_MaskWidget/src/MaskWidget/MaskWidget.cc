#include "MaskWidget.h"

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include "qscreen.h"
#define deskGeometry qApp->primaryScreen()->geometry()
#define deskGeometry2 qApp->primaryScreen()->availableGeometry()
#else
#include "qdesktopwidget.h"
#define deskGeometry qApp->desktop()->geometry()
#define deskGeometry2 qApp->desktop()->availableGeometry()
#endif

QScopedPointer<MaskWidget> MaskWidget::self{};
MaskWidget* MaskWidget::Instance() {
	if (self.isNull()) {
		static QMutex mutex;
		QMutexLocker locker(&mutex);
		if (self.isNull()) {
			self.reset(new MaskWidget());
		}
	}
	return self.data();
}

MaskWidget::MaskWidget(QWidget* parent) : QWidget(parent) {
	this->setOpacity(0.7);
	this->setBackgroundColor(QColor(0, 0, 0));

	// 不设置主窗体则遮罩层大小为默认桌面大小
	this->setGeometry(deskGeometry);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

	// 绑定全局事件,过滤弹窗窗体进行处理
	QCoreApplication::instance()->installEventFilter(this);
}

MaskWidget::~MaskWidget() = default;

void MaskWidget::showEvent(QShowEvent*) {
	if (mainWidget) {
		this->setGeometry(mainWidget->geometry());
	}
}

bool MaskWidget::eventFilter(QObject* watched, QEvent* event) {
	auto type = event->type();
	switch (type) {
		case QEvent::Show:
			if (dialogNames.contains(watched->objectName())) {
				this->show();
				this->activateWindow();
				QWidget* w = qobject_cast<QWidget*>(watched);
				w->activateWindow();
			}
			break;
		case QEvent::Hide:
			if (dialogNames.contains(watched->objectName())) {
				this->hide();
			}
			break;
		case QEvent::WindowActivate:
			if (mainWidget && watched->objectName() == mainWidget->objectName() && this->isVisible()) {
				this->activateWindow();
			}
			break;
		default: break;
	}

	return QObject::eventFilter(watched, event);
}

void MaskWidget::setMainWidget(QWidget* _mainWidget) {
	mainWidget = _mainWidget;
}

void MaskWidget::setDialogNames(const QStringList& _dialogNames) {
	if (this->dialogNames != _dialogNames) {
		this->dialogNames = _dialogNames;
	}
}

void MaskWidget::setBackgroundColor(const QColor& _color) {
	auto palette = this->palette();
	palette.setBrush(QPalette::Window, _color);
	this->setPalette(palette);
}

void MaskWidget::setOpacity(double _opacity) {
	this->setWindowOpacity(_opacity);
}
