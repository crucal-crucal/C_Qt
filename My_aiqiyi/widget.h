
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <Qpair>
#include <QIcon>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <qheaderview.h>
#include <QListWidgetItem>
#include <QToolTip>
#include <QtNetwork>
#include <QCoreApplication>


#include "mywidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
public:
    void init();
    void recommend();
    void TV();
    void movie();
    void annimation();
    void Children();

protected:

private:
    Ui::Widget *ui;

private:
    QList<QAction *> interface;
    const int N = 5;
    bool recommmend_check = false, TV_check = false, movie_check = false, annimation_check = false, children_check = false;
    QPushButton *btn1, *btn2, *btn3, *btn4, *btn5;
    QListWidgetItem *item;
    QVector<Mywidget *> w;
};

#endif // WIDGET_H
