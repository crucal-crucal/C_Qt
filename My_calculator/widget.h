<<<<<<< HEAD

#ifndef WIDGET_H
#define WIDGET_H
#define display ui->lineEdit

#include <QGridLayout>
#include <QIcon>
#include <QPushButton>
#include <QToolbutton>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget

{
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();
  // QToolButton *createButton(const QString &text, const char *member);

private slots:
  void digitClicked();
  void abortOperation();
  void connect_With_number();
  void connect_with_button();
  void unaryOperatorClicked();
  void clearAll();
  void additiveOperatorClicked();
  void multiplicativeOperatorClicked();
  void equalClicked();
  void pointClicked();
  void changeSignClicked();
  void backspaceClicked();
  void clear();
  void clearMemory();
  void readMemory();
  void setMemory();
  void addToMemory();
  void setBtnsize();
  void SetBtnIcon(QPixmap *map, QPushButton *Btn);

private:
  Ui::Widget *ui;

private:
  //    enum { NumDigitButtons = 10 };
  //    QToolButton *digitButtons[NumDigitButtons];
  int minsize = 41;
  bool calculate(double rightOperand, const QString &pendingOperator);

  bool waitingForOperand;

  double sumInMemory;
  //! [3] //! [4]
  double sumSoFar;
  //! [4] //! [5]
  double factorSoFar;
  //! [5] //! [6]
  QString pendingAdditiveOperator;
  //! [6] //! [7]
  QString pendingMultiplicativeOperator;
};

#endif // WIDGET_H
=======

#ifndef WIDGET_H
#define WIDGET_H
#define display ui->lineEdit

#include <QToolbutton>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //QToolButton *createButton(const QString &text, const char *member);

private slots:
    void digitClicked();
    void abortOperation();
    void connect_With_number();
    void connect_with_button();
    void unaryOperatorClicked();
    void clearAll();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();
    void setBtnsize();
    void SetBtnIcon(QPixmap *map, QPushButton *Btn);

private:
    Ui::Widget *ui;

private:
//    enum { NumDigitButtons = 10 };
//    QToolButton *digitButtons[NumDigitButtons];
    int minsize = 41;
    bool calculate(double rightOperand, const QString &pendingOperator);

    bool waitingForOperand;

    double sumInMemory;
    //! [3] //! [4]
    double sumSoFar;
    //! [4] //! [5]
    double factorSoFar;
    //! [5] //! [6]
    QString pendingAdditiveOperator;
    //! [6] //! [7]
    QString pendingMultiplicativeOperator;
};

#endif // WIDGET_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
