
#ifndef MYPLAINTEXTEDIT_H
#define MYPLAINTEXTEDIT_H


#include <QMainWindow>
#include <QPlainTextEdit>
#include <QMimeData>

class myplainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit myplainTextEdit(QWidget *parent = nullptr);

signals:


    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // MYPLAINTEXTEDIT_H
