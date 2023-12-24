#ifndef CLIENT_TELESIGNA_INFO_FORM_H
#define CLIENT_TELESIGNA_INFO_FORM_H

#include <QDialog>

#include "Src/include/config.h"
#define COIL_STATUS (0x00)
#define INPUT_STATUS (0x01)

namespace Ui {
class Client_Telesigna_Info_Form;
}

class Client_Telesigna_Info_Form : public QDialog {
  Q_OBJECT

 public:
  explicit Client_Telesigna_Info_Form(QWidget* parent = nullptr);
  ~Client_Telesigna_Info_Form();

  static Client_Telesigna_Info_Form* getInstance(QWidget* parent = nullptr);
  // 初始化界面，以及左上角名字
  void init();
  // 更新界面
  void updateInfo(CFG_CLIENT_TELESIGNA str);
  // 清空界面
  void cleanInfo() const;
  // 保存信息到文件
  void Save();
  // 设置默认值
  void setDefault();

 signals:
  void Values(CFG_CLIENT_TELESIGNA);
  void textChanged(bool);

 private:
  Ui::Client_Telesigna_Info_Form* ui;
  static Client_Telesigna_Info_Form* self;
  CFG_CLIENT_TELESIGNA local;
};

// 单例模式
inline Client_Telesigna_Info_Form* Client_Telesigna_Info_Form::getInstance(
    QWidget* parent) {
  if (self == nullptr) {
    self = new Client_Telesigna_Info_Form(parent);
    self->init();
  }
  return self;
}
#endif  // CLIENT_TELESIGNA_INFO_FORM_H
