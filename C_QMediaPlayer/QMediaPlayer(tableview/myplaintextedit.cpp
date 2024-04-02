
#include "myplaintextedit.h"

#include <QDragEnterEvent>
#include <QFileInfo>

myplainTextEdit::myplainTextEdit(QWidget *parent)
    : QPlainTextEdit{parent}
{
    setAcceptDrops(true);
}

void myplainTextEdit::dragEnterEvent(QDragEnterEvent *event)
{
    clear();
    appendPlainText("dragEnterEvent事件");
    auto n=event->mimeData()->formats().size();
    for (int i=0;i<n;i++)
    {
        appendPlainText(event->mimeData()->formats().at(i));
    }
    appendPlainText("\n dragEnterEvent事件");
    for (int i=0;i<n;i++)
    {
        auto url = event->mimeData()->urls().at(i);
        appendPlainText(url.path());
    }

    if(event->mimeData()->hasUrls())
    {
        auto filname = event->mimeData()->urls().at(0).fileName();
        QFileInfo fileinfo(filname);
        auto ext = fileinfo.suffix().toUpper();
        if(ext == "JPG" || ext == "BMP" || ext == "PNG")
            event->acceptProposedAction();//接受
        else event->ignore();//忽略
    }
    else event->ignore();
}

void myplainTextEdit::dropEvent(QDropEvent *event)
{
    qDebug()<<2;
}

