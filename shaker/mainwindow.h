<<<<<<< HEAD

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThreadPool>
#include "mythread.h"


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
    void on_actThread_Run_triggered();

    void on_actClear_triggered();

    void on_actThread_Quit_triggered();

    void on_actDice_Run_triggered();

    void on_actDice_Pause_triggered();

private:
    Ui::MainWindow *ui;

private:
    MyThread *mythread;
    QVector<QPixmap *> pixmap;
};

#endif // MAINWINDOW_H
=======

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThreadPool>
#include "mythread.h"


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
    void on_actThread_Run_triggered();

    void on_actClear_triggered();

    void on_actThread_Quit_triggered();

    void on_actDice_Run_triggered();

    void on_actDice_Pause_triggered();

private:
    Ui::MainWindow *ui;

private:
    MyThread *mythread;
    QVector<QPixmap *> pixmap;
};

#endif // MAINWINDOW_H
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
