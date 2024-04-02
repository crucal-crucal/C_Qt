#ifndef SERVER_TELESIGNA_INFO_FORM_H
#define SERVER_TELESIGNA_INFO_FORM_H

#include <QDialog>

#include "Src/include/config.h"

namespace Ui {
class Server_Telesigna_Info_Form;
}

class Server_Telesigna_Info_Form : public QDialog {
  Q_OBJECT

 public:
  explicit Server_Telesigna_Info_Form(QWidget* parent = nullptr);
  ~Server_Telesigna_Info_Form();

  static Server_Telesigna_Info_Form* getInstance(QWidget* parent = nullptr);
  // 初始化界面，以及左上角名字
  void init();
  // 更新界面
  void updateInfo(MAP_CFG_CLIENT client, MAP_CFG_CLIENT_TELESIGNA telesigna,
                  CFG_SERVER_TELESIGNA str);
  // 清空页面
  void cleanInfo() const;
  // 保存信息到文件
  void Save();
  // 设置默认值
  void setDefault();
  // 接收主线程发送的客户端信息
  void clientInfomation(MAP_CFG_CLIENT client,
                        MAP_CFG_CLIENT_TELESIGNA client_telesigna);
  // 选择更新
  void updateInfo_to_Client_Infomation();

 signals:
  void Values(CFG_SERVER_TELESIGNA);
  void textChanged(bool);
  void clientInfo(tmap, tmap);

 private:
  Ui::Server_Telesigna_Info_Form* ui;
  static Server_Telesigna_Info_Form* self;
  MAP_CFG_CLIENT local_client;
  MAP_CFG_CLIENT_TELESIGNA local_client_telesigna;
  unsigned int client_id = std::numeric_limits<unsigned int>::max();
  unsigned int addr_id = std::numeric_limits<unsigned int>::max();
};

// 单例模式
inline Server_Telesigna_Info_Form* Server_Telesigna_Info_Form::getInstance(
    QWidget* parent) {
  if (self == nullptr) {
    self = new Server_Telesigna_Info_Form(parent);
    self->init();
  }
  return self;
}
#endif  // SERVER_TELESIGNA_INFO_FORM_H
