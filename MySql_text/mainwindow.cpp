
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    qDebug()<<QSqlDatabase::drivers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QString dbname = "eshop";

    db.setHostName("localhost");
    db.setUserName(dbusername);
    db.setPassword(dbpasswd);
    db.setDatabaseName(dbname);

    if(!db.open())
    {
        QString str = "连接数据库失败：" + db.lastError().text();
        QMessageBox::information(this, "打开数据库", str);
        return false;
    }
    else
    {
        QMessageBox::information(this, "打开数据库", QString("连接数据库%1成功！！！！").arg(dbname));
        return true;
    }
}


void MainWindow::on_btn_query_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    model->setQuery("select *from clients");
//    model->setHeaderData(0, Qt::Horizontal, tr("id"));
//    model->setHeaderData(1, Qt::Horizontal, tr("name"));
    ui->tableView->setModel(model);
}


void MainWindow::on_btn_insert_clicked()
{
    QSqlQuery query;//这里不能用指针，它是一个值类型，因此不能使用指针进行声明和分配内存
    query.prepare("insert into clients (cid, cname, csex, cbirth, cphone, caddress, clevel) "
                   "values (:id, :name, :sex, :birth, :phone, :address, :level)");
    query.bindValue(":id", '2');
    query.bindValue(":name", "lds1");
    query.bindValue(":sex", "男");
    query.bindValue(":birth", "2020-10-10");
    query.bindValue(":phone", "12345678901");
    query.bindValue(":address", "abc");
    query.bindValue(":level", "普通");
}

