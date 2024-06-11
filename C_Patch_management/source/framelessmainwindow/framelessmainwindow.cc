#include "framelessmainwindow.hpp"
#include "qdatetime.h"
#include "qdebug.h"
#include "qevent.h"

#include "framelessmainwindow_p.hpp"

#ifdef Q_OS_WIN
#include "windows.h"
#include "windowsx.h"
#pragma comment (lib, "user32.lib")
#endif

/*!
 *  \FramelessMainWindowPrivate
 *  \internal
 */
FramelessMainWindowPrivate::FramelessMainWindowPrivate(FramelessMainWindow* q): q_ptr(q) {
}

FramelessMainWindowPrivate::~FramelessMainWindowPrivate() = default;

void FramelessMainWindowPrivate::init() {
	Q_Q(FramelessMainWindow);

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
	flags = q->windowFlags();
	titleBar = nullptr;
}

FramelessMainWindow::FramelessMainWindow(QWidget* parent) : QMainWindow(parent), d_ptr(new FramelessMainWindowPrivate(this)) {
	d_func()->init();
	// 设置背景透明 官方在5.3以后才彻底修复 WA_TranslucentBackground+FramelessWindowHint 并存不绘制的bug
#if (QT_VERSION >= QT_VERSION_CHECK(5, 3, 0))
	//	this->setAttribute(Qt::WA_TranslucentBackground);
#endif
	// 设置无边框属性
	this->setWindowFlags(d_ptr->flags | Qt::FramelessWindowHint);
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
	Q_D(FramelessMainWindow);

	Q_UNUSED(event)
	// 非最大化才能移动和拖动大小
	d->moveEnable = d->resizeEnable = windowState() == Qt::WindowNoState;
	// 发出最大化最小化等改变事件,以便界面上更改对应的信息比如右上角图标和文字
	Q_EMIT windowStateChange(!d->moveEnable);
	// 解决mac系统上无边框最小化失效的bug
#ifdef Q_OS_MACOS
	if (windowState() & Qt::WindowMinimized) {
		d->isMin = true;
	} else {
		if (d->isMin) {
			//设置无边框属性
			this->setWindowFlags(d->flags | Qt::FramelessWindowHint);
			this->setVisible(true);
			d->isMin = false;
		}
	}
#endif
}

void FramelessMainWindow::doResizeEvent(QEvent* event) { // NOLINT
	// 非win系统的无边框拉伸,win系统上已经采用了nativeEvent来处理拉伸
	// 为何不统一用计算的方式因为在win上用这个方式往左拉伸会发抖妹的
#ifndef Q_OS_WIN
	Q_D(FramelessMainWindow);

	if (const int type = event->type(); type == QEvent::Resize) {
		//重新计算八个描点的区域,描点区域的作用还有就是计算鼠标坐标是否在某一个区域内
		const int width = this->width();
		const int height = this->height();
		//左侧描点区域
		d->pressedRect[0] = QRect(0, d->padding, d->padding, height - d->padding * 2);
		//右侧描点区域
		d->pressedRect[1] = QRect(width - d->padding, d->padding, d->padding, height - d->padding * 2);
		//上侧描点区域
		d->pressedRect[2] = QRect(d->padding, 0, width - d->padding * 2, d->padding);
		//下侧描点区域
		d->pressedRect[3] = QRect(d->padding, height - d->padding, width - d->padding * 2, d->padding);

		//左上角描点区域
		d->pressedRect[4] = QRect(0, 0, d->padding, d->padding);
		//右上角描点区域
		d->pressedRect[5] = QRect(width - d->padding, 0, d->padding, d->padding);
		//左下角描点区域
		d->pressedRect[6] = QRect(0, height - d->padding, d->padding, d->padding);
		//右下角描点区域
		d->pressedRect[7] = QRect(width - d->padding, height - d->padding, d->padding, d->padding);
	} else if (type == QEvent::HoverMove) {
		//设置对应鼠标形状,这个必须放在这里而不是下面,因为可以在鼠标没有按下的时候识别
		const auto* hoverEvent = dynamic_cast<QHoverEvent*>(event);
		const QPoint point = hoverEvent->pos();
		if (d->resizeEnable) {
			if (d->pressedRect.at(0).contains(point) || d->pressedRect.at(1).contains(point)) {
				this->setCursor(Qt::SizeHorCursor);
			} else if (d->pressedRect.at(2).contains(point) || d->pressedRect.at(3).contains(point)) {
				this->setCursor(Qt::SizeVerCursor);
			} else if (d->pressedRect.at(4).contains(point) || d->pressedRect.at(7).contains(point)) {
				this->setCursor(Qt::SizeFDiagCursor);
			} else if (d->pressedRect.at(5).contains(point) || d->pressedRect.at(6).contains(point)) {
				this->setCursor(Qt::SizeBDiagCursor);
			} else {
				this->setCursor(Qt::ArrowCursor);
			}
		}

		//根据当前鼠标位置,计算XY轴移动了多少
		const int offsetX = point.x() - d->mousePoint.x();
		const int offsetY = point.y() - d->mousePoint.y();

		//根据按下处的位置判断是否是移动控件还是拉伸控件
		if (d->moveEnable && d->mousePressed) {
			this->move(this->x() + offsetX, this->y() + offsetY);
		}

		if (d->resizeEnable) {
			const int rectX = d->mouseRect.x();
			const int rectY = d->mouseRect.y();
			const int rectW = d->mouseRect.width();
			const int rectH = d->mouseRect.height();

			if (d->pressedArea.at(0)) {
				if (const int resizeW = this->width() - offsetX; this->minimumWidth() <= resizeW) {
					this->setGeometry(this->x() + offsetX, rectY, resizeW, rectH);
				}
			} else if (d->pressedArea.at(1)) {
				this->setGeometry(rectX, rectY, rectW + offsetX, rectH);
			} else if (d->pressedArea.at(2)) {
				if (const int resizeH = this->height() - offsetY; this->minimumHeight() <= resizeH) {
					this->setGeometry(rectX, this->y() + offsetY, rectW, resizeH);
				}
			} else if (d->pressedArea.at(3)) {
				this->setGeometry(rectX, rectY, rectW, rectH + offsetY);
			} else if (d->pressedArea.at(4)) {
				const int resizeW = this->width() - offsetX;
				const int resizeH = this->height() - offsetY;
				if (this->minimumWidth() <= resizeW) {
					this->setGeometry(this->x() + offsetX, this->y(), resizeW, resizeH);
				}
				if (this->minimumHeight() <= resizeH) {
					this->setGeometry(this->x(), this->y() + offsetY, resizeW, resizeH);
				}
			} else if (d->pressedArea.at(5)) {
				const int resizeW = rectW + offsetX;
				if (const int resizeH = this->height() - offsetY; this->minimumHeight() <= resizeH) {
					this->setGeometry(this->x(), this->y() + offsetY, resizeW, resizeH);
				}
			} else if (d->pressedArea.at(6)) {
				const int resizeW = this->width() - offsetX;
				const int resizeH = rectH + offsetY;
				if (this->minimumWidth() <= resizeW) {
					this->setGeometry(this->x() + offsetX, this->y(), resizeW, resizeH);
				}
				if (this->minimumHeight() <= resizeH) {
					this->setGeometry(this->x(), this->y(), resizeW, resizeH);
				}
			} else if (d->pressedArea.at(7)) {
				const int resizeW = rectW + offsetX;
				const int resizeH = rectH + offsetY;
				this->setGeometry(this->x(), this->y(), resizeW, resizeH);
			}
		}
	} else if (type == QEvent::MouseButtonPress) {
		//记住鼠标按下的坐标+窗体区域
		const QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
		d->mousePoint = mouseEvent->pos();
		d->mouseRect = this->geometry();

		//判断按下的手柄的区域位置
		if (d->pressedRect.at(0).contains(d->mousePoint)) {
			d->pressedArea[0] = true;
		} else if (d->pressedRect.at(1).contains(d->mousePoint)) {
			d->pressedArea[1] = true;
		} else if (d->pressedRect.at(2).contains(d->mousePoint)) {
			d->pressedArea[2] = true;
		} else if (d->pressedRect.at(3).contains(d->mousePoint)) {
			d->pressedArea[3] = true;
		} else if (d->pressedRect.at(4).contains(d->mousePoint)) {
			d->pressedArea[4] = true;
		} else if (d->pressedRect.at(5).contains(d->mousePoint)) {
			d->pressedArea[5] = true;
		} else if (d->pressedRect.at(6).contains(d->mousePoint)) {
			d->pressedArea[6] = true;
		} else if (d->pressedRect.at(7).contains(d->mousePoint)) {
			d->pressedArea[7] = true;
		} else {
			d->mousePressed = true;
		}
	} else if (type == QEvent::MouseMove) {
		//改成用HoverMove识别
	} else if (type == QEvent::MouseButtonRelease) {
		//恢复所有
		this->setCursor(Qt::ArrowCursor);
		d->mousePressed = false;
		for (int i = 0; i < 8; ++i) {
			d->pressedArea[i] = false;
		}
	}
#endif
}

bool FramelessMainWindow::eventFilter(QObject* watched, QEvent* event) {
	Q_D(FramelessMainWindow);

	const int type = event->type();
	if (watched == this) {
		if (type == QEvent::WindowStateChange) {
			doWindowStateChange(event);
		} else {
			doResizeEvent(event);
		}
	} else if (watched == d->titleBar) {
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
	Q_D(FramelessMainWindow);

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
				const bool left = pos.x() < d->padding;
				const bool right = pos.x() > width() - d->padding;
				const bool top = pos.y() < d->padding;
				const bool bottom = pos.y() > height() - d->padding;

				// 鼠标移动到四个角,这个消息是当鼠标移动或者有鼠标键按下时候发出的
				*result = 0;
				if (d->resizeEnable) {
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
				if (d->titleBar && d->titleBar->rect().contains(pos)) {
					if (const QWidget* child = d->titleBar->childAt(pos); !child) {
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
	Q_D(FramelessMainWindow);

	d->padding = _padding;
}

void FramelessMainWindow::setMoveEnable(const bool _moveEnable) {
	Q_D(FramelessMainWindow);

	d->moveEnable = _moveEnable;
}

void FramelessMainWindow::setResizeEnable(const bool _resizeEnable) {
	Q_D(FramelessMainWindow);

	d->resizeEnable = _resizeEnable;
}

void FramelessMainWindow::setTitleBar(QWidget* _titleBar) {
	Q_D(FramelessMainWindow);

	d->titleBar = _titleBar;
	d->titleBar->installEventFilter(this);
}
