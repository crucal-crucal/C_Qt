#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define NDEBUG

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
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

  private:
    Ui::MainWindow* ui;
    QString currentFile;
};
#endif  // MAINWINDOW_H
