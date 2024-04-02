#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "AxisTag.h"

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
    // 更新图形
    void timerSlot();

private:
    Ui::MainWindow *ui;
    QCustomPlot *m_Plot; // 显示图形
    QPointer<QCPGraph> m_Graph1, m_Graph2; // 两条曲线
    AxisTag *m_Tag1, *m_Tag2; // 两个标签
    QTimer *m_timer;
};
#endif // MAINWINDOW_H
