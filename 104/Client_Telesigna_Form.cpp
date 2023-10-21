#include "Client_Telesigna_Form.h"

#include "ui_Client_Telesigna_Form.h"

Client_Telesigna_Form* Client_Telesigna_Form::self = nullptr;

Client_Telesigna_Form::Client_Telesigna_Form(QWidget* parent) : QDialog(parent), ui(new Ui::Client_Telesigna_Form) {
    ui->setupUi(this);
    this->init();
    connect(ui->btn_ok, &QPushButton::clicked, this, &Client_Telesigna_Form::OK);
    connect(ui->btn_cancel, &QPushButton::clicked, this, [=]() {
        emit cannel();
        this->close();
    });
}

Client_Telesigna_Form::~Client_Telesigna_Form() { delete ui; }

void Client_Telesigna_Form::init() {
    this->setWindowTitle("Client_Telesigna_Form");
    ui->lineEdit_addr->setText("0");
    ui->lineEdit_inputFlag->setText("0");
    ui->lineEdit_describe->setText("0");
}

void Client_Telesigna_Form::modifyClient(QString mes) {
    QStringList list = mes.split(',');
    if (list.size() == 3) {
        QStringList t = list.at(0).split(':');
        ui->lineEdit_addr->setText(t[t.size() - 1]);
        t = list.at(1).split(':');
        ui->lineEdit_inputFlag->setText(t[t.size() - 1]);
        t = list.at(2).split(':');
        ui->lineEdit_describe->setText(t[t.size() - 1]);
    }
}

void Client_Telesigna_Form::OK() {
    QString addr = "遥信地址:" + ui->lineEdit_addr->text() + ",";
    QString inputFlag = "inputFlag:" + ui->lineEdit_inputFlag->text() + ",";
    QString describe = "描述:" + ui->lineEdit_describe->text();
    emit modified_values(addr + inputFlag + describe);
    this->close();
}
