#ifndef DELETE_FORM_H
#define DELETE_FORM_H

#include <QDialog>
#include <QDebug>

namespace Ui {
    class Server_delete_Form;
}

class Server_delete_Form : public QDialog {
    Q_OBJECT

  public:
    explicit Server_delete_Form(QWidget* parent = nullptr);
    ~Server_delete_Form();

    static Server_delete_Form* getInstance(QWidget* parent = nullptr);

    // 初始化界面，以及左上角名字
    void init();
    void OK();

  signals:
    void del_curMes();

  private:
    Ui::Server_delete_Form* ui;
    static Server_delete_Form* self;
};

inline Server_delete_Form* Server_delete_Form::getInstance(QWidget* parent) {
    if (self == nullptr) {
        self = new Server_delete_Form(parent);
        self->init();
    }
    return self;
}

#endif  // DELETE_FORM_H
