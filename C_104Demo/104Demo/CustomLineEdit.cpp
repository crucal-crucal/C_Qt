#include "CustomLineEdit.h"

#include "Src/include/Client_Infomation.h"

CustomLineEdit::CustomLineEdit(QWidget *parent) : QLineEdit{parent} {
  this->setReadOnly(true);
  connect(this, &CustomLineEdit::clientid, Client_Infomation::getInstance(),
          &Client_Infomation::infoMation);
}

void CustomLineEdit::clientInfo(tmap client, tmap tele) {
  loca_client = client;
  loca_tele = tele;
}

void CustomLineEdit::setType(clientType t) { type = t; }

void CustomLineEdit::mousePressEvent(QMouseEvent *event) {
  switch (type) {
    case telemetry: {
      this->setClient();
      emit clientid(loca_client, type);
      break;
    }
    case telesigna: {
      this->setClient();
      emit clientid(loca_client, type);
      break;
    }
    case cleint_telemetryID: {
      this->setClientTelemetry();
      emit clientid(loca_tele, type);
      break;
    }
    case client_telesignaID: {
      this->setClientTelesigna();
      emit clientid(loca_tele, type);
      break;
    }
    default:
      break;
  }
  Client_Infomation::getInstance()->exec();
  QLineEdit::mousePressEvent(event);
}

void CustomLineEdit::setClient() {
  Client_Infomation::getInstance()->setWindowTitle("对应客户端信息");
}

void CustomLineEdit::setClientTelemetry() {
  Client_Infomation::getInstance()->setWindowTitle("对应客户端遥测信息");
}

void CustomLineEdit::setClientTelesigna() {
  Client_Infomation::getInstance()->setWindowTitle("对应客户端遥信数据信息");
}
