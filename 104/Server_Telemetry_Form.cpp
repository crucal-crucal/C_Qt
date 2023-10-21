#include "Server_Telemetry_Form.h"

#include "ui_Server_Telemetry_Form.h"

Server_Telemetry_Form* Server_Telemetry_Form::self = nullptr;

Server_Telemetry_Form::Server_Telemetry_Form(QWidget* parent) : QDialog(parent), ui(new Ui::Server_Telemetry_Form) {
    ui->setupUi(this);
    this->init();
    connect(ui->btn_ok, &QPushButton::clicked, this, &Server_Telemetry_Form::OK);
    connect(ui->btn_cancel, &QPushButton::clicked, this, [=]() {
        emit cannel();
        this->close();
    });
}

Server_Telemetry_Form::~Server_Telemetry_Form() { delete ui; }

void Server_Telemetry_Form::init() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    this->setWindowTitle("Server_Telemetry_Form");
    ui->lineEdit_addr->setText("0");
    ui->lineEdit_coeff->setText("0");
    ui->lineEdit_clientID->setText("0");
    ui->lineEdit_clientTA->setText("0");
    ui->lineEdit_describe->setText("0");
}

void Server_Telemetry_Form::modifyServer(QString mes) {
    QStringList list = mes.split(',');
    if (list.size() == 5) {
        QStringList t = list.at(0).split(':');
        ui->lineEdit_addr->setText(t[t.size() - 1]);
        t = list.at(1).split(':');
        ui->lineEdit_coeff->setText(t[t.size() - 1]);
        t = list.at(2).split(':');
        ui->lineEdit_clientID->setText(t[t.size() - 1]);
        t = list.at(3).split(':');
        ui->lineEdit_clientTA->setText(t[t.size() - 1]);
        t = list.at(4).split(':');
        ui->lineEdit_describe->setText(t[t.size() - 1]);
    }
}

void Server_Telemetry_Form::OK() {
    QString addr = "遥测地址:" + ui->lineEdit_addr->text() + ",";
    QString coeff = "系数:" + ui->lineEdit_coeff->text() + ",";
    QString clientID = "对应客户端ID:" + ui->lineEdit_clientID->text() + ",";
    QString clientTelemetryAddr = "对应客户端遥测ID:" + ui->lineEdit_clientTA->text() + ",";
    QString describe = "描述:" + ui->lineEdit_describe->text();
    //    qDebug() << addr + coeff + clientID + clientTelemetryAddr + describe;
    qDebug() << "emit modified_values";
    emit modified_values(addr + coeff + clientID + clientTelemetryAddr + describe);
    this->close();
}
