#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_Xiahuaxian_clicked(bool checked);

    void on_Xieti_clicked(bool checked);

    void on_Cuti_clicked(bool checked);

    void on_Black_clicked();

    void on_Red_clicked();

    void on_Blue_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
