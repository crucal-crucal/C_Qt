#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QString fileName, qint64 fileSize, QWidget *parent = nullptr);
    ~Form();
    void updateProcess(qint64 recSize);
    void setStatus(bool);

private:
    Ui::Form *ui;
    qint64 m_fileSize;
};

#endif // FORM_H
