#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_Btn_start_clicked();

    void on_Btn_stop_clicked();

    void do_timer_timeout();

    void on_Btn_dynamic_clicked();

    void do_timer_shot();

private:
    Ui::Widget *ui;
    QTimer *tm, m_counter;
    int value = 0;
};
#endif // WIDGET_H
