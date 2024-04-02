#ifndef SAVEXML_H
#define SAVEXML_H
// #define NDEBUG

#include <QApplication>
#include <QDebug>
#include <QDomDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Src/include/config.h"

const int server_Size = 6, server_telemetry_Size = 5, server_telesigna_Size = 4;
const int client_Size = 12, client_telemetry_Size = 4,
          client_telesigna_Size = 3;

class SaveXml : public QObject {
  Q_OBJECT
 public:
  explicit SaveXml(QObject* parent = nullptr);

  QVector<QString> get_names(CFG_SERVER str);
  QVector<QString> get_names(CFG_SERVER_TELEMETRY str);
  QVector<QString> get_names(CFG_SERVER_TELESIGNA str);
  QVector<QString> get_names(CFG_CLIENT str);
  QVector<QString> get_names(CFG_CLIENT_TELEMETRY str);
  QVector<QString> get_names(CFG_CLIENT_TELESIGNA str);
  /*
   @Parameter: Server, Client
   @Change Source: All
  */
  void SaveFile(QString filepath, MAP_CFG_SERVER ui_Server,
                MAP_CFG_SERVER_TELEMETRY ui_ServerTelemetry,
                MAP_CFG_SERVER_TELESIGNA ui_ServerTelesigna,
                MAP_CFG_CLIENT ui_Client,
                MAP_CFG_CLIENT_TELEMETRY ui_ClientTelemetry,
                MAP_CFG_CLIENT_TELESIGNA ui_ClientTelesigna);
};

#endif  // SAVEXML_H
