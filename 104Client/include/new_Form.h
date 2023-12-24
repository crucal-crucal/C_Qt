#ifndef NEW_FORM_H
#define NEW_FORM_H

#include <QDebug>
#include <QDialog>

namespace Ui {
    class new_Form;
}

class new_Form : public QDialog {
    Q_OBJECT

  public:
    explicit new_Form(QWidget* parent = nullptr);
    ~new_Form();

    static new_Form* getInstance(QWidget* parent = nullptr);
    // 初始化界面，以及左上角名字
    void init();
    void OK();
  signals:
    void new_Values(std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>>,
                    std::unordered_map<QString, std::pair<QVector<QString>, QVector<QString>>>);

  private:
    Ui::new_Form* ui;
    static new_Form* self;
};

inline new_Form* new_Form::getInstance(QWidget* parent) {
    if (self == nullptr) {
        self = new new_Form(parent);
        self->init();
    }
    return self;
}
#endif  // NEW_FORM_H
