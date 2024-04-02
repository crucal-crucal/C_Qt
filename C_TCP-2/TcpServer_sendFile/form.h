<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 47b8f66 (update)
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
<<<<<<< HEAD
=======
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
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
