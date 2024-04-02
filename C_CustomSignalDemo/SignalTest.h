#pragma once

#include "defstruct.h"
#include <QMetaType>
#include <QObject>
#include <QPushButton>
#include <QVariant>

class SignalTest : public QWidget {
 Q_OBJECT
 public:
  SignalTest();

 signals:
  void signalTest(QVariant);

 private:
  MyDef test;
  QPushButton *btn{nullptr};
};
