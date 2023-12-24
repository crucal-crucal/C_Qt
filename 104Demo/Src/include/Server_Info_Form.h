#ifndef SERVER_INFO_FORM_H
#define SERVER_INFO_FORM_H

#include <QDialog>

#include "Src/include/config.h"

namespace Ui {
class Server_Info_Form;
}

class Server_Info_Form : public QDialog {
  Q_OBJECT

 public:
  explicit Server_Info_Form(QWidget* parent = nullptr);
  ~Server_Info_Form();

  static Server_Info_Form* getInstance(QWidget* parent = nullptr);
  // 初始化界面，以及左上角名字
  void init();
  // 更新界面
  void updateInfo(CFG_SERVER str);
  // 根据要求清除页面信息
  void cleanInfo() const;
  // 保存信息到文件
  void Save();
  // 设置默认值
  void setDefault();

 signals:
  void Values(CFG_SERVER);
  void textChanged(bool);

 private:
  Ui::Server_Info_Form* ui;
  static Server_Info_Form* self;
  CFG_SERVER local;
};

// 单例模式
inline Server_Info_Form* Server_Info_Form::getInstance(QWidget* parent) {
  if (self == nullptr) {
    self = new Server_Info_Form(parent);
    self->init();
  }
  return self;
}
#endif  // SERVER_INFO_FORM_H
