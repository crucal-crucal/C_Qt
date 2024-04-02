#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define FONTSIZE 10
// #define FORDEBUG

#include <QDebug>
#include <QFile>
#include <QFont>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPushButton>
#include <QStandardItemModel>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <QMenuBar>

#include "include/SaveXml.h"
#include "include/addXml.h"
#include "include/deleteXml.h"
#include "include/modifyXml.h"
#include "include/readXml.h"

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
    void open(QString);

    // @Parameter: filepath, new_ms, old_ms
    void modify_in_xml_server(QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms, old_father
    void modify_in_xml_server_telemetry(QString, QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms, old_father
    void modify_in_xml_server_telesigna(QString, QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms
    void modify_in_xml_client(QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms, old_father
    void modify_in_xml_client_telemetry(QString, QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms, old_father
    void modify_in_xml_client_telesigna(QString, QString, QString, QString);

    // @Parameter: filepath, new_ms, old_ms
    void add_in_xml_server_peer(QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms, old_father
    void add_in_xml_server_telemetry_peer(QString, QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms, old_father
    void add_in_xml_server_telesigna_peer(QString, QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms_server
    void add_in_xml_server_son_telemetry(QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms_server
    void add_in_xml_server_son_telesigna(QString, QString, QString);
    // @Parameter: filepath, del_mes
    void del_in_xml_server(QString, QString);
    // @Parameter: filepath, new_ms, old_ms_server, old_father
    void del_in_xml_server_telemetry(QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms_server, old_father
    void del_in_xml_server_telesigna(QString, QString, QString);
    // @Parameter: curText
    void Server_Info_mes(QString);
    // @Parameter: curText
    void Server_Telemetry_Info_mes(QString);
    // @Parameter: curText
    void Server_Telesigna_Info_mes(QString);

    // @Parameter: filepath, new_ms, old_ms
    void add_in_xml_client_peer(QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms, old_father
    void add_in_xml_client_telemetry_peer(QString, QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms, old_father
    void add_in_xml_client_telesigna_peer(QString, QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms_server
    void add_in_xml_client_son_telemetry(QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms_server
    void add_in_xml_client_son_telesigna(QString, QString, QString);
    // @Parameter: filepath, del_mes
    void del_in_xml_client(QString, QString);
    // @Parameter: filepath, new_ms, old_ms_server, old_father
    void del_in_xml_client_telemetry(QString, QString, QString);
    // @Parameter: filepath, new_ms, old_ms_server, old_father
    void del_in_xml_client_telesigna(QString, QString, QString);
    // @Parameter: curText
    void Client_Info_mes(QString);
    // @Parameter: curText
    void Client_Telemetry_Info_mes(QString);
    // @Parameter: curText
    void Client_Telesigna_Info_mes(QString);

    void save_in_xml(QString, std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> Server,
                     std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> Client);

    // 右键菜单修改，传向子界面
    void modify_Server(QString);
    //    void del_Server(QModelIndex);
    void add_Server();

    // 右键菜单修改，传向子界面
    void modify_Client(QString);
    //    void del_Client(QModelIndex);
    void add_Client();

  private slots:
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

    // 新键文件更新页面
    void new_Update(std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> Server,
                    std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> Client);
    // 清除 server_ui 上的信息
    void server_clean_ui();
    // 第一次更新 Server 页面上的信息
    void updateServer(std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> server);
    // 更新 Server 页面信息到 ui
    void updateServerToui();
    // 更新本地 Server 信息以及其子节点指向
    void updateLoca_server();
    // 鼠标右键点击，新建一个菜单
    void TreeMenu_Server(const QPoint& pos);
    // 修改页面具体显示
    void serverForm_modify();
    // 回收修改页面修改的信息，并同步到当前页面
    void modified_server(QString new_mes);
    // 删除界面显示
    void serverForm_del();
    // 同级节点添加页面具体显示
    void serverForm_add_peer();
    // 展示子节点添加
    void serverForm_add_son();
    // 判断是添加的是子节点还是同级节点
    void check_server_to_ui(QString new_mes);
    // 同级节点添加信息到 ui
    void add_serverpeer_to_ui(QString new_mes);
    // 子节点添加信息到 ui
    void add_serverson_to_ui(QString new_mes);
    // 删除当前节点 ui
    void del_server_to_ui();

    // 显示在Property
    void showinServer_Property(QModelIndex idx);
    // 更新旧的当前项信息
    void showinClient_Property(QModelIndex idx);
    // 更新当前目标信息索引
    QString getLocaidx(QString str);

    // 清除 client_ui 上的信息
    void client_clean_ui();
    // 更新 Client 页面上的信息
    void updateClient(std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> client);
    // 更新 Client 页面信息到 ui
    void updateClientToui();
    // 更新本地 Client 信息以及其子节点指向
    void updateLoca_client();
    // 鼠标右键点击，新建一个菜单
    void TreeMenu_Client(const QPoint& pos);
    // 修改页面具体显示
    void clientForm_modify();
    // 回收修改页面修改的信息，并同步到当前页面
    void modified_client(QString new_mes);
    // 删除界面显示
    void clientForm_del();
    // 同级节点添加页面具体显示
    void clientForm_add_peer();
    // 展示子节点添加
    void clientForm_add_son();
    // 判断是添加的是子节点还是同级节点
    void check_client_to_ui(QString new_mes);
    // 同级节点添加信息到ui
    void add_clientpeer_to_ui(QString new_mes);
    // 子节点添加信息到ui
    void add_clientson_to_ui(QString new_mes);
    // 删除当前节点 ui
    void del_client_to_ui();

    // 更新下标栏
    void updateWindowTitle();

  public:
    // 设置显示字体大小
    // @Parameter：字体大小像素，define
    void setFontSize(int num) const;

  private:
    Ui::MainWindow* ui;
    // 读 xml 对象
    std::shared_ptr<readXml> read_xml;
    //    // Server 基本信息修改界面
    //    Server_Form* server_form;
    //    // Server 遥测链表修改界面
    //    Server_Telemetry_Form* server_telemetry_form;
    //    // Server 遥信链表修改界面
    //    Server_Telesigna_Form* server_telesigna_form;
    //    // Client 基本信息修改界面
    //    Client_Form* client_form;
    //    // Client 遥测链表修改界面
    //    Client_Telemetry_Form* client_telemetry_form;
    //    // Client 遥信链表修改界面
    //    Client_Telesigna_Form* client_telesigna_form;
    // 修改 xml 对象
    std::shared_ptr<modifyXml> modify_xml;
    // 添加 xml 对象
    std::shared_ptr<addXml> add_xml;
    // 删除 xml 对象
    std::shared_ptr<deleteXml> del_xml;
    // 保存 xml 对象
    std::shared_ptr<SaveXml> save_xml;
    // 修改前记录当前项信息，以便在原有 xml 中寻找需要修改的项
    QString old_mes;
    // 当前项信息
    QString curRowtext, curServertext, curClienttext;
    // 本地拷贝，哈希表存储树的结构
    // @Parameter: 每一个 server 的基本信息，当前 server 对应的遥测链表， 当前 server 对应的遥信链表
    std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> loca_server;
    // @Parameter: 每一个 client 的基本信息，当前 client 对应的遥测链表， 当前 client 对应的遥信链表
    std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> loca_client;
    /*
     * 缺陷：当选中的子选项不唯一时，会出现歧义
     */
    // @Parameter: telemetry_name || telesigna_name, client_name
    // 为了方便快速查找每次选中行对应的 father，避免每次遍历所有节点查找
    std::unordered_map<QString, QString> loca_c_telemetry_to_client, loca_c_telesigna_to_client;
    // @Parameter: telemetry_name || telesigna_name, server_name
    // 为了方便快速查找每次选中行对应的 father，避免每次遍历所有节点查找
    std::unordered_map<QString, QString> loca_s_telemetry_to_server, loca_s_telesigna_to_server;
    // 本地当前子树的拷贝
    /*
     * loca_s_idx：当前页面显示对应后台显示
     * loca_s: 当前的 serverList 信息
     * loca_s_telemetry: 当前选中行 server 对应的遥测链表
     * loca_s_telesignal: 当前选中行 server 对应的遥信链表
     */
    std::unordered_map<QString, QString> loca_s_idx;
    QVector<QString> loca_s, loca_s_telemetry, loca_s_telesignal;
    /*
     * loca_c_idx：当前页面显示对应后台显示
     * loca_c: 当前的 clientList 信息
     * loca_c_telemetry: 当前选中行 client 对应的遥测链表
     * loca_c_telesignal: 当前选中行 client 对应的遥信链表
     */
    std::unordered_map<QString, QString> loca_c_idx;
    QVector<QString> loca_c, loca_c_telemetry, loca_c_telesignal;
    // 判断是加入哪种点
    bool server_add_peer = false, server_add_son = false;
    bool client_add_peer = false, client_add_son = false;
    // 判断是否需要在当前loca_list里添加元素
    bool add_to_loca_server = true, add_to_loca_client = true;
    // 当前加入点在本地拷贝中的下标
    int curidx;
    // 当前文件路径
    QString fpath;
    std::shared_ptr<QStandardItemModel> smodel, cmodel;

  public:
    // 当前文件是否保存
    static bool isSave;

    // QWidget interface
  protected:
    void closeEvent(QCloseEvent* event);
};
#endif  // MAINWINDOW_H
