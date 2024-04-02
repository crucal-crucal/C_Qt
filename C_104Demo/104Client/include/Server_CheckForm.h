#ifndef SERVER_CHECKFORM_H
#define SERVER_CHECKFORM_H

#include <QDialog>

namespace Ui {
    class Server_CheckForm;
}

class Server_CheckForm : public QDialog {
    Q_OBJECT

  public:
    explicit Server_CheckForm(QWidget* parent = nullptr);
    ~Server_CheckForm();

    static Server_CheckForm* getInstance(QWidget* parent = nullptr);
    // 初始化界面，以及左上角名字
    void init();

  private:
    Ui::Server_CheckForm* ui;
    static Server_CheckForm* self;
};

inline Server_CheckForm* Server_CheckForm::getInstance(QWidget* parent) {
    if (self == nullptr) {
        self = new Server_CheckForm(parent);
        self->init();
    }
    return self;
}

#endif  // SERVER_CHECKFORM_H
