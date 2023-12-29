#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedMemory>
#include <QDebug>
#include <QFileDialog>
#include <QBuffer>

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
    void clicked();

private:
    Ui::MainWindow *ui;
    QSharedMemory *m_SharedMemory;
};
#endif // MAINWINDOW_H
