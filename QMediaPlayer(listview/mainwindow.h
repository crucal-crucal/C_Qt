
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QAudioOutput>
#include <QVideoWidget>
#include <QResizeEvent>
#include <QDragMoveEvent>
#include <QMouseEvent>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QModelIndex>
#include <Qurl>
#include <QListView>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>

#include "videowidget.h"
#include "mynetwork.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    void setIcon();

private slots:

    void on_tbtn_play_clicked(bool checked);

    void on_tbtn_pause_clicked(bool checked);

    void on_tbtn_stop_clicked(bool checked);

    void on_tbtn_next_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_tbtn_last_clicked();

    void on_hSlider_sound_valueChanged(int value);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_btn_cycle_clicked(bool checked);

    void do_stateChanged(QMediaPlayer::PlaybackState state);

//    void do_positionChanged(qint64 position);

    void on_actionvideo_triggered();

    void on_actionplainTextEdit_triggered();

    void on_actionlabel_triggered();

    void on_action_add_triggered();

    void on_action_remove_triggered();

    void on_action_clear_triggered();

    void on_action_exit_triggered();

    void on_Btn_Serch_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

private:
    QMediaPlayer *player;
    QAudioOutput *output;
    QStringList m_strlist;
    QStringListModel *m_model; //数据模型
    QLabel *lab;
    //videowidget *m_videoWidget;
    bool loopplay = true, ispause = false, video_isshow = false, plain_isshow = false, label_isshow = false;
    MyNetWork *m_net;
    QVector<QUrl> sings;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
    void dragEnterEvent(QDragEnterEvent *event)override;
    void dropEvent(QDropEvent *event)override;
};

#endif // MAINWINDOW_H
