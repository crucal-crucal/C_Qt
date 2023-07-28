<<<<<<< HEAD

#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.connectDB();
    w.show();
    return a.exec();
}
=======

#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.connectDB();
    w.show();
    return a.exec();
}
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
