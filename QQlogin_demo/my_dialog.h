#ifndef MY_DIALOG_H
#define MY_DIALOG_H

#include <QDialog>
#include <QToolButton>
#include <QMessageBox>

#include "QMyChat.h"

namespace Ui {
class My_Dialog;
}

class My_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit My_Dialog(QWidget *parent = nullptr);
    ~My_Dialog();

private:
    Ui::My_Dialog *ui;
    QVector<bool> isShow;
};

#endif // MY_DIALOG_H
