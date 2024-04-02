#ifndef MYTEXTEDITBYCODE_H
#define MYTEXTEDITBYCODE_H

#include <QHBoxLayout>
#include <QScrollBar>
#include <QTextBrowser>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class MyTextEditByCode : public QWidget {
  Q_OBJECT
 public:
  explicit MyTextEditByCode(QWidget *parent = nullptr);
  ~MyTextEditByCode();

 signals:

 private:
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void initWidget();
  void initFont();
  void initConnection();
  void initHighlighter();
 private slots:
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void onTextEditHorizontalScrollBarChanged(int value);
  void onTextEditVerticalScrollBarChanged(int value);
  void onTextBrowserHorizontalScrollBarChanged(int value);
  void onScrollBarChanged(int value);

  void onTextEditChanged();
  void highlightCurrentLine();

 private:
  QTextEdit *textEdit;
  QTextBrowser *textBrowser;
  QScrollBar *scrollBar;
  QFont mFont;
};

#endif  // MYTEXTEDITBYCODE_H
