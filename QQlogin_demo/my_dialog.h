#ifndef MY_DIALOG_H
#define MY_DIALOG_H

#include <QDialog>

namespace Ui {
class My_Dialog;
}

class My_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit My_Dialog(QWidget *parent = nullptr);
    ~My_Dialog();

private slots:
    void on_Btn_close_clicked();

    void on_Btn_min_clicked();

private:
    Ui::My_Dialog *ui;
    My_Dialog * mydig_1;
};

#endif // MY_DIALOG_H
