#include "include/Client_Info_Form.h"

#include "include/mainwindow.h"
#include "ui_Client_Info_Form.h"

Client_Info_Form* Client_Info_Form::self = nullptr;

Client_Info_Form::Client_Info_Form(QWidget* parent) : QDialog(parent), ui(new Ui::Client_Info_Form) {
    ui->setupUi(this);
}

Client_Info_Form::~Client_Info_Form() { delete ui; }

void Client_Info_Form::init() {
    QFont font("Microsoft YaHei", FONTSIZE);
    ui->lab_Client_Property->setFont(font);
    ui->client_ip->setFont(font);
    ui->client_port->setFont(font);
    ui->client_pro->setFont(font);
    ui->client_slaveID->setFont(font);
    ui->client_gct->setFont(font);
    ui->client_des->setFont(font);

    ui->lineEdit_client_ip->setFont(font);
    ui->lineEdit_client_port->setFont(font);
    ui->lineEdit_client_pro->setFont(font);
    ui->lineEdit_client_slaveID->setFont(font);
    ui->lineEdit_client_gct->setFont(font);
    ui->textEdit_client_des->setFont(font);

    // 设置自动换行
    QTextOption textOption;
    textOption.setWrapMode(QTextOption::WrapAnywhere);
    ui->textEdit_client_des->document()->setDefaultTextOption(textOption);
}

void Client_Info_Form::updateInfo(QString str) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << "curText:\t" << str;
#endif
    QStringList list = str.split(',');
    if (list.size() != client_Size) {
        return qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');
    t = list.at(1).split(':');
    QString ip = t[t.size() - 1];
    ui->lineEdit_client_ip->setText(ip);

    t = list.at(2).split(':');
    QString port = t[t.size() - 1];
    ui->lineEdit_client_port->setText(port);

    t = list.at(3).split(':');
    QString protocol = t[t.size() - 1];
    ui->lineEdit_client_pro->setText(protocol);

    t = list.at(4).split(':');
    QString slaveID = t[t.size() - 1];
    ui->lineEdit_client_slaveID->setText(slaveID);

    t = list.at(5).split(':');
    QString generalCallTime = t[t.size() - 1];
    ui->lineEdit_client_gct->setText(generalCallTime);

    t = list.at(6).split(':');
    QString describe = t[t.size() - 1];
    ui->textEdit_client_des->setText(describe);
}
