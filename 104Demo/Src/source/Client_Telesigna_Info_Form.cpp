#include "Src/include/Client_Telesigna_Info_Form.h"

#include "Src/include/mainwindow.h"
#include "ui_Client_Telesigna_Info_Form.h"

Client_Telesigna_Info_Form* Client_Telesigna_Info_Form::self = nullptr;

Client_Telesigna_Info_Form::Client_Telesigna_Info_Form(QWidget* parent)
    : QDialog(parent), ui(new Ui::Client_Telesigna_Info_Form) {
  ui->setupUi(this);
  this->setDefault();
  connect(ui->btn_Save, &QPushButton::clicked, this,
          &Client_Telesigna_Info_Form::Save, Qt::UniqueConnection);
  connect(ui->lineEdit_addr, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });
  connect(ui->textEdit_client_des, &MyTextEdit::manualTextChanged, this,
          [&]() { emit textChanged(false); });
  // currentIndexChanged 有两个版本
  // 需使用 QOverload<int>::of(&QComboBox::currentIndexChanged)明确指定带有 int
  // 参数的版本
  connect(ui->comboBox_inputFlag,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [&](int idx) {
            if (idx != static_cast<int>(local.uiInputFlag)) {
              emit textChanged(false);
            }
          });
  ui->btn_Save->setToolTip("Ctrl+Shift+S");
}

Client_Telesigna_Info_Form::~Client_Telesigna_Info_Form() { delete ui; }

void Client_Telesigna_Info_Form::init() {
  QFont font("Microsoft YaHei", FONTSIZE);
  ui->lab_addr->setFont(font);
  ui->lab_inputFlag->setFont(font);
  ui->lab_describe->setFont(font);
  ui->lab_describe->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  ui->lineEdit_addr->setFont(font);
  ui->comboBox_inputFlag->setFont(font);
  ui->textEdit_client_des->setFont(font);

  ui->comboBox_inputFlag->addItem("COIL_STATUS");
  ui->comboBox_inputFlag->addItem("INPUT_STATUS");

  // 设置自动换行
  QTextOption textOption;
  textOption.setWrapMode(QTextOption::WrapAnywhere);
  ui->textEdit_client_des->document()->setDefaultTextOption(textOption);
}

void Client_Telesigna_Info_Form::updateInfo(CFG_CLIENT_TELESIGNA str) {
  local = str;
  ui->lineEdit_addr->setText(QString("%1").arg(str.uiClientTelesignaAddr));
  ui->comboBox_inputFlag->setCurrentIndex(static_cast<int>(str.uiInputFlag) %
                                          2);
  ui->textEdit_client_des->setText(QString::fromUtf8(str.szDescribe));
}

void Client_Telesigna_Info_Form::cleanInfo() const {
  ui->lineEdit_addr->clear();
  ui->textEdit_client_des->clear();
}

void Client_Telesigna_Info_Form::Save() {
  CFG_CLIENT_TELESIGNA cfgClientTelesigna;

  memset(&cfgClientTelesigna, 0, MAX_CFG_CLIENT_TELESIGNA);

  cfgClientTelesigna.uiClientTelesignaAddr = ui->lineEdit_addr->text().toUInt();
  cfgClientTelesigna.uiInputFlag = ui->comboBox_inputFlag->currentIndex();
  qstrncpy(cfgClientTelesigna.szDescribe,
           ui->textEdit_client_des->toPlainText().toUtf8().constData(),
           MAX_CFG_DESCRIBE);

  local = cfgClientTelesigna;
  emit Values(cfgClientTelesigna);
}

void Client_Telesigna_Info_Form::setDefault() {
  ui->lineEdit_addr->setText("0");
  ui->comboBox_inputFlag->setCurrentIndex(0);
  ui->textEdit_client_des->clear();
}
