#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
//    , mPlot(0)
{
    ui->setupUi(this);

//    mPlot = new QCustomPlot(this);
//    setCentralWidget(mPlot);
    // 创建一个画布，并设置数据
    ui->centralwidget->addGraph();

    QVector<QColor> colors = {
        Qt::red, Qt::green, Qt::black, Qt::darkRed, Qt::cyan, Qt::magenta
    };
    //设置轴的显示范围，以看到全部数据
    QTimer *m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [=](){
        // 创建x轴和y轴，再创建数据
        QVector<double> x(101), y(101);
        for (int i = 0; i < (int)x.size(); i++) {
            x[i] = QRandomGenerator::global()->bounded(-100, 100);
            y[i] = QRandomGenerator::global()->bounded(-100, 100);
        }
        ui->centralwidget->graph(0)->setData(x, y);
        int idx = QRandomGenerator::global()->bounded(colors.size());
        ui->centralwidget->graph(0)->setPen(QPen(colors[idx]));
        ui->centralwidget->xAxis->setRange(-200, 200);
        ui->centralwidget->yAxis->setRange(-200, 200);
        ui->centralwidget->replot();
    });
    m_timer->start(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}
