#ifndef CLIENT_DELETE_FORM_H
#define CLIENT_DELETE_FORM_H

#include <QDialog>

namespace Ui {
    class Client_delete_Form;
}

class Client_delete_Form : public QDialog {
    Q_OBJECT

  public:
    explicit Client_delete_Form(QWidget* parent = nullptr);
    ~Client_delete_Form();

    static Client_delete_Form* getInstance(QWidget* parent = nullptr);

    // 初始化界面，以及左上角名字
    void init();
    void OK();

  signals:
    void del_curMes();

  private:
    Ui::Client_delete_Form* ui;
    static Client_delete_Form* self;
};

inline Client_delete_Form* Client_delete_Form::getInstance(QWidget* parent) {
    if (self == nullptr) {
        self = new Client_delete_Form(parent);
        self->init();
    }
    return self;
}
#endif  // CLIENT_DELETE_FORM_H
