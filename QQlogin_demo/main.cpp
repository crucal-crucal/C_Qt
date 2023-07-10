#include "lgoin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lgoin w;
    w.show();
    return a.exec();
}
