#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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
    void on_Btn_Time_clicked();

    void on_Btn_settime_clicked();

    void on_Btn_setdate_clicked();

    void on_Btn_settd_clicked();

    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
