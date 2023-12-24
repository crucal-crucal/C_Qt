#ifndef CLIENT_FORM_H
#define CLIENT_FORM_H

#include <QDialog>

namespace Ui {
    class Client_Form;
}

class Client_Form : public QDialog {
    Q_OBJECT

  public:
    explicit Client_Form(QWidget* parent = nullptr);
    ~Client_Form();

    static Client_Form* getInstance(QWidget* parent = nullptr);
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
    Ui::Client_Form* ui;
    static Client_Form* self;
};

// 单例模式
inline Client_Form* Client_Form::getInstance(QWidget* parent) {
    if (self == nullptr) {
        self = new Client_Form(parent);
        self->init();
    }
    return self;
}

#endif  // CLIENT_FORM_H
