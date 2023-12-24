#ifndef SAVEXML_H
#define SAVEXML_H
//#define NDEBUG

#include <QApplication>
#include <QDebug>
#include <QDomDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <iostream>
#include <unordered_map>

class SaveXml : public QObject {
    Q_OBJECT
  public:
    explicit SaveXml(QObject* parent = nullptr);

    /*
     @Parameter: Server, Client
     @Change Source: All
    */
    void SaveFile(QString filepath, std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> server,
                  std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>> client);
};

#endif  // SAVEXML_H
