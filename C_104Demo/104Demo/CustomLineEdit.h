#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QDebug>
#include <QLineEdit>
#include <QMouseEvent>

#include "Src/include/config.h"

class CustomLineEdit : public QLineEdit {
  Q_OBJECT
 public:
  explicit CustomLineEdit(QWidget* parent = nullptr);

  void clientInfo(tmap client, tmap telemetry);

  void setType(clientType t);

  clientType getType() const;

 signals:
  void clientid(tmap, clientType);
  // QWidget interface
 protected:
  void mousePressEvent(QMouseEvent* event);

 private:
  clientType type;
  tmap loca_client;
  tmap loca_tele;
  unsigned int local_v;

 private:
  void setClient();
  void setClientTelemetry();
  void setClientTelesigna();
};

inline clientType CustomLineEdit::getType() const { return type; }

#endif  // CUSTOMLINEEDIT_H
