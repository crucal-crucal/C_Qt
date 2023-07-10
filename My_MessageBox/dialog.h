#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QErrorMessage>
#include <QLabel>

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
    void on_Btn_openfile_clicked();

    void on_Btn_directory_clicked();

    void on_Btn_save_clicked();

    void on_Btn_color_clicked();

    void on_Btn_font_clicked();

    void on_Btn_message_clicked();

    void on_Btn_close_clicked();

    void on_Btn_clean_clicked();

    void on_Btn_inptstring_clicked();

    void on_Btn_inptint_clicked();

    void on_Btn_inptdouble_clicked();

    void on_Btn_openfiles_clicked();

    void on_pushButton_10_clicked();

    void on_Btn_question_clicked();

    void on_Btn_information_clicked();

    void on_Btn_warning_clicked();

    void on_Btn_critical_clicked();

    void on_Btn_about_clicked();

    void on_Btn_aboutQt_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
