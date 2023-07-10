#ifndef MY_FINDPASSWD_H
#define MY_FINDPASSWD_H

#include <QDialog>

namespace Ui {
class My_findpasswd;
}

class My_findpasswd : public QDialog
{
    Q_OBJECT

public:
    explicit My_findpasswd(QWidget *parent = nullptr);
    ~My_findpasswd();

private slots:
    void on_Btn_cancel_clicked();

    void on_Btn_min_clicked();

    void on_Btn_close_clicked();

private:
    Ui::My_findpasswd *ui;
    My_findpasswd * findp_1;
};

#endif // MY_FINDPASSWD_H
