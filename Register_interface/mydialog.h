#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
    ~MyDialog();
    MyDialog *Dlg;

private slots:
    void on_exit_clicked();

    void on_Xiahuaxian_clicked(bool checked);

    void on_Xieti_clicked(bool checked);

    void on_Cuti_clicked(bool checked);

    void on_Black_clicked();

    void on_Red_clicked();

    void on_Blue_clicked();

private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
