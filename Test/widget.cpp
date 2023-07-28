
#include "widget.h"
#include "./ui_widget.h"
#include "QSqlDatabase"

#include <QMenu>
#include <QMessageBox>
#include <QPushButton>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug()<<QSqlDatabase::drivers();

    btn = new QPushButton(this);
    QMenu *menu = new QMenu;
    menu->addAction("111");
    menu->addAction("222");
    menu->addAction("333");
    btn->setMenu(menu);
//    btn->move(QCursor::pos());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        QMenu menu;
        QAction *act = menu.addAction("C++");
        connect(act, &QAction::triggered, this, [=](){
            QMessageBox::information(this, "title", "C++");
        });
        menu.addAction("Java");
        menu.addAction("Py");
        menu.exec(QCursor::pos());//菜单显示位置
    }
}


