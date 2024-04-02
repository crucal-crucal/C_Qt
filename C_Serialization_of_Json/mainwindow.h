#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
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

    void writeJson();
    void readJson();

  private:
    Ui::MainWindow* ui;
};
#endif  // MAINWINDOW_H
