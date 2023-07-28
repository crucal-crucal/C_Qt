#ifndef LGOIN_H
#define LGOIN_H

#include <QWidget>
#include <QLabel>
#include <my_dialog.h>
#include <my_register.h>
#include <my_findpasswd.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Lgoin; }
QT_END_NAMESPACE

class Lgoin : public QWidget
{
    Q_OBJECT

public:
    Lgoin(QWidget *parent = nullptr);
    ~Lgoin();

private slots:
    void on_Btn_min_clicked();

    void on_Btn_close_clicked();

    void on_Btn_login_clicked();

    void on_Btn_Qrcode_clicked();

    void on_Btn_Register_clicked();

    void on_Btn_findpasswd_clicked();

private:
    Ui::Lgoin *ui;
    QLabel * m_label;
    My_Dialog * mydig;
    My_register * my_res;
    My_findpasswd * findp;
};
#endif // LGOIN_H
