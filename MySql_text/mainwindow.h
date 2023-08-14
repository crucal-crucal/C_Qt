<<<<<<< HEAD
<<<<<<< HEAD

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

static const QString dbusername = "root";
static const QString dbpasswd = "540869cf";

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool connectDB();

    void deleteSqlData(); // 删除数据

private slots:
    void on_btn_query_clicked();

    void on_btn_insert_clicked();

private:
    Ui::MainWindow *ui;

private:
    QSqlTableModel *m_model;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
=======
=======
>>>>>>> 47b8f66 (update)

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>

const QString dbusername = "root";
const QString dbpasswd = "540869cf";

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool connectDB();

private slots:
    void on_btn_query_clicked();

    void on_btn_insert_clicked();

private:
    Ui::MainWindow *ui;

private:
    QSqlTableModel *m_model;
};

#endif // MAINWINDOW_H
<<<<<<< HEAD
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
=======
>>>>>>> 47b8f66 (update)
