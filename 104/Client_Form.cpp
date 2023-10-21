#include "Client_Form.h"

#include "ui_Client_Form.h"

Client_Form* Client_Form::self = nullptr;

Client_Form::Client_Form(QWidget* parent) : QDialog(parent), ui(new Ui::Client_Form) {
    ui->setupUi(this);
    this->init();
    connect(ui->btn_ok, &QPushButton::clicked, this, &Client_Form::OK);
    connect(ui->btn_cancel, &QPushButton::clicked, this, [=]() {
        emit cannel();
        this->close();
    });
}

Client_Form::~Client_Form() { delete ui; }

void Client_Form::init() {
    this->setWindowTitle("Client_Form");
    ui->lineEdit_id->setText("0");
    ui->lineEdit_ip->setText("0");
    ui->lineEdit_port->setText("0");
    ui->lineEdit_protocol->setText("0");
    ui->lineEdit_slaveID->setText("0");
    ui->lineEdit_gct->setText("0");
    ui->lineEdit_describe->setText("0");
}

void Client_Form::modifyClient(QString mes) {
    QStringList list = mes.split(',');
    if (list.size() == 7) {
        QStringList t = list.at(0).split(':');
        ui->lineEdit_id->setText(t[t.size() - 1]);
        t = list.at(1).split(':');
        ui->lineEdit_ip->setText(t[t.size() - 1]);
        t = list.at(2).split(':');
        ui->lineEdit_port->setText(t[t.size() - 1]);
        t = list.at(3).split(':');
        ui->lineEdit_protocol->setText(t[t.size() - 1]);
        t = list.at(4).split(':');
        ui->lineEdit_slaveID->setText(t[t.size() - 1]);
        t = list.at(5).split(':');
        ui->lineEdit_gct->setText(t[t.size() - 1]);
        t = list.at(6).split(':');
        ui->lineEdit_describe->setText(t[t.size() - 1]);
    }
}

void Client_Form::OK() {
    QString id = "客户端ID:" + ui->lineEdit_id->text() + ",";
    QString ip = "客户端IP:" + ui->lineEdit_ip->text() + ",";
    QString port = "客户端端口:" + ui->lineEdit_port->text() + ",";
    QString protocol = "客户端协议:" + ui->lineEdit_protocol->text() + ",";
    QString slaveID = "slaveID:" + ui->lineEdit_slaveID->text() + ",";
    QString generalCallTime = "总召间隔时长（单位：秒）:" + ui->lineEdit_gct->text() + ",";
    QString describe = "描述:" + ui->lineEdit_describe->text();
    emit modified_values(id + ip + port + protocol + slaveID + generalCallTime + describe);
    this->close();
}
