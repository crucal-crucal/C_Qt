<<<<<<< HEAD
#ifndef MY_OPENINTERFACE_H
#define MY_OPENINTERFACE_H

#include <QDialog>

namespace Ui {
class My_openInterface;
}

class My_openInterface : public QDialog
{
    Q_OBJECT

public:
    explicit My_openInterface(QWidget *parent = nullptr);
    ~My_openInterface();

    void newinterFace();
    void oldinterFace();

signals:
    void Yes();
    void No();
private:
    Ui::My_openInterface *ui;
};

#endif // MY_OPENINTERFACE_H
=======
#ifndef MY_OPENINTERFACE_H
#define MY_OPENINTERFACE_H

#include <QDialog>

namespace Ui {
class My_openInterface;
}

class My_openInterface : public QDialog
{
    Q_OBJECT

public:
    explicit My_openInterface(QWidget *parent = nullptr);
    ~My_openInterface();

private:
    Ui::My_openInterface *ui;
};

#endif // MY_OPENINTERFACE_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
