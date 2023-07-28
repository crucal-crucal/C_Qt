#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ZH_TO_PY.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
#ifdef NDEBUG
    qDebug() << __func__ << "运行";
#endif
    ui->setupUi(this);
    // 加载拼音文件
    ZH_TO_PY::Instance()->LoadPY(":data/zhtopy.txt");

    ui->txtChinese->setText("中文转拼音!123");

    connect(ui->btnPY, &QPushButton::clicked, this, &MainWindow::zhToPY);
    connect(ui->btnJP, &QPushButton::clicked, this, &MainWindow::zhToJP);
}

MainWindow::~MainWindow()
{
#ifdef NDEBUG
    qDebug() << __func__ << "运行";
#endif
    delete ui;
}

// 中文转为拼音
void MainWindow::zhToPY()
{
#ifdef NDEBUG
    qDebug() << __func__ << "运行";
#endif
    ui->txtResult->setText(ZH_TO_PY::Instance()->zhToPY(ui->txtChinese->text()));
}

// 中文转为简写拼音
void MainWindow::zhToJP()
{
#ifdef NDEBUG
    qDebug() << __func__ << "运行";
#endif
    ui->txtResult->setText(ZH_TO_PY::Instance()->zhToJP(ui->txtChinese->text()));
}

