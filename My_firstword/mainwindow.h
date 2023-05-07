#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <my_openinterface.h>
#include <QLabel>
#include <QSpinBox>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontComBoBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionItalic_triggered(bool checked);

    void on_actionBold_triggered(bool checked);

    void on_actionUnderline_triggered(bool checked);

    void on_actionabout_triggered();

    void on_actionaboutQt_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionnew_triggered();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    int flag_isOpen = 0;
    int flag_isNew = 0;
    QString Last_FileName;
    QString Last_FileContent;
    My_openInterface * openinterface;
    QLabel *label;
    QString subtext;
};
#endif // MAINWINDOW_H
