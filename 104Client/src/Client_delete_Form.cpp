#include "include/Client_delete_Form.h"

#include "include/Client_CheckForm.h"
#include "ui_Client_delete_Form.h"

Client_delete_Form* Client_delete_Form::self = nullptr;

Client_delete_Form::Client_delete_Form(QWidget* parent) : QDialog(parent), ui(new Ui::Client_delete_Form) {
    ui->setupUi(this);
    connect(ui->btn_ok, &QPushButton::clicked, this, &Client_delete_Form::OK);
    connect(ui->btn_cannel, &QPushButton::clicked, this, [=]() { this->close(); });
}

Client_delete_Form::~Client_delete_Form() { delete ui; }

void Client_delete_Form::init() {
    this->setWindowTitle("Client_delete_Form");
    this->resize(Width, Height);
}

void Client_delete_Form::OK() {
    emit del_curMes();
    this->close();
}
