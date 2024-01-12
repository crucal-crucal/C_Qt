#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*
 * 中文转化为拼音或者转化为简写拼音
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void zhToPY(); // 中文转为拼音
    void zhToJP(); // 中文转为简写拼音

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
