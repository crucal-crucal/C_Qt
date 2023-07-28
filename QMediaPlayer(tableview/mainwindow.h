
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
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>

#include "videowidget.h"
#include "mynetwork.h"
#include "my_music.h"

#define     FixedColumnCount    2       //文件固定6列

const QString dbusername = "root";
const QString dbpasswd = "540869cf";


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool connectDB();//连接数据库

public:
    void setIcon();

    void iniModelData(QStringList&);      //从StringList初始化数据模型

    void openDataFile(QString aFileName);

private slots:
    //自定义槽函数，与QItemSelectionModel的currentChanged()信号连接
//    void do_currentChanged(const QModelIndex &current, const QModelIndex &previous);

    void on_tbtn_play_clicked(bool checked);

    void on_tbtn_pause_clicked(bool checked);

    void on_tbtn_stop_clicked(bool checked);

    void on_tbtn_next_clicked();

//    void on_listView_doubleClicked(const QModelIndex &index);

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

    void on_act_openfile_triggered();

    void on_act_save_triggered();

    void on_act_mysqlquery_triggered();

    void on_act_mysqlinsert_triggered();

private:
    Ui::MainWindow *ui;

private:
    QMediaPlayer *player;
    QAudioOutput *output;
//    QStringList m_strlist;
//    QStringListModel *m_model; //数据模型
    QStringList m_strlist;
    QStandardItemModel  *m_model;      //数据模型
    QItemSelectionModel *m_selection;  //Item选择模型
    QStandardItem *aItem;
    QLabel *lab;
    bool loopplay = true, ispause = false, video_isshow = false, plain_isshow = false, label_isshow = false;
    MyNetWork *m_net;
    QVector<QString> musicPath;
    QVector<music> m_music;

protected:
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
    void dragEnterEvent(QDragEnterEvent *event)override;
    void dropEvent(QDropEvent *event)override;
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MAINWINDOW_H
