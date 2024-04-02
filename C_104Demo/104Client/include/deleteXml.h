#ifndef DELETEXML_H
#define DELETEXML_H

#include <QDebug>
#include <QMessageBox>
#include <QObject>

class deleteXml : public QObject {
    Q_OBJECT
  public:
    explicit deleteXml(QObject* parent = nullptr);
    /*
     @Parameters: filepath, need_del_mes
     @Change Source: Server
    */
    void delServer(QString filepath, QString del_mes);
    /*
     @Parameters: filepath, need_del_mes, old_father
     @Change Source: Server
    */
    void delServer_Telemetry(QString filepath, QString del_mes, QString old_father);
    /*
     @Parameters: filepath, need_del_mes
     @Change Source: Server
    */
    void delServer_Telesigna(QString filepath, QString del_mes, QString old_father);

    /*
     @Parameters: filepath, need_del_mes
     @Change Source: Client
    */
    void delClient(QString filepath, QString del_mes);
    /*
     @Parameters: filepath, need_del_mes, old_father
     @Change Source: Client
    */
    void delClient_Telemetry(QString filepath, QString del_mes, QString old_father);
    /*
     @Parameters: filepath, need_del_mes
     @Change Source: Client
    */
    void delClient_Telesigna(QString filepath, QString del_mes, QString old_father);
};

#endif  // DELETEXML_H
