#include "include/mainwindow.h"

#include "include/Client_CheckForm.h"
#include "include/Client_Form.h"
#include "include/Client_Info_Form.h"
#include "include/Client_Telemetry_Form.h"
#include "include/Client_Telemetry_Info_Form.h"
#include "include/Client_Telesigna_Form.h"
#include "include/Client_Telesigna_Info_Form.h"
#include "include/Client_delete_Form.h"
#include "include/Server_CheckForm.h"
#include "include/Server_Form.h"
#include "include/Server_Info_Form.h"
#include "include/Server_Telemetry_Form.h"
#include "include/Server_Telemetry_Info_Form.h"
#include "include/Server_Telesigna_Form.h"
#include "include/Server_Telesigna_Info_Form.h"
#include "include/Server_delete_Form.h"
#include "include/new_Form.h"
#include "ui_mainwindow.h"

bool MainWindow::isSave = true;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    Qt::WindowFlags flags = windowFlags();
    flags |= Qt::WindowStaysOnTopHint;
    setWindowFlags(flags);
    ui->setupUi(this);

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

    this->setWindowIcon(QIcon(":/image/xml.jpg"));
    this->setFontSize(FONTSIZE);
    this->setWindowTitle("Xml 解析工具");
    this->resize(1000, 700);
    //    ui->Box->setAlignment(Qt::AlignRight);

    cmodel = std::make_shared<QStandardItemModel>(this);
    smodel = std::make_shared<QStandardItemModel>(this);
    ui->Server->setModel(smodel.get());
    ui->Client->setModel(cmodel.get());

    read_xml = std::make_shared<readXml>(this);
    connect(this, &MainWindow::open, read_xml.get(), &readXml::openFile);
    connect(read_xml.get(), &readXml::server_itemname, this, &MainWindow::updateServer, Qt::UniqueConnection);
    connect(read_xml.get(), &readXml::client_itemname, this, &MainWindow::updateClient, Qt::UniqueConnection);

    ui->action_new->setShortcut(Qt::CTRL + Qt::Key_N);
    ui->action_open->setShortcut(Qt::CTRL + Qt::Key_O);
    ui->action_save->setShortcut(Qt::CTRL + Qt::Key_S);

    connect(ui->action_open, &QAction::triggered, this, &MainWindow::act_open, Qt::UniqueConnection);
    connect(ui->action_new, &QAction::triggered, this, &MainWindow::new_file, Qt::UniqueConnection);
    connect(ui->action_save, &QAction::triggered, this, &MainWindow::save_file, Qt::UniqueConnection);
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::btn_about, Qt::UniqueConnection);
    connect(ui->action_saveAs, &QAction::triggered, this, &MainWindow::save_As, Qt::UniqueConnection);
    connect(ui->action_help, &QAction::triggered, this, &MainWindow::help, Qt::UniqueConnection);

    connect(ui->Server, &QTreeView::pressed, this, &MainWindow::showinServer_Property, Qt::UniqueConnection);
    ui->Server->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Server->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->Server, &QTreeView::customContextMenuRequested, this, &MainWindow::TreeMenu_Server,
            Qt::UniqueConnection);

    connect(ui->Client, &QTreeView::pressed, this, &MainWindow::showinClient_Property, Qt::UniqueConnection);
    ui->Client->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Client->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->Client, &QTreeView::customContextMenuRequested, this, &MainWindow::TreeMenu_Client,
            Qt::UniqueConnection);

    connect(this, &MainWindow::modify_Server, Server_Form::getInstance(this), &Server_Form::modifyServer,
            Qt::UniqueConnection);
    connect(Server_Form::getInstance(this), &Server_Form::modified_values, this, &MainWindow::modified_server,
            Qt::UniqueConnection);
    connect(Server_Form::getInstance(this), &Server_Form::modified_values, this, &MainWindow::check_server_to_ui,
            Qt::UniqueConnection);

    connect(this, &MainWindow::modify_Server, Server_Telemetry_Form::getInstance(this),
            &Server_Telemetry_Form::modifyServer, Qt::UniqueConnection);
    connect(Server_Telemetry_Form::getInstance(this), &Server_Telemetry_Form::modified_values, this,
            &MainWindow::modified_server, Qt::UniqueConnection);
    connect(Server_Telemetry_Form::getInstance(this), &Server_Telemetry_Form::modified_values, this,
            &MainWindow::check_server_to_ui, Qt::UniqueConnection);

    connect(this, &MainWindow::modify_Server, Server_Telesigna_Form::getInstance(this),
            &Server_Telesigna_Form::modifyServer, Qt::UniqueConnection);
    connect(Server_Telesigna_Form::getInstance(this), &Server_Telesigna_Form::modified_values, this,
            &MainWindow::modified_server, Qt::UniqueConnection);
    connect(Server_Telesigna_Form::getInstance(this), &Server_Telesigna_Form::modified_values, this,
            &MainWindow::check_server_to_ui, Qt::UniqueConnection);

    connect(this, &MainWindow::modify_Client, Client_Form::getInstance(this), &Client_Form::modifyClient,
            Qt::UniqueConnection);
    connect(Client_Form::getInstance(this), &Client_Form::modified_values, this, &MainWindow::modified_client,
            Qt::UniqueConnection);
    connect(Client_Form::getInstance(this), &Client_Form::modified_values, this, &MainWindow::check_client_to_ui,
            Qt::UniqueConnection);

    connect(this, &MainWindow::modify_Client, Client_Telemetry_Form::getInstance(this),
            &Client_Telemetry_Form::modifyClient, Qt::UniqueConnection);
    connect(Client_Telemetry_Form::getInstance(this), &Client_Telemetry_Form::modified_values, this,
            &MainWindow::modified_client, Qt::UniqueConnection);
    connect(Client_Telemetry_Form::getInstance(this), &Client_Telemetry_Form::modified_values, this,
            &MainWindow::check_client_to_ui, Qt::UniqueConnection);

    connect(this, &MainWindow::modify_Client, Client_Telesigna_Form::getInstance(this),
            &Client_Telesigna_Form::modifyClient, Qt::UniqueConnection);
    connect(Client_Telesigna_Form::getInstance(this), &Client_Telesigna_Form::modified_values, this,
            &MainWindow::modified_client, Qt::UniqueConnection);
    connect(Client_Telesigna_Form::getInstance(this), &Client_Telesigna_Form::modified_values, this,
            &MainWindow::check_client_to_ui, Qt::UniqueConnection);

    connect(Server_delete_Form::getInstance(this), &Server_delete_Form::del_curMes, this, &MainWindow::del_server_to_ui,
            Qt::UniqueConnection);
    connect(Client_delete_Form::getInstance(this), &Client_delete_Form::del_curMes, this, &MainWindow::del_client_to_ui,
            Qt::UniqueConnection);

    modify_xml = std::make_shared<modifyXml>(this);
//    connect(this, &MainWindow::modify_in_xml_server, modify_xml.get(), &modifyXml::modifyServer, Qt::UniqueConnection);
//    connect(this, &MainWindow::modify_in_xml_server_telemetry, modify_xml.get(), &modifyXml::modifyServer_Telemetry,
//            Qt::UniqueConnection);
//    connect(this, &MainWindow::modify_in_xml_server_telesigna, modify_xml.get(), &modifyXml::modifyServer_Telesigna,
//            Qt::UniqueConnection);
//    connect(this, &MainWindow::modify_in_xml_client, modify_xml.get(), &modifyXml::modifyClient, Qt::UniqueConnection);
//    connect(this, &MainWindow::modify_in_xml_client_telemetry, modify_xml.get(), &modifyXml::modifyClient_Telemetry,
//            Qt::UniqueConnection);
//    connect(this, &MainWindow::modify_in_xml_client_telesigna, modify_xml.get(), &modifyXml::modifyClient_Telesigna,
//            Qt::UniqueConnection);

    add_xml = std::make_shared<addXml>(this);
    connect(this, &MainWindow::add_in_xml_server_peer, add_xml.get(), &addXml::addServer_peer, Qt::UniqueConnection);
    connect(this, &MainWindow::add_in_xml_server_telemetry_peer, add_xml.get(), &addXml::addServer_Telemetry_peer,
            Qt::UniqueConnection);
    connect(this, &MainWindow::add_in_xml_server_telesigna_peer, add_xml.get(), &addXml::addServer_Telesigna_peer,
            Qt::UniqueConnection);
    connect(this, &MainWindow::add_in_xml_server_son_telemetry, add_xml.get(), &addXml::addServer_son_Telemetry,
            Qt::UniqueConnection);
    connect(this, &MainWindow::add_in_xml_server_son_telesigna, add_xml.get(), &addXml::addServer_son_Telesigna,
            Qt::UniqueConnection);
    connect(this, &MainWindow::add_in_xml_client_peer, add_xml.get(), &addXml::addClient_peer, Qt::UniqueConnection);
    connect(this, &MainWindow::add_in_xml_client_telemetry_peer, add_xml.get(), &addXml::addClient_Telemetry_peer,
            Qt::UniqueConnection);
    connect(this, &MainWindow::add_in_xml_client_telesigna_peer, add_xml.get(), &addXml::addClient_Telesigna_peer,
            Qt::UniqueConnection);
    connect(this, &MainWindow::add_in_xml_client_son_telemetry, add_xml.get(), &addXml::addClient_son_Telemetry,
            Qt::UniqueConnection);
    connect(this, &MainWindow::add_in_xml_client_son_telesigna, add_xml.get(), &addXml::addClient_son_Telesigna,
            Qt::UniqueConnection);

    del_xml = std::make_shared<deleteXml>(this);
    connect(this, &MainWindow::del_in_xml_server, del_xml.get(), &deleteXml::delServer, Qt::UniqueConnection);
    connect(this, &MainWindow::del_in_xml_server_telemetry, del_xml.get(), &deleteXml::delServer_Telemetry,
            Qt::UniqueConnection);
    connect(this, &MainWindow::del_in_xml_server_telesigna, del_xml.get(), &deleteXml::delServer_Telesigna,
            Qt::UniqueConnection);
    connect(this, &MainWindow::del_in_xml_client, del_xml.get(), &deleteXml::delClient, Qt::UniqueConnection);
    connect(this, &MainWindow::del_in_xml_client_telemetry, del_xml.get(), &deleteXml::delClient_Telemetry,
            Qt::UniqueConnection);
    connect(this, &MainWindow::del_in_xml_client_telesigna, del_xml.get(), &deleteXml::delClient_Telesigna,
            Qt::UniqueConnection);

    connect(new_Form::getInstance(this), &new_Form::new_Values, this, &MainWindow::new_Update, Qt::UniqueConnection);

    save_xml = std::make_shared<SaveXml>(this);
    connect(this, &MainWindow::save_in_xml, save_xml.get(), &SaveXml::SaveFile, Qt::UniqueConnection);

    connect(this, &MainWindow::Client_Info_mes, Client_Info_Form::getInstance(), &Client_Info_Form::updateInfo,
            Qt::UniqueConnection);
    connect(this, &MainWindow::Client_Telemetry_Info_mes, Client_Telemetry_Info_Form::getInstance(),
            &Client_Telemetry_Info_Form::updateInfo, Qt::UniqueConnection);
    connect(this, &MainWindow::Client_Telesigna_Info_mes, Client_Telesigna_Info_Form::getInstance(),
            &Client_Telesigna_Info_Form::updateInfo, Qt::UniqueConnection);

    connect(this, &MainWindow::Server_Info_mes, Server_Info_Form::getInstance(), &Server_Info_Form::updateInfo,
            Qt::UniqueConnection);
    connect(this, &MainWindow::Server_Telemetry_Info_mes, Server_Telemetry_Info_Form::getInstance(),
            &Server_Telemetry_Info_Form::updateInfo, Qt::UniqueConnection);
    connect(this, &MainWindow::Server_Telesigna_Info_mes, Server_Telesigna_Info_Form::getInstance(),
            &Server_Telesigna_Info_Form::updateInfo, Qt::UniqueConnection);
}

MainWindow::~MainWindow() {
    delete ui;
    //    delete read_xml;
    //    delete modify_xml;
    //    delete add_xml;
}

void MainWindow::act_open() {
    qDebug() << "open file";
    QString dirpath = QApplication::applicationDirPath();
    QString filepath = QFileDialog::getOpenFileName(nullptr, "open File", dirpath, "*.xml");
    emit open(filepath);
    fpath = filepath;
    this->updateWindowTitle();
}

void MainWindow::new_file() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    QString filename = QFileDialog::getSaveFileName(nullptr, "newFile", "New_File", "(*.xml");
    if (filename.isEmpty()) {
        return qDebug() << "filename is Empty!", void();
    }
    fpath = filename;
    isSave = false;
    this->updateWindowTitle();
    this->server_clean_ui(), this->client_clean_ui();
    new_Form::getInstance(this)->exec();
}

void MainWindow::save_file() {
    isSave = true;
    this->updateWindowTitle();
    emit save_in_xml(fpath, loca_server, loca_client);
}

void MainWindow::save_As() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    QString filename = QFileDialog::getSaveFileName(nullptr, "SaveFile", "SaveFile", "(*.xml)");
    if (filename.isEmpty()) {
        return qDebug() << "filename is Empty", void();
    }
    fpath = filename;
    this->save_file();
}

void MainWindow::btn_about() {
    QString version = "1.0";
    QMessageBox::information(this, "Version", "current tool version: " + version);
}

void MainWindow::help() {
    QMessageBox::information(this, "帮助", "出现某项右键不弹窗的情况，需要先点击其父节点，再进行操作！");
}

void MainWindow::new_Update(std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> Server,
                            std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> Client) {
    isSave = false;
    this->updateWindowTitle();
    this->updateServer(Server);
    this->updateClient(Client);
}

void MainWindow::server_clean_ui() {
    // 新打开一个文件，需要将当前 model 清除
    QAbstractItemModel* oldmodel = ui->Server->model();
    if (oldmodel) {
        oldmodel->removeRows(0, oldmodel->rowCount());
    }
}

void MainWindow::setFontSize(int num) const {
    QFont font("Microsoft YaHei", num);
    //    font.setBold(true);

    {
        ui->Server->setFont(font);
        ui->Client->setFont(font);
    }

    ui->stackedWidget_client->addWidget(Client_Info_Form::getInstance());
    ui->stackedWidget_client->addWidget(Client_Telemetry_Info_Form::getInstance());
    ui->stackedWidget_client->addWidget(Client_Telesigna_Info_Form::getInstance());
    ui->stackedWidget_client->setCurrentWidget(Client_Info_Form::getInstance());

    ui->stackedWidget_server->addWidget(Server_Info_Form::getInstance());
    ui->stackedWidget_server->addWidget(Server_Telemetry_Info_Form::getInstance());
    ui->stackedWidget_server->addWidget(Server_Telesigna_Info_Form::getInstance());
    ui->stackedWidget_server->setCurrentWidget(Server_Info_Form::getInstance());
}

void MainWindow::closeEvent(QCloseEvent* event) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    if (!isSave) {
        QMessageBox messageBox(this);
        messageBox.setText("是否需要先保存文件");
        messageBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        messageBox.setDefaultButton(QMessageBox::Ok);

        // 获取对话框的按钮
        QAbstractButton* okBtn = messageBox.button(QMessageBox::Ok);
        QAbstractButton* cancelBtn = messageBox.button(QMessageBox::Cancel);
        connect(okBtn, &QPushButton::clicked, this, &MainWindow::save_file);
        connect(cancelBtn, &QPushButton::clicked, this, [&]() { qDebug() << "cannel SaveFile;!"; });
        messageBox.exec();
    }
    QMainWindow::closeEvent(event);
}

void MainWindow::updateServer(std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> server) {
    loca_server = server;
    this->updateLoca_server();
    this->server_clean_ui();

    //    QStandardItemModel* model = new QStandardItemModel(this);
    if (smodel.get() == nullptr) {
        return;
    }
    for (const auto& c : server) {
        QList<QStandardItem*> item;
        QString curmes = this->getLocaidx(c.first);
        QStandardItem* it = new QStandardItem(curmes);
        loca_s_idx[curmes] = c.first;
        item.append(it);
        smodel.get()->appendRow(item);

        for (const auto& t : c.second.first) {
            QList<QStandardItem*> item2;
            QStandardItem* it2 = new QStandardItem(t);
            item2.append(it2);
            it->appendRow(item2);
        }

        for (const auto& t : c.second.second) {
            QList<QStandardItem*> item2;
            QStandardItem* it2 = new QStandardItem(t);
            item2.append(it2);
            it->appendRow(item2);
        }
    }

    ui->Server->setModel(smodel.get());
    // 隐藏行数和列数
    ui->Server->header()->setVisible(false);
}

void MainWindow::updateServerToui() {
    this->updateLoca_server();
    //    QStandardItemModel* model = new QStandardItemModel(ui->Server);
    if (smodel.get() == nullptr) {
        return;
    }
    this->server_clean_ui();
    for (const auto& c : loca_server) {
        if (c.first.isEmpty()) {
            continue;
        }
        QList<QStandardItem*> item;
        QString curmes = this->getLocaidx(c.first);
        QStandardItem* it = new QStandardItem(curmes);
        loca_s_idx[curmes] = c.first;
        item.append(it);
        smodel.get()->appendRow(item);

        for (const auto& t : c.second.first) {
            QList<QStandardItem*> item2;
            QStandardItem* it2 = new QStandardItem(t);
            item2.append(it2);
            it->appendRow(item2);
        }

        for (const auto& t : c.second.second) {
            QList<QStandardItem*> item2;
            QStandardItem* it2 = new QStandardItem(t);
            item2.append(it2);
            it->appendRow(item2);
        }
    }

    ui->Server->setModel(smodel.get());
}

void MainWindow::updateLoca_server() {
    for (const auto& c : loca_server) {
        loca_s.append(c.first);
        QString curmes = this->getLocaidx(c.first);
        loca_s_idx[curmes] = c.first;
        for (const auto& t : c.second.first) {
            loca_s_telemetry_to_server[t] = c.first;
        }
        for (const auto& t : c.second.second) {
            loca_s_telesigna_to_server[t] = c.first;
        }
    }
    return;
}

void MainWindow::updateClient(std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> client) {
    loca_client = client;
    this->updateLoca_client();
    this->client_clean_ui();

    QStandardItemModel* model = new QStandardItemModel(ui->Client);
    for (const auto& c : client) {
        QList<QStandardItem*> item;
        QString curmes = this->getLocaidx(c.first);
        QStandardItem* it = new QStandardItem(curmes);
        loca_c_idx[curmes] = c.first;
        item.append(it);
        model->appendRow(item);

        for (const auto& t : c.second.first) {
            QList<QStandardItem*> item2;
            QStandardItem* it2 = new QStandardItem(t);
            item2.append(it2);
            it->appendRow(item2);
        }

        for (const auto& t : c.second.second) {
            QList<QStandardItem*> item2;
            QStandardItem* it2 = new QStandardItem(t);
            item2.append(it2);
            it->appendRow(item2);
        }
    }

    ui->Client->setModel(model);
    ui->Client->header()->setVisible(false);
}

void MainWindow::updateClientToui() {
    this->updateLoca_client();
    QStandardItemModel* model = new QStandardItemModel(ui->Client);
    for (const auto& c : loca_client) {
        if (c.first.isEmpty()) {
            continue;
        }
        QList<QStandardItem*> item;
        QString curmes = this->getLocaidx(c.first);
        QStandardItem* it = new QStandardItem(curmes);
        loca_c_idx[curmes] = c.first;
        item.append(it);
        model->appendRow(item);

        for (const auto& t : c.second.first) {
            QList<QStandardItem*> item2;
            QStandardItem* it2 = new QStandardItem(t);
            item2.append(it2);
            it->appendRow(item2);
        }

        for (const auto& t : c.second.second) {
            QList<QStandardItem*> item2;
            QStandardItem* it2 = new QStandardItem(t);
            item2.append(it2);
            it->appendRow(item2);
        }
    }

    ui->Client->setModel(model);
}

void MainWindow::updateLoca_client() {
    for (const auto& c : loca_client) {
        loca_c.append(c.first);
        QString curmes = this->getLocaidx(c.first);
        loca_c_idx[curmes] = c.first;
        for (const auto& t : c.second.first) {
            loca_c_telemetry_to_client[t] = c.first;
        }
        for (const auto& t : c.second.second) {
            loca_c_telesigna_to_client[t] = c.first;
        }
    }
#ifdef NDEBUG
    for (const auto& c : loca_c_telemetry_to_client) {
        qDebug() << c.first << "\t" << c.second;
    }

    for (const auto& c : loca_c_telesigna_to_client) {
        qDebug() << c.first << "\t" << c.second;
    }
#endif
    return;
}

void MainWindow::showinServer_Property(QModelIndex idx) {
    ui->Server->resizeColumnToContents(idx.row());
    QString selectedRowTxt = ui->Server->model()->itemData(idx).values()[0].toString();
    curRowtext = selectedRowTxt;
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << "Server Text:\t" << selectedRowTxt;
#endif
    QStringList list = selectedRowTxt.split(',');
    if (list.size() == Info_Size) {
        ui->stackedWidget_server->setCurrentWidget(Server_Info_Form::getInstance());
        curServertext = loca_s_idx[selectedRowTxt];
        emit Server_Info_mes(curServertext);
        loca_s_telemetry = loca_server[curServertext].first;
        loca_s_telesignal = loca_server[curServertext].second;
    } else if (list.size() == server_telemetry_Size){
        ui->stackedWidget_server->setCurrentWidget(Server_Telemetry_Info_Form::getInstance());
        emit Server_Telemetry_Info_mes(curRowtext);
        loca_s_telemetry = loca_server[loca_s_telemetry_to_server[curRowtext]].first;
        loca_s_telesignal = loca_server[loca_s_telesigna_to_server[curRowtext]].second;
    } else if (list.size() == server_telesigna_Size) {
        ui->stackedWidget_server->setCurrentWidget(Server_Telesigna_Info_Form::getInstance());
        emit Server_Telesigna_Info_mes(curRowtext);
        loca_s_telemetry = loca_server[loca_s_telemetry_to_server[curRowtext]].first;
        loca_s_telesignal = loca_server[loca_s_telesigna_to_server[curRowtext]].second;
    }
}

void MainWindow::showinClient_Property(QModelIndex idx) {
    ui->Client->resizeColumnToContents(idx.row());
    QString selectedRowTxt = ui->Client->model()->itemData(idx).values()[0].toString();
    curRowtext = selectedRowTxt;
    QStringList list = selectedRowTxt.split(',');
    qDebug() << list.size();
    if (list.size() == Info_Size) {
        ui->stackedWidget_client->setCurrentWidget(Client_Info_Form::getInstance());
        curClienttext = loca_c_idx[selectedRowTxt];
        emit Client_Info_mes(curClienttext);
        loca_c_telemetry = loca_client[curClienttext].first;
        loca_c_telesignal = loca_client[curClienttext].second;
    } else if (list.size() == client_telemetry_Size) {
        ui->stackedWidget_client->setCurrentWidget(Client_Telemetry_Info_Form::getInstance());
        qDebug() << "loca_idx:\t" << loca_c_telemetry_to_client[curRowtext];
        emit Client_Telemetry_Info_mes(curRowtext);
        loca_c_telemetry = loca_client[loca_c_telemetry_to_client[curRowtext]].first;
        loca_c_telesignal = loca_client[loca_c_telesigna_to_client[curRowtext]].second;
    } else if (list.size() == client_telesigna_Size) {
        ui->stackedWidget_client->setCurrentWidget(Client_Telesigna_Info_Form::getInstance());
        emit Client_Telesigna_Info_mes(curRowtext);
        loca_c_telemetry = loca_client[loca_c_telemetry_to_client[curRowtext]].first;
        loca_c_telesignal = loca_client[loca_c_telesigna_to_client[curRowtext]].second;
    }
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << "Client Text:\t" << selectedRowTxt;
#endif
}

QString MainWindow::getLocaidx(QString str) {
    QStringList t = str.split(',');
    QStringList ip = t[1].split(':');
    QStringList port = t[2].split(':');
    QString curmes = ip[ip.size() - 1] + ":" + port[port.size() - 1];
    return curmes;
}

void MainWindow::client_clean_ui() {
    // 新打开一个文件，需要将当前 model 清除
    QAbstractItemModel* oldmodel = ui->Client->model();
    if (oldmodel) {
        oldmodel->removeRows(0, oldmodel->rowCount());
    }
}

void MainWindow::TreeMenu_Server(const QPoint& pos) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    QString qss = "QMenu{color:#E8E8E8;background:#4D4D4D;margin:2px;}\
        QMenu::item{padding:3px 20px 3px 20px;}\
        QMenu::indicator{width:13px;height:13px;}\
        QMenu::item:selected{color:#E8E8E8;border:0px solid #575757;background:#1E90FF;}\
        QMenu::separator{height:1px;background:#757575;}";

    QMenu menu;
    menu.setStyleSheet(qss);

    QModelIndex curindex = ui->Server->indexAt(pos);
    QModelIndex idx = curindex.sibling(curindex.row(), 0);
    if (idx.isValid()) {
        menu.addAction("修改", this, [=]() { serverForm_modify(); });
        menu.addSeparator();  // 分割线
        menu.addAction("删除", this, [=]() { serverForm_del(); });
        menu.addSeparator();  // 分割线
        menu.addAction("添加同级节点", this, [=]() { serverForm_add_peer(); });
        menu.addSeparator();  // 分割线
        menu.addAction("添加子节点", this, [=]() { serverForm_add_son(); });
    } else {
        qDebug() << "cur idx is not Valid";
    }
    menu.exec(QCursor::pos());
}

void MainWindow::serverForm_modify() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    QItemSelectionModel* selectionModel = ui->Server->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
#ifdef NDEBUG
        qDebug() << "func:\t" << __func__;
#endif
        qDebug() << "this text is Empty!";
        return;
    }

    if (loca_s_idx[curRowtext] == curServertext) {
//        QModelIndex selectedIndex = selectedIndexes.first();
//        QVariant data = selectedIndex.data();
#ifdef NDEBUG
        qDebug() << "this text in loca_s";
        qDebug() << "func:\t" << __func__;
        qDebug() << "data:\t" << curServertext << "\n";
#endif
        old_mes = curServertext;
        emit modify_Server(old_mes);
        Server_Form::getInstance(this)->exec();
        isSave = false;
        this->updateWindowTitle();
        return;
    } else {
        int idx = loca_server[curServertext].first.indexOf(curRowtext);
        if (idx != -1) {
#ifdef NDEBUG
            qDebug() << "this text in loca_s_telemetry";
#endif
            QModelIndex selectedIndex = selectedIndexes.first();
            QVariant data = selectedIndex.data();
#ifdef NDEBUG
            qDebug() << "func:\t" << __func__;
            qDebug() << data << "\n";
#endif
            old_mes = data.toString();
            emit modify_Server(old_mes);
            Server_Telemetry_Form::getInstance(this)->exec();
            isSave = false;
            this->updateWindowTitle();
            return;
        }

        idx = loca_server[curServertext].second.indexOf(curRowtext);
        if (idx != -1) {
#ifdef NDEBUG
            qDebug() << "this text in loca_s_telesignal";
#endif
            QModelIndex selectedIndex = selectedIndexes.first();
            QVariant data = selectedIndex.data();
#ifdef NDEBUG
            qDebug() << "func:\t" << __func__;
            qDebug() << data << "\n";
#endif
            old_mes = data.toString();
            emit modify_Server(old_mes);
            Server_Telesigna_Form::getInstance(this)->exec();
            isSave = false;
            this->updateWindowTitle();
            return;
        }
    }

    qDebug() << "this text not in loca_s_telesignal && loca_s_telemetry && loca_s";
}

void MainWindow::modified_server(QString new_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
#endif
    int idx;
    qDebug() << curServertext << " " << old_mes;
    if (curServertext == old_mes) {
        idx = loca_s.indexOf(old_mes);
        auto t = loca_server.find(loca_s[idx]);
        auto t1 = loca_server.find(loca_s[idx])->second;
        loca_server.erase(t);
        if (idx != -1) {
            QString old_mes = this->getLocaidx(loca_s[idx]);
            loca_s_idx.erase(old_mes);
            loca_s[idx] = new_mes;
            QString curidx = this->getLocaidx(new_mes);
            loca_s_idx[curidx] = new_mes;
            loca_server[loca_s[idx]] = t1;
            this->updateServerToui();
            qDebug() << "modify server success in ui";
            isSave = false;
            this->updateWindowTitle();
#ifdef FORDEBUG
            if (!loca_s.isEmpty()) {
                for (int i = 0; i < loca_s.size(); i++) {
                    qDebug() << "loca_s:\t" << loca_s[i];
                }
            } else {
                qDebug() << "loca_s is empty";
            }
            if (!loca_s_telemetry.isEmpty()) {
                for (int i = 0; i < loca_s_telemetry.size(); i++) {
                    qDebug() << "loca_s_telemetry:\t" << loca_s_telemetry[i];
                }
            } else {
                qDebug() << "loca_s_telemetry is empty";
            }
            if (!loca_s_telesignal.isEmpty()) {
                for (int i = 0; i < loca_s_telesignal.size(); i++) {
                    qDebug() << "loca_s_telesignal:t" << loca_s_telesignal[i];
                }
            } else {
                qDebug() << "loca_s_telesignal is empty";
            }
#endif
            //            emit modify_in_xml_server(fpath, new_mes, old_mes);
            return;
        }
    } else {
        idx = loca_server[curServertext].first.indexOf(old_mes);
        if (idx != -1) {
            loca_s_telemetry = loca_server[curServertext].first;
            loca_s_telemetry[idx] = new_mes;
            loca_server[curServertext].first[idx] = new_mes;
            this->updateServerToui();
            qDebug() << "modify server_telemetry success in ui";
            //            emit modify_in_xml_server_telemetry(fpath, new_mes, old_mes, curServertext);
            isSave = false;
            this->updateWindowTitle();
            return;
        }

        idx = loca_server[curServertext].second.indexOf(old_mes);
        if (idx != -1) {
            loca_s_telesignal = loca_server[curServertext].second;
            loca_s_telesignal[idx] = new_mes;
            loca_server[curServertext].second[idx] = new_mes;
            this->updateServerToui();
            qDebug() << "modify server_telesignal success in ui";
            //            emit modify_in_xml_server_telesigna(fpath, new_mes, old_mes, curServertext);
            isSave = false;
            this->updateWindowTitle();
            return;
        }
    }
}

void MainWindow::serverForm_del() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    Server_delete_Form::getInstance(this)->exec();
}

void MainWindow::serverForm_add_peer() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    server_add_peer = true;
    if (curServertext == loca_s_idx[curRowtext]) {
        curidx = loca_s.indexOf(curServertext);
        Server_Form::getInstance(this)->exec();
        return;
    } else {
        int idx = loca_server[curServertext].first.indexOf(curRowtext);
        if (idx != -1) {
#ifdef NDEBUG
            qDebug() << "this text in loca_s_telemetry";
#endif
            curidx = idx;
            Server_Telemetry_Form::getInstance(this)->exec();
            return;
        }

        idx = loca_server[curServertext].second.indexOf(curRowtext);
        if (idx != -1) {
#ifdef NDEBUG
            qDebug() << "this text in loca_s_telesignal";
#endif
            curidx = idx;
            Server_Telesigna_Form::getInstance(this)->exec();
            return;
        }
    }
}

void MainWindow::serverForm_add_son() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    server_add_son = true;
    int idx = loca_s.indexOf(loca_s_idx[curRowtext]);
    if (idx != -1) {
#ifdef NDEBUG
        qDebug() << "this text in loca_s";
#endif
        curidx = idx;
        Server_CheckForm::getInstance(this)->exec();
        return;
    }

    idx = loca_s_telemetry.indexOf(curRowtext);
    if (idx != -1) {
#ifdef NDEBUG
        qDebug() << "this text in loca_s_telemetry";
#endif
        QMessageBox::information(this, "添加", "不能给当前节点添加子节点");
        return;
    }

    idx = loca_s_telesignal.indexOf(curRowtext);
    if (idx != -1) {
#ifdef NDEBUG
        qDebug() << "this text in loca_s_telesignal";
#endif
        QMessageBox::information(this, "添加", "不能给当前节点添加子节点");
        return;
    }
}

void MainWindow::check_server_to_ui(QString new_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    if (server_add_son) {
        qDebug() << "add son to server in ui";
        this->add_serverson_to_ui(new_mes);
        server_add_son = false;
        return;
    }

    if (server_add_peer) {
        qDebug() << "add peer to server in ui";
        this->add_serverpeer_to_ui(new_mes);
        server_add_peer = false;
        return;
    }
}

void MainWindow::add_serverpeer_to_ui(QString new_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes.split(',').size();
#endif
    QModelIndexList selectedIndexes = ui->Server->selectionModel()->selectedIndexes();
    if (!selectedIndexes.isEmpty()) {
        QModelIndex selectedIndex = selectedIndexes.first();
        QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(ui->Server->model());
        if (model) {
            QStandardItem* selectedNode = model->itemFromIndex(selectedIndex);
            QStandardItem* parentNode = selectedNode->parent();
            if (parentNode) {
                QStandardItem* newNode = new QStandardItem(new_mes);
                int row = selectedIndex.row();
                parentNode->insertRow(row + 1, newNode);
                bool flag = new_mes.split(',').size() == server_telemetry_Size ? true : false;
                if (flag) {
                    qDebug() << "insert to loca_s_telemetry";
                    //                    loca_s_telemetry.insert(curidx + 1, new_mes);
                    loca_server[curServertext].first.insert(curidx + 1, new_mes);
                    isSave = false;
                    this->updateWindowTitle();
                    //                    emit add_in_xml_server_telemetry_peer(fpath, new_mes, curRowtext,
                    //                    curServertext);
                } else {
                    qDebug() << "insert to loca_s_telesignal";
                    //                    loca_s_telesignal.insert(curidx + 1, new_mes);
                    loca_server[curServertext].second.insert(curidx + 1, new_mes);
                    isSave = false;
                    this->updateWindowTitle();
                    //                    emit add_in_xml_server_telesigna_peer(fpath, new_mes, curRowtext,
                    //                    curServertext);
                }
            } else {
                if (loca_server.find(new_mes) == loca_server.end()) {
                    QString curmes = this->getLocaidx(new_mes);
                    QStandardItem* newNode = new QStandardItem(curmes);
                    int row = selectedIndex.row();
                    model->insertRow(row + 1, newNode);
                    qDebug() << "insert to loca_s";
                    loca_s.insert(curidx + 1, new_mes);
                    loca_s_idx[curmes] = new_mes;
                    loca_server[new_mes] = {QVector<QString>(), QVector<QString>()};
                    isSave = false;
                    this->updateWindowTitle();
                    //                    emit add_in_xml_server_peer(fpath, new_mes, curRowtext);
                } else {
                    QMessageBox::information(this, "添加", "不能添加信息完全相同的节点");
                }
            }
        } else {
            qDebug() << "model is empty";
        }
    }
}

void MainWindow::add_serverson_to_ui(QString new_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    QModelIndexList selectedIndexes = ui->Server->selectionModel()->selectedIndexes();
    if (!selectedIndexes.isEmpty()) {
        QModelIndex selectedIndex = selectedIndexes.first();
        QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(ui->Server->model());
        if (model) {
            QStandardItem* selectedNode = model->itemFromIndex(selectedIndex);
            QStandardItem* newNode = new QStandardItem(new_mes);
            //            selectedNode->appendRow(newNode);
            selectedNode->insertRow(0, newNode);
            bool flag = new_mes.split(',').size() == server_telemetry_Size ? true : false;
            if (flag) {
                qDebug() << "insert to loca_s_telemetry";
                loca_s_telemetry.push_back(new_mes);
                loca_server[curServertext].first.push_back(new_mes);
                isSave = false;
                this->updateWindowTitle();
                //                emit add_in_xml_server_son_telemetry(fpath, new_mes, curServertext);
            } else {
                qDebug() << "insert to loca_s_telesignal";
                loca_s_telesignal.push_back(new_mes);
                loca_server[curServertext].second.push_back(new_mes);
                isSave = false;
                this->updateWindowTitle();
                //                emit add_in_xml_server_son_telesigna(fpath, new_mes, curServertext);
            }
        } else {
            qDebug() << "model is empty";
        }
    }
}

void MainWindow::del_server_to_ui() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif

    QModelIndex curindex = ui->Server->currentIndex();
    // 检查是否有效
    if (curindex.isValid()) {
        // 获取当前选定项的模型
        QAbstractItemModel* model = ui->Server->model();
        QString curText = curindex.data().toString();
        int curSize = curText.split(',').size();
#ifdef NDEBUG
        qDebug() << "curText:\t" << curText;
        qDebug() << "curSize:\t" << curSize;
#endif
        isSave = false;
        this->updateWindowTitle();
        if (curSize == Info_Size) {
            /*
             * 首先，使用std::remove()算法将要删除的元素移动到std::vector的末尾，
             * 返回一个指向新的结束位置的迭代器。这个操作不会真正删除元素，只是将要删除的元素移到了末尾。
             * 然后，使用std::vector::erase()函数，传入两个参数：
             * 第一个参数是移动到末尾的元素的起始位置的迭代器（通过std::remove()返回的迭代器），
             * 第二个参数是std::vector的结束位置的迭代器。这个函数将从std::vector中删除位于指定范围内的元素。
             * */
            loca_s.erase(std::remove(loca_s.begin(), loca_s.end(), loca_s_idx[curText]), loca_s.end());
            loca_s_idx.erase(curText);
            loca_server.erase(loca_s_idx[curText]);
            isSave = false;
            this->updateWindowTitle();
            //            emit del_in_xml_server(fpath, curText);
        } else if (curSize == server_telemetry_Size) {
            // 引用获取，避免不必要的复制，以便在原地修改
            auto& t = loca_server[curServertext].first;
            t.erase(std::remove(t.begin(), t.end(), curText), t.end());
            isSave = false;
            this->updateWindowTitle();
            //            emit del_in_xml_server_telemetry(fpath, curText, curServertext);
        } else if (curSize == server_telesigna_Size) {
            auto& t = loca_server[curServertext].second;
            t.erase(std::remove(t.begin(), t.end(), curText), t.end());
            isSave = false;
            this->updateWindowTitle();
            //            emit del_in_xml_server_telesigna(fpath, curText, curServertext);
        }
        // 删除当前选定项
        model->removeRow(curindex.row(), curindex.parent());
    } else {
        qDebug() << "curidx is not Valid";
        return;
    }
}

void MainWindow::TreeMenu_Client(const QPoint& pos) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    QString qss = "QMenu{color:#E8E8E8;background:#4D4D4D;margin:2px;}\
        QMenu::item{padding:3px 20px 3px 20px;}\
        QMenu::indicator{width:13px;height:13px;}\
        QMenu::item:selected{color:#E8E8E8;border:0px solid #575757;background:#1E90FF;}\
        QMenu::separator{height:1px;background:#757575;}";

    QMenu menu;
    menu.setStyleSheet(qss);

    QModelIndex curindex = ui->Client->indexAt(pos);
    QModelIndex idx = curindex.sibling(curindex.row(), 0);
    if (idx.isValid()) {
        menu.addAction("修改", this, [=]() { clientForm_modify(); });
        menu.addSeparator();  // 分割线
        menu.addAction("删除", this, [=]() { clientForm_del(); });
        menu.addSeparator();  // 分割线
        menu.addAction("添加同级节点", this, [=]() { clientForm_add_peer(); });
        menu.addSeparator();  // 分割线
        menu.addAction("添加子节点", this, [=]() { clientForm_add_son(); });
    }
    menu.exec(QCursor::pos());
}

void MainWindow::clientForm_modify() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    QItemSelectionModel* selectionModel = ui->Client->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
    if (selectedIndexes.isEmpty()) {
#ifdef NDEBUG
        qDebug() << "func:\t" << __func__;
#endif
        qDebug() << "this text is Empty!";
        return;
    }

    qDebug() << curRowtext << " " << curClienttext;
    if (loca_c_idx[curRowtext] == curClienttext) {
//        QModelIndex selectedIndex = selectedIndexes.first();
//        QVariant data = selectedIndex.data();
#ifdef NDEBUG
        qDebug() << "this text in loca_c";
        qDebug() << "func:\t" << __func__;
        qDebug() << "data:\t" << curClienttext << "\n";
#endif
        old_mes = curClienttext;
        emit modify_Client(old_mes);
        Client_Form::getInstance(this)->exec();
        return;
    } else {
        int idx = loca_client[curClienttext].first.indexOf(curRowtext);
        if (idx != -1) {
#ifdef NDEBUG
            qDebug() << "this text in loca_c_telemetry";
#endif
            QModelIndex selectedIndex = selectedIndexes.first();
            QVariant data = selectedIndex.data();
#ifdef NDEBUG
            qDebug() << "func:\t" << __func__;
            qDebug() << data << "\n";
#endif
            old_mes = data.toString();
            emit modify_Client(old_mes);
            Client_Telemetry_Form::getInstance(this)->exec();
            return;
        }

        idx = loca_client[curClienttext].second.indexOf(curRowtext);
        if (idx != -1) {
#ifdef NDEBUG
            qDebug() << "this text in loca_c_telesignal";
#endif
            QModelIndex selectedIndex = selectedIndexes.first();
            QVariant data = selectedIndex.data();
#ifdef NDEBUG
            qDebug() << "func:\t" << __func__;
            qDebug() << data << "\n";
#endif
            old_mes = data.toString();
            Client_Telesigna_Form::getInstance(this)->exec();
            emit modify_Client(old_mes);
            return;
        }
    }

    qDebug() << "this text not in loca_c_telesignal && loca_c_telemetry && loca_c";
}

void MainWindow::modified_client(QString new_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
#endif
    int idx;
    qDebug() << curClienttext << " " << old_mes;
    if (curClienttext == old_mes) {
        idx = loca_c.indexOf(old_mes);
        auto t = loca_client.find(loca_c[idx]);
        auto t1 = loca_client.find(loca_c[idx])->second;
        loca_client.erase(t);
        if (idx != -1) {
            QString old_mes = this->getLocaidx(loca_c[idx]);
            loca_c_idx.erase(old_mes);
            loca_c[idx] = new_mes;
            QString curidx = this->getLocaidx(new_mes);
            loca_c_idx[curidx] = new_mes;
            loca_client[loca_c[idx]] = t1;
            this->updateClientToui();
            qDebug() << "modify client success in ui";
            isSave = false;
            this->updateWindowTitle();
#ifdef FORDEBUG
            if (!loca_c.isEmpty()) {
                for (int i = 0; i < loca_c.size(); i++) {
                    qDebug() << "loca_c:\t" << loca_c[i];
                }
            } else {
                qDebug() << "loca_c is empty";
            }
            if (!loca_c_telemetry.isEmpty()) {
                for (int i = 0; i < loca_c_telemetry.size(); i++) {
                    qDebug() << "loca_c_telemetry:\t" << loca_c_telemetry[i];
                }
            } else {
                qDebug() << "loca_c_telemetry is empty";
            }
            if (!loca_c_telesignal.isEmpty()) {
                for (int i = 0; i < loca_c_telesignal.size(); i++) {
                    qDebug() << "loca_c_telesignal:t" << loca_c_telesignal[i];
                }
            } else {
                qDebug() << "loca_c_telesignal is empty";
            }
#endif
            //            emit modify_in_xml_client(fpath, new_mes, old_mes);
            return;
        }
    } else {
        idx = loca_client[curClienttext].first.indexOf(old_mes);
        if (idx != -1) {
            loca_c_telemetry = loca_client[curClienttext].first;
            loca_c_telemetry[idx] = new_mes;
            loca_client[curClienttext].first[idx] = new_mes;
            this->updateClientToui();
            qDebug() << "modify client_telemetry success in ui";
            isSave = false;
            this->updateWindowTitle();
            //            emit modify_in_xml_client_telemetry(fpath, new_mes, old_mes, curClienttext);
            return;
        }

        idx = loca_client[curClienttext].second.indexOf(old_mes);
        if (idx != -1) {
            loca_c_telesignal = loca_client[curClienttext].second;
            loca_c_telesignal[idx] = new_mes;
            loca_client[curClienttext].second[idx] = new_mes;
            this->updateClientToui();
            qDebug() << "modify client_telesignal success in ui";
            isSave = false;
            this->updateWindowTitle();
            //            emit modify_in_xml_client_telesigna(fpath, new_mes, old_mes, curClienttext);
            return;
        }
    }
}

void MainWindow::clientForm_del() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    Client_delete_Form::getInstance(this)->exec();
}

void MainWindow::clientForm_add_peer() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    client_add_peer = true;
    qDebug() << curClienttext << " " << curRowtext;
    if (curClienttext == loca_c_idx[curRowtext]) {
        curidx = loca_c.indexOf(curClienttext);
        Client_Form::getInstance(this)->exec();
        return;
    } else {
        int idx = loca_client[curClienttext].first.indexOf(curRowtext);
        if (idx != -1) {
#ifdef NDEBUG
            qDebug() << "this text in loca_c_telemetry";
#endif
            curidx = idx;
            Client_Telemetry_Form::getInstance(this)->exec();
            return;
        }

        idx = loca_client[curClienttext].second.indexOf(curRowtext);
        if (idx != -1) {
#ifdef NDEBUG
            qDebug() << "this text in loca_c_telesignal";
#endif
            curidx = idx;
            Client_Telesigna_Form::getInstance(this)->exec();
            return;
        }
    }
}

void MainWindow::clientForm_add_son() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    client_add_son = true;
    int idx = loca_c.indexOf(loca_c_idx[curRowtext]);
    if (idx != -1) {
#ifdef NDEBUG
        qDebug() << "this text in loca_c";
#endif
        curidx = idx;
        Client_CheckForm::getInstance(this)->exec();
        return;
    }

    idx = loca_c_telemetry.indexOf(curRowtext);
    if (idx != -1) {
#ifdef NDEBUG
        qDebug() << "this text in loca_c_telemetry";
#endif
        curidx = idx;
        QMessageBox::information(this, "添加", "不能给当前节点添加子节点");
        return;
    }

    idx = loca_c_telesignal.indexOf(curRowtext);
    if (idx != -1) {
#ifdef NDEBUG
        qDebug() << "this text in loca_c_telesignal";
#endif
        curidx = idx;
        QMessageBox::information(this, "添加", "不能给当前节点添加子节点");
        return;
    }
}

void MainWindow::check_client_to_ui(QString new_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    if (client_add_son) {
        qDebug() << "add son to client in ui";
        this->add_clientson_to_ui(new_mes);
        client_add_son = false;
        return;
    }

    if (client_add_peer) {
        qDebug() << "add peer to client in ui";
        this->add_clientpeer_to_ui(new_mes);
        client_add_peer = false;
        return;
    }
}

void MainWindow::add_clientpeer_to_ui(QString new_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes.split(',').size();
#endif
    QModelIndexList selectedIndexes = ui->Client->selectionModel()->selectedIndexes();
    if (!selectedIndexes.isEmpty()) {
        QModelIndex selectedIndex = selectedIndexes.first();
        QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(ui->Client->model());
        if (model) {
            QStandardItem* selectedNode = model->itemFromIndex(selectedIndex);
            QStandardItem* parentNode = selectedNode->parent();
            if (parentNode) {
                QStandardItem* newNode = new QStandardItem(new_mes);
                int row = selectedIndex.row();
                parentNode->insertRow(row + 1, newNode);
                bool flag = new_mes.split(',').size() == client_telemetry_Size ? true : false;
                if (flag) {
                    qDebug() << "insert to loca_c_telemetry";
                    //                    loca_c_telemetry.insert(curidx + 1, new_mes);
                    loca_client[curClienttext].first.insert(curidx + 1, new_mes);
                    isSave = false;
                    this->updateWindowTitle();
                    //                    emit add_in_xml_client_telemetry_peer(fpath, new_mes, curRowtext,
                    //                    curClienttext);
                } else {
                    qDebug() << "insert to loca_c_telesignal";
                    //                    loca_c_telesignal.insert(curidx + 1, new_mes);
                    loca_client[curClienttext].second.insert(curidx + 1, new_mes);
                    isSave = false;
                    this->updateWindowTitle();
                    //                    emit add_in_xml_client_telesigna_peer(fpath, new_mes, curRowtext,
                    //                    curClienttext);
                }
            } else {
                if (loca_client.find(new_mes) == loca_client.end()) {
                    QString curmes = this->getLocaidx(new_mes);
                    QStandardItem* newNode = new QStandardItem(curmes);
                    int row = selectedIndex.row();
                    model->insertRow(row + 1, newNode);
                    qDebug() << "insert to loca_c";
                    loca_c.insert(curidx + 1, new_mes);
                    loca_c_idx[curmes] = new_mes;
                    loca_client[new_mes] = {QVector<QString>(), QVector<QString>()};
                    isSave = false;
                    this->updateWindowTitle();
                    //                    emit add_in_xml_client_peer(fpath, new_mes, curRowtext);
                } else {
                    QMessageBox::information(this, "添加", "不能添加信息完全相同的节点");
                }
            }
        } else {
            qDebug() << "model is empty";
        }
    }
}

void MainWindow::add_clientson_to_ui(QString new_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    QModelIndexList selectedIndexes = ui->Client->selectionModel()->selectedIndexes();
    if (!selectedIndexes.isEmpty()) {
        QModelIndex selectedIndex = selectedIndexes.first();
        QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(ui->Client->model());
        if (model) {
            QStandardItem* selectedNode = model->itemFromIndex(selectedIndex);
            QStandardItem* newNode = new QStandardItem(new_mes);
            selectedNode->appendRow(newNode);
            bool flag = new_mes.split(',').size() == client_telemetry_Size ? true : false;
            if (flag) {
                qDebug() << "insert to loca_c_telemetry";
                loca_c_telemetry.push_back(new_mes);
                loca_client[curClienttext].first.push_back(new_mes);
                isSave = false;
                this->updateWindowTitle();
                //                emit add_in_xml_client_son_telemetry(fpath, new_mes, curClienttext);
            } else {
                qDebug() << "insert to loca_c_telesignal";
                loca_c_telesignal.push_back(new_mes);
                loca_client[curClienttext].second.push_back(new_mes);
                isSave = false;
                this->updateWindowTitle();
                //                emit add_in_xml_client_son_telesigna(fpath, new_mes, curClienttext);
            }
        } else {
            qDebug() << "model is empty";
        }
    }
}

void MainWindow::del_client_to_ui() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif

    QModelIndex curindex = ui->Client->currentIndex();
    // 检查是否有效
    if (curindex.isValid()) {
        // 获取当前选定项的模型
        QAbstractItemModel* model = ui->Client->model();
        QString curText = curindex.data().toString();
        int curSize = curText.split(',').size();
#ifdef NDEBUG
        qDebug() << "curText:\t" << curText;
        qDebug() << "curSize:\t" << curSize;
#endif
        if (curSize == Info_Size) {
            /*
             * 首先，使用std::remove()算法将要删除的元素移动到std::vector的末尾，
             * 返回一个指向新的结束位置的迭代器。这个操作不会真正删除元素，只是将要删除的元素移到了末尾。
             * 然后，使用std::vector::erase()函数，传入两个参数：
             * 第一个参数是移动到末尾的元素的起始位置的迭代器（通过std::remove()返回的迭代器），
             * 第二个参数是std::vector的结束位置的迭代器。这个函数将从std::vector中删除位于指定范围内的元素。
             * */
            loca_c.erase(std::remove(loca_c.begin(), loca_c.end(), loca_c_idx[curText]), loca_c.end());
            loca_c_idx.erase(curText);
            loca_client.erase(loca_c_idx[curText]);
            isSave = false;
            this->updateWindowTitle();
            //            emit del_in_xml_client(fpath, curText);
        } else if (curSize == client_telemetry_Size) {
            // 引用获取，避免不必要的复制，以便在原地修改
            auto& t = loca_client[curClienttext].first;
            t.erase(std::remove(t.begin(), t.end(), curText), t.end());
            isSave = false;
            this->updateWindowTitle();
            //            emit del_in_xml_client_telemetry(fpath, curText, curClienttext);
        } else if (curSize == client_telesigna_Size) {
            auto& t = loca_client[curClienttext].second;
            t.erase(std::remove(t.begin(), t.end(), curText), t.end());
            isSave = false;
            this->updateWindowTitle();
            //            emit del_in_xml_client_telesigna(fpath, curText, curClienttext);
        }
        // 删除当前选定项
        model->removeRow(curindex.row(), curindex.parent());
    } else {
        qDebug() << "curidx is not Valid";
        return;
    }
}

void MainWindow::updateWindowTitle() {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << fpath;
#endif
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
