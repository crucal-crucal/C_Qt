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
    void on_Btn_front_clicked();

    void on_Btn_left_clicked();

    void on_Btn_first_clicked();

    void on_Btn_section_clicked();

    void on_Btn_empty_clicked();

    void on_Btn_resize_clicked();

    void on_Btn_size_clicked();

    void on_Btn_fill_clicked();

    void on_Btn_index_clicked();

    void on_Btn_contains_clicked();

    void on_Btn_endswith_clicked();

    void on_Btn_count_clicked();

    void on_Btn_trimmed_clicked();

    void on_Btn_insert_clicked();

    void on_Btn_remove_clicked();

    void on_Btn_repalce_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
