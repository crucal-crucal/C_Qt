#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    void emitsignal();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void mySlot();
    void student();
    void teacher();
signals:
    void mysignal();
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
