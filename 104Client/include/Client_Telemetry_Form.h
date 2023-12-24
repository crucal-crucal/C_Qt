#ifndef CLIENT_TELEMETRY_FORM_H
#define CLIENT_TELEMETRY_FORM_H

#include <QDialog>
#include <QString>

namespace Ui {
    class Client_Telemetry_Form;
}

class Client_Telemetry_Form : public QDialog {
    Q_OBJECT

  public:
    explicit Client_Telemetry_Form(QWidget* parent = nullptr);
    ~Client_Telemetry_Form();

    static Client_Telemetry_Form* getInstance(QWidget* parent = nullptr);
    // 初始化界面，以及左上角名字
    void init();
    // 获取主界面上点击的信息，显示在子界面上
    void modifyClient(QString mes);
    // 确定按钮，将修改后的信息返回给主界面
    void OK();

  signals:
    void cannel();
    void modified_values(QString);

  private:
    Ui::Client_Telemetry_Form* ui;
    static Client_Telemetry_Form* self;
};

// 单例模式
inline Client_Telemetry_Form* Client_Telemetry_Form::getInstance(QWidget* parent) {
    if (self == nullptr) {
        self = new Client_Telemetry_Form(parent);
        self->init();
    }
    return self;
}

#endif  // CLIENT_TELEMETRY_FORM_H
