#pragma once

#include <QLabel>
#include <QList>
#include <QtGlobal>
#include <QTimer>

//样式，字体颜色：白色；圆角；背景色透明度
#define STYLE_SHEET "color:%1;border-radius:8px;background-color:rgba(80, 80, 80, %2);"

#ifdef NOTICEWIDGET_LIB
#define NOTICEWIDGET_EXPORT Q_DECL_EXPORT
#else
#define NOTICEWIDGET_EXPORT Q_DECL_IMPORT
#endif

/*
 * @brief 提示控件，渐变消失
 */

class NOTICEWIDGET_EXPORT CUVNoticeWidget final : public QLabel {
	Q_OBJECT

public:
	explicit CUVNoticeWidget(QWidget* parent = nullptr);
	~CUVNoticeWidget() override;

	/*
	 * @note 显示提示信息
	 * @param parent 父控件
	 * @param msg 提示信息
	 * @param delay_ms 提示时间，单位ms，默认2000ms
	 * @param bsuccess 是否成功，成功为绿色，失败为红色
	 */
	void notice(QWidget* parent, const QString& msg, int delay_ms = 2000, bool bsuccess = true);

private:
	/*
	 * @note 设置提示信息，确保始终在父窗口中间显示，调整大小
	 * @param msg 提示信息
	 * @param delay_ms 提示时间，单位ms，默认2000ms
	 * @param bsuccess 是否成功，成功为绿色，失败为红色
	 */
	void setMessage(const QString& msg, int delay_ms, bool bsuccess = true);
	/*
	 * @note 调整大小
	 */
	void changeSize();

public slots:
	/*
	 * @note 渐变消失背景
	 */
	void OnTimerTimeout();

private:
	QWidget* m_Parent{ nullptr };
	QTimer* m_Timer{ nullptr };
	int m_TimerCount{};
	int m_BaseWidth{};              //按一行时算的宽度
	int m_BaseHeight{};             //一行高度
	int m_MinHeight{};              //最小高度
	int m_TransparentVal{ 255 };    //透明度0~255，值越小越透明
	QString m_fontcolor{ "green" }; // 字体颜色
	QList<int> m_ListLinesLen{};

	int m_timer_interval_ms{ 50 };                                                   // 定时器间隔，单位ms
	int m_notice_def_delay_cnt{ 1000 / m_timer_interval_ms };                        // 默认提示时间1s
	int m_transparent_max_val{ 255 };                                                // 透明度最大值255，也就是不透明
	int m_transparent_cut_val{ m_transparent_max_val / m_notice_def_delay_cnt + 1 }; // 透明度递减值
	double m_size_scale{ 0.2 };                                                      // 大小比例
	int m_patch_height{ 10 };                                                        // 高度补偿
};
