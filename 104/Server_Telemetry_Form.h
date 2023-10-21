#ifndef SERVER_TELEMETRY_FORM_H
#define SERVER_TELEMETRY_FORM_H

#include <QDebug>
#include <QDialog>
#include <QString>

namespace Ui {
    class Server_Telemetry_Form;
}

class Server_Telemetry_Form : public QDialog {
    Q_OBJECT

  public:
    explicit Server_Telemetry_Form(QWidget* parent = nullptr);
    ~Server_Telemetry_Form();

    static Server_Telemetry_Form* getInstance(QWidget* parent = nullptr);
    // 初始化界面，以及左上角名字
    void init();
    // 获取主界面上点击的信息，显示在子界面上
    void modifyServer(QString mes);
    // 确定按钮，将修改后的信息返回给主界面
    void OK();

  signals:
    void cannel();
    void modified_values(QString);

  private:
    Ui::Server_Telemetry_Form* ui;
    static Server_Telemetry_Form* self;
};

// 单例模式
inline Server_Telemetry_Form* Server_Telemetry_Form::getInstance(QWidget* parent) {
    if (self == nullptr) {
        self = new Server_Telemetry_Form(parent);
        self->init();
    }
    return self;
}

#endif  // SERVER_TELEMETRY_FORM_H
