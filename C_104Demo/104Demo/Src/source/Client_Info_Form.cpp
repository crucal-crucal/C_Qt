#include "Src/include/Client_Info_Form.h"

#include "Src/include/mainwindow.h"
#include "ui_Client_Info_Form.h"

Client_Info_Form* Client_Info_Form::self = nullptr;

Client_Info_Form::Client_Info_Form(QWidget* parent)
    : QDialog(parent), ui(new Ui::Client_Info_Form) {
  ui->setupUi(this);
  this->setDefault();
  connect(ui->comboBox_usProtocol, &QComboBox::currentTextChanged, this,
          [&](QString s) {
            if (s == "Modbus Serial Port") {
              this->setDefault();
              this->showWidgets(false, true);
            } else if (s == "Modbus TCP/IP") {
              this->setDefault();
              this->showWidgets(true, true);
            } else {
              this->showWidgets(true, false);
            }
          });

  connect(ui->btn_Save, &QPushButton::clicked, this, &Client_Info_Form::Save,
          Qt::UniqueConnection);
  connect(ui->lineEdit_client_ip, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });
  connect(ui->lineEdit_client_port, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });
  connect(ui->lineEdit_client_slaveID, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });
  connect(ui->lineEdit_client_gct, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });
  connect(ui->textEdit_client_des, &MyTextEdit::manualTextChanged, this,
          [&]() { emit textChanged(false); });
  // currentIndexChanged 有两个版本
  // 需使用 QOverload<int>::of(&QComboBox::currentIndexChanged)明确指定带有 int
  // 参数的版本
  connect(ui->comboBox_usProtocol,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [&](int idx) {
            if (idx != local.usProtocol) {
              emit textChanged(false);
            }
          });
  connect(ui->comboBox_szSerialDevice, &QComboBox::currentTextChanged, this,
          [&](const QString& text) {
            if (text != QString::fromUtf8(local.szSerialDevice)) {
              emit textChanged(false);
            }
          });
  connect(ui->comboBox_iBaud,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [&](int idx) {
            if (idx != static_cast<int>(local.iBaud)) {
              emit textChanged(false);
            }
          });
  connect(ui->comboBox_cParity,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [&](int idx) {
            if (idx != static_cast<int>(local.cParity)) {
              emit textChanged(false);
            }
          });
  connect(ui->comboBox_iDataBit,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [&](int idx) {
            if (idx != static_cast<int>(local.iDataBit)) {
              emit textChanged(false);
            }
          });
  connect(ui->comboBox_iStopBit,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [&](int idx) {
            if (idx != static_cast<int>(local.iStopBit)) {
              emit textChanged(false);
            }
          });

  ui->btn_Save->setToolTip("Ctrl+Shift+S");
}

Client_Info_Form::~Client_Info_Form() { delete ui; }

void Client_Info_Form::init() {
  QFont font("Microsoft YaHei", FONTSIZE);

  ui->client_des->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  ui->client_ip->setFont(font);
  ui->client_port->setFont(font);
  ui->client_pro->setFont(font);
  ui->client_szSerialDevice->setFont(font);
  ui->client_iBaud->setFont(font);
  ui->client_cParity->setFont(font);
  ui->client_iDataBit->setFont(font);
  ui->client_iStopBit->setFont(font);
  ui->client_slaveID->setFont(font);
  ui->client_gct->setFont(font);
  ui->client_des->setFont(font);

  ui->lineEdit_client_ip->setFont(font);
  ui->lineEdit_client_port->setFont(font);
  ui->comboBox_usProtocol->setFont(font);
  ui->comboBox_szSerialDevice->setFont(font);
  ui->comboBox_iBaud->setFont(font);
  ui->comboBox_cParity->setFont(font);
  ui->comboBox_iDataBit->setFont(font);
  ui->comboBox_iStopBit->setFont(font);
  ui->lineEdit_client_slaveID->setFont(font);
  ui->lineEdit_client_gct->setFont(font);
  ui->textEdit_client_des->setFont(font);

  ui->comboBox_usProtocol->addItem("IEC 104");
  ui->comboBox_usProtocol->addItem("Modbus TCP/IP");
  ui->comboBox_usProtocol->addItem("Modbus Serial Port");

  for (int i = 1; i <= 20; i++) {
    QString s = QString("COM%1").arg(i);
    ui->comboBox_szSerialDevice->addItem(s);
  }

  std::vector<int> a = {300,   600,   1200,  2400,  4800,  9600,
                        14400, 19200, 38400, 56000, 57600, 115200};
  for (int i = 0; i < (int)a.size(); i++) {
    QString s = QString("%1 Baud").arg(a[i]);
    ui->comboBox_iBaud->addItem(s);
  }

  ui->comboBox_cParity->addItem("7 Data bits");
  ui->comboBox_cParity->addItem("8 Data bits");

  ui->comboBox_iDataBit->addItem("None Parity");
  ui->comboBox_iDataBit->addItem("Odd Parity");
  ui->comboBox_iDataBit->addItem("Even Parity");

  ui->comboBox_iStopBit->addItem("1 Stop Bit");
  ui->comboBox_iStopBit->addItem("2 Stop Bits");

  // 设置自动换行
  QTextOption textOption;
  textOption.setWrapMode(QTextOption::WrapAnywhere);
  ui->textEdit_client_des->document()->setDefaultTextOption(textOption);
}

void Client_Info_Form::updateInfo(CFG_CLIENT str) {
  local = str;
  ui->lineEdit_client_ip->setText(QString::fromUtf8(str.szIP));
  ui->lineEdit_client_port->setText(QString("%1").arg(str.usPort));
  ui->comboBox_usProtocol->setCurrentIndex(static_cast<int>(str.usProtocol));

  if (strcmp(str.szSerialDevice, "") == 0) {
    ui->comboBox_szSerialDevice->setCurrentIndex(-1);
  } else {
    ui->comboBox_szSerialDevice->setCurrentText(
        QString::fromUtf8(str.szSerialDevice));
  }

  ui->comboBox_iBaud->setCurrentIndex(static_cast<int>(str.iBaud));
  ui->comboBox_cParity->setCurrentIndex(static_cast<int>(str.cParity));
  ui->comboBox_iDataBit->setCurrentIndex(static_cast<int>(str.iDataBit));
  ui->comboBox_iStopBit->setCurrentIndex(static_cast<int>(str.iStopBit));
  ui->lineEdit_client_slaveID->setText(QString("%1").arg(str.usSlaveID));
  ui->lineEdit_client_gct->setText(QString("%1").arg(str.usGeneralCallTime));
  ui->textEdit_client_des->setText(QString::fromUtf8(str.szDescribe));
}

void Client_Info_Form::cleanInfo() const {
  ui->lineEdit_client_gct->setText("10");
  ui->textEdit_client_des->clear();
}

void Client_Info_Form::Save() {
  MainWindow::isSave = true;
  CFG_CLIENT cfgClient;

  memset(&cfgClient, 0, MAX_CFG_CLIENT);

  cfgClient.uiClientID = local.uiClientID;

  cfgClient.usProtocol = ui->comboBox_usProtocol->currentIndex() == -1
                             ? local.usProtocol
                             : ui->comboBox_usProtocol->currentIndex();
  qstrncpy(cfgClient.szIP, ui->lineEdit_client_ip->text().toUtf8().constData(),
           16);
  cfgClient.usPort = ui->lineEdit_client_port->text().toUInt();
  qstrncpy(cfgClient.szSerialDevice,
           ui->comboBox_szSerialDevice->currentText().toUtf8().constData(), 16);
  cfgClient.iBaud = ui->comboBox_iBaud->currentIndex() == -1
                        ? local.iBaud
                        : ui->comboBox_iBaud->currentIndex();
  cfgClient.cParity = ui->comboBox_cParity->currentIndex() == -1
                          ? local.cParity
                          : ui->comboBox_cParity->currentIndex();
  cfgClient.iDataBit = ui->comboBox_iDataBit->currentIndex() == -1
                           ? local.iDataBit
                           : ui->comboBox_iDataBit->currentIndex();
  cfgClient.iStopBit = ui->comboBox_iStopBit->currentIndex() == -1
                           ? local.iStopBit
                           : ui->comboBox_iStopBit->currentIndex();
  cfgClient.usSlaveID = ui->lineEdit_client_slaveID->text().toUInt();
  cfgClient.usGeneralCallTime = ui->lineEdit_client_gct->text().toUInt();
  qstrncpy(cfgClient.szDescribe,
           ui->textEdit_client_des->toPlainText().toUtf8().constData(),
           MAX_CFG_DESCRIBE);

  local = cfgClient;
  emit Values(cfgClient);
}

void Client_Info_Form::setDefault() {
  ui->comboBox_iBaud->setCurrentIndex(11);
  ui->comboBox_cParity->setCurrentIndex(1);
  ui->comboBox_iDataBit->setCurrentIndex(2);
  ui->lineEdit_client_gct->setText("10");
}

void Client_Info_Form::showWidgets(bool tcpIpVisible, bool seriaPortVisible) {
  ui->client_ip->setVisible(tcpIpVisible);
  ui->client_port->setVisible(tcpIpVisible);
  ui->client_szSerialDevice->setVisible(seriaPortVisible);
  ui->client_iBaud->setVisible(seriaPortVisible);
  ui->client_cParity->setVisible(seriaPortVisible);
  ui->client_iDataBit->setVisible(seriaPortVisible);
  ui->client_iStopBit->setVisible(seriaPortVisible);

  ui->lineEdit_client_ip->setVisible(tcpIpVisible);
  ui->lineEdit_client_port->setVisible(tcpIpVisible);
  ui->comboBox_szSerialDevice->setVisible(seriaPortVisible);
  ui->comboBox_iBaud->setVisible(seriaPortVisible);
  ui->comboBox_cParity->setVisible(seriaPortVisible);
  ui->comboBox_iDataBit->setVisible(seriaPortVisible);
  ui->comboBox_iStopBit->setVisible(seriaPortVisible);
}
