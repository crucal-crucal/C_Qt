#include "modifyXml.h"

modifyXml::modifyXml(QObject* parent) : QObject{parent} {}

int modifyXml::find_Server(QDomNodeList Nodes, QString old_f) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    int idx = -1;
    for (int i = 0; i < Nodes.size(); i++) {
        QDomNode childNode = Nodes.at(i).toElement();
        QString id = childNode.firstChildElement("id").text();
        QString ip = childNode.firstChildElement("ip").text();
        QString port = childNode.firstChildElement("port").text();
        QString dataType = childNode.firstChildElement("dataType").text();
        QString publicAddr = childNode.firstChildElement("publicAddr").text();
        QString describe = childNode.firstChildElement("describe").text();

        QString t = id + ip + port + dataType + publicAddr + describe;
        if (t == old_f) {
            qDebug() << "find in server success";
            idx = i;
            break;
        }
    }
    return idx;
}

void modifyXml::modifyServer(QString filepath, QString new_mes, QString old_mes) {
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

    auto replace = [&](QDomElement node) {
        QDomElement t = node.firstChildElement("id");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(id);
            cnt++;
//            qDebug() << "id 更换成功！";
        }
        t = node.firstChildElement("ip");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(ip);
            cnt++;
//            qDebug() << "ip 更换成功！";
        }
        t = node.firstChildElement("port");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(port);
            cnt++;
//            qDebug() << "port 更换成功！";
        }
        t = node.firstChildElement("dataType");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(dataType);
            cnt++;
//            qDebug() << "dataType 更换成功！";
        }
        t = node.firstChildElement("publicAddr");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(publicAddr);
            cnt++;
//            qDebug() << "publicAddr 更换成功！";
        }
        t = node.firstChildElement("describe");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(describe);
            cnt++;
//            qDebug() << "describe 更换成功！";
        }

        return cnt == server_Size;
        /*        // 不读 xml 中的注释
                if (node.nodeName() == "#comment") {
                    return false;
                }

                if (cnt == server_Size) {
                    cnt = 0;
                    return true;
                }
                if (!node.nodeName().compare("id")) {
                    QDomNode oldnode = node.firstChild();
                    node.firstChild().setNodeValue(id);
                    QDomNode newnode = node.firstChild();
                    node.replaceChild(newnode, oldnode);
                    qDebug() << "id 更换成功！";
                    cnt++;
                } else if (!node.nodeName().compare("ip")) {
                    QDomNode oldnode = node.firstChild();
                    node.firstChild().setNodeValue(ip);
                    QDomNode newnode = node.firstChild();
                    node.replaceChild(newnode, oldnode);
                    qDebug() << "ip 更换成功！";
                    cnt++;
                } else if (!node.nodeName().compare("port")) {
                    QDomNode oldnode = node.firstChild();
                    node.firstChild().setNodeValue(port);
                    QDomNode newnode = node.firstChild();
                    node.replaceChild(newnode, oldnode);
                    qDebug() << "port 更换成功！";
                    cnt++;
                } else if (!node.nodeName().compare("dataType")) {
                    QDomNode oldnode = node.firstChild();
                    node.firstChild().setNodeValue(dataType);
                    QDomNode newnode = node.firstChild();
                    node.replaceChild(newnode, oldnode);
                    qDebug() << "dataType 更换成功！";
                    cnt++;
                } else if (!node.nodeName().compare("publicAddr")) {
                    QDomNode oldnode = node.firstChild();
                    node.firstChild().setNodeValue(publicAddr);
                    QDomNode newnode = node.firstChild();
                    node.replaceChild(newnode, oldnode);
                    qDebug() << "publicAddr 更换成功！";
                    cnt++;
                } else if (!node.nodeName().compare("describe")) {
                    QDomNode oldnode = node.firstChild();
                    node.firstChild().setNodeValue(describe);
                    QDomNode newnode = node.firstChild();
                    node.replaceChild(newnode, oldnode);
                    qDebug() << "describe 更换成功！";
                    cnt++;
                }
                return false;*/
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
    bool ok = false;
    for (int i = 0; i < serverNodes.size(); i++) {
        QDomElement childNode = serverNodes.at(i).toElement();
        QString id = childNode.firstChildElement("id").text();
        QString ip = childNode.firstChildElement("ip").text();
        QString port = childNode.firstChildElement("port").text();
        QString dataType = childNode.firstChildElement("dataType").text();
        QString publicAddr = childNode.firstChildElement("publicAddr").text();
        QString describe = childNode.firstChildElement("describe").text();

        QString t = id + ip + port + dataType + publicAddr + describe;
        if (t == old) {
            ok = true;
            qDebug() << "find in server success";
            if (replace(childNode)) {
                qDebug() << "replace server finish";
                goto saveFile;
            }
            //            QDomNodeList nlist = childNode.childNodes();
            //            for (int j = 0; j < nlist.size(); j++) {
            //                auto node = nlist.at(j);
            //                if (replace(node)) {
            //                    qDebug() << "replace server finish!";
            //                    goto saveFile;
            //                }
            //            }
        }
    }

    if (!ok) {
        qDebug() << "not find in server success";
        return;
    }

saveFile:
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
        qDebug() << "writing to server xml success";
    }
    return;
}

void modifyXml::modifyServer_Telemetry(QString filepath, QString new_mes, QString old_mes, QString old_server) {
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

    auto replace = [&](QDomElement node) {
        QDomElement t = node.firstChildElement("addr");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(addr);
            cnt++;
//            qDebug() << "addr 更换成功！";
        }
        t = node.firstChildElement("coeff");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(coeff);
            cnt++;
//            qDebug() << "coeff 更换成功！";
        }
        t = node.firstChildElement("clientID");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(clientID);
            cnt++;
//            qDebug() << "clientID 更换成功！";
        }
        t = node.firstChildElement("clientTelemetryAddr");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(clientTA);
            cnt++;
//            qDebug() << "clientTelemetryAddr 更换成功！";
        }
        t = node.firstChildElement("describe");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(describe);
            cnt++;
//            qDebug() << "describe 更换成功！";
        }

        return cnt == server_telemetry_Size;
        /*
        // 不读 xml 中的注释
        if (node.nodeName() == "#comment") {
            return false;
        }

        if (cnt == server_telemetry_Size) {
            cnt = 0;
            return true;
        }
        if (!node.nodeName().compare("addr")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(addr);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "addr 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("coeff")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(coeff);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "coeff 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("clientID")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(clientID);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "clientID 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("clientTelemetryAddr")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(clientTA);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "clientTelemetryAddr 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("describe")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(describe);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "describe 更换成功！";
            cnt++;
        }
        return false;
*/
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

    int idx = find_Server(serverNodes, old_f);
    if (idx == -1) {
        return qDebug() << "not find Server", void();
    }

    auto element = serverNodes.at(idx).toElement();
    QDomNodeList telemetryList = element.elementsByTagName("telemetryList");
    for (int j = 0; j < telemetryList.size(); j++) {
        auto ele = telemetryList.at(j).toElement();
        QDomNodeList telemetryNode = ele.elementsByTagName("telemetry");
        bool ok = false;
        for (int k = 0; k < telemetryNode.size(); k++) {
            auto t = telemetryNode.at(k).toElement();
            if (t.text() == old_child) {
                ok = true;
                qDebug() << "find in server_telemetry success";
                if (replace(t)) {
                    qDebug() << "replace server_telemetry finish";
                    goto saveFile;
                }
                //                QDomNodeList nlist = t.childNodes();
                //                for (int p = 0; p < nlist.size(); p++) {
                //                    auto node = nlist.at(p);
                //                    if (replace(node)) {
                //                        qDebug() << "replace server_telemetry finish";
                //                        goto saveFile;
                //                    }
                //                }
            }
            if (!ok) {
                qDebug() << "not find in server_telemetry";
                return;
            }
        }
    }

saveFile:
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

void modifyXml::modifyServer_Telesigna(QString filepath, QString new_mes, QString old_mes, QString old_server) {
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

    auto replace = [&](QDomElement node) {
        QDomElement t = node.firstChildElement("addr");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(addr);
            cnt++;
//            qDebug() << "addr 更换成功！";
        }
        t = node.firstChildElement("clientID");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(clientID);
            cnt++;
//            qDebug() << "clientID 更换成功！";
        }
        t = node.firstChildElement("clientTelesignaAddr");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(clientTA);
            cnt++;
//            qDebug() << "clientTelesignaAddr 更换成功！";
        }
        t = node.firstChildElement("describe");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(describe);
            cnt++;
//            qDebug() << "describe 更换成功！";
        }

        return cnt == server_telesigna_Size;
        /*
        // 不读 xml 中的注释
        if (node.nodeName() == "#comment") {
            return false;
        }

        if (cnt == server_telesigna_Size) {
            cnt = 0;
            return true;
        }
        if (!node.nodeName().compare("addr")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(addr);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "addr 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("clientID")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(clientID);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "clientID 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("clientTelesignaAddr")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(clientTA);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "clientTelesignaAddr 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("describe")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(describe);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "describe 更换成功！";
            cnt++;
        }
        return false;
        */
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
    int idx = find_Server(serverNodes, old_f);
    if (idx == -1) {
        return qDebug() << "not find Server", void();
    }

    auto element = serverNodes.at(idx).toElement();
    QDomNodeList telemetryList = element.elementsByTagName("telesignaList");
    for (int j = 0; j < telemetryList.size(); j++) {
        auto ele = telemetryList.at(j).toElement();
        QDomNodeList telemetryNode = ele.elementsByTagName("telesigna");
        bool ok = false;
        for (int k = 0; k < telemetryNode.size(); k++) {
            auto t = telemetryNode.at(k).toElement();
            if (t.text() == old_child) {
                ok = true;
                qDebug() << "find in server_telesigna success";
                if (replace(t)) {
                    qDebug() << "replace server_telesigna finish";
                    goto saveFile;
                }
                //                QDomNodeList nlist = t.childNodes();
                //                for (int p = 0; p < nlist.size(); p++) {
                //                    auto node = nlist.at(p);
                //                    if (replace(node)) {
                //                        qDebug() << "replace server_telesigna finish";
                //                        goto saveFile;
                //                    }
                //                }
            }

            if (!ok) {
                qDebug() << "not find in server_telesigna";
                return;
            }
        }
    }

saveFile:
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

int modifyXml::find_Client(QDomNodeList Nodes, QString old_f) {
    int idx = -1;
    for (int i = 0; i < Nodes.size(); i++) {
        QDomNode childNode = Nodes.at(i).toElement();
        QString id = childNode.firstChildElement("id").text();
        QString ip = childNode.firstChildElement("ip").text();
        QString port = childNode.firstChildElement("port").text();
        QString protocol = childNode.firstChildElement("protocol").text();
        QString slaveID = childNode.firstChildElement("slaveID").text();
        QString generalCallTime = childNode.firstChildElement("generalCallTime").text();
        QString describe = childNode.firstChildElement("describe").text();

        QString t = id + ip + port + protocol + slaveID + generalCallTime + describe;
        if (t == old_f) {
            idx = i;
            qDebug() << "find in client success";
            break;
        }
    }

    return idx;
}

void modifyXml::modifyClient(QString filepath, QString new_mes, QString old_mes) {
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

    QString old;
    list = old_mes.split(',');
    for (int i = 0; i < list.size(); i++) {
        auto t = list.at(i).split(':');
        old += t[t.size() - 1];
    }

    auto replace = [&](QDomElement node) {
        QDomElement t = node.firstChildElement("id");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(id);
            cnt++;
//            qDebug() << "id 更换成功！";
        }
        t = node.firstChildElement("ip");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(ip);
            cnt++;
//            qDebug() << "ip 更换成功！";
        }
        t = node.firstChildElement("port");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(port);
            cnt++;
//            qDebug() << "port 更换成功！";
        }
        t = node.firstChildElement("protocol");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(protocol);
            cnt++;
//            qDebug() << "protocol 更换成功！";
        }
        t = node.firstChildElement("slaveID");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(slaveID);
            cnt++;
//            qDebug() << "slaveID 更换成功！";
        }
        t = node.firstChildElement("generalCallTime");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(generalCallTime);
            cnt++;
//            qDebug() << "generalCallTime 更换成功！";
        }
        t = node.firstChildElement("describe");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(describe);
            cnt++;
//            qDebug() << "describe 更换成功！";
        }

        return cnt == client_Size;
        /*
        // 不读 xml 中的注释
        if (node.nodeName() == "#comment") {
            return false;
        }

        if (cnt == client_Size) {
            cnt = 0;
            return true;
        }
        if (!node.nodeName().compare("id")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(id);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "id 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("ip")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(ip);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "ip 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("port")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(port);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "port 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("protocol")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(protocol);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "protocol 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("slaveID")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(slaveID);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "slaveID 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("generalCallTime")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(generalCallTime);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "generalCallTime 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("describe")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(describe);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "describe 更换成功！";
            cnt++;
        }
        return false;
        */
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
    bool ok = false;
    for (int i = 0; i < clientNodes.size(); i++) {
        QDomElement childNode = clientNodes.at(i).toElement();
        QString id = childNode.firstChildElement("id").text();
        QString ip = childNode.firstChildElement("ip").text();
        QString port = childNode.firstChildElement("port").text();
        QString protocol = childNode.firstChildElement("protocol").text();
        QString slaveID = childNode.firstChildElement("slaveID").text();
        QString generalCallTime = childNode.firstChildElement("generalCallTime").text();
        QString describe = childNode.firstChildElement("describe").text();

        QString t = id + ip + port + protocol + slaveID + generalCallTime + describe;
        if (t == old) {
            ok = true;
            qDebug() << "find in client success";
            if (replace(childNode)) {
                qDebug() << "replace client finish";
                goto saveFile;
            }
            //            QDomNodeList nlist = childNode.childNodes();
            //            for (int j = 0; j < nlist.size(); j++) {
            //                auto node = nlist.at(j);
            //                if (replace(node)) {
            //                    qDebug() << "replace client finish";
            //                    goto saveFile;
            //                }
            //            }
        }
    }

    if (!ok) {
        qDebug() << "not find in client";
        return;
    }

saveFile:
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
        qDebug() << "writing to client xml success";
    }
    return;
}

void modifyXml::modifyClient_Telemetry(QString filepath, QString new_mes, QString old_mes, QString old_client) {
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

    auto replace = [&](QDomElement node) {
        QDomElement t = node.firstChildElement("addr");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(addr);
            cnt++;
//            qDebug() << "addr 更换成功！";
        }
        t = node.firstChildElement("inputFlag");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(inputFlag);
            cnt++;
//            qDebug() << "inputFlag 更换成功！";
        }
        t = node.firstChildElement("dataType");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(dataType);
            cnt++;
//            qDebug() << "dataType 更换成功！";
        }
        t = node.firstChildElement("describe");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(describe);
            cnt++;
//            qDebug() << "describe 更换成功！";
        }

        return cnt == client_telemetry_Size;
        /*
        // 不读 xml 中的注释
        if (node.nodeName() == "#comment") {
            return false;
        }
        if (cnt == client_telemetry_Size) {
            cnt = 0;
            return true;
        }
        if (!node.nodeName().compare("addr")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(addr);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "addr 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("inputFlag")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(inputFlag);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "inputFlag 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("dataType")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(dataType);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "dataType 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("describe")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(describe);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "describe 更换成功！";
            cnt++;
        }
        return false;
        */
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

    int idx = find_Client(clientNodes, old_f);
    if (idx == -1) {
        return qDebug() << "not find Client", void();
    }

    auto element = clientNodes.at(idx).toElement();
    QDomNodeList telemetryList = element.elementsByTagName("telemetryList");
    for (int j = 0; j < telemetryList.size(); j++) {
        auto ele = telemetryList.at(j).toElement();
        QDomNodeList telemetryNode = ele.elementsByTagName("telemetry");
        bool ok = false;
        for (int k = 0; k < telemetryNode.size(); k++) {
            auto t = telemetryNode.at(k).toElement();
            if (t.text() == old_child) {
                ok = true;
                qDebug() << "find in client_telemetry success";
                if (replace(t)) {
                    qDebug() << "replace client_telemetry finish";
                    goto saveFile;
                }
                //                QDomNodeList nlist = t.childNodes();
                //                for (int p = 0; p < nlist.size(); p++) {
                //                    auto node = nlist.at(p);
                //                    if (replace(node)) {
                //                        qDebug() << "replace client_telemetry finish";
                //                        goto saveFile;
                //                    }
                //                }
            }
        }
        if (!ok) {
            qDebug() << "not find in client_telemetry";
            return;
        }
    }

saveFile:
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

void modifyXml::modifyClient_Telesigna(QString filepath, QString new_mes, QString old_mes, QString old_client) {
#ifdef NDEBUG
    qDebug() << __func__;
    qDebug() << new_mes;
    qDebug() << old_mes;
    qDebug() << filepath;
#endif
    QStringList list = new_mes.split(',');
    if (list.size() != client_telesigna_Size) {
        qDebug() << "This new text does not conform to the specification", void();
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

    auto replace = [&](QDomElement node) {
        QDomElement t = node.firstChildElement("addr");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(addr);
            cnt++;
//            qDebug() << "addr 更换成功！";
        }
        t = node.firstChildElement("inputFlag");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(inputFlag);
            cnt++;
//            qDebug() << "inputFlag 更换成功！";
        }
        t = node.firstChildElement("describe");
        if (!t.isNull()) {
            t.firstChild().setNodeValue(describe);
            cnt++;
//            qDebug() << "describe 更换成功！";
        }

        return cnt == client_telesigna_Size;
        /*
        // 不读 xml 中的注释
        if (node.nodeName() == "#comment") {
            return false;
        }
        if (cnt == client_telesigna_Size) {
            cnt = 0;
            return true;
        }
        if (!node.nodeName().compare("addr")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(addr);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "addr 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("inputFlag")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(inputFlag);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "inputFlag 更换成功！";
            cnt++;
        } else if (!node.nodeName().compare("describe")) {
            QDomNode oldnode = node.firstChild();
            node.firstChild().setNodeValue(describe);
            QDomNode newnode = node.firstChild();
            node.replaceChild(newnode, oldnode);
            qDebug() << "describe 更换成功！";
            cnt++;
        }
        return false;
*/
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

    int idx = find_Client(clientNodes, old_f);

    auto element = clientNodes.at(idx).toElement();
    QDomNodeList telemetryList = element.elementsByTagName("telesignaList");
    for (int j = 0; j < telemetryList.size(); j++) {
        auto ele = telemetryList.at(j).toElement();
        QDomNodeList telemetryNode = ele.elementsByTagName("telesigna");
        bool ok = false;
        for (int k = 0; k < telemetryNode.size(); k++) {
            auto t = telemetryNode.at(k).toElement();
            if (t.text() == old_child) {
                ok = true;
                qDebug() << "find in client_telesigna success";
                if (replace(t)) {
                    qDebug() << "replace client_telesigna finish";
                    goto saveFile;
                }
                //                QDomNodeList nlist = t.childNodes();
                //                for (int p = 0; p < nlist.size(); p++) {
                //                    auto node = nlist.at(p);
                //                    if (replace(node)) {
                //                        qDebug() << "replace client_telesigna finish";
                //                        goto saveFile;
                //                    }
                //                }
            }
        }

        if (!ok) {
            qDebug() << "not find in client_telesigna";
            return;
        }
    }

saveFile:
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
