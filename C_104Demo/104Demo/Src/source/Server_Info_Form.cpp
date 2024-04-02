#include "Src/include/Server_Info_Form.h"

#include "Src/include/mainwindow.h"
#include "ui_Server_Info_Form.h"
Server_Info_Form* Server_Info_Form::self = nullptr;

Server_Info_Form::Server_Info_Form(QWidget* parent)
    : QDialog(parent), ui(new Ui::Server_Info_Form) {
  ui->setupUi(this);
  this->setDefault();

  connect(ui->btn_Save, &QPushButton::clicked, this, &Server_Info_Form::Save,
          Qt::UniqueConnection);

  connect(ui->lineEdit_ip, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });
  connect(ui->lineEdit_port, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });
  connect(ui->lineEdit_publicAddr, &QLineEdit::textEdited, this,
          [&]() { emit textChanged(false); });
  connect(ui->textEdit_server_des, &MyTextEdit::manualTextChanged, this,
          [&]() { emit textChanged(false); });
  // currentIndexChanged 有两个版本
  // 需使用 QOverload<int>::of(&QComboBox::currentIndexChanged)明确指定带有 int
  // 参数的版本
  connect(ui->comboBox_dataType,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [&](int idx) {
            if (idx != local.usDataType) {
              emit textChanged(false);
            }
          });
  ui->btn_Save->setToolTip("Ctrl+Shift+S");
}

Server_Info_Form::~Server_Info_Form() { delete ui; }

void Server_Info_Form::init() {
  QFont font("Microsoft YaHei", FONTSIZE);

  ui->lab_describe->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  ui->lab_ip->setFont(font);
  ui->lab_port->setFont(font);
  ui->lab_dataType->setFont(font);
  ui->lab_publicAddr->setFont(font);
  ui->lab_describe->setFont(font);

  ui->lineEdit_ip->setFont(font);
  ui->lineEdit_port->setFont(font);
  ui->comboBox_dataType->setFont(font);
  ui->lineEdit_publicAddr->setFont(font);
  ui->textEdit_server_des->setFont(font);

  ui->comboBox_dataType->addItem("无符号8位整型");
  ui->comboBox_dataType->addItem("有符号8位整型");
  ui->comboBox_dataType->addItem("无符号16位网络字节序整型");
  ui->comboBox_dataType->addItem("有符号16位网络字节序整型");
  ui->comboBox_dataType->addItem("无符号16位主机字节序整型");
  ui->comboBox_dataType->addItem("有符号16位主机字节序整型");
  ui->comboBox_dataType->addItem("无符号32位网络字节序整型");
  ui->comboBox_dataType->addItem("有符号32位网络字节序整型");
  ui->comboBox_dataType->addItem("无符号32位主机字节序整型");
  ui->comboBox_dataType->addItem("有符号32位主机字节序整型");
  ui->comboBox_dataType->addItem("浮点型网络字节序");
  ui->comboBox_dataType->addItem("浮点型主机字节序");
  ui->comboBox_dataType->addItem("双精度浮点型网络字节序");
  ui->comboBox_dataType->addItem("双精度浮点型主机字节序");

  // 设置自动换行
  QTextOption textOption;
  textOption.setWrapMode(QTextOption::WrapAnywhere);
  ui->textEdit_server_des->document()->setDefaultTextOption(textOption);
}

void Server_Info_Form::updateInfo(CFG_SERVER str) {
  local = str;

  ui->lineEdit_ip->setText(str.szIP);
  ui->lineEdit_port->setText(QString("%1").arg(str.usPort));
  ui->comboBox_dataType->setCurrentIndex(static_cast<int>(str.usDataType));
  ui->lineEdit_publicAddr->setText(QString("%1").arg(str.usPublicAddr));
  ui->textEdit_server_des->setText(QString::fromUtf8(str.szDescribe));
}

void Server_Info_Form::cleanInfo() const {
  ui->lineEdit_ip->clear();
  ui->lineEdit_port->clear();
  ui->lineEdit_publicAddr->clear();
  ui->textEdit_server_des->clear();
}

void Server_Info_Form::Save() {
  CFG_SERVER cfgServer;

  memset(&cfgServer, 0, MAX_CFG_SERVER);

  cfgServer.uiServerID = local.uiServerID;

  qstrncpy(cfgServer.szIP, ui->lineEdit_ip->text().toUtf8().data(), 16);
  cfgServer.usPort = atoi(ui->lineEdit_port->text().toUtf8().data());
  cfgServer.usDataType = ui->comboBox_dataType->currentIndex();
  cfgServer.usPublicAddr =
      atoi(ui->lineEdit_publicAddr->text().toUtf8().constData());
  qstrncpy(cfgServer.szDescribe,
           ui->textEdit_server_des->toPlainText().toUtf8().constData(),
           MAX_CFG_DESCRIBE);

  local = cfgServer;
  emit Values(cfgServer);
}

void Server_Info_Form::setDefault() {
  ui->lineEdit_ip->setText("0");
  ui->lineEdit_port->setText("0");
  ui->comboBox_dataType->setCurrentIndex(0);
  ui->lineEdit_publicAddr->setText("0");
  ui->textEdit_server_des->clear();
}
