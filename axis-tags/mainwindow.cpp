#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_Plot(0) // 将成员变量mplot的初始值设置为0，避免不必要的指针错误
    , m_Tag1(0)
    , m_Tag2(0)
{
    ui->setupUi(this);
    m_Plot = new QCustomPlot(this);
    this->setCentralWidget(m_Plot);

    // 设置绘图区域的左侧纵坐标轴的刻度标签颜色为不透明，即显示刻度标签的颜色。
    m_Plot->yAxis->setTickLabelColor(true);
//    connect(m_Plot->yAxis2, &QCPAxis::rangeChanged, m_Plot->yAxis, &QCPAxis::setRange);
    connect(m_Plot->yAxis2, SIGNAL(rangeChanged(QCPRange)), m_Plot->yAxis, SLOT(setRange(QCPRange)));

    // 将第二个纵坐标轴设置为可见
    // 默认情况下，QCustomPlot组件只有一个纵坐标轴（yAxis）
    // 因此需要使用 yAxis2 属性来访问第二个纵坐标轴，并将其设置为可见状态
    m_Plot->yAxis2->setVisible(true);
    // 在绘图区域的右侧添加一个新的坐标轴
    m_Plot->axisRect()->addAxis(QCPAxis::atRight);
    // 设置新坐标轴的内边距为30
    m_Plot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30);
    m_Plot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30);

    // 添加一个新的曲线，并连接到X轴和右侧第一个纵坐标轴上
    m_Graph1 = m_Plot->addGraph(m_Plot->xAxis, m_Plot->axisRect()->axis(QCPAxis::atRight, 0));
    // 添加一个新的曲线，并连接到X轴和右侧第二个纵坐标轴上
    m_Graph2 = m_Plot->addGraph(m_Plot->xAxis, m_Plot->axisRect()->axis(QCPAxis::atRight, 1));
    // 设置画笔
    m_Graph1->setPen(QPen(QColor(250, 120, 0)));
    m_Graph2->setPen(QPen(QColor(0, 180, 60)));

    // 新建标签连接到坐标轴上
    m_Tag1 = new AxisTag(m_Graph1->valueAxis());
    m_Tag1->setPen(m_Graph1->pen());
    m_Tag2 = new AxisTag(m_Graph2->valueAxis());
    m_Tag2->setPen(m_Graph2->pen());

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::timerSlot);
    m_timer->start(40);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerSlot()
{
    // 添加数据
    m_Graph1->addData(m_Graph1->dataCount(), qSin(m_Graph1->dataCount() / 50.0) + qSin(m_Graph1->dataCount() / 50.0 / 0.3843) * 0.25);
    m_Graph2->addData(m_Graph2->dataCount(), qCos(m_Graph2->dataCount() / 50.0) + qSin(m_Graph2->dataCount() / 50.0 / 0.4364) * 0.15);

    // 将 X 轴的范围自适应数据的范围
    m_Plot->xAxis->rescale();
    // 将纵坐标轴的范围自适应数据的范围
    m_Graph1->rescaleValueAxis(false, true);
    m_Graph2->rescaleValueAxis(false, true);
    // 对 X 轴进行平移，使得曲线始终保持在右侧。这里使用 setRange() 方法将 X 轴的范围设置为当前范围的上限值加上 100，这样就可以使得曲线保持在右侧
    m_Plot->xAxis->setRange(m_Plot->xAxis->range().upper, 100, Qt::AlignRight);

    // 获取最新的数据点的值
    double graph1val = m_Graph1->dataMainValue(m_Graph1->dataCount() - 1),
           graph2val = m_Graph2->dataMainValue(m_Graph2->dataCount() - 1);
    m_Tag1->updatePosotion(graph1val);
    m_Tag2->updatePosotion(graph2val);
    m_Tag1->setText(QString::number(graph1val, 'f', 2)),
           m_Tag2->setText(QString::number(graph2val, 'f', 2));

    m_Plot->replot();

}

