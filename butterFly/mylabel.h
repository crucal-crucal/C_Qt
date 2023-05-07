#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QWidget>


class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

signals:

private slots:
    void fly();

private:
    QTimer *tm;
    bool f = true;
    QPixmap pixmap;
};

#endif // MYLABEL_H
