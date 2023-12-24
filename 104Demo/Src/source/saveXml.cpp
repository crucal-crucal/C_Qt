#include "Src/include/SaveXml.h"

SaveXml::SaveXml(QObject* parent) : QObject{parent} {}

QVector<QString> SaveXml::get_names(CFG_SERVER str) {
  QVector<QString> res;
  res.reserve(server_Size);
  res.push_back(QString::number(str.uiServerID));
  res.push_back(QString::fromUtf8(str.szIP));
  res.push_back(QString::number(str.usPort));
  res.push_back(QString::number(str.usDataType));
  res.push_back(QString::number(str.usPublicAddr));
  res.push_back(QString::fromUtf8(str.szDescribe));
  return res;
}

QVector<QString> SaveXml::get_names(CFG_SERVER_TELEMETRY str) {
  QVector<QString> res;
  res.reserve(server_telemetry_Size);
  res.push_back(QString::number(str.uiServerTelemetryAddr));
  res.push_back(QString::number(str.fCoeff));
  res.push_back(QString::number(str.uiClientID));
  res.push_back(QString::number(str.uiClientTelemetryAddr));
  res.push_back(QString::fromUtf8(str.szDescribe));
  return res;
}

QVector<QString> SaveXml::get_names(CFG_SERVER_TELESIGNA str) {
  QVector<QString> res;
  res.reserve(server_telesigna_Size);
  res.push_back(QString::number(str.uiServerTelesignaAddr));
  res.push_back(QString::number(str.uiClientID));
  res.push_back(QString::number(str.uiClientTelesignaAddr));
  res.push_back(QString::fromUtf8(str.szDescribe));
  return res;
}

QVector<QString> SaveXml::get_names(CFG_CLIENT str) {
  if (str.usProtocol == 0) {
    qstrncpy(str.szSerialDevice, "", 16);
  }
  QVector<QString> res;
  res.reserve(client_Size);
  res.push_back(QString::number(str.uiClientID));
  res.push_back(QString::number(str.usProtocol));
  res.push_back(QString::fromUtf8(str.szIP));
  res.push_back(QString::number(str.usPort));
  res.push_back(QString("%1").arg(str.szSerialDevice));
  res.push_back(QString::number(str.iBaud));
  res.push_back(QString::number(str.cParity));
  res.push_back(QString::number(str.iDataBit));
  res.push_back(QString::number(str.iStopBit));
  res.push_back(QString::number(str.usSlaveID));
  res.push_back(QString::number(str.usGeneralCallTime));
  res.push_back(QString::fromUtf8(str.szDescribe));

  return res;
}

QVector<QString> SaveXml::get_names(CFG_CLIENT_TELEMETRY str) {
  QVector<QString> res;
  res.reserve(client_telemetry_Size);
  res.push_back(QString::number(str.uiClientTelemetryAddr));
  res.push_back(QString::number(str.uiInputFlag));
  res.push_back(QString::number(str.uiDataType));
  res.push_back(QString::fromUtf8(str.szDescribe));
  return res;
}

QVector<QString> SaveXml::get_names(CFG_CLIENT_TELESIGNA str) {
  QVector<QString> res;
  res.reserve(client_telesigna_Size);
  res.push_back(QString::number(str.uiClientTelesignaAddr));
  res.push_back(QString::number(str.uiInputFlag));
  res.push_back(QString::fromUtf8(str.szDescribe));
  return res;
}

void SaveXml::SaveFile(QString filepath, MAP_CFG_SERVER ui_Server,
                       MAP_CFG_SERVER_TELEMETRY ui_ServerTelemetry,
                       MAP_CFG_SERVER_TELESIGNA ui_ServerTelesigna,
                       MAP_CFG_CLIENT ui_Client,
                       MAP_CFG_CLIENT_TELEMETRY ui_ClientTelemetry,
                       MAP_CFG_CLIENT_TELESIGNA ui_ClientTelesigna) {
  // 创建 QDomDocument 对象
  QDomDocument doc;

  QDomProcessingInstruction version = doc.createProcessingInstruction(
      "xml", "version=\"1.0\" encoding=\"UTF-8\"");
  doc.appendChild(version);
  // 创建根元素 <config>
  QDomElement configElement = doc.createElement("config");
  doc.appendChild(configElement);

  // 创建 <serverList> 元素
  QDomElement serverListElement = doc.createElement("serverList");
  configElement.appendChild(serverListElement);

  for (const auto& [key, value] : ui_Server) {
    auto sname = get_names(value);
    // 创建 <server> 元素
    QDomElement serverElement = doc.createElement("server");
    serverListElement.appendChild(serverElement);
    QVector<QString> posname{"id",       "ip",         "port",
                             "dataType", "publicAddr", "describe"};
    for (int i = 0; i < sname.size(); i++) {
      QDomElement ele = doc.createElement(posname[i]);
      ele.appendChild(doc.createTextNode(sname[i]));
      serverElement.appendChild(ele);
    }
    // 创建 <telemetryList> 元素
    QDomElement telemetryListElement = doc.createElement("telemetryList");
    serverElement.appendChild(telemetryListElement);
    for (const auto& c : ui_ServerTelemetry[key]) {
      if (c.isEmpty()) {
        continue;
      }
      // 创建 <telemetry> 元素
      QDomElement telemetryElement = doc.createElement("telemetry");
      telemetryListElement.appendChild(telemetryElement);
      posname = {"addr", "coeff", "clientID", "clientTelemetryAddr",
                 "describe"};
      QVector<QString> tname = get_names(c);
      for (int i = 0; i < tname.size(); i++) {
        QDomElement ele = doc.createElement(posname[i]);
        ele.appendChild(doc.createTextNode(tname[i]));
        telemetryElement.appendChild(ele);
      }
    }
    // 创建 <telesignaList> 元素
    QDomElement telesignaListElement = doc.createElement("telesignaList");
    serverElement.appendChild(telesignaListElement);
    for (const auto& c : ui_ServerTelesigna[key]) {
      if (c.isEmpty()) {
        continue;
      }
      // 创建 <telesigna> 元素
      QDomElement telesignaElement = doc.createElement("telesigna");
      telesignaListElement.appendChild(telesignaElement);
      posname = {"addr", "clientID", "clientTelesignaAddr", "describe"};
      QVector<QString> tname = get_names(c);
      for (int i = 0; i < tname.size(); i++) {
        QDomElement ele = doc.createElement(posname[i]);
        ele.appendChild(doc.createTextNode(tname[i]));
        telesignaElement.appendChild(ele);
      }
    }
  }

  // 创建 <clientList> 元素
  QDomElement clientListElement = doc.createElement("clientList");
  configElement.appendChild(clientListElement);
  for (const auto& [key, value] : ui_Client) {
    auto cname = get_names(value);
    // 创建 <client> 元素
    QDomElement clientElement = doc.createElement("client");
    clientListElement.appendChild(clientElement);
    QVector<QString> posname{"id",      "protocol",        "ip",
                             "port",    "serialDevice",    "baud",
                             "parity",  "dataBit",         "stopBit",
                             "slaveID", "generalCallTime", "describe"};
    for (int i = 0; i < cname.size(); i++) {
      QDomElement ele = doc.createElement(posname[i]);
      ele.appendChild(doc.createTextNode(cname[i]));
      clientElement.appendChild(ele);
    }
    // 创建 <telemetryList> 元素
    QDomElement telemetryListElement = doc.createElement("telemetryList");
    clientElement.appendChild(telemetryListElement);
    for (const auto& c : ui_ClientTelemetry[key]) {
      if (c.isEmpty()) {
        continue;
      }
      // 创建 <telemetry> 元素
      QDomElement telemetryElement = doc.createElement("telemetry");
      telemetryListElement.appendChild(telemetryElement);
      posname = {"addr", "inputFlag", "dataType", "describe"};
      QVector<QString> tname = get_names(c);
      for (int i = 0; i < tname.size(); i++) {
        QDomElement ele = doc.createElement(posname[i]);
        ele.appendChild(doc.createTextNode(tname[i]));
        telemetryElement.appendChild(ele);
      }
    }
    // 创建 <telesignaList> 元素
    QDomElement telesignaListElement = doc.createElement("telesignaList");
    clientElement.appendChild(telesignaListElement);
    for (const auto& c : ui_ClientTelesigna[key]) {
      if (c.isEmpty()) {
        continue;
      }
      // 创建 <telesigna> 元素
      QDomElement telesignaElement = doc.createElement("telesigna");
      telesignaListElement.appendChild(telesignaElement);
      posname = {"addr", "inputFlag", "describe"};
      QVector<QString> tname = get_names(c);
      for (int i = 0; i < tname.size(); i++) {
        QDomElement ele = doc.createElement(posname[i]);
        ele.appendChild(doc.createTextNode(tname[i]));
        telesignaElement.appendChild(ele);
      }
    }
  }

  if (filepath.isEmpty()) {
    return qDebug() << "filename is Empty!", void();
  }
  // 创建保存文件的 QFile 对象
  QFile file(filepath);

  // 设置新的文件权限
  if (file.setPermissions(QFile::ReadOther | QFile::WriteOther)) {
    qDebug() << "Read-only attribute removed successfully.";
  } else {
    qDebug() << "Failed to remove read-only attribute.";
  }

  if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
    qDebug() << ("error:ParserXML->writeOperateXml->file.open\n" +
                 file.errorString());
  }

  QTextStream ts(&file);
  ts.setCodec("UTF-8");
  doc.save(ts, 4);

  file.close();

  if (ts.status() != QTextStream::Ok) {
    qDebug() << "Error writing XMl to file";
  } else {
    qDebug() << "writing to xml success";
  }
  return;
}
