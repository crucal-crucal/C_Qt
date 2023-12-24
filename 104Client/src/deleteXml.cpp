#include "include/deleteXml.h"

#include "include/modifyXml.h"

deleteXml::deleteXml(QObject* parent) : QObject{parent} {}

void deleteXml::delServer(QString filepath, QString del_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << del_mes;
    qDebug() << filepath;
#endif
    QStringList list = del_mes.split(',');
    if (list.size() != server_Size) {
        return qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');
    QString id = t[t.size() - 1];

    t = list.at(1).split(':');
    QString ip = t[t.size() - 1];

    t = list.at(2).split(':');
    QString port = t[t.size() - 1];

    t = list.at(3).split(':');
    QString dataType = t[t.size() - 1];

    t = list.at(4).split(':');
    QString publicAddr = t[t.size() - 1];

    t = list.at(5).split(':');
    QString describe = t[t.size() - 1];

    QString curText = id + ip + port + dataType + publicAddr + describe;

    QFile file(filepath);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "open error";
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "setContent error";
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    qDebug() << "根节点:\t" << root.nodeName();

    QDomElement serverlistelement = root.firstChildElement("serverList");
    QDomNodeList serverNodes = serverlistelement.elementsByTagName("server");

    int idx = modifyXml::find_Server(serverNodes, curText);
    if (idx == -1) {
        return qDebug() << "not find Server", void();
    }

    auto element = serverNodes.at(idx).toElement();
    // 删除 server 节点及其所有子项
    if (!element.isNull()) {
        QDomNodeList childNodes = element.childNodes();
        for (int i = childNodes.size() - 1; i >= 0; i--) {
            QDomNode childNode = childNodes.at(i);
            element.removeChild(childNode);
        }
        // 从父节点中移除 server 节点
        serverlistelement.removeChild(element);
    }

    // 保存修改后的 xml 文档
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning("error:ParserXML->writeOperateXml->file.open\n");
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    doc.save(ts, 4);

    file.close();

    if (ts.status() != QTextStream::Ok) {
        qDebug() << "Error writing XMl to file";
    } else {
        QMessageBox::information(nullptr, "删除", "删除成功");
        qDebug() << "writing to server xml success";
    }
    return;
}

void deleteXml::delServer_Telemetry(QString filepath, QString del_mes, QString old_father) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << del_mes;
    qDebug() << old_father;
    qDebug() << filepath;
#endif
    QStringList list = del_mes.split(',');
    if (list.size() != server_telemetry_Size) {
        return qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');
    QString addr = t[t.size() - 1];

    t = list.at(1).split(':');
    QString coeff = t[t.size() - 1];

    t = list.at(2).split(':');
    QString clientID = t[t.size() - 1];

    t = list.at(3).split(':');
    QString clientTA = t[t.size() - 1];

    t = list.at(4).split(':');
    QString describe = t[t.size() - 1];

    QString curText = addr + coeff + clientID + clientTA + describe;

    QString old_f;
    list = old_father.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

    auto del = [&](QDomElement t) {
        t.parentNode().removeChild(t);
        return t.isNull();
    };

    QFile file(filepath);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "open error";
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "setContent error";
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    qDebug() << "根节点:\t" << root.nodeName();

    QDomElement serverlistelement = root.firstChildElement("serverList");
    QDomNodeList serverNodes = serverlistelement.elementsByTagName("server");

    int idx = modifyXml::find_Server(serverNodes, old_f);
    if (idx == -1) {
        return qDebug() << "not find Server", void();
    }

    auto element = serverNodes.at(idx).toElement();
    QDomNodeList telemetryList = element.elementsByTagName("telemetryList");
    for (int i = 0; i < telemetryList.size(); i++) {
        auto ele = telemetryList.at(i).toElement();
        QDomNodeList teletryNode = ele.elementsByTagName("telemetry");
        for (int j = 0; j < teletryNode.size(); j++) {
            auto t = teletryNode.at(j).toElement();
            if (t.text() == curText) {
                qDebug() << "find in server_telemetry success";
                if (del(t)) {
                    qDebug() << "del server_telemetry success";
                    goto saveFile;
                }
            }
        }
    }

saveFile:
    // 保存修改后的 xml 文档
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning("error:ParserXML->writeOperateXml->file.open\n");
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    doc.save(ts, 4);

    file.close();

    if (ts.status() != QTextStream::Ok) {
        qDebug() << "Error writing XMl to file";
    } else {
        QMessageBox::information(nullptr, "删除", "删除成功");
        qDebug() << "writing to server_telemetry xml success";
    }
    return;
}

void deleteXml::delServer_Telesigna(QString filepath, QString del_mes, QString old_father) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << del_mes;
    qDebug() << old_father;
    qDebug() << filepath;
#endif
    QStringList list = del_mes.split(',');
    if (list.size() != server_telesigna_Size) {
        return qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');
    QString addr = t[t.size() - 1];

    t = list.at(1).split(':');
    QString clientID = t[t.size() - 1];

    t = list.at(2).split(':');
    QString clientTA = t[t.size() - 1];

    t = list.at(3).split(':');
    QString describe = t[t.size() - 1];

    QString curText = addr + clientID + clientTA + describe;

    QString old_f;
    list = old_father.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

    auto del = [&](QDomElement t) {
        t.parentNode().removeChild(t);
        return t.isNull();
    };

    QFile file(filepath);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "open error";
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "setContent error";
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    qDebug() << "根节点:\t" << root.nodeName();

    QDomElement serverlistelement = root.firstChildElement("serverList");
    QDomNodeList serverNodes = serverlistelement.elementsByTagName("server");

    int idx = modifyXml::find_Server(serverNodes, old_f);
    if (idx == -1) {
        return qDebug() << "not find Server", void();
    }

    auto element = serverNodes.at(idx).toElement();
    QDomNodeList telemetryList = element.elementsByTagName("telesignaList");
    for (int i = 0; i < telemetryList.size(); i++) {
        auto ele = telemetryList.at(i).toElement();
        QDomNodeList teletryNode = ele.elementsByTagName("telesigna");
        for (int j = 0; j < teletryNode.size(); j++) {
            auto t = teletryNode.at(j).toElement();
            if (t.text() == curText) {
                qDebug() << "find in server_telesigna success";
                if (del(t)) {
                    qDebug() << "del server_telesigna success";
                    goto saveFile;
                }
            }
        }
    }

saveFile:
    // 保存修改后的 xml 文档
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning("error:ParserXML->writeOperateXml->file.open\n");
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    doc.save(ts, 4);

    file.close();

    if (ts.status() != QTextStream::Ok) {
        qDebug() << "Error writing XMl to file";
    } else {
        QMessageBox::information(nullptr, "删除", "删除成功");
        qDebug() << "writing to server_telesigna xml success";
    }
    return;
}

void deleteXml::delClient(QString filepath, QString del_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << del_mes;
    qDebug() << filepath;
#endif
    QStringList list = del_mes.split(',');
    if (list.size() != client_Size) {
        return qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');
    QString id = t[t.size() - 1];

    t = list.at(1).split(':');
    QString ip = t[t.size() - 1];

    t = list.at(2).split(':');
    QString port = t[t.size() - 1];

    t = list.at(3).split(':');
    QString protocol = t[t.size() - 1];

    t = list.at(4).split(':');
    QString slaveID = t[t.size() - 1];

    t = list.at(5).split(':');
    QString generalCallTime = t[t.size() - 1];

    t = list.at(6).split(':');
    QString describe = t[t.size() - 1];

    QString curText = id + ip + port + protocol + slaveID + generalCallTime + describe;

    QFile file(filepath);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "open error";
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "setContent error";
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    qDebug() << "根节点:\t" << root.nodeName();

    QDomElement clientlistelement = root.firstChildElement("clientList");
    QDomNodeList clientNodes = clientlistelement.elementsByTagName("client");

    int idx = modifyXml::find_Client(clientNodes, curText);
    if (idx == -1) {
        return qDebug() << "not find client", void();
    }

    auto element = clientNodes.at(idx).toElement();
    // 删除 client 节点及其所有子项
    if (!element.isNull()) {
        QDomNodeList childNodes = element.childNodes();
        for (int i = childNodes.size() - 1; i >= 0; i--) {
            QDomNode childNode = childNodes.at(i);
            element.removeChild(childNode);
        }
        // 从父节点中移除 client 节点
        clientlistelement.removeChild(element);
    }

    // 保存修改后的 xml 文档
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning("error:ParserXML->writeOperateXml->file.open\n");
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    doc.save(ts, 4);

    file.close();

    if (ts.status() != QTextStream::Ok) {
        qDebug() << "Error writing XMl to file";
    } else {
        QMessageBox::information(nullptr, "删除", "删除成功");
        qDebug() << "writing to client xml success";
    }
    return;
}

void deleteXml::delClient_Telemetry(QString filepath, QString del_mes, QString old_father) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << del_mes;
    qDebug() << old_father;
    qDebug() << filepath;
#endif
    QStringList list = del_mes.split(',');
    if (list.size() != client_telemetry_Size) {
        return qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');
    QString addr = t[t.size() - 1];

    t = list.at(1).split(':');
    QString inputFlag = t[t.size() - 1];

    t = list.at(2).split(':');
    QString dataType = t[t.size() - 1];

    t = list.at(3).split(':');
    QString describe = t[t.size() - 1];

    QString curText = addr + inputFlag + dataType + describe;

    QString old_f;
    list = old_father.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

    auto del = [&](QDomElement t) {
        t.parentNode().removeChild(t);
        return t.isNull();
    };

    QFile file(filepath);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "open error";
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "setContent error";
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    qDebug() << "根节点:\t" << root.nodeName();

    QDomElement clientlistelement = root.firstChildElement("clientList");
    QDomNodeList clientNodes = clientlistelement.elementsByTagName("client");

    int idx = modifyXml::find_Client(clientNodes, old_f);
    if (idx == -1) {
        return qDebug() << "not find Client", void();
    }

    auto element = clientNodes.at(idx).toElement();
    QDomNodeList telemetryList = element.elementsByTagName("telemetryList");
    for (int i = 0; i < telemetryList.size(); i++) {
        auto ele = telemetryList.at(i).toElement();
        QDomNodeList teletryNode = ele.elementsByTagName("telemetry");
        for (int j = 0; j < teletryNode.size(); j++) {
            auto t = teletryNode.at(j).toElement();
            if (t.text() == curText) {
                qDebug() << "find in client_telemetry success";
                if (del(t)) {
                    qDebug() << "del client_telemetry success";
                    goto saveFile;
                }
            }
        }
    }

saveFile:
    // 保存修改后的 xml 文档
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning("error:ParserXML->writeOperateXml->file.open\n");
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    doc.save(ts, 4);

    file.close();

    if (ts.status() != QTextStream::Ok) {
        qDebug() << "Error writing XMl to file";
    } else {
        QMessageBox::information(nullptr, "删除", "删除成功");
        qDebug() << "writing to client_telemetry xml success";
    }
    return;
}

void deleteXml::delClient_Telesigna(QString filepath, QString del_mes, QString old_father) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << del_mes;
    qDebug() << filepath;
#endif
    QStringList list = del_mes.split(',');
    if (list.size() != client_telesigna_Size) {
        qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');
    QString addr = t[t.size() - 1];

    t = list.at(1).split(':');
    QString inputFlag = t[t.size() - 1];

    t = list.at(2).split(':');
    QString describe = t[t.size() - 1];

    QString curText = addr + inputFlag + describe;

    QString old_f;
    list = old_father.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

    auto del = [&](QDomElement t) {
        t.parentNode().removeChild(t);
        return t.isNull();
    };

    QFile file(filepath);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "open error";
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "setContent error";
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    qDebug() << "根节点:\t" << root.nodeName();

    QDomElement clientlistelement = root.firstChildElement("clientList");
    QDomNodeList clientNodes = clientlistelement.elementsByTagName("client");

    int idx = modifyXml::find_Client(clientNodes, old_f);
    if (idx == -1) {
        return qDebug() << "not find Client", void();
    }

    auto element = clientNodes.at(idx).toElement();
    QDomNodeList telemetryList = element.elementsByTagName("telesignaList");
    for (int i = 0; i < telemetryList.size(); i++) {
        auto ele = telemetryList.at(i).toElement();
        QDomNodeList teletryNode = ele.elementsByTagName("telesigna");
        for (int j = 0; j < teletryNode.size(); j++) {
            auto t = teletryNode.at(j).toElement();
            if (t.text() == curText) {
                qDebug() << "find in client_telesigna success";
                if (del(t)) {
                    qDebug() << "del client_telesigna success";
                    goto saveFile;
                }
            }
        }
    }

saveFile:
    // 保存修改后的 xml 文档
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning("error:ParserXML->writeOperateXml->file.open\n");
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    doc.save(ts, 4);

    file.close();

    if (ts.status() != QTextStream::Ok) {
        qDebug() << "Error writing XMl to file";
    } else {
        QMessageBox::information(nullptr, "删除", "删除成功");
        qDebug() << "writing to client_telesigna xml success";
    }
    return;
}
