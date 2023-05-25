
#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H


#include <QMainWindow>
#include <QVideoWidget>
#include <QKeyEvent>
#include <QMouseEvent>

class videowidget : public QVideoWidget
{
    Q_OBJECT

public:
    videowidget(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    bool isfull = false;
};

#endif // VIDEOWIDGET_H
