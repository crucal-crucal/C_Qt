#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <mylabel.h>
#include <QRandomGenerator>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

//private slots:
//    void fly();

private slots:
    void on_Btn_music_clicked();

private:
    Ui::Widget *ui;

private:
    const int butterflynum = 100;
    QVector<MyLabel *> butterfly;
    QMediaPlayer *player;
    QAudioOutput *output;
};
#endif // WIDGET_H
