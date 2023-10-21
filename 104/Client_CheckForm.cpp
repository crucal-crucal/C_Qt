#include "Client_CheckForm.h"

#include "Client_Telemetry_Form.h"
#include "Client_Telesigna_Form.h"
#include "ui_Client_CheckForm.h"

Client_CheckForm* Client_CheckForm::self = nullptr;

Client_CheckForm::Client_CheckForm(QWidget* parent) : QDialog(parent), ui(new Ui::Client_CheckForm) {
    ui->setupUi(this);
    connect(ui->btn_telemetryList, &QPushButton::clicked, this, [&]() {
        this->close();
        Client_Telemetry_Form::getInstance(this)->exec();
    });
    connect(ui->btn_telesignaList, &QPushButton::clicked, this, [&]() {
        this->close();
        Client_Telesigna_Form::getInstance(this)->exec();
    });
}

Client_CheckForm::~Client_CheckForm() { delete ui; }

void Client_CheckForm::init() {
    this->setWindowTitle("Client_CheckForm");
    this->resize(Width, Height);
}
