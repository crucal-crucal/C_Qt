#ifndef AXISTAG_H
#define AXISTAG_H

#include <QObject>
#include <QPen>
#include <QBrush>
#include "../../qcustomplot/qcustomplot.h"

class AxisTag : public QObject
{
    Q_OBJECT
public:
    explicit AxisTag(QCPAxis *parent = nullptr);
    virtual ~AxisTag();

    void setPen(const QPen &pen); // 设置箭头和标签的边框笔刷
    void setBrush(const QBrush &brush); // 设置标签的填充笔刷
    void setText(const QString &text); // 设置标签的文本

    QPen pen() const {
        return m_Label->pen();
    }

    QBrush bursh() const {
        return m_Label->brush();
    }

    QString text() const {
        return m_Label->text();
    }

    void updatePosotion(double value); // 更新箭头和标签的位置
private:
    QCPAxis *m_Axis;
    // QPointer是一个智能指针类，类似于QSharedPointer 和 QWeekPointer
    // 但是在对象被删除时可以自动将指针设置为nullptr
    // 从而避免空指针引用问题
    // QCPItemTracer是自定义绘图元素，用于在QCustomPlot中跟踪数据点
    QPointer<QCPItemTracer> m_DummyTracer;
    // QCPItemLine是自定义绘图元素，用于在QCustomPlot中绘制直线
    QPointer<QCPItemLine> m_Arrow;
    // QCPItemText是自定义绘图元素，用于在QCustomPlot中绘制文本标签
    QPointer<QCPItemText> m_Label;
};

#endif // AXISTAG_H
