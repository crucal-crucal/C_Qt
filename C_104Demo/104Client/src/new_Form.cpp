#include "include/new_Form.h"

#include "ui_new_Form.h"

new_Form* new_Form::self = nullptr;

new_Form::new_Form(QWidget* parent) : QDialog(parent), ui(new Ui::new_Form) {
    ui->setupUi(this);
    this->init();
    connect(ui->btn_ok, &QPushButton::clicked, this, &new_Form::OK);
    connect(ui->btn_cancel, &QPushButton::clicked, this, [&]() { this->close(); });
}

new_Form::~new_Form() { delete ui; }

void new_Form::init() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    ui->lineEdit_client_id->setText("0");
    ui->lineEdit_client_describe->setText("0");
    ui->lineEdit_client_gct->setText("0");
    ui->lineEdit_client_ip->setText("0");
    ui->lineEdit_client_port->setText("0");
    ui->lineEdit_client_protocol->setText("0");
    ui->lineEdit_client_slaveID->setText("0");
    ui->lineEdit_server_dataType->setText("0");
    ui->lineEdit_server_describe->setText("0");
    ui->lineEdit_server_id->setText("0");
    ui->lineEdit_server_ip->setText("0");
    ui->lineEdit_server_port->setText("0");
    ui->lineEdit_server_publicAddr->setText("0");
}

void new_Form::OK() {
    QString serverid = "服务端ID:" + ui->lineEdit_server_id->text() + ",";
    QString serverip = "服务端IP:" + ui->lineEdit_server_ip->text() + ",";
    QString serverport = "服务端端口:" + ui->lineEdit_server_port->text() + ",";
    QString serverdt = "数据类型:" + ui->lineEdit_server_dataType->text() + ",";
    QString serverpb = "公共地址:" + ui->lineEdit_server_publicAddr->text() + ",";
    QString serverdes = "描述:" + ui->lineEdit_server_describe->text();
    QString clientid = "客户端ID:" + ui->lineEdit_client_id->text() + ",";
    QString clientip = "客户端IP:" + ui->lineEdit_client_ip->text() + ",";
    QString clientport = "客户端端口:" + ui->lineEdit_client_port->text() + ",";
    QString clientpro = "客户端协议:" + ui->lineEdit_client_protocol->text() + ",";
    QString clientsalveID = "slaveID:" + ui->lineEdit_client_slaveID->text() + ",";
    QString clientgCT = "总召间隔时长（单位：秒）:" + ui->lineEdit_client_gct->text() + ",";
    QString clientdes = "描述:" + ui->lineEdit_client_describe->text();

    std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> Server, Client;
    QString server = serverid + serverip + serverport + serverdt + serverpb + serverdes;
    QString client = clientid + clientip + clientport + clientpro + clientsalveID + clientgCT + clientdes;
    Server[server] = {QVector<QString>(), QVector<QString>()};
    Client[client] = {QVector<QString>(), QVector<QString>()};
    emit new_Values(Server, Client);
    this->close();
}
