#include "SaveXml.h"

SaveXml::SaveXml(QObject* parent) : QObject{parent} {}

void SaveXml::SaveFile(QString filepath,
                       std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> server,
                       std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> client) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif

    std::map<QString, std::pair<QVector<QString>, QVector<QString>>> Server, Client;
    for (const auto& [key, value] : server) {
        Server[key] = value;
    }
    for (const auto& [key, value] : client) {
        Client[key] = value;
    }
    // 创建 QDomDocument 对象
    QDomDocument doc;

    QDomProcessingInstruction version = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(version);
    // 创建根元素 <config>
    QDomElement configElement = doc.createElement("config");
    doc.appendChild(configElement);

    auto get_names = [&](QString server) -> QVector<QString> {
        QVector<QString> result;
        QStringList t = server.split(",");
        for (const auto& c : t) {
            QStringList p = c.split(':');
            result.push_back(p[p.size() - 1]);
        }

        return result;
    };

    // 创建 <serverList> 元素
    QDomElement serverListElement = doc.createElement("serverList");
    configElement.appendChild(serverListElement);

    for (const auto& [key, value] : Server) {
        if (key.isEmpty()) {
            continue;
        }
        // 创建 <server> 元素
        QDomElement serverElement = doc.createElement("server");
        serverListElement.appendChild(serverElement);
        QVector<QString> posname{"id", "ip", "port", "dataType", "publicAddr", "describe"};
        auto sname = get_names(key);
        for (int i = 0; i < sname.size(); i++) {
            QDomElement ele = doc.createElement(posname[i]);
            ele.appendChild(doc.createTextNode(sname[i]));
            serverElement.appendChild(ele);
        }
        // 创建 <telemetryList> 元素
        QDomElement telemetryListElement = doc.createElement("telemetryList");
        serverElement.appendChild(telemetryListElement);
        for (const auto& c : value.first) {
            // 创建 <telemetry> 元素
            QDomElement telemetryElement = doc.createElement("telemetry");
            telemetryListElement.appendChild(telemetryElement);
            posname = {"addr", "coeff", "clientID", "clientTelemetryAddr", "describe"};
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
        for (const auto& c : value.second) {
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
    for (const auto& [key, value] : Client) {
        if (key.isEmpty()) {
            continue;
        }
        // 创建 <client> 元素
        QDomElement clientElement = doc.createElement("client");
        clientListElement.appendChild(clientElement);
        QVector<QString> posname{"id", "ip", "port", "protocol", "slaveID", "generalCallTime", "describe"};
        auto cname = get_names(key);
        for (int i = 0; i < cname.size(); i++) {
            QDomElement ele = doc.createElement(posname[i]);
            ele.appendChild(doc.createTextNode(cname[i]));
            clientElement.appendChild(ele);
        }
        // 创建 <telemetryList> 元素
        QDomElement telemetryListElement = doc.createElement("telemetryList");
        clientElement.appendChild(telemetryListElement);
        for (const auto& c : value.first) {
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
        for (const auto& c : value.second) {
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

    //    QString filename = QFileDialog::getSaveFileName(nullptr, "Open File", "Save_File", "(*.xml");
    if (filepath.isEmpty()) {
        return qDebug() << "filename is Empty!", void();
    }
    // 创建保存文件的 QFile 对象
    QFile file(filepath);

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
        qDebug() << "writing to xml success";
    }
    return;
}
