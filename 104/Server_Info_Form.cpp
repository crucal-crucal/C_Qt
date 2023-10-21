#include "Server_Info_Form.h"

#include "mainwindow.h"
#include "ui_Server_Info_Form.h"

Server_Info_Form* Server_Info_Form::self = nullptr;

Server_Info_Form::Server_Info_Form(QWidget* parent) : QDialog(parent), ui(new Ui::Server_Info_Form) {
    ui->setupUi(this);
}

Server_Info_Form::~Server_Info_Form() { delete ui; }

void Server_Info_Form::init() {
    QFont font("Microsoft YaHei", FONTSIZE);
    ui->label->setFont(font);

    ui->lab_ip->setFont(font);
    ui->lab_port->setFont(font);
    ui->lab_dataType->setFont(font);
    ui->lab_publicAddr->setFont(font);
    ui->lab_describe->setFont(font);

    ui->lineEdit_ip->setFont(font);
    ui->lineEdit_port->setFont(font);
    ui->lineEdit_dataType->setFont(font);
    ui->lineEdit_publicAddr->setFont(font);
    ui->textEdit_server_des->setFont(font);

    // 设置自动换行
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WrapAnywhere);
    ui->textEdit_server_des->document()->setDefaultTextOption(textOption);
}

void Server_Info_Form::updateInfo(QString str) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << "curText:\t" << str;
#endif
    QStringList list = str.split(',');
    if (list.size() != server_Size) {
        return qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');

    t = list.at(1).split(':');
    QString ip = t[t.size() - 1];
    ui->lineEdit_ip->setText(ip);

    t = list.at(2).split(':');
    QString port = t[t.size() - 1];
    ui->lineEdit_port->setText(port);

    t = list.at(3).split(':');
    QString dataType = t[t.size() - 1];
    ui->lineEdit_dataType->setText(dataType);

    t = list.at(4).split(':');
    QString publicAddr = t[t.size() - 1];
    ui->lineEdit_publicAddr->setText(publicAddr);

    t = list.at(5).split(':');
    QString describe = t[t.size() - 1];
    ui->textEdit_server_des->setText(describe);
}
