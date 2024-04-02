#include "include/readXml.h"

readXml::readXml(QObject* parent) : QObject{parent} {}

bool readXml::compareVersions(const QString& version1, const QString& version2) {
    QStringList parts1 = version1.split('.');
    QStringList parts2 = version2.split('.');

    for (int i = 0; i < std::max(parts1.size(), parts2.size()); ++i) {
        int part1 = (i < parts1.size()) ? parts1[i].toInt() : 0;
        int part2 = (i < parts2.size()) ? parts2[i].toInt() : 0;

        if (part1 > part2)
            return false;
        else if (part1 < part2)
            return true;
    }

    return true;  // 版本号相等
}

void readXml::openFile(const QString filepath) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    QFile file(filepath);
    if (!file.exists()) {
        qDebug() << "xml 文件不存在!";
        return;
    }

    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(nullptr, "打开文件", "打开文件失败");
        return;
    }

    QDomDocument doc;
    doc.setContent(&file);

    QDomElement root = doc.documentElement();
    qDebug() << "根节点:\t" << root.nodeName();
    readServer(root);
    readClient(root);

    qDebug() << "read success";
    server.clear(), client.clear();

    file.close();
}

void readXml::readServer(QDomElement root) {
    QDomElement serverlistelement = root.firstChildElement("serverList");

    QDomNodeList serverNodes = serverlistelement.elementsByTagName("server");
    //    qDebug() << serverNodes.size();
    for (int i = 0; i < serverNodes.size(); i++) {
        auto element = serverNodes.at(i).toElement();
        QString id, ip, port, dataType, publicAddr, describe;
        if (compareVersions(VERSION, "1.0.0")) {
            id = "服务端ID:" + element.firstChildElement("id").text() + ",";
            ip = "服务端IP:" + element.firstChildElement("ip").text() + ",";
            port = "服务端端口:" + element.firstChildElement("port").text() + ",";
            dataType = "数据类型:" + element.firstChildElement("dataType").text() + ",";
            publicAddr = "公共地址:" + element.firstChildElement("publicAddr").text() + ",";
            describe = "描述:" + element.firstChildElement("describe").text();
        } else {
            id = element.firstChildElement("id").text() + ":";
            ip = element.firstChildElement("ip").text() + ":";
            port = element.firstChildElement("port").text() + ":";
            dataType = element.firstChildElement("dataType").text() + ":";
            publicAddr = element.firstChildElement("publicAddr").text() + ":";
            describe = element.firstChildElement("describe").text();
        }
#ifdef NDEBUG
        qDebug() << id;
        qDebug() << ip;
        qDebug() << port;
        qDebug() << dataType;
        qDebug() << publicAddr;
        qDebug() << describe;
#endif
        QString t = id + ip + port + dataType + publicAddr + describe;
        server[t] = {QVector<QString>(), QVector<QString>()};
        readtelemetryList_Server(element, t);
    }

    emit server_itemname(server);
}

void readXml::readtelemetryList_Server(QDomElement element, QString t) {
    QDomNodeList telemetryList = element.elementsByTagName("telemetryList");
    for (int i = 0; i < telemetryList.size(); i++) {
        auto ele = telemetryList.at(i).toElement();
        QDomNodeList telemetryNode = ele.elementsByTagName("telemetry");
        for (int j = 0; j < telemetryNode.size(); j++) {
            auto t = telemetryNode.at(j).toElement();
            QString addr = "遥测地址:" + t.firstChildElement("addr").text() + ",";
            QString coeff = "系数:" + t.firstChildElement("coeff").text() + ",";
            QString clientID = "对应客户端ID:" + t.firstChildElement("clientID").text() + ",";
            QString clientTelemetryAddr =
                "对应客户端遥测地址:" + t.firstChildElement("clientTelemetryAddr").text() + ",";
            QString describe = "描述:" + t.firstChildElement("describe").text();
#ifdef NDEBUG
            qDebug() << addr;
            qDebug() << coeff;
            qDebug() << clientID;
            qDebug() << clientTelemetryAddr;
            qDebug() << describe;
#endif
            server_telemetryList.append(addr + coeff + clientID + clientTelemetryAddr + describe);
        }
        readtelesignaList_Server(element, t);
    }
}

void readXml::readtelesignaList_Server(QDomElement element, QString t) {
    QDomNodeList telesignaList = element.elementsByTagName("telesignaList");
    for (int i = 0; i < telesignaList.size(); i++) {
        auto ele = telesignaList.at(i).toElement();
        QDomNodeList telesignaNode = ele.elementsByTagName("telesigna");
        for (int j = 0; j < telesignaNode.size(); j++) {
            auto t = telesignaNode.at(j).toElement();
            QString addr = "遥信地址:" + t.firstChildElement("addr").text() + ",";
            QString clientID = "对应客户端ID:" + t.firstChildElement("clientID").text() + ",";
            QString clientTelesignaAddr = "对应客户端遥信ID:" + t.firstChildElement("clientTelesignaAddr").text() + ",";
            QString describe = "描述:" + t.firstChildElement("describe").text();
#ifdef NDEBUG
            qDebug() << addr;
            qDebug() << clientID;
            qDebug() << clientTelesignaAddr;
            qDebug() << describe;
#endif
            server_telesignaList.append(addr + clientID + clientTelesignaAddr + describe);
        }
    }

    server[t] = {server_telemetryList, server_telesignaList};
    server_telemetryList.clear();
    server_telesignaList.clear();
}

void readXml::readClient(QDomElement root) {
    QDomElement clientlistelement = root.firstChildElement("clientList");

    QDomNodeList clientNodes = clientlistelement.elementsByTagName("client");
    for (int i = 0; i < clientNodes.size(); i++) {
        auto element = clientNodes.at(i).toElement();
        QString id, ip, port, protocol, slaveID, generalCallTime, describe;
        if (compareVersions(VERSION, "1.0.0")) {
            id = "客户端ID:" + element.firstChildElement("id").text() + ",";
            ip = "客户端IP:" + element.firstChildElement("ip").text() + ",";
            port = "客户端端口:" + element.firstChildElement("port").text() + ",";
            protocol = "客户端协议:" + element.firstChildElement("protocol").text() + ",";
            slaveID = "slaveID:" + element.firstChildElement("slaveID").text() + ",";
            generalCallTime = "总召间隔时长（单位：秒）:" + element.firstChildElement("generalCallTime").text() + ",";
            describe = "描述:" + element.firstChildElement("describe").text();
        } else {
            id = element.firstChildElement("id").text() + ":";
            ip = element.firstChildElement("ip").text() + ":";
            port = element.firstChildElement("port").text() + ":";
            protocol = element.firstChildElement("protocol").text() + ":";
            slaveID = element.firstChildElement("slaveID").text() + ":";
            generalCallTime = element.firstChildElement("generalCallTime").text() + ":";
            describe = element.firstChildElement("describe").text();
        }

#ifdef NDEBUG
        qDebug() << id;
        qDebug() << ip;
        qDebug() << port;
        qDebug() << protocol;
        qDebug() << slaveID;
        qDebug() << generalCallTime;
        qDebug() << describe;
#endif
        QString t = id + ip + port + protocol + slaveID + generalCallTime + describe;
        readtelemetryList_Client(element, t);
    }
    emit client_itemname(client);
}

void readXml::readtelemetryList_Client(QDomElement element, QString t) {
    QDomNodeList telemetryList = element.elementsByTagName("telemetryList");
    for (int i = 0; i < telemetryList.size(); i++) {
        auto ele = telemetryList.at(i).toElement();
        QDomNodeList telemetryNode = ele.elementsByTagName("telemetry");
        for (int j = 0; j < telemetryNode.size(); j++) {
            auto t = telemetryNode.at(j).toElement();
            QString addr = "遥测地址:" + t.firstChildElement("addr").text() + ",";
            QString inputFlag = "inputFlag:" + t.firstChildElement("inputFlag").text() + ",";
            QString dataType = "数据类型:" + t.firstChildElement("dataType").text() + ",";
            QString describe = "描述:" + t.firstChildElement("describe").text();
#ifdef NDEBUG
            qDebug() << addr;
            qDebug() << inputFlag;
            qDebug() << dataType;
            qDebug() << describe;
#endif
            client_telemetryList.append(addr + inputFlag + dataType + describe);
        }

        readtelesignaList_Client(element, t);
    }
}

void readXml::readtelesignaList_Client(QDomElement element, QString t) {
    QDomNodeList telesignaList = element.elementsByTagName("telesignaList");
    for (int i = 0; i < telesignaList.size(); i++) {
        auto ele = telesignaList.at(i).toElement();
        QDomNodeList telesignaNode = ele.elementsByTagName("telesigna");
        for (int j = 0; j < telesignaNode.size(); j++) {
            auto t = telesignaNode.at(j).toElement();
            QString addr = "遥信地址:" + t.firstChildElement("addr").text() + ",";
            QString inputFlag = "inputFlag:" + t.firstChildElement("inputFlag").text() + ",";
            QString describe = "描述:" + t.firstChildElement("describe").text();
#ifdef NDEBUG
            qDebug() << addr;
            qDebug() << inputFlag;
            qDebug() << describe;
#endif
            client_telesignaList.append(addr + inputFlag + describe);
        }
        client[t] = {client_telemetryList, client_telesignaList};
        client_telemetryList.clear();
        client_telesignaList.clear();
    }
}
