#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 *      未定义表示使用 UI
 *   1：自定义组件使用 QTextEdit
 *   2：自定义组件使用 QPlainTextEdit
 */
#define NOUI 2
// #define NDEBUG

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFontDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>

#ifdef NOUI
#if NOUI == 1
#include "Src/include/MyTextEditByCode.h"
#else
#include "Src/include/MyCodeEditor.h"
#endif
#else
#include "Src/include/MyTextEdit.h"
#endif

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif
#include <QPrinter>
#endif
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void init();

  void saveSuccessAction(MyCodeEditor *codeEditor);

 private slots:
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void newFile();
  void openFile();
  void openRecentFile();
  void saveFile();
  void saveAsFile();
  void print();
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void font();
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void copy();
  void paste();
  void cut();
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void undo();
  void redo();
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void exit();
  void about();
  /**********************************************
   * @projectName   %{CurrentProject:Name}
   * @brief         摘要
   * @param         void
   * @return        void
   **********************************************/
  void clearHistory();

  MyCodeEditor *getCodeEditor();

  void on_tabWidget_tabCloseRequested(int index);

 private:
  Ui::MainWindow *ui;
  QString mfontFamily;
  int mfontSize;
  std::unique_ptr<QSettings> m_Settings;

 private:
  // 初始化菜单
  void initMenu();
  // 初始化字体
  void initFont();
  // 初始化动作
  void initAction();
  // 获取历史记录
  QList<QString> getHistory();
  // 保存打开历史记录
  void saveHistory(QString path);
  // 创建 Tab
  void createTab(QString fileName);

  // QWidget interface
 protected:
  void closeEvent(QCloseEvent *event);
};
#endif  // MAINWINDOW_H
