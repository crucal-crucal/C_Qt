#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

typedef enum Direct
{
    Sn_Left,
    Sn_Right,
    Sn_Up,
    Sn_Down
}dir_t;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);
    void addTop();
    void addDown();
    void addRight();
    void addLeft();
    //按键处理
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::Widget *ui;
    //初始方向
    int Move_flag = Sn_Up;
    bool GameStart = 0;
    //定时器
    QTimer *timer;
    int my_time = 100;
    //蛇
    QList <QRectF> snake;
    //小方块的大小
    int nodeWidth = 20;
    int nodeHeight = 20;

protected slots:
    void timeout();
};
#endif // WIDGET_H
