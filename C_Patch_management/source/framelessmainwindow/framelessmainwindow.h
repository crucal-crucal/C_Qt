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

class FRAMELESSMAINWINDOW_EXPORT FramelessMainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit FramelessMainWindow(QWidget* parent = nullptr);
	~FramelessMainWindow() override;

protected:
	void showEvent(QShowEvent* event) override;

	// 事件过滤器识别拖动拉伸等
	void doWindowStateChange(const QEvent* event);
	void doResizeEvent(QEvent* event);
	bool eventFilter(QObject* watched, QEvent* event) override;

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

private:
	// 边距+可移动+可拉伸
	int padding{};
	bool moveEnable{};
	bool resizeEnable{};

	// 标题栏控件
	QWidget* titleBar{ nullptr };

	// 鼠标是否按下、按下坐标、按下时窗体区域
	bool mousePressed{};
	QPoint mousePoint{};
	QRect mouseRect{};

	// 鼠标是否按下某个区域、按下区域的大小
	// 依次为 左、右、上、下、左上、右上、左下、右下
	QList<bool> pressedArea{};
	QList<QRect> pressedRect{};

	// 记录是否最小化
	bool isMin{};
	// 存储窗体默认的属性
	Qt::WindowFlags flags{};

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
