#ifndef CLIENT_CHECKFORM_H
#define CLIENT_CHECKFORM_H

#include <QDialog>

namespace Ui {
    class Client_CheckForm;
}

const int Width = 230, Height = 80;

class Client_CheckForm : public QDialog {
    Q_OBJECT

  public:
    explicit Client_CheckForm(QWidget* parent = nullptr);
    ~Client_CheckForm();

    static Client_CheckForm* getInstance(QWidget* parent = nullptr);

    // 初始化界面，以及左上角名字
    void init();

  private:
    Ui::Client_CheckForm* ui;
    static Client_CheckForm* self;
};

inline Client_CheckForm* Client_CheckForm::getInstance(QWidget* parent) {
    if (self == nullptr) {
        self = new Client_CheckForm(parent);
        self->init();
    }
    return self;
}

#endif  // CLIENT_CHECKFORM_H
