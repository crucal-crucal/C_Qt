#ifndef CLIENT_INFO_FORM_H
#define CLIENT_INFO_FORM_H

#include <QDialog>
#include <QLineEdit>
#include <QObject>

#include "Src/include/config.h"

namespace Ui {
class Client_Info_Form;
}

class Client_Info_Form : public QDialog {
  Q_OBJECT

 public:
  explicit Client_Info_Form(QWidget* parent = nullptr);
  ~Client_Info_Form();

  static Client_Info_Form* getInstance(QWidget* parent = nullptr);
  // 初始化界面，以及左上角名字
  void init();
  // 更新界面
  void updateInfo(CFG_CLIENT str);
  // 根据要求清除页面
  void cleanInfo() const;
  // 保存信息到文件
  void Save();
  // 设置默认值
  void setDefault();

 signals:
  void Values(CFG_CLIENT);
  void textChanged(bool);

 private:
  Ui::Client_Info_Form* ui;
  static Client_Info_Form* self;
  CFG_CLIENT local;

  void showWidgets(bool tcpIpVisible, bool seriaPortVisible);
};

// 单例模式
inline Client_Info_Form* Client_Info_Form::getInstance(QWidget* parent) {
  if (self == nullptr) {
    self = new Client_Info_Form(parent);
    self->init();
  }

  return self;
}

#endif  // CLIENT_INFO_FORM_H
