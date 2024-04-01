#pragma once

#include <QWidget>
#include <QShowEvent>
#include <QEvent>
#include <QScopedPointer>
#include <QMutex>
#include <QApplication>
#include <QDebug>
#include <QScreen>

/*
 * @brief 弹窗遮罩层控件
 * 1. 可设置需要遮罩的主窗体，自动跟随主窗体位置显示遮罩面积。
 * 2. 只需要将弹窗窗体的名称一开始传入队列即可。
 * 3. 可设置透明度。
 * 4. 可设置遮罩层颜色。
 * 5. 不阻塞消息循坏。
 */

#ifdef MASKWIDGET
#define MASKWIDGET_EXPORT Q_DECL_EXPORT
#else
#define MASKWIDGET_EXPORT Q_DECL_IMPORT
#endif

class MASKWIDGET_EXPORT MaskWidget : public QWidget {
  Q_OBJECT
  public:
	static MaskWidget* Instance();
	explicit MaskWidget(QWidget* parent = nullptr);
	~MaskWidget() override;

  protected:
	void showEvent(QShowEvent*) override;
	bool eventFilter(QObject* watched, QEvent* event) override;

  public slots:
	/*
	 * @note: 设置需要遮罩的主窗体
	 * @parma: _mainWidget 需要遮罩的主窗体
	 */
	void setMainWidget(QWidget* _mainWidget);
	/*
	 * @note: 设置需要遮罩的窗体对象名称集合
	 * @parma: _dialogNames 需要遮罩的窗体对象名称集合
	 */
	void setDialogNames(const QStringList& _dialogNames);
	/*
	 * @note: 设置遮罩的背景颜色
	 * @parma: _color 遮罩的背景颜色
	 */
	void setBackgroundColor(const QColor& _color);
	/*
	 * @note: 设置遮罩的透明度
	 * @parma: _opacity 遮罩的透明度
	 * @note: 范围0.0-1.0
	 */
	void setOpacity(double _opacity);
  private:
	static QScopedPointer<MaskWidget> self;

	// 需要遮罩得主窗体
	QWidget* mainWidget{nullptr};
	// 需要弹窗得窗体对象名称集合链表
	QStringList dialogNames{nullptr};
};
