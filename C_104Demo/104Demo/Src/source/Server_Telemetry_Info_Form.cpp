#include "Src/include/Server_Telemetry_Info_Form.h"

#include "Src/include/Client_Infomation.h"
#include "Src/include/mainwindow.h"
#include "ui_Server_Telemetry_Info_Form.h"

Server_Telemetry_Info_Form* Server_Telemetry_Info_Form::self = nullptr;

Server_Telemetry_Info_Form::Server_Telemetry_Info_Form(QWidget* parent)
    : QDialog(parent), ui(new Ui::Server_Telemetry_Info_Form) {
  ui->setupUi(this);
  this->setDefault();
  connect(ui->btn_Save, &QPushButton::clicked, this,
          &Server_Telemetry_Info_Form::Save, Qt::UniqueConnection);

  connect(ui->lineEdit_addr, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });
  connect(ui->lineEdit_coeff, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });
  connect(ui->lineEdit_clientID, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });
  connect(ui->lineEdit_clientTA, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });

  connect(ui->textEdit_server_des, &MyTextEdit::manualTextChanged, this,
          [&]() { emit textChanged(false); });
  ui->btn_Save->setToolTip("Ctrl+Shift+S");

  connect(this, &Server_Telemetry_Info_Form::clientInfo, ui->lineEdit_clientID,
          &CustomLineEdit::clientInfo);
  connect(this, &Server_Telemetry_Info_Form::clientInfo, ui->lineEdit_clientTA,
          &CustomLineEdit::clientInfo);

  connect(Client_Infomation::getInstance(), &Client_Infomation::teleMetry, this,
          [&](tvalue v) {
            ui->lineEdit_clientID->setText(v.first);
            client_id = v.second;
            emit textChanged(false);
            this->updateInfo_to_Client_Infomation();
          });
  connect(Client_Infomation::getInstance(),
          &Client_Infomation::clientTelemetryValue, this, [&](tvalue v) {
            ui->lineEdit_clientTA->setText(v.first);
            addr_id = v.second;
            emit textChanged(false);
          });
}

Server_Telemetry_Info_Form::~Server_Telemetry_Info_Form() { delete ui; }

void Server_Telemetry_Info_Form::init() {
  QFont font("Microsoft YaHei", FONTSIZE);

  ui->lab_addr->setFont(font);
  ui->lab_coeff->setFont(font);
  ui->lab_clientID->setFont(font);
  ui->lab_clientTA->setFont(font);
  ui->lab_describe->setFont(font);

  ui->lab_describe->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  ui->lineEdit_addr->setFont(font);
  ui->lineEdit_coeff->setFont(font);
  ui->lineEdit_clientID->setFont(font);
  ui->lineEdit_clientTA->setFont(font);
  ui->textEdit_server_des->setFont(font);

  ui->lineEdit_clientID->setType(telemetry);
  ui->lineEdit_clientTA->setType(cleint_telemetryID);

  // 设置自动换行
  QTextOption textOption;
  textOption.setWrapMode(QTextOption::WrapAnywhere);
  ui->textEdit_server_des->document()->setDefaultTextOption(textOption);
}

void Server_Telemetry_Info_Form::updateInfo(MAP_CFG_CLIENT client,
                                            MAP_CFG_CLIENT_TELEMETRY telemerty,
                                            CFG_SERVER_TELEMETRY str) {
  std::vector<QString> res, metry;
  for (const auto& [id, c] : client) {
    res.emplace_back(MainWindow::getLocaClientidx(c).first);
  }
  client_id = str.uiClientID;
  addr_id = str.uiClientTelemetryAddr;
  QString s;
  if (static_cast<size_t>(str.uiClientID) < res.size()) {
    s = res[str.uiClientID];
    for (const auto& c : telemerty[str.uiClientID]) {
      metry.emplace_back(
          QString("%1（%2）").arg(c.uiClientTelemetryAddr).arg(c.szDescribe));
    }
  } else {
    s = "此处索引无效，需要重新选择";
  }
  QString s1;
  if (static_cast<size_t>(str.uiClientTelemetryAddr) <= metry.size() &&
      str.uiClientTelemetryAddr) {
    s1 = metry[str.uiClientTelemetryAddr - 1];
  } else {
    s1 = "此处索引无效，需要重新选择";
  }

  ui->lineEdit_addr->setText(QString("%1").arg(str.uiServerTelemetryAddr));
  ui->lineEdit_coeff->setText(QString("%1").arg(str.fCoeff));
  ui->lineEdit_clientID->setText(s);
  ui->lineEdit_clientTA->setText(s1);
  ui->textEdit_server_des->setText(QString::fromUtf8(str.szDescribe));
}

void Server_Telemetry_Info_Form::cleanInfo() const {
  ui->lineEdit_addr->clear();
  ui->lineEdit_clientID->clear();
  ui->lineEdit_clientTA->clear();
  ui->lineEdit_coeff->clear();
  ui->textEdit_server_des->clear();
}

void Server_Telemetry_Info_Form::Save() {
  CFG_SERVER_TELEMETRY cfgServerTelemetry;

  memset(&cfgServerTelemetry, 0, MAX_CFG_SERVER_TELEMETRY);

  cfgServerTelemetry.uiServerTelemetryAddr = ui->lineEdit_addr->text().toUInt();
  cfgServerTelemetry.fCoeff = ui->lineEdit_coeff->text().toFloat();
  cfgServerTelemetry.uiClientID = client_id;
  cfgServerTelemetry.uiClientTelemetryAddr = addr_id;
  qstrncpy(cfgServerTelemetry.szDescribe,
           ui->textEdit_server_des->toPlainText().toUtf8().constData(),
           MAX_CFG_DESCRIBE);

  emit Values(cfgServerTelemetry);
}

void Server_Telemetry_Info_Form::setDefault() {
  ui->lineEdit_addr->setText("0");
  ui->lineEdit_clientID->setText("0");
  ui->lineEdit_clientTA->setText("0");
  ui->lineEdit_coeff->setText("0");
  ui->textEdit_server_des->clear();
}

void Server_Telemetry_Info_Form::clientInfomation(
    MAP_CFG_CLIENT client, MAP_CFG_CLIENT_TELEMETRY client_telemetry) {
  local_client = client;
  local_client_telemetry = client_telemetry;
  this->updateInfo_to_Client_Infomation();
}

void Server_Telemetry_Info_Form::updateInfo_to_Client_Infomation() {
  unsigned int op = local_client.begin()->first;
  tmap t1, t2;
  for (const auto& c : local_client) {
    if (c.second.uiClientID == client_id) {
      op = c.first;
    }
    auto mes = MainWindow::getLocaClientidx(c.second);
    t1[mes] = QString::fromUtf8(c.second.szDescribe);
  }

  for (const auto& c : local_client_telemetry[op]) {
    auto mes = std::make_pair(
        QString("%1（%2）").arg(c.uiClientTelemetryAddr).arg(c.szDescribe),
        c.uiClientTelemetryAddr);
    t2[mes] = QString::fromUtf8(c.szDescribe);
  }

  emit clientInfo(t1, t2);
}
