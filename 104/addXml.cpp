#include "addXml.h"

#include "modifyXml.h"
#include "mainwindow.h"

addXml::addXml(QObject* parent) : QObject{parent} {}

void addXml::addServer_peer(QString filepath, QString new_mes, QString old_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
    qDebug() << old_mes;
    qDebug() << filepath;
#endif
    QStringList list = new_mes.split(',');
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

    QString old;
    list = old_mes.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old += t[t.size() - 1];
    }

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
    int idx = -1;
    for (int i = 0; i < serverNodes.size(); i++) {
        QDomNode childNode = serverNodes.at(i).toElement();
        QString id = childNode.firstChildElement("id").text();
        QString ip = childNode.firstChildElement("ip").text();
        QString port = childNode.firstChildElement("port").text();
        QString dataType = childNode.firstChildElement("dataType").text();
        QString publicAddr = childNode.firstChildElement("publicAddr").text();
        QString describe = childNode.firstChildElement("describe").text();

        QString t = id + ip + port + dataType + publicAddr + describe;
        if (t == old) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        qDebug() << "Invalid insert idx.";
        return;
    }

    // 创建新的 <server> 节点
    QDomElement newServerElement = doc.createElement("server");

    QDomElement idElement = doc.createElement("id");
    QDomText idText = doc.createTextNode(id);
    idElement.appendChild(idText);
    newServerElement.appendChild(idElement);

    QDomElement ipElement = doc.createElement("ip");
    QDomText ipText = doc.createTextNode(ip);
    ipElement.appendChild(ipText);
    newServerElement.appendChild(ipElement);

    QDomElement portElement = doc.createElement("port");
    QDomText portText = doc.createTextNode(port);
    portElement.appendChild(portText);
    newServerElement.appendChild(portElement);

    QDomElement dataTypeElement = doc.createElement("dataType");
    QDomText dataTypeText = doc.createTextNode(dataType);
    dataTypeElement.appendChild(dataTypeText);
    newServerElement.appendChild(dataTypeElement);

    QDomElement publicAddrElement = doc.createElement("publicAddr");
    QDomText publicAddrText = doc.createTextNode(publicAddr);
    publicAddrElement.appendChild(publicAddrText);
    newServerElement.appendChild(publicAddrElement);

    QDomElement describeElement = doc.createElement("describe");
    QDomText describeText = doc.createTextNode(describe);
    describeElement.appendChild(describeText);
    newServerElement.appendChild(describeElement);

    QDomElement telemetryListElement = doc.createElement("telemetryList");
    QDomText telemetryListText = doc.createTextNode("");
    telemetryListElement.appendChild(telemetryListText);
    newServerElement.appendChild(telemetryListElement);

    QDomElement telesignaListElement = doc.createElement("telesignaList");
    QDomText telesignaListText = doc.createTextNode("");
    telesignaListElement.appendChild(telesignaListText);
    newServerElement.appendChild(telesignaListElement);

    // 在指定位置插入新节点
    QDomNode insertBeforeNode = serverNodes.at(idx);
    serverlistelement.insertBefore(newServerElement, insertBeforeNode.nextSibling());

    // 保存修改后的 XML 到文件
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning("error:ParserXML->writeOperateXml->file.open\n");
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    // 保存 XML 内容，缩进 4 个空格
    doc.save(ts, 4);

    file.close();

    if (ts.status() != QTextStream::Ok) {
        qDebug() << "Error writing XMl to file";
    } else {
        qDebug() << "writing to server xml success";
    }
    return;
}

void addXml::addServer_Telemetry_peer(QString filepath, QString new_mes, QString old_mes, QString old_server) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
    qDebug() << old_mes;
    qDebug() << filepath;
#endif
    QStringList list = new_mes.split(',');
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

    QString old_child;
    list = old_mes.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_child += t[t.size() - 1];
    }

    QString old_f;
    list = old_server.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

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
        return qDebug() << "not find server", void();
    }

    auto server_telemetry_ele = serverNodes.at(idx).toElement().firstChildElement("telemetryList");
    QDomNodeList telemetryNode = server_telemetry_ele.elementsByTagName("telemetry");
    for (int i = 0; i < telemetryNode.size(); i++) {
        auto t = telemetryNode.at(i).toElement();
        if (t.text() == old_child) {
            idx = i;
            qDebug() << "find in server_telemetry success";
            break;
        }
    }

    // 创建新的 <telemetry> 节点
    QDomElement newTelemetryElement = doc.createElement("telemetry");
    // 创建子元素并设置其内容
    QDomElement addrElement = doc.createElement("addr");
    QDomText addrText = doc.createTextNode(addr);
    addrElement.appendChild(addrText);
    newTelemetryElement.appendChild(addrElement);

    QDomElement coeffElement = doc.createElement("coeff");
    QDomText coeffText = doc.createTextNode(coeff);
    coeffElement.appendChild(coeffText);
    newTelemetryElement.appendChild(coeffElement);

    QDomElement clientIDElement = doc.createElement("clientID");
    QDomText clientIDText = doc.createTextNode(clientID);
    clientIDElement.appendChild(clientIDText);
    newTelemetryElement.appendChild(clientIDElement);

    QDomElement clientTAElement = doc.createElement("clientTelemetryAddr");
    QDomText clientTAText = doc.createTextNode(clientTA);
    clientTAElement.appendChild(clientTAText);
    newTelemetryElement.appendChild(clientTAElement);

    QDomElement describeElement = doc.createElement("describe");
    QDomText describeText = doc.createTextNode(describe);
    describeElement.appendChild(describeText);
    newTelemetryElement.appendChild(describeElement);

    // 在指定位置插入新节点
    QDomNode insertBeforeNode = telemetryNode.at(idx);
    server_telemetry_ele.insertBefore(newTelemetryElement, insertBeforeNode.nextSibling());

    if (idx == -1) {
        qDebug() << "Invalid insert idx.";
        return;
    }

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
        qDebug() << "writing to server_telemetry xml success";
    }
    return;
}

void addXml::addServer_Telesigna_peer(QString filepath, QString new_mes, QString old_mes, QString old_server) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
    qDebug() << old_mes;
    qDebug() << filepath;
#endif
    QStringList list = new_mes.split(',');
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

    QString old_child;
    list = old_mes.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_child += t[t.size() - 1];
    }

    QString old_f;
    list = old_server.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

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
        return qDebug() << "not find server", void();
    }

    auto server_telesigna_ele = serverNodes.at(idx).toElement().firstChildElement("telesignaList");
    QDomNodeList telesignaNode = server_telesigna_ele.elementsByTagName("telesigna");
    for (int i = 0; i < telesignaNode.size(); i++) {
        auto t = telesignaNode.at(i).toElement();
        if (t.text() == old_child) {
            idx = i;
            qDebug() << "find in server_telesigna success";
            break;
        }
    }

    // 创建新的 <telesigna> 节点
    QDomElement newTelesignalElement = doc.createElement("telesigna");
    // 创建子元素并设置其内容
    QDomElement addrElement = doc.createElement("addr");
    QDomText addrText = doc.createTextNode(addr);
    addrElement.appendChild(addrText);
    newTelesignalElement.appendChild(addrElement);

    QDomElement clientIDElement = doc.createElement("clientID");
    QDomText clientIDText = doc.createTextNode(clientID);
    clientIDElement.appendChild(clientIDText);
    newTelesignalElement.appendChild(clientIDElement);

    QDomElement clientTAElement = doc.createElement("clientTelesignaAddr");
    QDomText clientTAText = doc.createTextNode(clientTA);
    clientTAElement.appendChild(clientTAText);
    newTelesignalElement.appendChild(clientTAElement);

    QDomElement describeElement = doc.createElement("describe");
    QDomText describeText = doc.createTextNode(describe);
    describeElement.appendChild(describeText);
    newTelesignalElement.appendChild(describeElement);

    // 在指定位置插入新节点
    QDomNode insertBeforeNode = telesignaNode.at(idx);
    server_telesigna_ele.insertBefore(newTelesignalElement, insertBeforeNode.nextSibling());

    if (idx == -1) {
        qDebug() << "Invalid insert idx.";
        return;
    }

    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning("error:ParserXML->writeOperateXml->file.open\n");
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    doc.save(ts, 4);

    file.close();

    if (ts.status() != QTextStream::Ok) {
        qDebug() << "Error writing XMl to file";
        return;
    }
    return qDebug() << "writing to server_telesigna xml success", void();
}

void addXml::addServer_son_Telemetry(QString filepath, QString new_mes, QString old_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
    qDebug() << old_mes;
    qDebug() << filepath;
#endif
    QStringList list = new_mes.split(',');
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

    QString old_f;
    list = old_mes.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

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
        return qDebug() << "not find server", void();
    }

    QDomElement tryListElement = serverNodes.at(idx).firstChildElement("telemetryList").toElement();

    // 创建新的 <telemetry> 节点
    QDomElement newTelemetryElement = doc.createElement("telemetry");
    // 创建子元素并设置其内容
    QDomElement addrElement = doc.createElement("addr");
    QDomText addrText = doc.createTextNode(addr);
    addrElement.appendChild(addrText);
    newTelemetryElement.appendChild(addrElement);

    QDomElement coeffElement = doc.createElement("coeff");
    QDomText coeffText = doc.createTextNode(coeff);
    coeffElement.appendChild(coeffText);
    newTelemetryElement.appendChild(coeffElement);

    QDomElement clientIDElement = doc.createElement("clientID");
    QDomText clientIDText = doc.createTextNode(clientID);
    clientIDElement.appendChild(clientIDText);
    newTelemetryElement.appendChild(clientIDElement);

    QDomElement clientTAElement = doc.createElement("clientTelemetryAddr");
    QDomText clientTAText = doc.createTextNode(clientTA);
    clientTAElement.appendChild(clientTAText);
    newTelemetryElement.appendChild(clientTAElement);

    QDomElement describeElement = doc.createElement("describe");
    QDomText describeText = doc.createTextNode(describe);
    describeElement.appendChild(describeText);
    newTelemetryElement.appendChild(describeElement);

    // 在指定位置插入新节点
    idx = tryListElement.childNodes().size();
    QDomNode insertBeforeNode = tryListElement.childNodes().at(idx);
    tryListElement.insertBefore(newTelemetryElement, insertBeforeNode);

    if (idx == -1) {
        qDebug() << "Invalid insert idx.";
        return;
    }

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
        qDebug() << "writing to server_telemetry xml success";
    }
    return;
}

void addXml::addServer_son_Telesigna(QString filepath, QString new_mes, QString old_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
    qDebug() << old_mes;
    qDebug() << filepath;
#endif
    QStringList list = new_mes.split(',');
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

    QString old_f;
    list = old_mes.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

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
        return qDebug() << "not find server", void();
    }

    QDomElement tryListElement = serverNodes.at(idx).firstChildElement("telesignaList").toElement();

    // 创建新的 <telemetry> 节点
    QDomElement newTelemetryElement = doc.createElement("telesigna");
    // 创建子元素并设置其内容
    QDomElement addrElement = doc.createElement("addr");
    QDomText addrText = doc.createTextNode(addr);
    addrElement.appendChild(addrText);
    newTelemetryElement.appendChild(addrElement);

    QDomElement clientIDElement = doc.createElement("clientID");
    QDomText clientIDText = doc.createTextNode(clientID);
    clientIDElement.appendChild(clientIDText);
    newTelemetryElement.appendChild(clientIDElement);

    QDomElement clientTAElement = doc.createElement("clientTelesignaAddr");
    QDomText clientTAText = doc.createTextNode(clientTA);
    clientTAElement.appendChild(clientTAText);
    newTelemetryElement.appendChild(clientTAElement);

    QDomElement describeElement = doc.createElement("describe");
    QDomText describeText = doc.createTextNode(describe);
    describeElement.appendChild(describeText);
    newTelemetryElement.appendChild(describeElement);

    // 在指定位置插入新节点
    idx = tryListElement.childNodes().size();
    QDomNode insertBeforeNode = tryListElement.childNodes().at(idx);
    tryListElement.insertBefore(newTelemetryElement, insertBeforeNode);

    if (idx == -1) {
        qDebug() << "Invalid insert idx.";
        return;
    }

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
        qDebug() << "writing to server_telesigna xml success";
    }
    return;
}

void addXml::addClient_peer(QString filepath, QString new_mes, QString old_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
    qDebug() << old_mes;
    qDebug() << filepath;
#endif
    QStringList list = new_mes.split(',');
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

    QString old_f;
    list = old_mes.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

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
        return qDebug() << "not find client", void();
    }

    // 创建新的 <client> 节点
    QDomElement newClientElement = doc.createElement("client");

    QDomElement idElement = doc.createElement("id");
    QDomText idText = doc.createTextNode(id);
    idElement.appendChild(idText);
    newClientElement.appendChild(idElement);

    QDomElement ipElement = doc.createElement("ip");
    QDomText ipText = doc.createTextNode(ip);
    ipElement.appendChild(ipText);
    newClientElement.appendChild(ipElement);

    QDomElement portElement = doc.createElement("port");
    QDomText portText = doc.createTextNode(port);
    portElement.appendChild(portText);
    newClientElement.appendChild(portElement);

    QDomElement protocolElement = doc.createElement("protocol");
    QDomText protocolText = doc.createTextNode(protocol);
    protocolElement.appendChild(protocolText);
    newClientElement.appendChild(protocolElement);

    QDomElement slaveIDElement = doc.createElement("slaveID");
    QDomText slaveIDText = doc.createTextNode(slaveID);
    slaveIDElement.appendChild(slaveIDText);
    newClientElement.appendChild(slaveIDElement);

    QDomElement generalCallTimeElement = doc.createElement("generalCallTime");
    QDomText generalCallTimeText = doc.createTextNode(generalCallTime);
    generalCallTimeElement.appendChild(generalCallTimeText);
    newClientElement.appendChild(generalCallTimeElement);

    QDomElement describeElement = doc.createElement("describe");
    QDomText describeText = doc.createTextNode(describe);
    describeElement.appendChild(describeText);
    newClientElement.appendChild(describeElement);

    QDomElement telemetryListElement = doc.createElement("telemetryList");
    QDomText telemetryListText = doc.createTextNode("");
    telemetryListElement.appendChild(telemetryListText);
    newClientElement.appendChild(telemetryListElement);

    QDomElement telesignaListElement = doc.createElement("telesignaList");
    QDomText telesignaListText = doc.createTextNode("");
    telesignaListElement.appendChild(telesignaListText);
    newClientElement.appendChild(telesignaListElement);

    // 在指定位置插入新节点
    QDomNode insertBeforeNode = clientNodes.at(idx);
    clientlistelement.insertBefore(newClientElement, insertBeforeNode.nextSibling());

    // 保存修改后的 XML 到文件
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        qWarning("error:ParserXML->writeOperateXml->file.open\n");
    }

    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    // 保存 XML 内容，缩进 4 个空格
    doc.save(ts, 4);

    file.close();

    if (ts.status() != QTextStream::Ok) {
        qDebug() << "Error writing XMl to file";
    } else {
        qDebug() << "writing to client xml success";
    }
    return;
}

void addXml::addClient_Telemetry_peer(QString filepath, QString new_mes, QString old_mes, QString old_client) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
    qDebug() << old_mes;
    qDebug() << filepath;
#endif
    QStringList list = new_mes.split(',');
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

    QString old_child;
    list = old_mes.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_child += t[t.size() - 1];
    }

    QString old_f;
    list = old_client.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

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
        return qDebug() << "not find client", void();
    }

    auto client_telemetry_ele = clientNodes.at(idx).toElement().firstChildElement("telemetryList");
    QDomNodeList telemetryNode = client_telemetry_ele.elementsByTagName("telemetry");
    for (int i = 0; i < telemetryNode.size(); i++) {
        auto t = telemetryNode.at(i).toElement();
        if (t.text() == old_child) {
            idx = i;
            qDebug() << "find in client_telemetry success";
            break;
        }
    }

    // 创建新的 <telemetry> 节点
    QDomElement newTelemetryElement = doc.createElement("telemetry");
    // 创建子元素并设置其内容
    QDomElement addrElement = doc.createElement("addr");
    QDomText addrText = doc.createTextNode(addr);
    addrElement.appendChild(addrText);
    newTelemetryElement.appendChild(addrElement);

    QDomElement inputFlagElement = doc.createElement("inputFlag");
    QDomText inputFlagText = doc.createTextNode(inputFlag);
    inputFlagElement.appendChild(inputFlagText);
    newTelemetryElement.appendChild(inputFlagElement);

    QDomElement dataTypeElement = doc.createElement("dataType");
    QDomText dataTypeText = doc.createTextNode(dataType);
    dataTypeElement.appendChild(dataTypeText);
    newTelemetryElement.appendChild(dataTypeElement);

    QDomElement describeElement = doc.createElement("describe");
    QDomText describeText = doc.createTextNode(describe);
    describeElement.appendChild(describeText);
    newTelemetryElement.appendChild(describeElement);

    // 在指定位置插入新节点
    QDomNode insertBeforeNode = telemetryNode.at(idx);
    client_telemetry_ele.insertBefore(newTelemetryElement, insertBeforeNode.nextSibling());

    if (idx == -1) {
        qDebug() << "Invalid insert idx.";
        return;
    }

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
        qDebug() << "writing to client_telemetry xml success";
    }
    return;
}

void addXml::addClient_Telesigna_peer(QString filepath, QString new_mes, QString old_mes, QString old_client) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
    qDebug() << old_mes;
    qDebug() << filepath;
#endif
    QStringList list = new_mes.split(',');
    if (list.size() != client_telesigna_Size) {
        return qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');
    QString addr = t[t.size() - 1];

    t = list.at(1).split(':');
    QString inputFlag = t[t.size() - 1];

    t = list.at(2).split(':');
    QString describe = t[t.size() - 1];

    QString old_child;
    list = old_mes.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_child += t[t.size() - 1];
    }

    QString old_f;
    list = old_client.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

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
        return qDebug() << "not find client", void();
    }

    auto client_telemetry_ele = clientNodes.at(idx).toElement().firstChildElement("telesignaList");
    QDomNodeList telemetryNode = client_telemetry_ele.elementsByTagName("telesigna");
    for (int i = 0; i < telemetryNode.size(); i++) {
        auto t = telemetryNode.at(i).toElement();
        if (t.text() == old_child) {
            idx = i;
            qDebug() << "find in client_telesigna success";
            break;
        }
    }

    // 创建新的 <telemetry> 节点
    QDomElement newTelemetryElement = doc.createElement("telemetry");
    // 创建子元素并设置其内容
    QDomElement addrElement = doc.createElement("addr");
    QDomText addrText = doc.createTextNode(addr);
    addrElement.appendChild(addrText);
    newTelemetryElement.appendChild(addrElement);

    QDomElement inputFlagElement = doc.createElement("inputFlag");
    QDomText inputFlagText = doc.createTextNode(inputFlag);
    inputFlagElement.appendChild(inputFlagText);
    newTelemetryElement.appendChild(inputFlagElement);

    QDomElement describeElement = doc.createElement("describe");
    QDomText describeText = doc.createTextNode(describe);
    describeElement.appendChild(describeText);
    newTelemetryElement.appendChild(describeElement);

    // 在指定位置插入新节点
    QDomNode insertBeforeNode = telemetryNode.at(idx);
    client_telemetry_ele.insertBefore(newTelemetryElement, insertBeforeNode.nextSibling());

    if (idx == -1) {
        qDebug() << "Invalid insert idx.";
        return;
    }

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
        qDebug() << "writing to client_telesigna xml success";
    }
    return;
}

void addXml::addClient_son_Telemetry(QString filepath, QString new_mes, QString old_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
    qDebug() << old_mes;
    qDebug() << filepath;
#endif
    QStringList list = new_mes.split(',');
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

    QString old_f;
    list = old_mes.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

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
        return qDebug() << "not find client", void();
    }

    QDomElement tryListElement = clientNodes.at(idx).firstChildElement("telemetryList").toElement();

    // 创建新的 <telemetry> 节点
    QDomElement newTelemetryElement = doc.createElement("telemetry");
    // 创建子元素并设置其内容
    QDomElement addrElement = doc.createElement("addr");
    QDomText addrText = doc.createTextNode(addr);
    addrElement.appendChild(addrText);
    newTelemetryElement.appendChild(addrElement);

    QDomElement inputFlagElement = doc.createElement("inputFlag");
    QDomText inputFlagText = doc.createTextNode(inputFlag);
    inputFlagElement.appendChild(inputFlagText);
    newTelemetryElement.appendChild(inputFlagElement);

    QDomElement dataTypeElement = doc.createElement("dataType");
    QDomText dataTypeText = doc.createTextNode(dataType);
    dataTypeElement.appendChild(dataTypeText);
    newTelemetryElement.appendChild(dataTypeElement);

    QDomElement describeElement = doc.createElement("describe");
    QDomText describeText = doc.createTextNode(describe);
    describeElement.appendChild(describeText);
    newTelemetryElement.appendChild(describeElement);

    // 在指定位置插入新节点
    idx = tryListElement.childNodes().size();
    QDomNode insertBeforeNode = tryListElement.childNodes().at(idx);
    tryListElement.insertBefore(newTelemetryElement, insertBeforeNode);

    if (idx == -1) {
        qDebug() << "Invalid insert idx.";
        return;
    }

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
        qDebug() << "writing to client_telemetry xml success";
    }
    return;
}

void addXml::addClient_son_Telesigna(QString filepath, QString new_mes, QString old_mes) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
    qDebug() << old_mes;
    qDebug() << filepath;
#endif
    QStringList list = new_mes.split(',');
    if (list.size() != client_telesigna_Size) {
        return qDebug() << "This new text does not conform to the specification", void();
    }
    QStringList t = list.at(0).split(':');
    QString addr = t[t.size() - 1];

    t = list.at(1).split(':');
    QString inputFlag = t[t.size() - 1];

    t = list.at(2).split(':');
    QString describe = t[t.size() - 1];

    QString old_f;
    list = old_mes.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old_f += t[t.size() - 1];
    }

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
        return qDebug() << "not find client", void();
    }

    QDomElement tryListElement = clientNodes.at(idx).firstChildElement("telesignaList").toElement();

    // 创建新的 <telemetry> 节点
    QDomElement newTelemetryElement = doc.createElement("telesigna");
    // 创建子元素并设置其内容
    QDomElement addrElement = doc.createElement("addr");
    QDomText addrText = doc.createTextNode(addr);
    addrElement.appendChild(addrText);
    newTelemetryElement.appendChild(addrElement);

    QDomElement inputFlagElement = doc.createElement("inputFlag");
    QDomText inputFlagText = doc.createTextNode(inputFlag);
    inputFlagElement.appendChild(inputFlagText);
    newTelemetryElement.appendChild(inputFlagElement);

    QDomElement describeElement = doc.createElement("describe");
    QDomText describeText = doc.createTextNode(describe);
    describeElement.appendChild(describeText);
    newTelemetryElement.appendChild(describeElement);

    // 在指定位置插入新节点
    idx = tryListElement.childNodes().size();
    QDomNode insertBeforeNode = tryListElement.childNodes().at(idx);
    tryListElement.insertBefore(newTelemetryElement, insertBeforeNode);

    if (idx == -1) {
        qDebug() << "Invalid insert idx.";
        return;
    }

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
        qDebug() << "writing to client_telesigna xml success";
    }
    return;
}
