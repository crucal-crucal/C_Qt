#include "lgoin.h"

#include <QApplication>
#include "QMyChat.h"
//#define NDEBUG

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lgoin w;
    w.show();
#ifdef NDEBUG
    QMyChat* myChat = new QMyChat();
    myChat->show();
#endif
    return a.exec();
}
