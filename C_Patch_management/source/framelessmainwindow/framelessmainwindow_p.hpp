#pragma once

#include <QWidget>

class FramelessMainWindow;

class FramelessMainWindowPrivate {
	Q_DISABLE_COPY(FramelessMainWindowPrivate)
	Q_DECLARE_PUBLIC(FramelessMainWindow)

public:
	explicit FramelessMainWindowPrivate(FramelessMainWindow* q);
	~FramelessMainWindowPrivate();

	void init();

	FramelessMainWindow* const q_ptr{ nullptr };
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
};
