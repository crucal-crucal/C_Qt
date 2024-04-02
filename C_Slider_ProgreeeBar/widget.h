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
    void on_Dial_valueChanged(int value);

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalScrollBar_valueChanged(int value);

    void on_R_Btn_Bin_clicked();

    void on_radioButton_5_clicked();

    void on_checkBox_Visible_clicked(bool checked);

    void on_checkBox_inverted_clicked(bool checked);

    void on_R_Btn_percentage_clicked();

    void on_R_Btn_point_clicked();

    void on_R_Btn_OCT_clicked();

    void on_R_Btn_HEX_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
