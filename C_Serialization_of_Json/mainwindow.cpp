#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->writeJson();
    this->readJson();
}

MainWindow::~MainWindow() { delete ui; }

/*
{
    "Name": "crucal",
    "Sex": "man",
    "Age": 20,
    "Family": {
        "Father": "a",
        "Mother": "b",
        "Brother": ["c", "d", "e", "f"]
    },
    "IsAlive": true,
    "Comment": "yyds"
}
 */
void MainWindow::writeJson() {
    QJsonObject obj;
    obj.insert("Name", "crucal");
    obj.insert("Sex", "man");
    obj.insert("Age", 20);

    QJsonObject sonobj;
    sonobj.insert("Father", "a");
    sonobj.insert("Mother", "b");

    QJsonArray array;
    array.append("c"), array.append("d"), array.append("e"), array.append("f");
    sonobj.insert("Brother", array);

    obj.insert("Family", sonobj);
    obj.insert("IsAlive", true);
    obj.insert("Comment", "yyds");

    QJsonDocument doc(obj);
    QByteArray json = doc.toJson();

    QFile file("E:\\QT\\MyQt\\Serialization_of_Json\\test.json");
    if (!file.open(QFile::WriteOnly)) {
        qDebug() << __func__;
        return qDebug() << "open error!", void();
    }

    file.write(json);
    file.close();
}

void MainWindow::readJson() {
    QFile file("E:\\QT\\MyQt\\Serialization_of_Json\\test.json");
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << __func__;
        return qDebug() << "open error!", void();
    }
    QByteArray all = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(all);
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        QStringList keys = obj.keys();

        for (const auto& key : keys) {
            QJsonValue val = obj.value(key);
            if (val.isBool()) {
                qDebug() << key << ": " << val.toBool();
            } else if (val.isDouble()) {
                qDebug() << key << ": " << val.toDouble();
            } else if (val.isString()) {
                qDebug() << key << ": " << val.toString();
            } else if (val.isObject()) {
                qDebug() << key << ": ";
                QJsonObject subobj = val.toObject();
                QStringList subKeys = subobj.keys();
                for (const auto& subkey : subKeys) {
                    QJsonValue val = subobj.value(subkey);
                    if (val.isString()) {
                        qDebug() << subkey << ":" << val.toString();
                    } else if (val.isArray()) {
                        qDebug() << subkey << ":";
                        QJsonArray arr = val.toArray();
                        for (const auto& c : arr) {
                            qDebug() << " " << c.toString();
                        }
                    }
                }
            }
        }
    }
}
