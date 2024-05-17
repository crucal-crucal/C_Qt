#include "framelessmainwindow.h"
#include "qdatetime.h"
#include "qdebug.h"
#include "qevent.h"

#ifdef Q_OS_WIN
#include "windows.h"
#include "windowsx.h"
#pragma comment (lib, "user32.lib")
#endif

FramelessMainWindow::FramelessMainWindow(QWidget* parent) : QMainWindow(parent) {
	padding = 8;
	moveEnable = true;
	resizeEnable = true;

	mousePressed = false;
	mousePoint = QPoint(0, 0);
	mouseRect = QRect(0, 0, 0, 0);

	for (int i = 0; i < 8; ++i) {
		pressedArea << false;
		pressedRect << QRect(0, 0, 0, 0);
	}

	isMin = false;
	flags = this->windowFlags();
	titleBar = nullptr;
	// 设置背景透明 官方在5.3以后才彻底修复 WA_TranslucentBackground+FramelessWindowHint 并存不绘制的bug
#if (QT_VERSION >= QT_VERSION_CHECK(5, 3, 0))
	//	this->setAttribute(Qt::WA_TranslucentBackground);
#endif
	// 设置无边框属性
	this->setWindowFlags(flags | Qt::FramelessWindowHint);
	// 安装事件过滤器识别拖动
	this->installEventFilter(this);
	// 设置属性产生win窗体效果,移动到边缘半屏或者最大化等
	// 设置以后会产生标题栏,需要在下面拦截消息WM_NCCALCSIZE重新去掉
#ifdef Q_OS_WIN
	const auto hwnd = reinterpret_cast<HWND>(this->winId());
	const auto style = ::GetWindowLong(hwnd, GWL_STYLE);
	::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
#endif
}

FramelessMainWindow::~FramelessMainWindow() = default;

void FramelessMainWindow::showEvent(QShowEvent* event) {
	// 解决有时候窗体重新显示的时候假死不刷新的bug
	setAttribute(Qt::WA_Mapped);
	QMainWindow::showEvent(event);
}

void FramelessMainWindow::doWindowStateChange(const QEvent* event) {
	Q_UNUSED(event)
	// 非最大化才能移动和拖动大小
	moveEnable = resizeEnable = windowState() == Qt::WindowNoState;
	// 发出最大化最小化等改变事件,以便界面上更改对应的信息比如右上角图标和文字
	Q_EMIT windowStateChange(!moveEnable);
	// 解决mac系统上无边框最小化失效的bug
#ifdef Q_OS_MACOS
	if (windowState() & Qt::WindowMinimized) {
		isMin = true;
	} else {
		if (isMin) {
			//设置无边框属性
			this->setWindowFlags(flags | Qt::FramelessWindowHint);
			this->setVisible(true);
			isMin = false;
		}
	}
#endif
}

void FramelessMainWindow::doResizeEvent(QEvent* event) { // NOLINT
	// 非win系统的无边框拉伸,win系统上已经采用了nativeEvent来处理拉伸
	// 为何不统一用计算的方式因为在win上用这个方式往左拉伸会发抖妹的
#ifndef Q_OS_WIN
	if (const int type = event->type(); type == QEvent::Resize) {
		//重新计算八个描点的区域,描点区域的作用还有就是计算鼠标坐标是否在某一个区域内
		const int width = this->width();
		const int height = this->height();
		//左侧描点区域
		pressedRect[0] = QRect(0, padding, padding, height - padding * 2);
		//右侧描点区域
		pressedRect[1] = QRect(width - padding, padding, padding, height - padding * 2);
		//上侧描点区域
		pressedRect[2] = QRect(padding, 0, width - padding * 2, padding);
		//下侧描点区域
		pressedRect[3] = QRect(padding, height - padding, width - padding * 2, padding);

		//左上角描点区域
		pressedRect[4] = QRect(0, 0, padding, padding);
		//右上角描点区域
		pressedRect[5] = QRect(width - padding, 0, padding, padding);
		//左下角描点区域
		pressedRect[6] = QRect(0, height - padding, padding, padding);
		//右下角描点区域
		pressedRect[7] = QRect(width - padding, height - padding, padding, padding);
	} else if (type == QEvent::HoverMove) {
		//设置对应鼠标形状,这个必须放在这里而不是下面,因为可以在鼠标没有按下的时候识别
		const auto* hoverEvent = dynamic_cast<QHoverEvent*>(event);
		const QPoint point = hoverEvent->pos();
		if (resizeEnable) {
			if (pressedRect.at(0).contains(point) || pressedRect.at(1).contains(point)) {
				this->setCursor(Qt::SizeHorCursor);
			} else if (pressedRect.at(2).contains(point) || pressedRect.at(3).contains(point)) {
				this->setCursor(Qt::SizeVerCursor);
			} else if (pressedRect.at(4).contains(point) || pressedRect.at(7).contains(point)) {
				this->setCursor(Qt::SizeFDiagCursor);
			} else if (pressedRect.at(5).contains(point) || pressedRect.at(6).contains(point)) {
				this->setCursor(Qt::SizeBDiagCursor);
			} else {
				this->setCursor(Qt::ArrowCursor);
			}
		}

		//根据当前鼠标位置,计算XY轴移动了多少
		const int offsetX = point.x() - mousePoint.x();
		const int offsetY = point.y() - mousePoint.y();

		//根据按下处的位置判断是否是移动控件还是拉伸控件
		if (moveEnable && mousePressed) {
			this->move(this->x() + offsetX, this->y() + offsetY);
		}

		if (resizeEnable) {
			const int rectX = mouseRect.x();
			const int rectY = mouseRect.y();
			const int rectW = mouseRect.width();
			const int rectH = mouseRect.height();

			if (pressedArea.at(0)) {
				if (const int resizeW = this->width() - offsetX; this->minimumWidth() <= resizeW) {
					this->setGeometry(this->x() + offsetX, rectY, resizeW, rectH);
				}
			} else if (pressedArea.at(1)) {
				this->setGeometry(rectX, rectY, rectW + offsetX, rectH);
			} else if (pressedArea.at(2)) {
				if (const int resizeH = this->height() - offsetY; this->minimumHeight() <= resizeH) {
					this->setGeometry(rectX, this->y() + offsetY, rectW, resizeH);
				}
			} else if (pressedArea.at(3)) {
				this->setGeometry(rectX, rectY, rectW, rectH + offsetY);
			} else if (pressedArea.at(4)) {
				const int resizeW = this->width() - offsetX;
				const int resizeH = this->height() - offsetY;
				if (this->minimumWidth() <= resizeW) {
					this->setGeometry(this->x() + offsetX, this->y(), resizeW, resizeH);
				}
				if (this->minimumHeight() <= resizeH) {
					this->setGeometry(this->x(), this->y() + offsetY, resizeW, resizeH);
				}
			} else if (pressedArea.at(5)) {
				const int resizeW = rectW + offsetX;
				if (const int resizeH = this->height() - offsetY; this->minimumHeight() <= resizeH) {
					this->setGeometry(this->x(), this->y() + offsetY, resizeW, resizeH);
				}
			} else if (pressedArea.at(6)) {
				const int resizeW = this->width() - offsetX;
				const int resizeH = rectH + offsetY;
				if (this->minimumWidth() <= resizeW) {
					this->setGeometry(this->x() + offsetX, this->y(), resizeW, resizeH);
				}
				if (this->minimumHeight() <= resizeH) {
					this->setGeometry(this->x(), this->y(), resizeW, resizeH);
				}
			} else if (pressedArea.at(7)) {
				const int resizeW = rectW + offsetX;
				const int resizeH = rectH + offsetY;
				this->setGeometry(this->x(), this->y(), resizeW, resizeH);
			}
		}
	} else if (type == QEvent::MouseButtonPress) {
		//记住鼠标按下的坐标+窗体区域
		const QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
		mousePoint = mouseEvent->pos();
		mouseRect = this->geometry();

		//判断按下的手柄的区域位置
		if (pressedRect.at(0).contains(mousePoint)) {
			pressedArea[0] = true;
		} else if (pressedRect.at(1).contains(mousePoint)) {
			pressedArea[1] = true;
		} else if (pressedRect.at(2).contains(mousePoint)) {
			pressedArea[2] = true;
		} else if (pressedRect.at(3).contains(mousePoint)) {
			pressedArea[3] = true;
		} else if (pressedRect.at(4).contains(mousePoint)) {
			pressedArea[4] = true;
		} else if (pressedRect.at(5).contains(mousePoint)) {
			pressedArea[5] = true;
		} else if (pressedRect.at(6).contains(mousePoint)) {
			pressedArea[6] = true;
		} else if (pressedRect.at(7).contains(mousePoint)) {
			pressedArea[7] = true;
		} else {
			mousePressed = true;
		}
	} else if (type == QEvent::MouseMove) {
		//改成用HoverMove识别
	} else if (type == QEvent::MouseButtonRelease) {
		//恢复所有
		this->setCursor(Qt::ArrowCursor);
		mousePressed = false;
		for (int i = 0; i < 8; ++i) {
			pressedArea[i] = false;
		}
	}
#endif
}

bool FramelessMainWindow::eventFilter(QObject* watched, QEvent* event) {
	const int type = event->type();
	if (watched == this) {
		if (type == QEvent::WindowStateChange) {
			doWindowStateChange(event);
		} else {
			doResizeEvent(event);
		}
	} else if (watched == titleBar) {
		// 双击标题栏发出双击信号给主界面
		// 下面的 *result = HTCAPTION; 标志位也会自动识别双击标题栏
#ifndef Q_OS_WIN
		if (type == QEvent::MouseButtonDblClick || type == QEvent::NonClientAreaMouseButtonDblClick) {
			Q_EMIT titleDblClick();
		}
#endif
	}

	return QMainWindow::eventFilter(watched, event);
}

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
bool FramelessMainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
#else
bool FramelessMainWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
#endif
{
	if (eventType == "windows_generic_MSG") {
#ifdef Q_OS_WIN
		switch (const auto* msg = static_cast<MSG*>(message); msg->message) {
			case WM_NCCALCSIZE: {
				*result = 0;
				return true;
			}
			case WM_SYSKEYDOWN | WM_SYSKEYUP: break;
			case WM_NCHITTEST: {
				// 计算鼠标对应的屏幕坐标
				// 这里最开始用的 LOWORD HIWORD 在多屏幕的时候会有问题
				// 官方说明在这里 https://docs.microsoft.com/zh-cn/windows/win32/inputdev/wm-nchittest
				const long x = GET_X_LPARAM(msg->lParam);
				const long y = GET_Y_LPARAM(msg->lParam);
				const QPoint pos = mapFromGlobal(QPoint(x, y));

				// 判断当前鼠标位置在哪个区域
				const bool left = pos.x() < padding;
				const bool right = pos.x() > width() - padding;
				const bool top = pos.y() < padding;
				const bool bottom = pos.y() > height() - padding;

				// 鼠标移动到四个角,这个消息是当鼠标移动或者有鼠标键按下时候发出的
				*result = 0;
				if (resizeEnable) {
					if (left && top) {
						*result = HTTOPLEFT;
					} else if (left && bottom) {
						*result = HTBOTTOMLEFT;
					} else if (right && top) {
						*result = HTTOPRIGHT;
					} else if (right && bottom) {
						*result = HTBOTTOMRIGHT;
					} else if (left) {
						*result = HTLEFT;
					} else if (right) {
						*result = HTRIGHT;
					} else if (top) {
						*result = HTTOP;
					} else if (bottom) {
						*result = HTBOTTOM;
					}
				}

				// 先处理掉拉伸
				if (0 != *result) {
					return true;
				}

				// 识别标题栏拖动产生半屏全屏效果
				if (titleBar && titleBar->rect().contains(pos)) {
					if (const QWidget* child = titleBar->childAt(pos); !child) {
						*result = HTCAPTION;
						return true;
					}
				}
				break;
			}
			case PBT_APMSUSPEND:
			case WM_POWERBROADCAST: {
				// 系统休眠的时候自动最小化可以规避程序可能出现的问题
				this->showMinimized();
				break;
			}
			case PBT_APMRESUMEAUTOMATIC: {
				// 休眠唤醒后自动打开
				this->showNormal();
			}
			default: break;
		}
#endif
	} else if (eventType == "xcb_generic_event_t" || eventType == "NSEvent") {
#ifdef Q_OS_MACOS
#endif
#ifdef Q_OS_LINUX
#endif
	}
	return false;
}

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#ifdef Q_OS_WIN
bool FramelessMainWindow::winEvent(MSG *message, long *result)
{
	return nativeEvent("windows_generic_MSG", message, result);
}
#endif
#endif

void FramelessMainWindow::setPadding(const int _padding) {
	this->padding = _padding;
}

void FramelessMainWindow::setMoveEnable(const bool _moveEnable) {
	this->moveEnable = _moveEnable;
}

void FramelessMainWindow::setResizeEnable(const bool _resizeEnable) {
	this->resizeEnable = _resizeEnable;
}

void FramelessMainWindow::setTitleBar(QWidget* _titleBar) {
	this->titleBar = _titleBar;
	this->titleBar->installEventFilter(this);
}
