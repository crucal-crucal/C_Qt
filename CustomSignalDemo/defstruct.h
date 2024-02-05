#pragma once

#include <string>
#include <QMetaType>

struct MyDef {
  int a{};
  int b{};
  std::string c{};

  MyDef() {
    reset();
  }

  MyDef &operator=(const MyDef &other) {
    if (this == &other) {
      return *this;
    }
    a = other.a;
    b = other.b;
    c = other.c;
    return *this;
  }

  void reset() {
    a = 0;
    b = 0;
    c = "default";
  }
};

Q_DECLARE_METATYPE(MyDef)