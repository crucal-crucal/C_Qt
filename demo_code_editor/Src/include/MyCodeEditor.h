#ifndef MYCODEEDITOR_H
#define MYCODEEDITOR_H

#include <qglobal.h>

#include <QDebug>
#include <QEvent>
#include <QFileDialog>
#include <QPainter>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QTextStream>
#include <QWidget>

#include "Src/include/MyHighlighter.h"

class LineNumberWidget;

class MyCodeEditor : public QPlainTextEdit {
  Q_OBJECT
 public:
  explicit MyCodeEditor(QWidget *parent = nullptr,
                        QFont font = QFont("Consolas", 14));
  ~MyCodeEditor();

  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void lineNumberWidgetPaintEvent(QPaintEvent *event);
  void lineNumberWidgetMousePressEvent(QMouseEvent *event);
  void lineNumberWidgetwheelEventEvent(QWheelEvent *event);

  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  bool saveFile();
  bool saveAsFile();
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void setFileName(QString fileName);
  QString getFileName();
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void setAllFont(QFont font);

  bool checkSaved();
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
  void updateSaveState();

 private:
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
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
  MyHighlighter *mHighlighter;
  QString mFileName;
  bool isSaved = false;

  // QWidget interface
 protected:
  void resizeEvent(QResizeEvent *event);
};

class LineNumberWidget : public QWidget {
 public:
  explicit LineNumberWidget(MyCodeEditor *editor = nullptr);

  // QWidget interface
 protected:
  void paintEvent(QPaintEvent *event) override;

  void mousePressEvent(QMouseEvent *event) override;

 private:
  MyCodeEditor *codeEditor;

  // QWidget interface
 protected:
  void wheelEvent(QWheelEvent *event) override;
};

inline LineNumberWidget::LineNumberWidget(MyCodeEditor *editor)
    : QWidget(editor) {
  codeEditor = editor;
}

inline void LineNumberWidget::paintEvent(QPaintEvent *event) {
  // 把绘制任务交给 MyCodeEditor
  codeEditor->lineNumberWidgetPaintEvent(event);
}

inline void LineNumberWidget::mousePressEvent(QMouseEvent *event) {
  // 把鼠标点击事件交给 MyCodeEditor
  codeEditor->lineNumberWidgetMousePressEvent(event);
}

inline void LineNumberWidget::wheelEvent(QWheelEvent *event) {
  // 把滚轮事件交给 MyCodeEditor
  codeEditor->lineNumberWidgetwheelEventEvent(event);
}

#endif  // MYCODEEDITOR_H
