#ifndef SERVER_TELESIGNA_FORM_H
#define SERVER_TELESIGNA_FORM_H

#include <QDialog>
#include <QDebug>

namespace Ui {
    class Server_Telesigna_Form;
}

class Server_Telesigna_Form : public QDialog {
    Q_OBJECT

  public:
    explicit Server_Telesigna_Form(QWidget* parent = nullptr);
    ~Server_Telesigna_Form();

    static Server_Telesigna_Form* getInstance(QWidget* parent = nullptr);
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
    Ui::Server_Telesigna_Form* ui;
    static Server_Telesigna_Form* self;
};

// 单例模式
inline Server_Telesigna_Form* Server_Telesigna_Form::getInstance(QWidget* parent) {
    if (self == nullptr) {
        self = new Server_Telesigna_Form(parent);
        self->init();
    }
    return self;
}

#endif  // SERVER_TELESIGNA_FORM_H
