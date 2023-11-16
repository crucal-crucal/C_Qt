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
  void bold(bool bold);
  void italic(bool italic);
  void underline(bool onderline);
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

 private:
  Ui::MainWindow *ui;
  QString currentFile;
  // 初始化菜单
  void initMenu();
};
#endif  // MAINWINDOW_H
