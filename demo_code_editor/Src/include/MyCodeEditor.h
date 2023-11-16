#ifndef MYCODEEDITOR_H
#define MYCODEEDITOR_H

#include <qglobal.h>

#include <QDebug>
#include <QPainter>
#include <QPlainTextEdit>
#include <QWidget>

class LineNumberWidget;

class MyCodeEditor : public QPlainTextEdit {
  Q_OBJECT
 public:
  explicit MyCodeEditor(QWidget *parent = nullptr);
  ~MyCodeEditor();

  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void lineNumberWidgetPaintEvent(QPaintEvent *event);

 signals:

 private slots:
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void highlightCurrentLine();
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void updateLineNumberWidget(const QRect &rect, int dy);
  void updateLineNumberWidgetWidth();

 private:
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void initFont();
  void initConnection();
  void initHighlighter();

  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  int getLineNumberWidgetWidth();

 private:
  LineNumberWidget *lineNumberWidget;

  // QWidget interface
 protected:
  void resizeEvent(QResizeEvent *event);
};

class LineNumberWidget : public QWidget {
 public:
  explicit LineNumberWidget(MyCodeEditor *editor = nullptr) : QWidget(editor) {
    codeEditor = editor;
  }

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent *event) override {
    // 把绘制任务交给 MyCodeEditor
    codeEditor->lineNumberWidgetPaintEvent(event);
  }

 private:
  MyCodeEditor *codeEditor;
};

#endif  // MYCODEEDITOR_H
