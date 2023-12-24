#ifndef MODIFYXML_H
#define MODIFYXML_H
#define NDEBUG

#include <QDebug>
#include <QDomDocument>
#include <QFileDialog>
#include <QObject>

const int server_Size = 6, server_telemetry_Size = 5, server_telesigna_Size = 4;
const int client_Size = 7, client_telemetry_Size = 4, client_telesigna_Size = 3;
const int Info_Size = 1;

class modifyXml : public QObject {
    Q_OBJECT
  public:
    explicit modifyXml(QObject* parent = nullptr);

    /*
     @Parameters: findList, old_ms
     @Change Source: Server
    */
    static int find_Server(QDomNodeList Nodes, QString old_f);
    /*
     @Parameters: filepath, new_ms, old_ms
     @Change Source: Server
    */
    void modifyServer(QString filepath, QString new_mes, QString old_mes);
    /*
     @Parameters: filepath, new_ms, old_ms, old_father
     @Change Source: Server_Telemetry
    */
    void modifyServer_Telemetry(QString filepath, QString new_mes, QString old_mes, QString old_server);
    /*
     @Parameters: filepath, new_ms, old_ms, old_father
     @Change Source: Server_Telesigna
    */
    void modifyServer_Telesigna(QString filepath, QString new_mes, QString old_mes, QString old_server);

    /*
     @Parameters: findList, old_ms
     @Change Source: Client
    */
    static int find_Client(QDomNodeList Nodes, QString old_f);
    /*
     @Parameters: filepath, new_ms, old_ms
     @Change Source: Client
    */
    void modifyClient(QString filepath, QString new_mes, QString old_mes);
    /*
     @Parameters: filepath, new_ms, old_ms, old_father
     @Change Source: Client_Telemetry
    */
    void modifyClient_Telemetry(QString filepath, QString new_mes, QString old_mes, QString old_client);
    /*
     @Parameters: filepath, new_ms, old_ms, old_father
     @Change Source: Client_Telesigna
    */
    void modifyClient_Telesigna(QString filepath, QString new_mes, QString old_mes, QString old_client);

  private:
    int cnt = 0;
};

#endif  // MODIFYXML_H
