
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    qDebug()<<QSqlDatabase::drivers();
    db = QSqlDatabase::addDatabase("QMYSQL");
    connect(ui->btn_delete, &QPushButton::clicked, this, &MainWindow::deleteSqlData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deleteSqlData()
{
    QSqlQuery query;
    query.prepare("delete from person where id = :id;"); //将Sql语句预处理，并将其存储在query对象中
    // 这样，在执行Sql语句时，可以直接从QSqlQuery中获取该语句，而无需重新解析和编译SQL语句，从而提高效率
    // prepare方法通常与bindValue方法一起使用，用于绑定SQL语句的参数，
    // bindValue方法可以将参数与占位符进行绑定，从而在执行SQL语句时，可以动态的设置这些参数的值
    // 需要注意的是，prepare方法通常用于执行多次相同或类似的SQL语句，从而提高执行效率，如果只需要执行一次SQL语句，
    // 也可以使用exec方法指定执行语句
    query.bindValue(":id", 01);
    bool flag = query.exec();
    if (!flag){
        qDebug()<<"error:\t"<<query.lastError().text();
    } else {
        qDebug()<<"successful!";
    }
}

bool MainWindow::connectDB()
{
    QString dbname = "eshop";

    db.setHostName("localhost"); // 本地域名
    db.setUserName(dbusername); // 设置用户名
    db.setPassword(dbpasswd); // 设置密码
    db.setPort(3306); // 如果绑定的端口是默认的就不用设置
    // MySql的默认端口就是3306
    db.setDatabaseName(dbname); // 设置需要访问的数据库

    if(!db.open())
    {
        QString str = "连接数据库失败：" + db.lastError().text(); // 打印失败信息
        QMessageBox::information(this, "打开数据库", str);
        return false;
    }
    else
    {
        QMessageBox::information(this, "打开数据库", QString("连接数据库成功！！！！"));
        return true;
    }
}

// 两种查询数据的方法，显示需要一个model来获取，然后通过view显示出来
// 对数据进行直接操作时，直接使用第二种while的方法即可
void MainWindow::on_btn_query_clicked()
{
//    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
//    model->setQuery("select *from person;");
////    model->setHeaderData(0, Qt::Horizontal, tr("id"));
////    model->setHeaderData(1, Qt::Horizontal, tr("name"));
//    ui->tableView->setModel(model);

    QSqlQuery query;
    QString sql = "select *from person;";
    query.exec(sql);
    while(query.next()){
        // 取出每个字段的值
        qDebug() << query.value(0).toUInt()
                 << query.value(1).toString()
                 << query.value("sex").toString();
    }

    qDebug()<<"\n";
}


void MainWindow::on_btn_insert_clicked()
{
    QSqlQuery query;//这里不能用指针，它是一个值类型，因此不能使用指针进行声明r和分配内存
    query.prepare("insert into person (id, name, sex) "
                   "values (:id, :name, :sex)");
    query.bindValue(":id", 1);
    query.bindValue(":name", "Alice");
    query.bindValue(":sex", "woman");
    // 在插入数据的时候，如果插入失败，可以进行数据的回滚
    db.transaction(); //创建一个事务，如果语句正确，就提交到数据库，创建事务的目的就是为了保护数据
    // 否则回滚到提交之前的状态
    bool flag = query.exec();
    if(!flag){
        db.rollback(); // 回滚数据
        qDebug()<<"插入出错:\t"<<query.lastError().text();
    }else{
        db.commit(); // 提交到数据库
        qDebug()<<"插入成功！";
    }
}

