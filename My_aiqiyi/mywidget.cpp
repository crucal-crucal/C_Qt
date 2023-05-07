
#include "mywidget.h"
#include "widget.h"

#include <QBuffer>
#include <QMouseEvent>
#include <QMoveEvent>

Mywidget::Mywidget(QWidget *parent)
    : QWidget{parent}
{
    btn1 = new QPushButton(this);
    btn1->resize(QSize(150, 80));
    btn1->setIcon(QIcon(":/images/1.png"));
    btn1->setIconSize(btn1->size());
    btn1->move(0, 30);
    btn1->installEventFilter(this);

    btn2 = new QPushButton(this);
    btn2->resize(QSize(150, 20));
    btn2->setText("电视剧1");
    btn2->move(0, 110);

    btn3 = new QPushButton(this);
    btn3->resize(QSize(150, 80));
    btn3->setIcon(QIcon(":/images/2.png"));
    btn3->setIconSize(btn3->size());
    btn3->move(150, 30);
    btn3->installEventFilter(this);

    btn4 = new QPushButton(this);
    btn4->resize(QSize(150, 20));
    btn4->setText("电视剧2");
    btn4->move(150, 110);

    btn5 = new QPushButton(this);
    btn5->resize(QSize(150, 80));
    btn5->setIcon(QIcon(":/images/3.png"));
    btn5->setIconSize(btn5->size());
    btn5->move(300, 30);
    btn5->installEventFilter(this);

    btn6 = new QPushButton(this);
    btn6->resize(QSize(150, 20));
    btn6->setText("电视剧3");
    btn6->move(300, 110);

    btn7 = new QPushButton(this);
    btn7->resize(QSize(150, 80));
    btn7->setIcon(QIcon(":/images/4.png"));
    btn7->setIconSize(btn7->size());
    btn7->move(450, 30);
    btn7->installEventFilter(this);

    btn8 = new QPushButton(this);
    btn8->resize(QSize(150, 20));
    btn8->setText("电视剧4");
    btn8->move(450, 110);

    btn9 = new QPushButton(this);
    btn9->resize(QSize(150, 80));
    btn9->setIcon(QIcon(":/images/5.png"));
    btn9->setIconSize(btn9->size());
    btn9->move(600, 30);
    btn9->installEventFilter(this);

    btn10 = new QPushButton(this);
    btn10->resize(QSize(150, 20));
    btn10->setText("电视剧5");
    btn10->move(600, 110);

    label = new QLabel(this);
    label->resize(QSize(90, 30));
    label->setText("猜你喜欢");
    label->move(0, 0);

    lab1 = new QLabel(this);
    lab1->setPixmap(QPixmap(":/images/1.png"));
    lab1->resize(lab1->sizeHint());
    lab1->hide();
}

bool Mywidget::eventFilter(QObject *watched, QEvent *event)
{
    QPushButton *btn = qobject_cast<QPushButton *>(watched);
    if (event->type() == QEvent::Enter)
    {
        // 如果鼠标进入按钮，则显示图像
        QByteArray imageData;//存储字节数组
        QBuffer buffer(&imageData);//创建缓冲区，读写字节数组
        QIcon icon = btn->icon();
        icon.pixmap(btn->size()*1.5).toImage().scaled(btn->size()*1.5).save(&buffer, "PNG");
        //将icon转化为pixmap再缩放图像，最后保存为PNG格式的字节数组
        QString html = QString("<img src='data:image/png;base64,%1'>").arg(QString::fromLatin1(imageData.toBase64(QByteArray::Base64Encoding)));
        //将字节数组转化为Base64编码的字符串，并且嵌入到HTML代码中
        QToolTip::showText(QCursor::pos(), html);
    }
    else if (event->type() == QEvent::Leave)
    {
        lab1->hide();
    }

    // 将事件传递给父类的事件过滤器
    return QObject::eventFilter(this, event);
}



