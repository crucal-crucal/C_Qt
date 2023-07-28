
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QThreadPool>

#include "mywork.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
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
    MyWork *work;
    QVector<QPixmap *> pixmap;
};

#endif // MAINWINDOW_H
