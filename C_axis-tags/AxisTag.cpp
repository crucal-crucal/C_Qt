#include "AxisTag.h"

AxisTag::AxisTag(QCPAxis *parent)
    : QObject{parent}
    , m_Axis{parent} // 代表坐标轴
{
    // 作为一个可见的锚点，始终固定在坐标轴矩形的右侧
    m_DummyTracer = new QCPItemTracer(m_Axis->parentPlot());
    // 设置对象为可见
    m_DummyTracer->setVisible(true);
    // 将x轴坐标类型设置为ptAxisRectRatio，表示x坐标轴相对于坐标轴矩形的比例
    m_DummyTracer->position->setTypeX(QCPItemPosition::ptAxisRectRatio);
    // 将y轴坐标类型设置为ptPlotCoords，表示y坐标轴相对于绘图区域的坐标
    m_DummyTracer->position->setTypeY(QCPItemPosition::ptPlotCoords);
    // 将坐标系设置为m_Axis所在的坐标系
    m_DummyTracer->position->setAxisRect(m_Axis->axisRect());
    // 将坐标系设置为m_Axis所在的坐标轴
    m_DummyTracer->position->setAxes(0, m_Axis);
    // 位于坐标轴举行的右侧，y坐标为0
    m_DummyTracer->position->setCoords(1, 0);


    m_Arrow = new QCPItemLine(m_Axis->parentPlot());
    // 显示在其他层之上
    m_Arrow->setLayer("overlay");
    // 将 m_Arrow 对象的裁剪属性设置为 false，表示它可以超出坐标轴矩形的范围。
    m_Arrow->setClipToAxisRect(false);
    // 设置箭头形状为带有箭头的尖头
    m_Arrow->setHead(QCPLineEnding::esSpikeArrow);
    // m_Arrow的尖头位于m_DummyTracer的位置
    m_Arrow->end->setParentAnchor(m_DummyTracer->position);
    // 箭头的起始点应该与尖头重合
    m_Arrow->start->setParentAnchor(m_Arrow->end);
    // 表示箭头的起始点位于m_DummyTracer右侧，与m_DummyTracer对象相距15个px
    m_Arrow->start->setCoords(15, 0);

    m_Label = new QCPItemText(m_Axis->parentPlot());
    // 显示在其他层之上
    m_Label->setLayer("overlay");
    // 将 m_Arrow 对象的裁剪属性设置为 false，表示它可以超出坐标轴矩形的范围。
    m_Label->setClipToAxisRect(false);
    // 将 m_Label 对象的内边距设置为 (3, 0, 3, 0)，即上下边距为 0，左右边距为 3
    m_Label->setPadding(QMargins(3, 0, 3, 0));
    // 将m_Label 对象的填充颜色设置为白色
    m_Label->setBrush(QBrush(Qt::white));
    // 将m_Label 对象边框设置为蓝色
    m_Label->setPen(QPen(Qt::blue));
    // 对齐方式，左对齐和垂直居中
    m_Label->setPositionAlignment(Qt::AlignLeft | Qt::AlignCenter);
    // 将m_Label 对象的位置设置为箭头的起始点
    m_Label->position->setParentAnchor(m_Arrow->start);
}

AxisTag::~AxisTag()
{
    if (m_DummyTracer) {
        m_DummyTracer->parentPlot()->removeItem(m_DummyTracer);
    }

    if (m_Arrow) {
        m_Arrow->parentPlot()->removeItem(m_Arrow);
    }

    if (m_Label) {
        m_Label->parentPlot()->removeItem(m_Label);
    }
}

void AxisTag::setPen(const QPen &pen)
{
    m_Arrow->setPen(pen);
    m_Label->setPen(pen);
}

void AxisTag::setBrush(const QBrush &brush)
{
    m_Label->setBrush(brush);
}

void AxisTag::setText(const QString &text)
{
    m_Label->setText(text);
}

void AxisTag::updatePosotion(double value)
{
    // value为标签显示的值
    m_DummyTracer->position->setCoords(1, value);
    // offset为偏移量
    m_Arrow->end->setCoords(m_Axis->offset(), 0);
}
