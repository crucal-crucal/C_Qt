#include "Server_delete_Form.h"

#include "Client_CheckForm.h"
#include "ui_Server_delete_Form.h"

Server_delete_Form* Server_delete_Form::self = nullptr;

Server_delete_Form::Server_delete_Form(QWidget* parent) : QDialog(parent), ui(new Ui::Server_delete_Form) {
    ui->setupUi(this);
    connect(ui->btn_ok, &QPushButton::clicked, this, &Server_delete_Form::OK);
    connect(ui->btn_cannel, &QPushButton::clicked, this, [=]() { this->close(); });
}

Server_delete_Form::~Server_delete_Form() { delete ui; }

void Server_delete_Form::init() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    this->setWindowTitle("Server_delete_Form");
    this->resize(Width, Height);
}

void Server_delete_Form::OK() {
    emit del_curMes();
    this->close();
}
