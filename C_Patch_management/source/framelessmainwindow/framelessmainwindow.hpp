#pragma once

#include <QMainWindow>

/*
 * @brief 无边框MainWindow，支持拖拽，拉伸，移动以及自定义标题栏
 */
#ifdef FRAMELESSMAINWINDOW_LIB
#define FRAMELESSMAINWINDOW_EXPORT Q_DECL_EXPORT
#else
#define FRAMELESSMAINWINDOW_EXPORT Q_DECL_IMPORT
#endif

class FramelessMainWindowPrivate;

class FRAMELESSMAINWINDOW_EXPORT FramelessMainWindow : public QMainWindow {
	Q_OBJECT
	Q_DECLARE_PRIVATE(FramelessMainWindow)

public:
	explicit FramelessMainWindow(QWidget* parent = nullptr);
	~FramelessMainWindow() override;

protected:
	void showEvent(QShowEvent* event) override;

	// 事件过滤器识别拖动拉伸等
	void doWindowStateChange(const QEvent* event);
	void doResizeEvent(QEvent* event);
	bool eventFilter(QObject* watched, QEvent* event) override;

	const QScopedPointer<FramelessMainWindowPrivate> d_ptr{ nullptr };

	// 拦截系统事件用于修复系统休眠后唤醒程序的bug
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
	bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result);
#else
	bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
#endif

	// Qt4的写法
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#ifdef Q_OS_WIN
	bool winEvent(MSG *message, long *result);
#endif
#endif

public Q_SLOTS:
	// 设置边距+可拖动+可拉伸
	void setPadding(int _padding);
	void setMoveEnable(bool _moveEnable);
	void setResizeEnable(bool _resizeEnable);

	// 设置标题栏控件
	void setTitleBar(QWidget* _titleBar);

Q_SIGNALS:
	void titleDblClick();
	void windowStateChange(bool max);
};
