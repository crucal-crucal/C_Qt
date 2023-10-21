#ifndef READXML_H
#define READXML_H
// #define NDEBUG
#define VERSION "1.0.0"

#include <QApplication>
#include <QDebug>
#include <QDomDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <iostream>
#include <unordered_map>

class readXml : public QObject {
    Q_OBJECT
  public:
    explicit readXml(QObject* parent = nullptr);

    // 自定义的版本号比较函数，将版本号字符串转换为数值形式进行比较
    static bool compareVersions(const QString& version1, const QString& version2);

    // 打开 xml 文件
    void openFile(const QString fp);

    /*
     @Parameter: config
     @Change Source: Server
    */
    void readServer(QDomElement root);
    /*
     @Parameter: server.element, server_name
     @Change Source: Server
    */
    void readtelemetryList_Server(QDomElement element, QString t);
    /*
     @Parameter: server.element, server_name
     @Change Source: Server
    */
    void readtelesignaList_Server(QDomElement element, QString t);

    /*
     @Parameter: config
     @Change Source: Client
    */
    void readClient(QDomElement root);
    /*
     @Parameter: client.element, Client_name
     @Change Source: Client
    */
    void readtelemetryList_Client(QDomElement element, QString t);
    /*
     @Parameter: client.element, Client_name
     @Change Source: Client
    */
    void readtelesignaList_Client(QDomElement element, QString t);

  signals:
    /*
     @Parameters: server.id~server.describe(server的各个属性）, server.telemetryList（server的遥测链表）,
     server.telesignaList（server的遥信链表）
     @Read Source: Server
     @Feature：向界面返回 xml 文件的各项信息
    */
    void server_itemname(std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>>);
    /*
    @Parameters: clinet.id~clinet.describe(clinet的各个属性）, clinet.telemetryList（server的遥测链表）,
    clinet.telesignaList（server的遥信链表）
    @Read Source: Client
    @Feature：向界面返回 xml 文件的各项信息
    */
    void client_itemname(std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>>);

  private:
    // 将 xml 里面的信息读取到 哈希表中
    // @Parameter: 每一个 server 的基本信息，当前 server 对应的遥测链表， 当前 server 对应的遥信链表
    // @Parameter: 每一个 client 的基本信息，当前 client 对应的遥测链表， 当前 client 对应的遥信链表
    std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> server, client;
    // 对于每一个独立的 server || client，都应该有一个对应的遥信链表，遥测链表的拷贝，发出信号过后，清除当前列表
    // 以便于剩下的 server || client 使用
    QVector<QString> server_telemetryList, server_telesignaList;
    QVector<QString> client_telemetryList, client_telesignaList;
    QString filepath;
};

#endif  // READXML_H
