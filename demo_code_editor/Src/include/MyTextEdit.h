#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QDebug>
#include <QTextEdit>
#include <QWidget>

namespace Ui {
class MyTextEdit;
}

class MyTextEdit : public QWidget {
  Q_OBJECT

 public:
  explicit MyTextEdit(QWidget *parent = nullptr);
  ~MyTextEdit();

  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void initConnect();
  void initFont();
  void initHighlighter();

 private slots:
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void textEditHScrollBarChanged(int value);
  void scrollBarChanged(int value);

  void textEditVScrollBarChanged(int value);
  void textBrowserVScrollBarChanged(int value);
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void onTextChanged();

 private:
  Ui::MyTextEdit *ui;
};

#endif  // MYTEXTEDIT_H
