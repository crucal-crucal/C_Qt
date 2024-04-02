#ifndef CLIENT_INFOMATION_H
#define CLIENT_INFOMATION_H

#include <QAction>
#include <QDebug>
#include <QDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPushButton>
#include <QStandardItemModel>

#include "Src/include/config.h"

namespace Ui {
class Client_Infomation;
}

class Client_Infomation : public QDialog {
  Q_OBJECT

 public:
  explicit Client_Infomation(QDialog* parent = nullptr);
  ~Client_Infomation();

  static Client_Infomation* getInstance(QDialog* parent = nullptr);

  void infoMation(tmap t, clientType type);

  tvalue getValue();

  void btnOk();
 signals:
  void teleMetry(tvalue);
  void teleSigna(tvalue);
  void clientTelemetryValue(tvalue);
  void clientTelesignaValue(tvalue);

 private slots:

 private:
  Ui::Client_Infomation* ui;
  static Client_Infomation* self;
  clientType local_type;
  QStandardItemModel* model;
  tmap local;
};

// 单例模式
inline Client_Infomation* Client_Infomation::getInstance(QDialog* parent) {
  if (self == nullptr) {
    self = new Client_Infomation(parent);
  }

  return self;
}

#endif  // CLIENT_INFOMATION_H
