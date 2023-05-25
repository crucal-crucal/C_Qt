
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videowidget.h"

#include <QJsonDocument>
#include <QJsonObject>


void MainWindow::setIcon()
{
    ui->tbtn_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->tbtn_pause->setIcon(QIcon(":/images/103.bmp"));
    ui->tbtn_stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->tbtn_last->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->tbtn_next->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->tbtn_mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAcceptDrops(true);
    ui->setupUi(this);
    m_net = new MyNetWork(this);

    m_model= new QStringListModel(this);    //创建数据模型
    m_model->setStringList(m_strlist);      //为模型设置StringList，会导入StringList的内容

    ui->listView->setModel(m_model);        //为listView设置数据模型

    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑

    connect(m_net, &MyNetWork::SearchFinished, this, [this](QVector<QUrl> v){
        for (auto &c:v)
            m_strlist.emplace_back(c.toString());
        m_model->setStringList(m_strlist);
    });

    this->resize(450, 400);
//    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口边框
    player = new QMediaPlayer;
    this->output = new QAudioOutput(this);
    player->setAudioOutput(output);
    ui->m_widget->hide();
    ui->plainTextEdit->hide();
    ui->lab_pixmap->hide();
    //m_videoWidget = new videowidget;
    player->setVideoOutput(ui->m_widget);
    setIcon();


    ui->btn_cycle->setChecked(1);
    ui->tbtn_play->setChecked(0);

    ui->menuBar->setStyleSheet("background-color:pink;");
    connect(ui->tbtn_mute, &QToolButton::clicked, this, [&](){
        output->setMuted(!output->isMuted());
        auto muted = output->isMuted();
        ui->tbtn_mute->setIcon(style()->standardIcon(muted ? QStyle::SP_MediaVolumeMuted : QStyle::SP_MediaVolume));
    });

    connect(player, &QMediaPlayer::durationChanged, this, [&](qint64 duration){
        ui->label_time->setText(QString("%1:%2").arg(duration/1000/60, 2, 10, QChar('0')).arg(duration/1000%60, 2, 10, QChar('0')));
        ui->hSlider_progress->setRange(0, duration);
    });
    connect(player, &QMediaPlayer::positionChanged, this, [&](qint64 pos){
        ui->label_played->setText(QString("%1:%2").arg(pos/1000/60, 2, 10, QChar('0')).arg(pos/1000%60, 2, 10, QChar('0')));
        ui->hSlider_progress->setValue(pos);
    });
    connect(ui->hSlider_progress, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);

    connect(player, &QMediaPlayer::playbackStateChanged, this,  &MainWindow::do_stateChanged);

//    connect(player,&QMediaPlayer::positionChanged,      //播放位置发生变化
//            this, &MainWindow::do_positionChanged);

//    connect(player,&QMediaPlayer::durationChanged,      //播放源长度发生变化
//            this, &MainWindow::do_durationChanged);

//    connect(player, &QMediaPlayer::sourceChanged,       //播放源发生变化
//            this, &MainWindow::do_sourceChanged);

//    connect(player, &QMediaPlayer::metaDataChanged,     //元数据发生变化
//            this,  &MainWindow::do_metaDataChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_stateChanged(QMediaPlayer::PlaybackState state)
{//播放器状态变化时执行，更新按钮状态，或播放下一曲
    ui->tbtn_play->setEnabled(state!=QMediaPlayer::PlayingState);
    ui->tbtn_pause->setEnabled(state==QMediaPlayer::PlayingState);
    ui->tbtn_stop->setEnabled(state==QMediaPlayer::PlayingState);

    //播放完一曲后停止了，如果loopPlay为true，自动播放下一曲
    if (loopplay && (state ==QMediaPlayer::StoppedState))
    {
//        qDebug()<<1;
        QModelIndex curidx = ui->listView->currentIndex();

        auto idx = (curidx.row()+1) % m_model->rowCount();
        curidx = curidx.sibling(idx, curidx.column());//获取当前项的下一项
        ui->listView->setCurrentIndex(curidx);
        player->play();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    auto pos = player->position();//当前位置
    auto dur = player->duration();//总进度

    if(event->key() == Qt::Key_End)
    {
        player->setPosition(std::min(pos+1000, dur));
    }
    else if(event->key()==Qt::Key_Home)
    {
        player->setPosition(std::max(pos-1000, 0ll));
    }
    else if(event->key()==Qt::Key_Alt)
    {
        if(!ispause)
        {
            player->pause();
            ispause = true;
        }
        else
        {
            player->play();
            ispause = false;
        }
    }
    else if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        on_Btn_Serch_clicked();
    }

    QMainWindow::keyPressEvent(event);
//    event->accept();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QSize sz = ui->plainTextEdit->size();
    ui->plainTextEdit->resize(this->width()-10, sz.height());
    event->accept();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    //qDebug()<<"拖动";
    if(event->mimeData()->hasUrls())
    {
        QUrl url = event->mimeData()->urls()[0];
        QString s = QFileInfo(url.toLocalFile()).suffix().toLower();
        if(s == "mp4" || s == "jpg" || s == "png" || s == "mp3" || s == "wav")
            event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QUrl url = event->mimeData()->urls()[0];
    QString path = url.path();
    QString s = QFileInfo(url.toLocalFile()).suffix().toLower();
    if(s == "mp4")
    {
        if(!ui->m_widget->isVisible()) ui->m_widget->show();
        m_strlist.emplaceBack(path);
        m_model->setStringList(m_strlist);
        player->setSource(url);
        player->play();
    }
    else if(s == "jpg" || s == "png")
    {
        if(!ui->lab_pixmap->isVisible()) ui->lab_pixmap->show();
        QString s = event->mimeData()->urls()[0].path();
        s = s.right(s.length()-1);
        QPixmap map(s);
        ui->lab_pixmap->setPixmap(map);
        ui->lab_pixmap->setScaledContents(true);
    }
    else if(s == "mp3" || s == "wav")
    {
        m_strlist.emplaceBack(path);
        m_model->setStringList(m_strlist);
        player->setSource(url);
        player->play();
    }
    event->accept();
}


void MainWindow::on_tbtn_play_clicked(bool checked)
{
    auto curidx = ui->listView->currentIndex();
    QString filname = ui->listView->model()->data(curidx).toString();

    ui->statusbar->showMessage(filname.section("/", -1, -1));
    player->setSource(QUrl::fromLocalFile(filname));
    player->play();
}


void MainWindow::on_tbtn_pause_clicked(bool checked)
{
    player->pause();
}


void MainWindow::on_tbtn_stop_clicked(bool checked)
{
    player->stop();
}


void MainWindow::on_tbtn_next_clicked()
{
    QModelIndex curidx = ui->listView->currentIndex();
    int currow = curidx.row()+1;
    currow %= m_model->rowCount();

    curidx = curidx.sibling(currow, curidx.column());//获取当前项的下一项
    ui->listView->setCurrentIndex(curidx);
    QString filname = ui->listView->model()->data(ui->listView->currentIndex()).toString();
    ui->statusbar->showMessage(filname.section("/", -1, -1));
    player->setSource(QUrl::fromLocalFile(filname));
    player->play();
}


void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    auto curidx = ui->listView->currentIndex();
    QString filname = ui->listView->model()->data(curidx).toString();

    ui->statusbar->showMessage(filname.section("/", -1, -1));
    player->setSource(QUrl::fromLocalFile(filname));
    player->play();
}


void MainWindow::on_tbtn_last_clicked()
{
    QModelIndex curidx = ui->listView->currentIndex();
    int currow = (curidx.row()+m_model->rowCount()-1)%m_model->rowCount();

    curidx = curidx.sibling(currow, curidx.column());//获取当前项的下一项
    ui->listView->setCurrentIndex(curidx);
    QString filname = ui->listView->model()->data(ui->listView->currentIndex()).toString();
    ui->statusbar->showMessage(filname.section("/", -1, -1));
    player->setSource(QUrl::fromLocalFile(filname));
    player->play();
}

void MainWindow::on_hSlider_sound_valueChanged(int value)
{
    //与音量相关联
    player->audioOutput()->setVolume(value/100.0);
}


void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    player->setPlaybackRate(arg1);
}


void MainWindow::on_btn_cycle_clicked(bool checked)
{
    loopplay = checked;
//    qDebug()<<loopplay;
}


void MainWindow::on_actionvideo_triggered()
{
    if(!video_isshow)
    {
        ui->m_widget->show();
        video_isshow = true;
    }
    else
    {
        ui->m_widget->hide();
        video_isshow = false;
    }
}


void MainWindow::on_actionplainTextEdit_triggered()
{
    if(!plain_isshow)
    {
        ui->plainTextEdit->show();
        plain_isshow = true;
    }
    else
    {
        ui->plainTextEdit->hide();
        plain_isshow = false;
    }
}


void MainWindow::on_actionlabel_triggered()
{
    if(!label_isshow)
    {
        ui->lab_pixmap->show();
        label_isshow = true;
    }
    else
    {
        ui->lab_pixmap->hide();
        label_isshow = false;
    }
}


void MainWindow::on_action_add_triggered()
{
    auto filname = QFileDialog::getOpenFileNames(this, "open a file",
                                                   "D:\\CloudMusic\\Mymusic",
                                                   "所有文件(*.*);;音频文件(*.mp3 *.wav *wma);;视频文件(*.mp4)");
    for (auto &c:filname)
        m_strlist.emplaceBack(c);

    m_model->setStringList(m_strlist);

//    ui->listView->setModel(m_model);
}


void MainWindow::on_action_remove_triggered()
{
    //删除当前项
    QModelIndex index=ui->listView->currentIndex();  //获取当前项的模型索引
    m_model->removeRow(index.row());       //删除当前项
}


void MainWindow::on_action_clear_triggered()
{
    QAbstractItemModel *model = ui->listView->model();
    auto cnt = model->rowCount();
    for (int i=cnt-1;i>=0;i--)
    {
        model->removeRow(i);
    }

//    //清除列表
//    m_model->removeRows(0,m_model->rowCount());   //清除数据模型的所有项
}


void MainWindow::on_action_exit_triggered()
{
    this->close();
    player->pause();
}

void MainWindow::on_Btn_Serch_clicked()
{
    QString str = ui->lineEdit->text();
    m_net->search(str);
    m_strlist.clear();
    m_model->setStringList(m_strlist);
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    auto row = index.row();
    player->setSource(m_strlist[row]);
    player->play();
}

