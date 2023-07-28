#ifndef MY_REGISTER_H
#define MY_REGISTER_H

#include <QDialog>

namespace Ui {
class My_register;
}

class My_register : public QDialog
{
    Q_OBJECT

public:
    explicit My_register(QWidget *parent = nullptr);
    ~My_register();

private slots:
    void on_Btn_close_clicked();

    void on_Btn_min_clicked();

private:
    Ui::My_register *ui;
    My_register * myres_1;
};

#endif // MY_REGISTER_H
