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
    void on_pushButton_clicked();

    void on_Btn_color_clicked();

    void on_Btn_input_clicked();

    void on_Btn_progress_clicked();

    void on_Btn_file_clicked();

    void on_Btn_existing_clicked();

    void on_Btn_save_clicked();

    void on_Btn_massage_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
