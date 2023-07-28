<<<<<<< HEAD
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
=======
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
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
