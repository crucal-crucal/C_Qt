#include "Client_Telemetry_Info_Form.h"

#include "mainwindow.h"
#include "ui_Client_Telemetry_Info_Form.h"

Client_Telemetry_Info_Form* Client_Telemetry_Info_Form::self = nullptr;

Client_Telemetry_Info_Form::Client_Telemetry_Info_Form(QWidget* parent) :
    QDialog(parent), ui(new Ui::Client_Telemetry_Info_Form) {
    ui->setupUi(this);
}

Client_Telemetry_Info_Form::~Client_Telemetry_Info_Form() { delete ui; }

void Client_Telemetry_Info_Form::init() {
    QFont font("Microsoft YaHei", FONTSIZE);
    ui->lab_addr->setFont(font);
    ui->lab_inputFlag->setFont(font);
    ui->lab_dataType->setFont(font);
    ui->lab_describe->setFont(font);
    ui->label_telemetry->setFont(font);

    ui->lineEdit_addr->setFont(font);
    ui->lineEdit_inputFlag->setFont(font);
    ui->lineEdit_dataType->setFont(font);
    ui->lineEdit_describe->setFont(font);
}

void Client_Telemetry_Info_Form::updateInfo(QString str) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << "curText:\t" << str;
#endif
    QStringList list = str.split(',');
    if (list.size() != client_telemetry_Size) {
        return qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');
    QString addr = t[t.size() - 1];
    ui->lineEdit_addr->setText(addr);

    t = list.at(1).split(':');
    QString inputFlag = t[t.size() - 1];
    ui->lineEdit_inputFlag->setText(inputFlag);

    t = list.at(2).split(':');
    QString dataType = t[t.size() - 1];
    ui->lineEdit_dataType->setText(dataType);

    t = list.at(3).split(':');
    QString describe = t[t.size() - 1];
    ui->lineEdit_describe->setText(describe);
}
