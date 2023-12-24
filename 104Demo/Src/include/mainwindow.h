#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define FONTSIZE 10

// #define NDEBUG

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFont>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPushButton>
#include <QShortcut>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QTimer>
#include <QVBoxLayout>
#include <iostream>
#include <memory>
#include <set>
#include <unordered_map>

#include "Src/include/config.h"
#include "Src/include/saveXml.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 signals:
  // @Parameter: filepath
  void open(const char* szXmlFileName);
  // @Parameter: curText
  void Server_Info_mes(CFG_SERVER);
  // @Parameter: curText
  void Server_Telemetry_Info_mes(MAP_CFG_CLIENT, MAP_CFG_CLIENT_TELEMETRY,
                                 CFG_SERVER_TELEMETRY);
  // @Parameter: curText
  void Server_Telesigna_Info_mes(MAP_CFG_CLIENT, MAP_CFG_CLIENT_TELESIGNA,
                                 CFG_SERVER_TELESIGNA);
  // @Parameter: curText
  void Client_Info_mes(CFG_CLIENT);
  // @Parameter: curText
  void Client_Telemetry_Info_mes(CFG_CLIENT_TELEMETRY);
  // @Parameter: curText
  void Client_Telesigna_Info_mes(CFG_CLIENT_TELESIGNA);
  // 右键菜单修改，传向子界面
  void modify_Server(CFG_SERVER);
  // 右键菜单修改，传向子界面
  void modify_Client(CFG_CLIENT);
  // @Parameter: Server, Server_Telemetry, Server_Telesigna, Client,
  // Client_Telemetry, Client_Telesigna
  void save_in_xml(MAP_CFG_SERVER, MAP_CFG_SERVER_TELEMETRY,
                   MAP_CFG_SERVER_TELESIGNA, MAP_CFG_CLIENT,
                   MAP_CFG_CLIENT_TELEMETRY, MAP_CFG_CLIENT_TELESIGNA);
  // @Parameter: filepath, Server, Server_Telemetry, Server_Telesigna, Client,
  // Client_Telemetry, Client_Telesigna
  void save_as_in_xml(QString, MAP_CFG_SERVER, MAP_CFG_SERVER_TELEMETRY,
                      MAP_CFG_SERVER_TELESIGNA, MAP_CFG_CLIENT,
                      MAP_CFG_CLIENT_TELEMETRY, MAP_CFG_CLIENT_TELESIGNA);
  // 服务端对应遥测客户端信息
  void client_telemetryInfomation(MAP_CFG_CLIENT, MAP_CFG_CLIENT_TELEMETRY);
  void client_telesignaInfomation(MAP_CFG_CLIENT, MAP_CFG_CLIENT_TELESIGNA);

 private slots:
  // ServerConect
  void serverConnect();
  // ClientConnect
  void clientConnect();
  // 设置快捷键
  void setShortCut();
  // 打开文件
  void act_open();
  // 新建文件
  void new_file();
  // 保存文件
  void save_file();
  // 另存为
  void save_As();
  // 关于
  void btn_about();
  // 帮助按钮
  void help();
  // 其他操作之前是否需要先保存文件
  bool Save_before();
  // 切换页面之前提醒
  void warn_before();
  // 切换页面更改GroupBox
  void onTabChanged(int index);
  // 客户端切换Tab界面
  void tabChangedClient();
  // 服务端切换Tab界面
  void tabChangedServer();

  /********************************************Server**************************************************************/
  // 显示在Property
  void showinServer_Property(QModelIndex idx);
  // 清除 server_ui 上的信息
  void server_clean_ui();
  // 第一次更新 Server 页面上的信息
  void updateServer(MAP_CFG_SERVER ui_Server,
                    MAP_CFG_SERVER_TELEMETRY ui_ServerTelemetry,
                    MAP_CFG_SERVER_TELESIGNA ui_ServerTelesigna);
  // 更新本地 Server 信息以及其子节点指向
  void updateLoca_server(MAP_CFG_SERVER ui_Server,
                         MAP_CFG_SERVER_TELEMETRY ui_ServerTelemetry,
                         MAP_CFG_SERVER_TELESIGNA ui_ServerTelesigna);
  // 更新修改之前信息
  void update_old_s_telemetry(CFG_SERVER_TELEMETRY str);
  void update_old_s_telesigna(CFG_SERVER_TELESIGNA str);
  // 鼠标右键点击，新建一个菜单
  void TreeMenu_Server(const QPoint& pos);
  // 回收修改页面修改的信息，并同步到当前页面
  void modified_server(CFG_SERVER new_mes);
  void modified_server_Telemetry(CFG_SERVER_TELEMETRY new_mes);
  void modified_server_Telesigna(CFG_SERVER_TELESIGNA new_mes);
  // 删除指定信息
  void del_loca_s_telemetry(CFG_SERVER_TELEMETRY t);
  void del_loca_s_telesigna(CFG_SERVER_TELESIGNA t);
  // 删除界面显示
  void serverForm_del();
  // 添加客户端
  void add_Server();
  // 添加遥测
  void add_Server_Telemetry();
  // 添加遥信
  void add_Server_Telesigna();
  // 删除遥测
  void del_Server_Telemetry();
  // 删除遥测
  void del_Server_Telesigna();
  // 打开文件成功，清除本地 server 对应哈希表
  void clearLoca_server();
  // 更新当前索引
  void update_server_id(QModelIndex curindex);
  // 排它处理
  bool exclusive(CFG_SERVER cfg_server);
  bool exclusive(CFG_SERVER_TELEMETRY cfg_telemetry);
  bool exclusive(CFG_SERVER_TELESIGNA cfg_telesigna);

  /*****************************************Client*****************************************************************/
  // 显示在Property
  void showinClient_Property(QModelIndex idx);
  // 清除 client_ui 上的信息
  void client_clean_ui();
  // 更新 Client 页面上的信息
  void updateClient(MAP_CFG_CLIENT ui_Client,
                    MAP_CFG_CLIENT_TELEMETRY ui_ClientTelemetry,
                    MAP_CFG_CLIENT_TELESIGNA ui_ClientTelesigna);
  // 更新本地 Client 信息以及其子节点指向
  void updateLoca_client(MAP_CFG_CLIENT ui_Client,
                         MAP_CFG_CLIENT_TELEMETRY ui_ClientTelemetry,
                         MAP_CFG_CLIENT_TELESIGNA ui_ClientTelesigna);
  // 更新修改之前信息
  void update_old_c_telemetry(CFG_CLIENT_TELEMETRY str);
  void update_old_c_telesigna(CFG_CLIENT_TELESIGNA str);
  // 鼠标右键点击，新建一个菜单
  void TreeMenu_Client(const QPoint& pos);
  // 回收修改页面修改的信息，并同步到当前页面
  void modified_client(CFG_CLIENT new_mes);
  void modified_client_Telemetry(CFG_CLIENT_TELEMETRY new_mes);
  void modified_client_Telesigna(CFG_CLIENT_TELESIGNA new_mes);
  // 删除指定信息
  void del_loca_c_telemetry(CFG_CLIENT_TELEMETRY t);
  void del_loca_c_telesigna(CFG_CLIENT_TELESIGNA t);
  // 删除界面显示
  void clientForm_del();
  // 添加客户端
  void add_Client();
  // 添加遥测
  void add_Client_Telemetry();
  // 添加遥信
  void add_Client_Telesigna();
  // 删除遥测
  void del_Client_Telemetry();
  // 删除遥测
  void del_Client_Telesigna();
  // 打开文件成功，清除本地 client 对应的哈希表
  void clearLoca_client();
  // 更新当前索引
  void update_client_id(QModelIndex curindex);
  // 排它处理
  bool exclusive(CFG_CLIENT cfg_client);
  bool exclusive(CFG_CLIENT_TELEMETRY cfg_telemetry);
  bool exclusive(CFG_CLIENT_TELESIGNA cfg_telesigna);

  /**********************************************************************************************************/
  // 更新下标栏
  void updateWindowTitle();
  // 更新保存标签
  void updateSave(bool bl);

  /*  针对子界面的快捷键保存函数 */
  // Client_Info_Form Save
  void Client_Info_Save();
  // CLient_Telemetry _Info_Form Save
  void Client_Telemetry_Info_Save();
  // Client_Telesigna_Info Save
  void Client_Telesigna_Info_Save();
  // Server_Info_Form Save
  void Server_Info_Save();
  // Server_Telemetry _Info_Form Save
  void Server_Telemetry_Info_Save();
  // Server_Telesigna_Info Save
  void Server_Telesigna_Info_Save();

  // 获取UI页面遥测信息
  QString getTelemetryText(CFG_CLIENT_TELEMETRY t);
  QString getTelemetryText(CFG_SERVER_TELEMETRY t);
  // 获取UI页面遥信信息
  QString getTelesignaText(CFG_CLIENT_TELESIGNA t);
  QString getTelesignaText(CFG_SERVER_TELESIGNA t);

 public:
  // @Parameter：字体大小像素，define
  void init(int num);
  // 更新当前目标信息索引 Server
  static QString getLocaServeridx(CFG_SERVER str);
  // 更新当前目标信息索引 Client
  static std::pair<QString, unsigned int> getLocaClientidx(CFG_CLIENT str);

 private:
  Ui::MainWindow* ui;
  // config
  std::unique_ptr<CConfig> config;
  // 当前项在 UI 上的 text
  QString curRowtext;
  // 当前服务端和客户端对应索引，通过索引对应服务端或者客户端遥信，遥测
  int curServeridx = 0;
  int curClientidx = 0;

  // 信息发送到子界面之前，备份旧数据，以便快速找到更改项
  CFG_SERVER old_server;
  CFG_SERVER_TELEMETRY old_s_telemetry;
  CFG_SERVER_TELESIGNA old_s_telesigna;
  CFG_CLIENT old_client;
  CFG_CLIENT_TELEMETRY old_c_telemetry;
  CFG_CLIENT_TELESIGNA old_c_telesigna;

  // 本地拷贝
  // 将 xml 文件中的信息全部读取到 map 中，界面操作，同步到map，保存使用本地 map
  // 覆盖文件
  // @Parameter: 每一个 client 的基本信息，当前 client 对应的遥测链表， 当前
  // client 对应的遥信链表
  MAP_CFG_CLIENT loca_client;
  // @Parameter: telemetry_name, telesigna_name, client_name
  // 为了方便快速查找每次选中行对应的 father，避免每次遍历所有节点查找
  MAP_CFG_CLIENT_TELEMETRY loca_c_telemetry;
  MAP_CFG_CLIENT_TELESIGNA loca_c_telesigna;
  // @Parameter: 每一个 server 的基本信息，当前 server 对应的遥测链表， 当前
  // server 对应的遥信链表
  MAP_CFG_SERVER loca_server;
  // @Parameter: telemetry_name, telesigna_name, server_name
  // 为了方便快速查找每次选中行对应的 father，避免每次遍历所有节点查找
  MAP_CFG_SERVER_TELEMETRY loca_s_telemetry;
  MAP_CFG_SERVER_TELESIGNA loca_s_telesigna;

  // Key：UI显示内容，Value：Server 对应的索引
  QHash<QString, unsigned int> loca_s_idx;
  // Key：Server 对应索引，方便查找属于哪一个 Server
  // Value：当前索引对应的哈希表，哈希表存储 Key：遥测在 UI
  // 显示内容，Value：遥测信息
  std::unordered_map<unsigned int, QHash<QString, CFG_SERVER_TELEMETRY>>
      loca_s_telemetry_idx;
  std::unordered_map<unsigned int, QHash<QString, CFG_SERVER_TELESIGNA>>
      loca_s_telesigna_idx;

  // Key：UI显示内容，Value：Client 对应的索引
  //  QHash<QString, unsigned int> loca_c_idx;
  QHash<QString, int> loca_c_idx;
  // Key：Server 对应索引，方便查找属于哪一个 Client
  // Value：当前索引对应的哈希表，哈希表存储 Key：遥测在 UI
  // 显示内容，Value：遥测信息
  std::unordered_map<unsigned int, QHash<QString, CFG_CLIENT_TELEMETRY>>
      loca_c_telemetry_idx;
  std::unordered_map<unsigned int, QHash<QString, CFG_CLIENT_TELESIGNA>>
      loca_c_telesigna_idx;

  // 判断是否需要修改
  bool mod_server = false, mod_client = false;
  bool mod_server_Telemetry = false, mod_server_Telesigna = false;
  bool mod_client_Telemetry = true, mod_client_Telesigna = true;
  // 当前文件路径
  QString fpath;
  // ui 界面 TreeView 的 model
  std::shared_ptr<QStandardItemModel> smodel, cmodel;

  /************************************/
  // 右侧界面
  QGroupBox* Property;
  // GroupBox 子界面，用于显示当前选中的详细信息以及修改信息
  QStackedWidget* Property_form;

  // 保存文件组件
  std::unique_ptr<SaveXml> save_xml;

 public:
  // 当前文件是否保存
  static bool isSave;

  // 释放内存
  template <typename T>
  void deleteInstance(T* instance) {
    if (instance) {
      delete instance;
      instance = nullptr;
    }
  }

  // QWidget interface，界面关闭事件
 protected:
  void closeEvent(QCloseEvent* event);
};

#endif  // MAINWINDOW_H
