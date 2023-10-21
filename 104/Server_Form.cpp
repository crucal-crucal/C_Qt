#include "Server_Form.h"

#include "ui_Server_Form.h"

Server_Form* Server_Form::self = nullptr;

Server_Form::Server_Form(QWidget* parent) : QDialog(parent), ui(new Ui::Server_Form) {
    ui->setupUi(this);
    this->init();
    connect(ui->btn_ok, &QPushButton::clicked, this, &Server_Form::OK);
    connect(ui->btn_cancel, &QPushButton::clicked, this, [=]() {
        emit cannel();
        this->close();
    });
}

Server_Form::~Server_Form() { delete ui; }

void Server_Form::init() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    this->setWindowTitle("Server_Form");
    ui->lineEdit_id->setText("0");
    ui->lineEdit_ip->setText("0");
    ui->lineEdit_port->setText("0");
    ui->lineEdit_dataType->setText("0");
    ui->lineEdit_publicAddr->setText("0");
    ui->lineEdit_describe->setText("0");
}

void Server_Form::modifyServer(QString mes) {
    QStringList list = mes.split(',');
    if (list.size() == 6) {
        QStringList t = list.at(0).split(':');
        ui->lineEdit_id->setText(t[t.size() - 1]);
        t = list.at(1).split(':');
        ui->lineEdit_ip->setText(t[t.size() - 1]);
        t = list.at(2).split(':');
        ui->lineEdit_port->setText(t[t.size() - 1]);
        t = list.at(3).split(':');
        ui->lineEdit_dataType->setText(t[t.size() - 1]);
        t = list.at(4).split(':');
        ui->lineEdit_publicAddr->setText(t[t.size() - 1]);
        t = list.at(5).split(':');
        ui->lineEdit_describe->setText(t[t.size() - 1]);
    }
}

void Server_Form::OK() {
    QString id = "服务端ID:" + ui->lineEdit_id->text() + ",";
    QString ip = "服务端IP:" + ui->lineEdit_ip->text() + ",";
    QString port = "服务端端口:" + ui->lineEdit_port->text() + ",";
    QString dataType = "数据类型:" + ui->lineEdit_dataType->text() + ",";
    QString publicAddr = "公共地址:" + ui->lineEdit_publicAddr->text() + ",";
    QString describe = "描述:" + ui->lineEdit_describe->text();
    emit modified_values(id + ip + port + dataType + publicAddr + describe);
    this->close();
}
