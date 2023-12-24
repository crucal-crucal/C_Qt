#include "Src/include/mainwindow.h"

#include "Src/include/Client_Info_Form.h"
#include "Src/include/Client_Telemetry_Info_Form.h"
#include "Src/include/Client_Telesigna_Info_Form.h"
#include "Src/include/Server_Info_Form.h"
#include "Src/include/Server_Telemetry_Info_Form.h"
#include "Src/include/Server_Telesigna_Info_Form.h"
#include "Src/include/config.h"
#include "ui_mainwindow.h"

bool MainWindow::isSave = true;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // 右侧 GroupBox
  Property = new QGroupBox(ui->stackedWidget);
  // GroupBox 子界面
  Property_form = new QStackedWidget(Property);

  // 控制菜单
  QMenuBar* menuBar = new QMenuBar(this);
  setMenuWidget(menuBar);
  QMenu* fileMenu = menuBar->addMenu("文件");
  fileMenu->addAction(ui->action_new);
  fileMenu->addAction(ui->action_open);
  fileMenu->addAction(ui->action_save);
  fileMenu->addAction(ui->action_saveAs);
  QMenu* aboutMenu = menuBar->addMenu("关于");
  aboutMenu->addAction(ui->action_about);
  QMenu* helpMenu = menuBar->addMenu("帮助");
  helpMenu->addAction(ui->action_help);

  this->setWindowIcon(QIcon(":/image/xml.ico"));
  this->init(FONTSIZE);
  this->setWindowTitle("IEC104规约转换器配置工具 v1.0");
  this->resize(1000, 700);

  // 保存
  save_xml = std::make_unique<SaveXml>();
  connect(this, &MainWindow::save_as_in_xml, save_xml.get(), &SaveXml::SaveFile,
          Qt::UniqueConnection);

  // 读取
  config = std::make_unique<CConfig>();
  connect(config.get(), &CConfig::cfg_client_mes, this,
          &MainWindow::updateClient, Qt::UniqueConnection);
  connect(config.get(), &CConfig::cfg_server_mes, this,
          &MainWindow::updateServer, Qt::UniqueConnection);

  // TreeView model
  cmodel = std::make_unique<QStandardItemModel>(this);
  smodel = std::make_unique<QStandardItemModel>(this);
  ui->Server->setModel(smodel.get());
  ui->Client->setModel(cmodel.get());

#ifdef NDEBUG
  qDebug() << "open file";
  //  this->clearLoca();

  QString filepath =
      "E:\\QT\\Work\\build-104Demo-Desktop_Qt_5_15_2_MinGW_64_bit-"
      "Debug\\debug\\new_config.xml";
  if (!config.get()->LoadFile(filepath.toUtf8().constData())) {
    qDebug() << "LoadFile error!";
  }
  fpath = filepath;
  this->updateWindowTitle();
#endif

  // 按钮关联
  connect(ui->action_open, &QAction::triggered, this, &MainWindow::act_open,
          Qt::UniqueConnection);
  connect(ui->action_new, &QAction::triggered, this, &MainWindow::new_file,
          Qt::UniqueConnection);
  connect(ui->action_save, &QAction::triggered, this, &MainWindow::save_file,
          Qt::UniqueConnection);
  connect(ui->action_about, &QAction::triggered, this, &MainWindow::btn_about,
          Qt::UniqueConnection);
  connect(ui->action_saveAs, &QAction::triggered, this, &MainWindow::save_As,
          Qt::UniqueConnection);
  connect(ui->action_help, &QAction::triggered, this, &MainWindow::help,
          Qt::UniqueConnection);

  // 标签页切换
  connect(ui->tabWidget, &QTabWidget::currentChanged, this,
          &MainWindow::onTabChanged, Qt::UniqueConnection);

  // Server
  this->serverConnect();

  // Client
  this->clientConnect();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::serverConnect() {
  // 点击响应
  connect(ui->Server->selectionModel(), &QItemSelectionModel::currentChanged,
          this, &MainWindow::showinServer_Property, Qt::UniqueConnection);
  // 不可编辑
  ui->Server->setEditTriggers(QAbstractItemView::NoEditTriggers);
  // 启用自定义上下文菜单
  ui->Server->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->Server, &QTreeView::customContextMenuRequested, this,
          &MainWindow::TreeMenu_Server, Qt::UniqueConnection);

  // 传递给右侧子界面信息
  connect(this, &MainWindow::Server_Info_mes, Server_Info_Form::getInstance(),
          &Server_Info_Form::updateInfo, Qt::UniqueConnection);
  connect(this, &MainWindow::Server_Telemetry_Info_mes,
          Server_Telemetry_Info_Form::getInstance(),
          &Server_Telemetry_Info_Form::updateInfo, Qt::UniqueConnection);
  connect(this, &MainWindow::Server_Telesigna_Info_mes,
          Server_Telesigna_Info_Form::getInstance(),
          &Server_Telesigna_Info_Form::updateInfo, Qt::UniqueConnection);

  // 更新底部 statusbar
  connect(Server_Info_Form::getInstance(), &Server_Info_Form::textChanged, this,
          &MainWindow::updateSave, Qt::UniqueConnection);
  connect(Server_Telemetry_Info_Form::getInstance(),
          &Server_Telemetry_Info_Form::textChanged, this,
          &MainWindow::updateSave, Qt::UniqueConnection);
  connect(Server_Telesigna_Info_Form::getInstance(),
          &Server_Telesigna_Info_Form::textChanged, this,
          &MainWindow::updateSave, Qt::UniqueConnection);

  // 子界面保存传递
  connect(Server_Info_Form::getInstance(), &Server_Info_Form::Values, this,
          [&](CFG_SERVER mes) {
            mod_server = true;
            this->modified_server(mes);
          });
  connect(Server_Telemetry_Info_Form::getInstance(this),
          &Server_Telemetry_Info_Form::Values, this,
          &MainWindow::modified_server_Telemetry, Qt::UniqueConnection);
  connect(Server_Telesigna_Info_Form::getInstance(this),
          &Server_Telesigna_Info_Form::Values, this,
          &MainWindow::modified_server_Telesigna, Qt::UniqueConnection);

  // 传递给子界面客户端信息
  connect(this, &MainWindow::client_telemetryInfomation,
          Server_Telemetry_Info_Form::getInstance(),
          &Server_Telemetry_Info_Form::clientInfomation, Qt::UniqueConnection);
  connect(this, &MainWindow::client_telesignaInfomation,
          Server_Telesigna_Info_Form::getInstance(),
          &Server_Telesigna_Info_Form::clientInfomation, Qt::UniqueConnection);
}

void MainWindow::clientConnect() {
  // 点击响应
  connect(ui->Client->selectionModel(), &QItemSelectionModel::currentChanged,
          this, &MainWindow::showinClient_Property, Qt::UniqueConnection);
  // 不可编辑
  ui->Client->setEditTriggers(QAbstractItemView::NoEditTriggers);
  // 启用自定义上下文菜单
  ui->Client->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->Client, &QTreeView::customContextMenuRequested, this,
          &MainWindow::TreeMenu_Client, Qt::UniqueConnection);

  // 传递给右侧子界面信息
  connect(this, &MainWindow::Client_Info_mes, Client_Info_Form::getInstance(),
          &Client_Info_Form::updateInfo, Qt::UniqueConnection);
  connect(this, &MainWindow::Client_Telemetry_Info_mes,
          Client_Telemetry_Info_Form::getInstance(),
          &Client_Telemetry_Info_Form::updateInfo, Qt::UniqueConnection);
  connect(this, &MainWindow::Client_Telesigna_Info_mes,
          Client_Telesigna_Info_Form::getInstance(),
          &Client_Telesigna_Info_Form::updateInfo, Qt::UniqueConnection);

  // 更新底部 statusbar
  connect(Client_Info_Form::getInstance(), &Client_Info_Form::textChanged, this,
          &MainWindow::updateSave, Qt::UniqueConnection);
  connect(Client_Telemetry_Info_Form::getInstance(),
          &Client_Telemetry_Info_Form::textChanged, this,
          &MainWindow::updateSave, Qt::UniqueConnection);
  connect(Client_Telesigna_Info_Form::getInstance(),
          &Client_Telesigna_Info_Form::textChanged, this,
          &MainWindow::updateSave, Qt::UniqueConnection);

  // 子界面保存传递
  connect(Client_Info_Form::getInstance(), &Client_Info_Form::Values, this,
          [&](CFG_CLIENT mes) {
            mod_client = true;
            this->modified_client(mes);
          });
  connect(Client_Telemetry_Info_Form::getInstance(this),
          &Client_Telemetry_Info_Form::Values, this,
          &MainWindow::modified_client_Telemetry, Qt::UniqueConnection);
  connect(Client_Telesigna_Info_Form::getInstance(this),
          &Client_Telesigna_Info_Form::Values, this,
          &MainWindow::modified_client_Telesigna, Qt::UniqueConnection);
}

// 快捷键设定
void MainWindow::setShortCut() {
  QShortcut* newShortcut = new QShortcut(QKeySequence("Ctrl+N"), this);
  connect(newShortcut, &QShortcut::activated, this,
          [&]() { ui->action_new->trigger(); });

  QShortcut* openShortcut = new QShortcut(QKeySequence("Ctrl+O"), this);
  connect(openShortcut, &QShortcut::activated, this,
          [&]() { ui->action_open->trigger(); });

  QShortcut* saveShortcut = new QShortcut(QKeySequence("Ctrl+S"), this);
  connect(saveShortcut, &QShortcut::activated, this,
          [&]() { ui->action_save->trigger(); });

  QShortcut* sSaveShortcut = new QShortcut(QKeySequence("Ctrl+Shift+S"), this);

  /**********************************************
  std::bind
  创建一个函数对象，将成员函数绑定到特定对象，并传递给其他函数或对象，以在稍后的时间执行该函数
  将子界面保存函数的地址绑定到当前 this 对象，从而在 Lambda 表达式中调用
  **********************************************/
  std::map<QWidget*, std::function<void()>> formSaveFunc;

  formSaveFunc.emplace(Client_Info_Form::getInstance(),
                       std::bind(&MainWindow::Client_Info_Save, this));
  formSaveFunc.emplace(
      Client_Telemetry_Info_Form::getInstance(),
      std::bind(&MainWindow::Client_Telemetry_Info_Save, this));
  formSaveFunc.emplace(
      Client_Telesigna_Info_Form::getInstance(),
      std::bind(&MainWindow::Client_Telesigna_Info_Save, this));
  formSaveFunc.emplace(Server_Info_Form::getInstance(),
                       std::bind(&MainWindow::Server_Info_Save, this));
  formSaveFunc.emplace(
      Server_Telemetry_Info_Form::getInstance(),
      std::bind(&MainWindow::Server_Telemetry_Info_Save, this));
  formSaveFunc.emplace(
      Server_Telesigna_Info_Form::getInstance(),
      std::bind(&MainWindow::Server_Telesigna_Info_Save, this));

  connect(sSaveShortcut, &QShortcut::activated, this, [=]() {
    auto widget = this->Property_form->currentWidget();
    auto it = formSaveFunc.find(widget);
    if (it != formSaveFunc.end()) {
      it->second();
    }
  });
}

void MainWindow::act_open() {
  if (!isSave) {
    this->Save_before();
  }

  qDebug() << "open file";

  QString dirpath = QApplication::applicationDirPath();
  QString filepath =
      QFileDialog::getOpenFileName(nullptr, "open File", dirpath, "*.xml");

  if (!config.get()->LoadFile(filepath.toUtf8().constData())) {
    return qDebug() << "LoadFile error!", void();
  }

  fpath = filepath;
  this->updateWindowTitle();
}

void MainWindow::new_file() {
  if (!isSave) {
    if (!this->Save_before()) {
      return;
    } else {
      goto NEWFILE;
    }
  }

NEWFILE:
  QString filename =
      QFileDialog::getSaveFileName(nullptr, "newFile", "config", "*.xml");
  if (filename.isEmpty()) {
    return qDebug() << "filename is Empty!", void();
  }
  loca_client.clear();
  loca_c_telemetry.clear();
  loca_c_telesigna.clear();
  loca_server.clear();
  loca_s_telemetry.clear();
  loca_s_telesigna.clear();
  this->clearLoca_client();
  this->clearLoca_server();
  fpath = filename;
  isSave = false;
  this->updateWindowTitle();
  this->server_clean_ui(), this->client_clean_ui();
  this->save_file();
}

void MainWindow::save_file() {
  isSave = true;
  emit save_as_in_xml(fpath, loca_server, loca_s_telemetry, loca_s_telesigna,
                      loca_client, loca_c_telemetry, loca_c_telesigna);
  this->updateWindowTitle();
}

void MainWindow::save_As() {
  QString filename =
      QFileDialog::getSaveFileName(nullptr, "SaveFile", "SaveFile", "*.xml)");
  if (filename.isEmpty()) {
    return qDebug() << "filename is Empty", void();
  }
  fpath = filename;
  emit save_as_in_xml(filename, loca_server, loca_s_telemetry, loca_s_telesigna,
                      loca_client, loca_c_telemetry, loca_c_telesigna);
  this->updateWindowTitle();
}

void MainWindow::btn_about() {
  QString version = "1.0";
  QMessageBox::information(this, "Version", "current tool version: " + version);
  return;
}

void MainWindow::help() {
  QMessageBox::information(this, "帮助", "右边子界面保存快捷键Ctrl+Shift+S");
  return;
}

bool MainWindow::Save_before() {
  QMessageBox messageBox(this);
  messageBox.setText("是否需要先保存文件");
  messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  messageBox.setDefaultButton(QMessageBox::Ok);

  int result = messageBox.exec();
  if (result == QMessageBox::Ok) {
    this->save_file();
    return true;
  }
  return false;
}

void MainWindow::warn_before() {
  QMessageBox messageBox(this);
  messageBox.setText("是否需要先保存文件");
  messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  messageBox.setDefaultButton(QMessageBox::Ok);

  // 获取对话框的按钮
  int result = messageBox.exec();
  if (result == QMessageBox::Ok) {
    this->save_file();
  }
}

void MainWindow::onTabChanged(int index) {
  switch (index) {
    case 0: {
      this->tabChangedClient();
      break;
    }
    case 1: {
      this->tabChangedServer();
      break;
    }
    default:
      break;
  }
}

void MainWindow::tabChangedClient() {
  QModelIndex curindex = ui->Client->currentIndex();
  if (curindex.isValid()) {
    this->showinClient_Property(curindex);
  } else {
    this->Property->setTitle("客户端信息");
  }
}

void MainWindow::tabChangedServer() {
  QModelIndex curindex = ui->Server->currentIndex();
  if (curindex.isValid()) {
    this->showinServer_Property(curindex);
  } else {
    this->Property->setTitle("服务端信息");
  }
}

void MainWindow::server_clean_ui() {
  this->clearLoca_server();
  // 新打开一个文件，需要将当前 model 清除
  QAbstractItemModel* oldmodel = ui->Server->model();
  if (oldmodel) {
    oldmodel->removeRows(0, oldmodel->rowCount());
  }
  Server_Info_Form::getInstance()->cleanInfo();
}

void MainWindow::init(int num) {
  QFont font("Microsoft YaHei", num);
  ui->Server->setFont(font);
  ui->Client->setFont(font);
  this->Property->setFont(font);

  // 隐藏行数和列数
  ui->Server->header()->setVisible(false);
  // 隐藏行数和列数
  ui->Client->header()->setVisible(false);

  ui->stackedWidget->resize(100, this->height());
  this->Property_form->resize(this->height(), 500);

  this->Property->setTitle("客户端信息");
  this->Property_form->move(Property->x(), Property->y() + 10);
  this->Property_form->addWidget(Client_Info_Form::getInstance());
  this->Property_form->addWidget(Client_Telemetry_Info_Form::getInstance());
  this->Property_form->addWidget(Client_Telesigna_Info_Form::getInstance());
  this->Property_form->addWidget(Server_Info_Form::getInstance());
  this->Property_form->addWidget(Server_Telemetry_Info_Form::getInstance());
  this->Property_form->addWidget(Server_Telesigna_Info_Form::getInstance());

  this->Property_form->setCurrentWidget(Client_Info_Form::getInstance());

  ui->stackedWidget->addWidget(this->Property);
  ui->stackedWidget->setCurrentWidget(this->Property);

  this->setShortCut();
}

void MainWindow::closeEvent(QCloseEvent* event) {
  if (!isSave) {
    this->Save_before();
  }

  deleteInstance(Client_Info_Form::getInstance());
  deleteInstance(Client_Telemetry_Info_Form::getInstance());
  deleteInstance(Client_Telesigna_Info_Form::getInstance());
  deleteInstance(Server_Info_Form::getInstance());
  deleteInstance(Server_Telemetry_Info_Form::getInstance());
  deleteInstance(Server_Telesigna_Info_Form::getInstance());

  QMainWindow::closeEvent(event);
}

void MainWindow::updateServer(MAP_CFG_SERVER ui_Server,
                              MAP_CFG_SERVER_TELEMETRY ui_ServerTelemetry,
                              MAP_CFG_SERVER_TELESIGNA ui_ServerTelesigna) {
  this->updateLoca_server(ui_Server, ui_ServerTelemetry, ui_ServerTelesigna);
  this->server_clean_ui();

  if (smodel.get() == nullptr) {
    return;
  }

  for (const auto& [id, server] : loca_server) {
    QString curmes = this->getLocaServeridx(server);
    QStandardItem* it = new QStandardItem(curmes);
    loca_s_idx.insert(curmes, id);
    smodel.get()->appendRow(it);

    QStandardItem* telemetry = new QStandardItem("遥测");
    it->appendRow(telemetry);
    for (const auto& t : loca_s_telemetry[id]) {
      if (!t.isEmpty()) {
        QString str = this->getTelemetryText(t);
        QStandardItem* it2 = new QStandardItem(str);
        loca_s_telemetry_idx[id].insert(str, t);
        telemetry->appendRow(it2);
      }
    }

    QStandardItem* telesigna = new QStandardItem("遥信");
    it->appendRow(telesigna);
    for (const auto& t : loca_s_telesigna[id]) {
      if (!t.isEmpty()) {
        QString str = this->getTelesignaText(t);
        QStandardItem* it2 = new QStandardItem(str);
        loca_s_telesigna_idx[id].insert(str, t);
        telesigna->appendRow(it2);
      }
    }
  }

  ui->Server->setModel(smodel.get());
  // 隐藏行数和列数
  ui->Server->header()->setVisible(false);
}

void MainWindow::updateLoca_server(
    MAP_CFG_SERVER ui_Server, MAP_CFG_SERVER_TELEMETRY ui_ServerTelemetry,
    MAP_CFG_SERVER_TELESIGNA ui_ServerTelesigna) {
  loca_server = ui_Server;
  loca_s_telemetry = ui_ServerTelemetry;
  loca_s_telesigna = ui_ServerTelesigna;

  return;
}

void MainWindow::updateClient(MAP_CFG_CLIENT ui_Client,
                              MAP_CFG_CLIENT_TELEMETRY ui_ClientTelemetry,
                              MAP_CFG_CLIENT_TELESIGNA ui_ClientTelesigna) {
  this->updateLoca_client(ui_Client, ui_ClientTelemetry, ui_ClientTelesigna);
  this->client_clean_ui();

  if (cmodel.get() == nullptr) {
    return;
  }

  for (const auto& [id, client] : loca_client) {
    QString curmes = this->getLocaClientidx(client).first;
    QStandardItem* it = new QStandardItem(curmes);
    loca_c_idx.insert(curmes, id);
    cmodel.get()->appendRow(it);

    QStandardItem* telemetry = new QStandardItem("遥测");
    it->appendRow(telemetry);
    for (const auto& t : loca_c_telemetry[id]) {
      if (!t.isEmpty()) {
        QString str = this->getTelemetryText(t);
        QStandardItem* it2 = new QStandardItem(str);
        loca_c_telemetry_idx[id].insert(str, t);
        telemetry->appendRow(it2);
      }
    }

    QStandardItem* telesigna = new QStandardItem("遥信");
    it->appendRow(telesigna);
    for (const auto& t : loca_c_telesigna[id]) {
      if (!t.isEmpty()) {
        QString str = this->getTelesignaText(t);
        QStandardItem* it2 = new QStandardItem(str);
        loca_c_telesigna_idx[id].insert(str, t);
        telesigna->appendRow(it2);
      }
    }
  }

  ui->Client->setModel(cmodel.get());
  ui->Client->header()->setVisible(false);
}

void MainWindow::updateLoca_client(
    MAP_CFG_CLIENT ui_Client, MAP_CFG_CLIENT_TELEMETRY ui_ClientTelemetry,
    MAP_CFG_CLIENT_TELESIGNA ui_ClientTelesigna) {
  loca_client = ui_Client;
  loca_c_telemetry = ui_ClientTelemetry;
  loca_c_telesigna = ui_ClientTelesigna;

  return;
}

void MainWindow::update_old_c_telemetry(CFG_CLIENT_TELEMETRY str) {
  old_c_telemetry = str;
}

void MainWindow::update_old_c_telesigna(CFG_CLIENT_TELESIGNA str) {
  old_c_telesigna = str;
}

std::pair<QString, unsigned int> MainWindow::getLocaClientidx(CFG_CLIENT str) {
  std::unordered_map<unsigned short, QString> mp = {
      {0, "IEC 104"}, {1, "Modbus TCP/IP"}, {2, "Modbus Serial Port"}};
  unsigned short usProtocol = str.usProtocol;
  if (usProtocol == 2) {
    return {QString("客户端 (%1-%2)").arg(mp[usProtocol], str.szSerialDevice),
            str.uiClientID};
  } else {
    return {QString("客户端 (%1-%2:%3)")
                .arg(mp[usProtocol], str.szIP, QString::number(str.usPort)),
            str.uiClientID};
  }
}

void MainWindow::showinServer_Property(QModelIndex idx) {
  auto getparentText = [&](QModelIndex idx) {
    if (idx.isValid()) {
      auto t = smodel.get()->itemFromIndex(idx);
      auto par = t->parent();
      if (par) {
        return par->text();
      }
    }

    return QString("");
  };

  auto getparparText = [&](QModelIndex idx) {
    if (idx.isValid()) {
      auto t = smodel.get()->itemFromIndex(idx);
      auto par = t->parent();
      if (par) {
        auto parr = par->parent();
        if (parr) {
          return parr->text();
        }
      }
    }

    return QString("");
  };

  ui->Server->resizeColumnToContents(idx.row());
  QString selectedRowTxt =
      ui->Server->model()->itemData(idx).values()[0].toString();
  curRowtext = selectedRowTxt;

  QString parentText = idx.parent().data().toString();
  Property->setTitle("服务端信息");
  if (selectedRowTxt.contains("服务端")) {
    this->Property_form->setVisible(true);
    this->Property_form->setCurrentWidget(Server_Info_Form::getInstance());
    curServeridx = loca_s_idx.value(curRowtext);
    old_server = loca_server[curServeridx];
    emit Server_Info_mes(loca_server[curServeridx]);
    return;
  }

  if (selectedRowTxt.contains("地址") && parentText.contains("遥测")) {
    curServeridx = loca_s_idx.value(getparparText(idx));
    this->Property_form->setVisible(true);
    this->update_old_s_telemetry(
        loca_s_telemetry_idx[curServeridx].value(curRowtext));
    this->Property_form->setCurrentWidget(
        Server_Telemetry_Info_Form::getInstance());
    emit Server_Telemetry_Info_mes(
        loca_client, loca_c_telemetry,
        loca_s_telemetry_idx[curServeridx].value(curRowtext));
    emit client_telemetryInfomation(loca_client, loca_c_telemetry);
  } else if (selectedRowTxt.contains("地址") && parentText.contains("遥信")) {
    curServeridx = loca_s_idx.value(getparparText(idx));
    this->Property_form->setVisible(true);
    this->update_old_s_telesigna(
        loca_s_telesigna_idx[curServeridx].value(curRowtext));
    this->Property_form->setCurrentWidget(
        Server_Telesigna_Info_Form::getInstance());
    emit Server_Telesigna_Info_mes(
        loca_client, loca_c_telesigna,
        loca_s_telesigna_idx[curServeridx].value(curRowtext));
    emit client_telesignaInfomation(loca_client, loca_c_telesigna);
  } else if (selectedRowTxt.contains("遥测")) {
    curServeridx = loca_s_idx.value(getparentText(idx));
    this->Property_form->setVisible(false);
    Server_Telemetry_Info_Form::getInstance()->cleanInfo();
  } else if (selectedRowTxt.contains("遥信")) {
    curServeridx = loca_s_idx.value(getparentText(idx));
    this->Property_form->setVisible(false);
    Server_Telesigna_Info_Form::getInstance()->cleanInfo();
  }
}

void MainWindow::clearLoca_server() {
  loca_s_idx.clear();
  loca_s_telemetry_idx.clear();
  loca_s_telesigna_idx.clear();
}

void MainWindow::update_server_id(QModelIndex curindex) {
  auto* model = smodel.get();
  if (!model) {
    return;
  }

  int row = curindex.row();
  int n = model->rowCount();
  // local
  if (row + 1 == n) {
    // 删除最后一个元素的情况
    auto it = loca_server.find(row);
    if (it != loca_server.end()) {
      loca_server.erase(it);
    }
  } else {
    for (int i = row + 1; i < n; i++) {
      // 更新 loca_server 中的索引
      auto it = loca_server.find(i);
      if (it != loca_server.end()) {
        it->second.uiServerID = i - 1;
        loca_server[i - 1] = std::move(it->second);
        loca_server.erase(it);
      }
      // 更新 loca_s_telemetry 中的索引
      auto telemetry_it = loca_s_telemetry.find(i);
      if (telemetry_it != loca_s_telemetry.end()) {
        loca_s_telemetry[i - 1] = std::move(telemetry_it->second);
        loca_s_telemetry.erase(telemetry_it);
      }
      // 更新 loca_s_telesigna 中的索引
      auto telesigna_it = loca_s_telesigna.find(i);
      if (telesigna_it != loca_s_telesigna.end()) {
        loca_s_telesigna[i - 1] = std::move(telesigna_it->second);
        loca_s_telesigna.erase(telesigna_it);
      }
    }
  }

  // UI && idx
  model->removeRow(row);
  int cnt = 0;
  this->clearLoca_server();
  for (const auto& [id, server] : loca_server) {
    QModelIndex modelIndex = model->index(cnt, 0);
    QString mes = this->getLocaServeridx(server);
    loca_s_idx.insert(mes, id);
    model->setData(modelIndex, mes);
    cnt++;

    for (const auto& t : loca_s_telemetry[id]) {
      QString str = this->getTelemetryText(t);
      loca_s_telemetry_idx[id].insert(str, t);
    }

    for (const auto& t : loca_s_telesigna[id]) {
      QString str = this->getTelesignaText(t);
      loca_s_telesigna_idx[id].insert(str, t);
    }
  }

  this->Property_form->setVisible(false);
  this->save_file();
}

bool MainWindow::exclusive(CFG_SERVER cfg_server) {
  for (const auto& [id, server] : loca_server) {
    if (!strcmp(cfg_server.szIP, server.szIP) &&
        cfg_server.usPort == server.usPort && server != old_server) {
      return true;
    }
  }

  return false;
}

bool MainWindow::exclusive(CFG_SERVER_TELEMETRY cfg_telemetry) {
  // 底层跟 for 循环一致
  bool addrExists = std::any_of(
      loca_s_telemetry[curServeridx].begin(),
      loca_s_telemetry[curServeridx].end(), [&](const CFG_SERVER_TELEMETRY& t) {
        return t.uiServerTelemetryAddr == cfg_telemetry.uiServerTelemetryAddr &&
               t != old_s_telemetry;
      });
  return addrExists;
}

bool MainWindow::exclusive(CFG_SERVER_TELESIGNA cfg_telesigna) {
  bool addrExists = std::any_of(
      loca_s_telesigna[curServeridx].begin(),
      loca_s_telesigna[curServeridx].end(), [&](const CFG_SERVER_TELESIGNA& t) {
        return t.uiServerTelesignaAddr == cfg_telesigna.uiServerTelesignaAddr &&
               t != old_s_telesigna;
      });

  return addrExists;
}

void MainWindow::showinClient_Property(QModelIndex idx) {
  auto getparentText = [&](QModelIndex idx) {
    if (idx.isValid()) {
      auto t = cmodel.get()->itemFromIndex(idx);
      auto par = t->parent();
      if (par) {
        return par->text();
      }
    }

    return QString("");
  };

  auto getparparText = [&](QModelIndex idx) {
    if (idx.isValid()) {
      auto t = cmodel.get()->itemFromIndex(idx);
      auto par = t->parent();
      if (par) {
        auto parr = par->parent();
        if (parr) {
          return parr->text();
        }
      }
    }

    return QString("");
  };

  ui->Client->resizeColumnToContents(idx.row());
  auto curidx = ui->Client->currentIndex();
  QString selectedRowTxt = cmodel.get()->itemFromIndex(curidx)->text();
  curRowtext = selectedRowTxt;

  QString parentText = idx.parent().data().toString();
  this->Property->setTitle("客户端信息");
  if (selectedRowTxt.contains("客户端")) {
    this->Property_form->setVisible(true);
    this->Property_form->setCurrentWidget(Client_Info_Form::getInstance());
    curClientidx = loca_c_idx.value(curRowtext);
    old_client = loca_client[curClientidx];
    emit Client_Info_mes(loca_client[curClientidx]);
    return;
  }

  if (selectedRowTxt.contains("地址") && parentText.contains("遥测")) {
    curClientidx = loca_c_idx.value(getparparText(idx));
    this->Property_form->setVisible(true);
    this->update_old_c_telemetry(
        loca_c_telemetry_idx[curClientidx].value(curRowtext));
    this->Property_form->setCurrentWidget(
        Client_Telemetry_Info_Form::getInstance());
    emit Client_Telemetry_Info_mes(
        loca_c_telemetry_idx[curClientidx].value(curRowtext));
  } else if (selectedRowTxt.contains("地址") && parentText.contains("遥信")) {
    curClientidx = loca_c_idx.value(getparparText(idx));
    this->Property_form->setVisible(true);
    this->update_old_c_telesigna(
        loca_c_telesigna_idx[curClientidx].value(curRowtext));
    this->Property_form->setCurrentWidget(
        Client_Telesigna_Info_Form::getInstance());
    emit Client_Telesigna_Info_mes(
        loca_c_telesigna_idx[curClientidx].value(curRowtext));
  } else if (selectedRowTxt.contains("遥测")) {
    curClientidx = loca_c_idx.value(getparentText(idx));
    this->Property_form->setVisible(false);
    Client_Telemetry_Info_Form::getInstance()->cleanInfo();
  } else if (selectedRowTxt.contains("遥信")) {
    curClientidx = loca_c_idx.value(getparentText(idx));
    this->Property_form->setVisible(false);
    Client_Telesigna_Info_Form::getInstance()->cleanInfo();
  }
}

QString MainWindow::getLocaServeridx(CFG_SERVER str) {
  QString curmes = QString("服务端(%2:%3)").arg(str.szIP).arg(str.usPort);
  return curmes;
}

void MainWindow::update_old_s_telemetry(CFG_SERVER_TELEMETRY str) {
  old_s_telemetry = str;
}

void MainWindow::update_old_s_telesigna(CFG_SERVER_TELESIGNA str) {
  old_s_telesigna = str;
}

void MainWindow::client_clean_ui() {
  this->clearLoca_client();
  // 新打开一个文件，需要将当前 model 清除
  QAbstractItemModel* oldmodel = ui->Client->model();
  if (oldmodel) {
    oldmodel->removeRows(0, oldmodel->rowCount());
  }
  Client_Info_Form::getInstance()->cleanInfo();
}

void MainWindow::TreeMenu_Server(const QPoint& pos) {
  QMenu menu;

  QAction* addAction =
      menu.addAction("添加服务端", this, [=]() { add_Server(); });
  menu.addSeparator();  // 分割线
  QAction* delAction =
      menu.addAction("删除服务端", this, [=]() { serverForm_del(); });
  menu.addSeparator();  // 分割线
  QAction* addtelemetryAction =
      menu.addAction("添加遥测节点", this, [=]() { add_Server_Telemetry(); });
  menu.addSeparator();  // 分割线
  QAction* addtelesignaAction =
      menu.addAction("添加遥信节点", this, [=]() { add_Server_Telesigna(); });
  menu.addSeparator();  // 分割线
  QAction* deltelemetryAction =
      menu.addAction("删除遥测节点", this, [=]() { del_Server_Telemetry(); });
  menu.addSeparator();  // 分割线
  QAction* deltelesignaAction =
      menu.addAction("删除遥信节点", this, [=]() { del_Server_Telesigna(); });

  addAction->setVisible(false);
  delAction->setVisible(false);
  addtelemetryAction->setVisible(false);
  deltelemetryAction->setVisible(false);
  addtelesignaAction->setVisible(false);
  deltelesignaAction->setVisible(false);

  QModelIndex curindex = ui->Server->indexAt(pos);
  QModelIndex idx = curindex.sibling(curindex.row(), 0);
  QString curData = idx.data().toString();
  QString curParData = idx.parent().data().toString();

  bool isValid = idx.isValid();
  bool isAddress = curData.contains("地址");
  bool isTelemetry = curData.contains("遥测");
  bool isTelesigna = curData.contains("遥信");
  bool isParTelemetry = curParData.contains("遥测");
  bool isParTelesigna = curParData.contains("遥信");

  addAction->setVisible((curData.contains("服务端") || !isValid) &&
                        !isTelemetry);
  delAction->setVisible((curData.contains("服务端") || !isValid) &&
                        !isTelemetry);
  delAction->setEnabled(isValid);
  addtelemetryAction->setVisible(isTelemetry && isValid);
  deltelemetryAction->setVisible(isParTelemetry && isAddress && isValid);
  addtelesignaAction->setVisible(isTelesigna && isValid);
  deltelesignaAction->setVisible(isParTelesigna && isAddress && isValid);

  menu.exec(QCursor::pos());
}

void MainWindow::modified_server(CFG_SERVER new_mes) {
  auto curidx = ui->Server->currentIndex();
  if (old_server == new_mes || !curidx.isValid()) {
    return;
  }
  QStandardItem* curNode = smodel.get()->itemFromIndex(curidx);
  QString str = this->getLocaServeridx(new_mes);
  QString oldstr = this->getLocaServeridx(old_server);
  auto it = loca_s_idx.find(oldstr);
  if (this->exclusive(new_mes)) {
    isSave = true;
    this->updateWindowTitle();
    QMessageBox::information(this, "提示",
                             "不能添加完全相同的节点, 请重新更改");
    emit Server_Info_mes(loca_server[curServeridx]);
    return;
  }
  if (mod_server) {
    isSave = false;
    old_server = new_mes;
    loca_server[curServeridx] = new_mes;
    loca_s_idx.erase(it);
    loca_s_idx.insert(str, curServeridx);
    curNode->setText(str);
    this->updateWindowTitle();
    mod_server = false;
    this->save_file();
  }
}

void MainWindow::modified_server_Telemetry(CFG_SERVER_TELEMETRY new_mes) {
  auto curidx = ui->Server->currentIndex();
  if (!curidx.isValid()) return;
  curRowtext = smodel.get()->itemFromIndex(curidx)->text();
  this->update_old_s_telemetry(
      loca_s_telemetry_idx[curServeridx].value(curRowtext));
  mod_server_Telemetry = old_s_telemetry == new_mes;
  if (mod_server_Telemetry) {
    isSave = true;
    this->updateWindowTitle();
    return;
  }

  if (this->exclusive(new_mes)) {
    isSave = true;
    this->updateWindowTitle();
    QMessageBox::information(this, "提示",
                             "不能添加完全相同的节点, 请重新更改");
    emit Server_Telemetry_Info_mes(
        loca_client, loca_c_telemetry,
        loca_s_telemetry_idx[curServeridx].value(curRowtext));
    return;
  }
  // local
  mod_server_Telemetry = true;
  auto local_it =
      std::find(loca_s_telemetry[curServeridx].begin(),
                loca_s_telemetry[curServeridx].end(), old_s_telemetry);
  if (local_it != loca_s_telemetry[curServeridx].end()) {
    qDebug() << "modified old_s_telemetry";
    old_s_telemetry = new_mes;
    *local_it = new_mes;
  }

  // UI
  QStandardItem* curNode = smodel.get()->itemFromIndex(curidx);
  QString str = this->getTelemetryText(new_mes);
  QString oldstr = this->getTelemetryText(old_s_telemetry);
  auto it = loca_s_telemetry_idx[curServeridx].find(oldstr);
  loca_s_telemetry_idx[curServeridx].erase(it);
  loca_s_telemetry_idx[curServeridx].insert(str, new_mes);
  curNode->setText(str);

  isSave = false;
  this->updateWindowTitle();
  this->save_file();
}

void MainWindow::modified_server_Telesigna(CFG_SERVER_TELESIGNA new_mes) {
  auto curidx = ui->Server->currentIndex();
  if (!curidx.isValid()) return;
  curRowtext = smodel.get()->itemFromIndex(curidx)->text();
  this->update_old_s_telesigna(
      loca_s_telesigna_idx[curServeridx].value(curRowtext));
  mod_server_Telesigna = old_s_telesigna == new_mes;
  if (mod_server_Telesigna) {
    isSave = true;
    this->updateWindowTitle();
    return;
  }

  if (this->exclusive(new_mes)) {
    isSave = true;
    this->updateWindowTitle();
    QMessageBox::information(this, "提示",
                             "不能添加完全相同的节点, 请重新更改");
    emit Server_Telesigna_Info_mes(
        loca_client, loca_c_telesigna,
        loca_s_telesigna_idx[curServeridx].value(curRowtext));
    return;
  }
  mod_server_Telesigna = true;
  auto local_it =
      std::find(loca_s_telesigna[curServeridx].begin(),
                loca_s_telesigna[curServeridx].end(), old_s_telesigna);
  if (local_it != loca_s_telesigna[curServeridx].end()) {
    qDebug() << "modified old_s_telesigna";
    old_s_telesigna = new_mes;
    *local_it = new_mes;
  }

  // UI
  QStandardItem* curNode = smodel.get()->itemFromIndex(curidx);
  QString str = this->getTelesignaText(new_mes);
  QString oldstr = this->getTelesignaText(old_s_telesigna);
  auto it = loca_s_telesigna_idx[curServeridx].find(oldstr);
  loca_s_telesigna_idx[curServeridx].erase(it);
  loca_s_telesigna_idx[curServeridx].insert(str, new_mes);
  curNode->setText(str);
  isSave = false;
  this->updateWindowTitle();
  this->save_file();
}

void MainWindow::del_loca_s_telemetry(CFG_SERVER_TELEMETRY t) {
  auto curidx = ui->Server->currentIndex();
  if (!curidx.isValid()) return;
  isSave = false;
  this->updateWindowTitle();
  // UI
  QStandardItem* curNode = smodel.get()->itemFromIndex(curidx);
  QString str = curNode->text();
  QStandardItem* parent = curNode->parent();
  for (int i = 0; i < parent->rowCount(); i++) {
    if (parent->child(i)->text() == str) {
      parent->removeRow(i);
      break;
    }
  }
  // local
  auto& op = loca_s_telemetry[curServeridx];
  for (auto& c : op) {
    if (c == t) {
      std::cout << "del_loca_s_telemetry successful";
      op.erase(std::remove(op.begin(), op.end(), c));
      break;
    }
  }

  this->save_file();
}

void MainWindow::del_loca_s_telesigna(CFG_SERVER_TELESIGNA t) {
  auto curidx = ui->Server->currentIndex();
  if (!curidx.isValid()) return;
  isSave = false;
  this->updateWindowTitle();
  // UI
  QStandardItem* curNode = smodel.get()->itemFromIndex(curidx);
  QString str = curNode->text();
  QStandardItem* parent = curNode->parent();
  for (int i = 0; i < parent->rowCount(); i++) {
    if (parent->child(i)->text() == str) {
      parent->removeRow(i);
      break;
    }
  }
  // local
  auto& op = loca_s_telesigna[curServeridx];
  for (auto& c : op) {
    if (c == t) {
      std::cout << "del_loca_s_telesigna successful";
      op.erase(std::remove(op.begin(), op.end(), c));
      break;
    }
  }

  this->save_file();
}

void MainWindow::serverForm_del() {
  QModelIndex curindex = ui->Server->currentIndex();
  // 检查是否有效
  if (curindex.isValid()) {
    isSave = false;
    this->updateWindowTitle();
    this->update_server_id(curindex);
    curServeridx = -1;
  }
}

void MainWindow::add_Server() {
  CFG_SERVER cfgServer;

  memset(&cfgServer, 0, MAX_CFG_SERVER);

  unsigned int id = static_cast<unsigned int>(ui->Server->model()->rowCount());

  cfgServer.uiServerID = id;
  qstrncpy(cfgServer.szIP, 0, 16);
  cfgServer.usPort = 0;
  cfgServer.usDataType = 0;
  cfgServer.usPublicAddr = 0;
  qstrncpy(cfgServer.szDescribe, "", MAX_CFG_DESCRIBE);

  for (const auto& [id, server] : loca_server) {
    if (strcmp(server.szIP, cfgServer.szIP) == 0 &&
        server.usPort == cfgServer.usPort) {
      QMessageBox::information(this, "警告",
                               "还有初始节点，请更新初始节点再进行添加");
      return;
    }
  }

  loca_server[id] = cfgServer;
  loca_s_telemetry[id] = VECTOR_CFG_SERVER_TELEMETRY{};
  loca_s_telesigna[id] = VECTOR_CFG_SERVER_TELESIGNA{};

  isSave = false;
  this->updateWindowTitle();

  QStandardItem* rootNode = smodel.get()->invisibleRootItem();
  QStandardItem* newItem = new QStandardItem(this->getLocaServeridx(cfgServer));
  loca_s_idx.insert(this->getLocaServeridx(cfgServer), cfgServer.uiServerID);
  QStandardItem* telemetry = new QStandardItem("遥测");
  QStandardItem* telesigna = new QStandardItem("遥信");
  newItem->appendRow(telemetry);
  newItem->appendRow(telesigna);
  rootNode->appendRow(newItem);

  this->save_file();
}

void MainWindow::add_Server_Telemetry() {
  CFG_SERVER_TELEMETRY cfgServerTelemetry;

  memset(&cfgServerTelemetry, 0, MAX_CFG_SERVER_TELEMETRY);

  loca_s_telemetry[curServeridx].emplace_back(cfgServerTelemetry);

  isSave = false;
  this->updateWindowTitle();
  auto curidx = ui->Server->currentIndex();
  if (!curidx.isValid()) return;
  QStandardItem* curNode = smodel.get()->itemFromIndex(curidx);
  QString str =
      QString("地址：%1").arg(cfgServerTelemetry.uiServerTelemetryAddr);
  loca_s_telemetry_idx[curServeridx].insert(str, cfgServerTelemetry);
  QStandardItem* newItem = new QStandardItem(str);
  curNode->appendRow(newItem);

  this->save_file();
}

void MainWindow::add_Server_Telesigna() {
  CFG_SERVER_TELESIGNA cfgServerTelesigna;

  memset(&cfgServerTelesigna, 0, MAX_CFG_SERVER_TELESIGNA);

  loca_s_telesigna[curServeridx].emplace_back(cfgServerTelesigna);

  isSave = false;
  this->updateWindowTitle();
  auto curidx = ui->Server->currentIndex();
  if (!curidx.isValid()) return;
  QStandardItem* curNode = smodel.get()->itemFromIndex(curidx);
  QString str =
      QString("地址：%1").arg(cfgServerTelesigna.uiServerTelesignaAddr);
  loca_s_telesigna_idx[curServeridx].insert(str, cfgServerTelesigna);
  QStandardItem* newItem = new QStandardItem(str);
  curNode->appendRow(newItem);

  this->save_file();
}

void MainWindow::del_Server_Telemetry() {
  this->del_loca_s_telemetry(loca_s_telemetry_idx[curServeridx][curRowtext]);
}

void MainWindow::del_Server_Telesigna() {
  this->del_loca_s_telesigna(loca_s_telesigna_idx[curServeridx][curRowtext]);
}

void MainWindow::TreeMenu_Client(const QPoint& pos) {
  QMenu menu;

  QAction* addAction =
      menu.addAction("添加客户端", this, [=]() { add_Client(); });
  menu.addSeparator();  // 分割线
  QAction* delAction =
      menu.addAction("删除客户端", this, [=]() { clientForm_del(); });
  menu.addSeparator();  // 分割线
  QAction* addtelemetryAction =
      menu.addAction("添加遥测节点", this, [=]() { add_Client_Telemetry(); });
  menu.addSeparator();  // 分割线
  QAction* addtelesignaAction =
      menu.addAction("添加遥信节点", this, [=]() { add_Client_Telesigna(); });
  menu.addSeparator();  // 分割线
  QAction* deltelemetryAction =
      menu.addAction("删除遥测节点", this, [=]() { del_Client_Telemetry(); });
  menu.addSeparator();  // 分割线
  QAction* deltelesignaAction =
      menu.addAction("删除遥信节点", this, [=]() { del_Client_Telesigna(); });

  addAction->setVisible(false);
  delAction->setVisible(false);
  addtelemetryAction->setVisible(false);
  deltelemetryAction->setVisible(false);
  addtelesignaAction->setVisible(false);
  deltelesignaAction->setVisible(false);

  QModelIndex curindex = ui->Client->indexAt(pos);
  QModelIndex idx = curindex.sibling(curindex.row(), 0);
  QString curData = idx.data().toString();
  QString curParData = idx.parent().data().toString();

  bool isValid = idx.isValid();
  bool isAddress = curData.contains("地址");
  bool isTelemetry = curData.contains("遥测");
  bool isTelesigna = curData.contains("遥信");
  bool isParTelemetry = curParData.contains("遥测");
  bool isParTelesigna = curParData.contains("遥信");

  addAction->setVisible((curData.contains("客户端") || !isValid) &&
                        !isTelemetry);
  delAction->setVisible((curData.contains("客户端") || !isValid) &&
                        !isTelemetry);
  delAction->setEnabled(isValid);
  addtelemetryAction->setVisible(isTelemetry && isValid);
  deltelemetryAction->setVisible(isParTelemetry && isAddress && isValid);
  addtelesignaAction->setVisible(isTelesigna && isValid);
  deltelesignaAction->setVisible(isParTelesigna && isAddress && isValid);

  menu.exec(QCursor::pos());
}

void MainWindow::modified_client(CFG_CLIENT new_mes) {
  auto curidx = ui->Client->currentIndex();
  std::cout << old_client;
  std::cout << "************************\n";
  std::cout << new_mes;
  if (new_mes == old_client || !curidx.isValid()) {
    return;
  }
  QStandardItem* curNode = cmodel.get()->itemFromIndex(curidx);
  QString str = this->getLocaClientidx(new_mes).first;
  QString oldstr = this->getLocaClientidx(old_client).first;
  auto it = loca_c_idx.find(oldstr);
  if (this->exclusive(new_mes)) {
    isSave = true;
    this->updateWindowTitle();
    QMessageBox::information(this, "提示",
                             "不能添加完全相同的节点, 请重新更改");
    emit Client_Info_mes(loca_client[curClientidx]);
    return;
  }
  if (mod_client) {
    isSave = false;
    old_client = new_mes;
    loca_client[curClientidx] = new_mes;
    loca_c_idx.erase(it);
    loca_c_idx.insert(str, curClientidx);

    curNode->setText(str);
    this->updateWindowTitle();
    mod_client = false;
    this->save_file();
  }
}

void MainWindow::modified_client_Telemetry(CFG_CLIENT_TELEMETRY new_mes) {
  auto curidx = ui->Client->currentIndex();
  if (!curidx.isValid()) return;
  curRowtext = cmodel.get()->itemFromIndex(curidx)->text();
  this->update_old_c_telemetry(
      loca_c_telemetry_idx[curClientidx].value(curRowtext));
  mod_client_Telemetry = old_c_telemetry == new_mes;
  if (mod_client_Telemetry) {
    isSave = true;
    this->updateWindowTitle();
    return;
  }

  if (this->exclusive(new_mes)) {
    QMessageBox::information(this, "提示",
                             "不能添加完全相同的节点, 请重新更改");
    isSave = true;
    this->updateWindowTitle();
    emit Client_Telemetry_Info_mes(
        loca_c_telemetry_idx[curClientidx].value(curRowtext));
    return;
  }
  // local
  mod_client_Telemetry = true;
  auto local_it =
      std::find(loca_c_telemetry[curClientidx].begin(),
                loca_c_telemetry[curClientidx].end(), old_c_telemetry);
  if (local_it != loca_c_telemetry[curClientidx].end()) {
    qDebug() << "modified old_c_telemetry";
    *local_it = new_mes;
    old_c_telemetry = new_mes;
  }

  // UI && idx
  QStandardItem* curNode = cmodel.get()->itemFromIndex(curidx);
  QString str = this->getTelemetryText(new_mes);
  QString oldstr = this->getTelemetryText(old_c_telemetry);
  auto it = loca_c_telemetry_idx[curClientidx].find(oldstr);
  loca_c_telemetry_idx[curClientidx].erase(it);
  loca_c_telemetry_idx[curClientidx].insert(str, new_mes);
  curNode->setText(str);

  isSave = false;
  this->updateWindowTitle();
  this->save_file();
}

void MainWindow::modified_client_Telesigna(CFG_CLIENT_TELESIGNA new_mes) {
  auto curidx = ui->Client->currentIndex();
  if (!curidx.isValid()) return;
  curRowtext = cmodel.get()->itemFromIndex(curidx)->text();
  this->update_old_c_telesigna(
      loca_c_telesigna_idx[curClientidx].value(curRowtext));
  mod_client_Telesigna = old_c_telesigna == new_mes;
  if (mod_client_Telesigna) {
    isSave = true;
    this->updateWindowTitle();
    return;
  }

  if (this->exclusive(new_mes)) {
    QMessageBox::information(this, "提示",
                             "不能添加完全相同的节点, 请重新更改");
    isSave = true;
    this->updateWindowTitle();
    emit Client_Telesigna_Info_mes(
        loca_c_telesigna_idx[curClientidx].value(curRowtext));
    return;
  }
  mod_client_Telesigna = true;
  auto local_it =
      std::find(loca_c_telesigna[curClientidx].begin(),
                loca_c_telesigna[curClientidx].end(), old_c_telesigna);
  if (local_it != loca_c_telesigna[curClientidx].end()) {
    qDebug() << "modified old_c_telemetry";
    old_c_telesigna = new_mes;
    *local_it = new_mes;
  }

  // UI
  QStandardItem* curNode = cmodel.get()->itemFromIndex(curidx);
  QString str = this->getTelesignaText(new_mes);
  QString oldstr = this->getTelesignaText(old_c_telesigna);
  auto it = loca_c_telesigna_idx[curClientidx].find(oldstr);
  loca_c_telesigna_idx[curClientidx].erase(it);
  loca_c_telesigna_idx[curClientidx].insert(str, new_mes);
  curNode->setText(str);

  isSave = false;
  this->updateWindowTitle();
  this->save_file();
}

void MainWindow::del_loca_c_telemetry(CFG_CLIENT_TELEMETRY t) {
  auto curidx = ui->Client->currentIndex();
  if (!curidx.isValid()) return;
  isSave = false;
  this->updateWindowTitle();
  // UI
  QStandardItem* curNode = cmodel.get()->itemFromIndex(curidx);
  QString str = curNode->text();
  QStandardItem* parent = curNode->parent();
  for (int i = 0; i < parent->rowCount(); i++) {
    if (parent->child(i)->text() == str) {
      parent->removeRow(i);
      break;
    }
  }
  // local
  auto& op = loca_c_telemetry[curClientidx];
  for (auto& c : op) {
    if (c == t) {
      std::cout << "del_loca_c_telemetry successful";
      op.erase(std::remove(op.begin(), op.end(), c));
      break;
    }
  }

  this->Property_form->setVisible(false);
  this->save_file();
}

void MainWindow::del_loca_c_telesigna(CFG_CLIENT_TELESIGNA t) {
  auto curidx = ui->Client->currentIndex();
  if (!curidx.isValid()) return;
  isSave = false;
  this->updateWindowTitle();
  // UI
  QStandardItem* curNode = cmodel.get()->itemFromIndex(curidx);
  QString str = curNode->text();
  QStandardItem* parent = curNode->parent();
  for (int i = 0; i < parent->rowCount(); i++) {
    if (parent->child(i)->text() == str) {
      parent->removeRow(i);
      break;
    }
  }
  // local
  auto& op = loca_c_telesigna[curClientidx];
  for (auto& c : op) {
    if (c == t) {
      std::cout << "del_loca_c_telesigna successful";
      op.erase(std::remove(op.begin(), op.end(), c));
      break;
    }
  }

  this->Property_form->setVisible(false);
  this->save_file();
}

void MainWindow::clientForm_del() {
  QModelIndex curindex = ui->Client->currentIndex();
  // 检查是否有效
  if (curindex.isValid()) {
    isSave = false;
    this->updateWindowTitle();
    this->update_client_id(curindex);
    curClientidx = -1;
  }
}

void MainWindow::add_Client() {
  CFG_CLIENT cfgClient;

  memset(&cfgClient, 0, MAX_CFG_CLIENT);

  unsigned int id = static_cast<unsigned int>(ui->Client->model()->rowCount());

  cfgClient.uiClientID = id;
  cfgClient.usProtocol = 0;
  qstrncpy(cfgClient.szIP, 0, 16);
  cfgClient.usPort = 0;
  qstrncpy(cfgClient.szSerialDevice, "", 16);
  cfgClient.iBaud = 0;
  cfgClient.cParity = 0;
  cfgClient.iDataBit = 0;
  cfgClient.iStopBit = 0;
  cfgClient.usSlaveID = 0;
  cfgClient.usGeneralCallTime = 10;
  qstrncpy(cfgClient.szDescribe, "", MAX_CFG_DESCRIBE);

  loca_client[id] = cfgClient;
  loca_c_telemetry[id] = VECTOR_CFG_CLIENT_TELEMETRY{};
  loca_c_telesigna[id] = VECTOR_CFG_CLIENT_TELESIGNA{};

  isSave = false;
  this->updateWindowTitle();

  QStandardItem* rootNode = cmodel.get()->invisibleRootItem();
  QStandardItem* newItem =
      new QStandardItem(this->getLocaClientidx(cfgClient).first);
  loca_c_idx.insert(this->getLocaClientidx(cfgClient).first,
                    cfgClient.uiClientID);
  QStandardItem* telemetry = new QStandardItem("遥测");
  QStandardItem* telesigna = new QStandardItem("遥信");
  newItem->appendRow(telemetry);
  newItem->appendRow(telesigna);
  rootNode->appendRow(newItem);

  this->save_file();
}

void MainWindow::add_Client_Telemetry() {
  CFG_CLIENT_TELEMETRY cfgClientTelemetry;

  memset(&cfgClientTelemetry, 0, MAX_CFG_CLIENT_TELEMETRY);

  loca_c_telemetry[curClientidx].emplace_back(cfgClientTelemetry);

  isSave = false;
  this->updateWindowTitle();
  auto curidx = ui->Client->currentIndex();
  if (!curidx.isValid()) return;
  QStandardItem* curNode = cmodel.get()->itemFromIndex(curidx);
  QString str =
      QString("地址：%1").arg(cfgClientTelemetry.uiClientTelemetryAddr);
  loca_c_telemetry_idx[curClientidx].insert(str, cfgClientTelemetry);
  QStandardItem* newItem = new QStandardItem(str);
  curNode->appendRow(newItem);

  this->save_file();
}

void MainWindow::add_Client_Telesigna() {
  CFG_CLIENT_TELESIGNA cfgClientTelesigna;

  memset(&cfgClientTelesigna, 0, MAX_CFG_CLIENT_TELESIGNA);

  loca_c_telesigna[curClientidx].emplace_back(cfgClientTelesigna);

  isSave = false;
  this->updateWindowTitle();
  auto curidx = ui->Client->currentIndex();
  if (!curidx.isValid()) return;
  QStandardItem* curNode = cmodel.get()->itemFromIndex(curidx);
  QString str =
      QString("地址：%1").arg(cfgClientTelesigna.uiClientTelesignaAddr);
  loca_c_telesigna_idx[curClientidx].insert(str, cfgClientTelesigna);
  QStandardItem* newItem = new QStandardItem(str);
  curNode->appendRow(newItem);

  this->save_file();
}

void MainWindow::del_Client_Telemetry() {
  this->del_loca_c_telemetry(loca_c_telemetry_idx[curClientidx][curRowtext]);
}

void MainWindow::del_Client_Telesigna() {
  this->del_loca_c_telesigna(loca_c_telesigna_idx[curClientidx][curRowtext]);
}

void MainWindow::clearLoca_client() {
  loca_c_idx.clear();
  loca_c_telemetry_idx.clear();
  loca_c_telesigna_idx.clear();
}

void MainWindow::update_client_id(QModelIndex curindex) {
  auto* model = cmodel.get();
  if (!model) {
    return;
  }

  int row = curindex.row();
  int n = model->rowCount();
  // local
  if (row + 1 == n) {
    // 删除最后一个元素的情况
    auto it = loca_client.find(row);
    if (it != loca_client.end()) {
      loca_client.erase(it);
    }
  } else {
    for (int i = row + 1; i < n; i++) {
      // 更新 loca_client 中的索引
      auto it = loca_client.find(i);
      if (it != loca_client.end()) {
        it->second.uiClientID = i - 1;
        loca_client[i - 1] = std::move(it->second);
        loca_client.erase(it);
      }
      // 更新 loca_c_telemetry 中的索引
      auto telemetry_it = loca_c_telemetry.find(i);
      if (telemetry_it != loca_c_telemetry.end()) {
        loca_c_telemetry[i - 1] = std::move(telemetry_it->second);
        loca_c_telemetry.erase(telemetry_it);
      }
      // 更新 loca_c_telesigna 中的索引
      auto telesigna_it = loca_c_telesigna.find(i);
      if (telesigna_it != loca_c_telesigna.end()) {
        loca_c_telesigna[i - 1] = std::move(telesigna_it->second);
        loca_c_telesigna.erase(telesigna_it);
      }
    }
  }

  // UI && idx
  model->removeRow(row);
  int cnt = 0;
  this->clearLoca_client();
  for (const auto& [id, client] : loca_client) {
    QModelIndex modelIndex = model->index(cnt, 0);
    QString mes = this->getLocaClientidx(client).first;
    loca_c_idx.insert(mes, id);
    model->setData(modelIndex, mes);
    cnt++;

    for (const auto& t : loca_c_telemetry[id]) {
      QString str = this->getTelemetryText(t);
      loca_c_telemetry_idx[id].insert(str, t);
    }

    for (const auto& t : loca_c_telesigna[id]) {
      QString str = this->getTelesignaText(t);
      loca_c_telesigna_idx[id].insert(str, t);
    }
  }

  this->Property_form->setVisible(false);
  this->save_file();
}

bool MainWindow::exclusive(CFG_CLIENT cfg_client) {
  if (cfg_client.usProtocol == 2) {
    for (const auto& [id, client] : loca_client) {
      if (!strcmp(cfg_client.szSerialDevice, client.szSerialDevice) &&
          client.usProtocol == 2 && client != old_client) {
        return true;
      }
    }
  } else {
    for (const auto& [id, client] : loca_client) {
      if (!strcmp(cfg_client.szIP, client.szIP) &&
          cfg_client.usPort == client.usPort && client.usProtocol != 2 &&
          client != old_client) {
        return true;
      }
    }
  }

  return false;
}

bool MainWindow::exclusive(CFG_CLIENT_TELEMETRY cfg_telemetry) {
  for (const auto& t : loca_c_telemetry[curClientidx]) {
    if (t.uiClientTelemetryAddr == cfg_telemetry.uiClientTelemetryAddr &&
        t != old_c_telemetry) {
      return true;
    }
  }

  return false;
}

bool MainWindow::exclusive(CFG_CLIENT_TELESIGNA cfg_telesigna) {
  for (const auto& t : loca_c_telesigna[curClientidx]) {
    if (t.uiClientTelesignaAddr == cfg_telesigna.uiClientTelesignaAddr &&
        t != old_c_telesigna) {
      return true;
    }
  }

  return false;
}

void MainWindow::updateWindowTitle() {
  QLabel* statusLabel = ui->statusbar->findChild<QLabel*>();
  if (!isSave) {
    if (!statusLabel) {
      QLabel* statusLabel = new QLabel(fpath + " *", this);
      ui->statusbar->addPermanentWidget(statusLabel);
    } else {
      statusLabel->setText(fpath + " *");
    }
  } else {
    if (!statusLabel) {
      QLabel* statusLabel = new QLabel(fpath, this);
      ui->statusbar->addPermanentWidget(statusLabel);
    } else {
      statusLabel->setText(fpath);
    }
  }
}

void MainWindow::updateSave(bool bl) {
  if (bl != isSave) {
    isSave = bl;
    this->updateWindowTitle();
  }
}

void MainWindow::Client_Info_Save() { Client_Info_Form::getInstance()->Save(); }

void MainWindow::Client_Telemetry_Info_Save() {
  Client_Telemetry_Info_Form::getInstance()->Save();
}

void MainWindow::Client_Telesigna_Info_Save() {
  Client_Telesigna_Info_Form::getInstance()->Save();
}

void MainWindow::Server_Info_Save() { Server_Info_Form::getInstance()->Save(); }

void MainWindow::Server_Telemetry_Info_Save() {
  Server_Telemetry_Info_Form::getInstance()->Save();
}

void MainWindow::Server_Telesigna_Info_Save() {
  Server_Telesigna_Info_Form::getInstance()->Save();
}

QString MainWindow::getTelemetryText(CFG_CLIENT_TELEMETRY t) {
  return QString("地址：%1").arg(t.uiClientTelemetryAddr);
}

QString MainWindow::getTelemetryText(CFG_SERVER_TELEMETRY t) {
  return QString("地址：%1").arg(t.uiServerTelemetryAddr);
}

QString MainWindow::getTelesignaText(CFG_CLIENT_TELESIGNA t) {
  return QString("地址：%1").arg(t.uiClientTelesignaAddr);
}

QString MainWindow::getTelesignaText(CFG_SERVER_TELESIGNA t) {
  return QString("地址：%1").arg(t.uiServerTelesignaAddr);
}
