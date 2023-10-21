#ifndef ADDXML_H
#define ADDXML_H

#include <QDebug>
#include <QDomDocument>
#include <QFileDialog>
#include <QObject>

class addXml : public QObject {
    Q_OBJECT
  public:
    explicit addXml(QObject* parent = nullptr);

    /*
     @Parameters: filepath, new_ms, old_ms
     @Add Source: Server
    */
    void addServer_peer(QString filepath, QString new_mes, QString old_mes);
    /*
     @Parameters: filepath, new_ms, old_ms
     @Add Source: Server_Telemetry
    */
    void addServer_Telemetry_peer(QString filepath, QString new_mes, QString old_mes, QString old_server);
    /*
     @Parameters: filepath, new_ms, old_ms
     @Add Source: Server_Telesigna
    */
    void addServer_Telesigna_peer(QString filepath, QString new_mes, QString old_mes, QString old_server);
    /*
     @Parameters: filepath, new_ms, old_ms
     @Add Source: Server
    */
    void addServer_son_Telemetry(QString filepath, QString new_mes, QString old_mes);
    /*
     @Parameters: filepath, new_ms, old_ms
     @Add Source: Server
    */
    void addServer_son_Telesigna(QString filepath, QString new_mes, QString old_mes);

    /*
     @Parameters: filepath, new_ms, old_ms
     @Add Source: Server
    */
    void addClient_peer(QString filepath, QString new_mes, QString old_mes);
    /*
     @Parameters: filepath, new_ms, old_ms
     @Add Source: Server_Telemetry
    */
    void addClient_Telemetry_peer(QString filepath, QString new_mes, QString old_mes, QString old_client);
    /*
     @Parameters: filepath, new_ms, old_ms
     @Add Source: Server_Telesigna
    */
    void addClient_Telesigna_peer(QString filepath, QString new_mes, QString old_mes, QString old_client);
    /*
     @Parameters: filepath, new_ms, old_ms
     @Add Source: Server
    */
    void addClient_son_Telemetry(QString filepath, QString new_mes, QString old_mes);
    /*
     @Parameters: filepath, new_ms, old_ms
     @Add Source: Server
    */
    void addClient_son_Telesigna(QString filepath, QString new_mes, QString old_mes);
};

#endif  // ADDXML_H
