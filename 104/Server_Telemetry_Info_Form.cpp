#include "Server_Telemetry_Info_Form.h"

#include "mainwindow.h"
#include "ui_Server_Telemetry_Info_Form.h"

Server_Telemetry_Info_Form* Server_Telemetry_Info_Form::self = nullptr;

Server_Telemetry_Info_Form::Server_Telemetry_Info_Form(QWidget* parent) :
    QDialog(parent), ui(new Ui::Server_Telemetry_Info_Form) {
    ui->setupUi(this);
}

Server_Telemetry_Info_Form::~Server_Telemetry_Info_Form() { delete ui; }

void Server_Telemetry_Info_Form::init() {
    QFont font("Microsoft YaHei", FONTSIZE);
    ui->label->setFont(font);

    ui->lab_addr->setFont(font);
    ui->lab_coeff->setFont(font);
    ui->lab_clientID->setFont(font);
    ui->lab_clientTA->setFont(font);
    ui->lab_describe->setFont(font);

    ui->lineEdit_addr->setFont(font);
    ui->lineEdit_coeff->setFont(font);
    ui->lineEdit_clientID->setFont(font);
    ui->lineEdit_clientTA->setFont(font);
    ui->lineEdit_describe->setFont(font);
}

void Server_Telemetry_Info_Form::updateInfo(QString str) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << "curText:\t" << str;
#endif
    QStringList list = str.split(',');
    if (list.size() != server_telemetry_Size) {
        return qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');
    QString addr = t[t.size() - 1];
    ui->lineEdit_addr->setText(addr);

    t = list.at(1).split(':');
    QString coeff = t[t.size() - 1];
    ui->lineEdit_coeff->setText(coeff);

    t = list.at(2).split(':');
    QString clientID = t[t.size() - 1];
    ui->lineEdit_clientID->setText(clientID);

    t = list.at(3).split(':');
    QString clientTA = t[t.size() - 1];
    ui->lineEdit_clientTA->setText(clientTA);

    t = list.at(4).split(':');
    QString describe = t[t.size() - 1];
    ui->lineEdit_describe->setText(describe);
}
