#include "Server_CheckForm.h"

#include "Client_CheckForm.h"
#include "Server_Telemetry_Form.h"
#include "Server_Telesigna_Form.h"
#include "ui_Server_CheckForm.h"

Server_CheckForm* Server_CheckForm::self = nullptr;

Server_CheckForm::Server_CheckForm(QWidget* parent) : QDialog(parent), ui(new Ui::Server_CheckForm) {
    ui->setupUi(this);
    this->init();
    connect(ui->btn_telemetryList, &QPushButton::clicked, this, [&]() {
        Server_Telemetry_Form::getInstance(this)->exec();
        this->close();
    });
    connect(ui->btn_telesignaList, &QPushButton::clicked, this, [&]() {
        Server_Telesigna_Form::getInstance(this)->exec();
        this->close();
    });
}

Server_CheckForm::~Server_CheckForm() { delete ui; }

void Server_CheckForm::init() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    this->setWindowTitle("Server_CheckForm");
    this->resize(Width, Height);
}
