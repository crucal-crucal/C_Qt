<<<<<<< HEAD
#include "my_dialog.h"
#include "ui_my_dialog.h"

My_Dialog::My_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::My_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("QQ");

    QList<QString> name;
    auto func = [&] {
        name << "Alice" << "Bob" << "George" << "crucal" << "huord" << "clide"
        << "clasic" << "tom" << "jon";
    };
    func();

    QVector<QToolButton *> vector;
    for (int i = 0; i < (int)name.size(); i++) {
        QToolButton *btn = new QToolButton();
        QPixmap pixmap(":/images/1 (2).jpg");
        // 加载图片
        btn->setIcon(pixmap);
        // 设置图片大小
        btn->setIconSize(QSize(100, 100));
        btn->setText(name[i]);
        // 设置为透明
        btn->setAutoRaise(true);
        // 设置显示格式
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        // 添加按钮
        ui->verticalLayout_2->addWidget(btn);
        // 存储按钮
        vector.push_back(btn);
        // 当前按钮未显示
        isShow.push_back(false);
    }

    // 在 lambda 表达式中使用 [&] 捕获所有外部变量时，
    // i 是一个循环变量，每次循环的值都会发生变化。
    // 当信号被触发时，lambda 表达式中使用的 i 的值可能已经超出了 vector 数组的范围，导致程序出现数组越界错误。
    // 所以需要使用 [=]
    for (int i = 0; i < (int)vector.size(); i++) {
        connect(vector[i], &QToolButton::clicked, this, [ = ]() {
            if (isShow[i]) {
                QMessageBox::warning(this, "警告", "该聊天已被打开");
                return;
            }
            isShow[i] = true;
            QMyChat* myChat = new QMyChat(this, vector[i]->text());
            myChat->setWindowIcon(vector[i]->icon());
            myChat->setWindowTitle(vector[i]->text());
            myChat->show();

            // 关闭时将isshow设置为false
            connect(myChat, &QMyChat::closeWidget, this, [ = ]() {
                isShow[i] = false;
            });
        });
    }
}

My_Dialog::~My_Dialog()
{
    delete ui;
}
=======
#include "my_dialog.h"
#include "ui_my_dialog.h"

My_Dialog::My_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::My_Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("QQ");

    QList<QString> name;
    auto func=[&]{
        name << "Alice" << "Bob" << "George" << "crucal" << "huord" << "clide"
             << "clasic" << "tom" << "jon";
    };
    func();

    QVector<QToolButton *> vector;
    for (int i=0;i<(int)name.size();i++){
        QToolButton *btn = new QToolButton();
        QPixmap pixmap(":/images/1 (2).jpg");
        // 加载图片
        btn->setIcon(pixmap);
        // 设置图片大小
        btn->setIconSize(QSize(100, 100));
        btn->setText(name[i]);
        // 设置为透明
        btn->setAutoRaise(true);
        // 设置显示格式
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        // 添加按钮
        ui->verticalLayout_2->addWidget(btn);
        // 存储按钮
        vector.push_back(btn);
        // 当前按钮未显示
        isShow.push_back(false);
    }

    // 在 lambda 表达式中使用 [&] 捕获所有外部变量时，
    // i 是一个循环变量，每次循环的值都会发生变化。
    // 当信号被触发时，lambda 表达式中使用的 i 的值可能已经超出了 vector 数组的范围，导致程序出现数组越界错误。
    // 所以需要使用 [=]
    for (int i=0;i<(int)vector.size();i++){
        connect(vector[i], &QToolButton::clicked, this, [=](){
            if(isShow[i]){
                QMessageBox::warning(this, "警告", "该聊天已被打开");
                return;
            }
            isShow[i] = true;
            QMyChat* myChat = new QMyChat(this, vector[i]->text());
            myChat->setWindowIcon(vector[i]->icon());
            myChat->setWindowTitle(vector[i]->text());
            myChat->show();

            // 关闭时将isshow设置为false
            connect(myChat, &QMyChat::closeWidget, this, [=](){
                isShow[i] = false;
            });
        });
    }
}

My_Dialog::~My_Dialog()
{
    delete ui;
}
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
