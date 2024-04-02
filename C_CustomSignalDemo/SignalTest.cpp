#include "SignalTest.h"

SignalTest::SignalTest() {
  resize(1080, 800);
  btn = new QPushButton(this);
  connect(btn, &QPushButton::clicked, this, [&]() {
    test.a++;
    test.b = 2;
    test.c = "3";
    QVariant val = QVariant::fromValue(test);
    emit signalTest(val);
  });
}
