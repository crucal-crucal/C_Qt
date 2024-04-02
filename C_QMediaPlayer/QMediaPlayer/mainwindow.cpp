
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videowidget.h"

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
    this->resize(1000, 600);
//    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口边框
    m_network = new MyNetWork(this);

    player = new QMediaPlayer;
    this->output = new QAudioOutput(this);
    player->setAudioOutput(output);
    ui->m_widget->hide();
    ui->plainTextEdit->hide();
    ui->lab_pixmap->hide();

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

    connect(m_network, &MyNetWork::SearchFinished, this, [&](QVector<music> v){
        m_music = v;
    });
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
        int count=ui->listWidget->count();
        int curRow=ui->listWidget->currentRow();
        curRow++;
        curRow %= count;
        ui->listWidget->setCurrentRow(curRow);
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
//        qDebug()<<event->key()<<Qt::Key_Space;
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
        on_Btn_Search_clicked();
    }
    QMainWindow::keyPressEvent(event);
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
        if(s == "mp4" || s == "jpg" || s == "png")
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
        QListWidgetItem *item = new QListWidgetItem(path);
        ui->listWidget->insertItem(ui->listWidget->currentRow(), item);
        player->setSource(url);
        player->play();
    }
    else
    {
        if(!ui->lab_pixmap->isVisible()) ui->lab_pixmap->show();
        QString s = event->mimeData()->urls()[0].path();
        s = s.right(s.length()-1);
        QPixmap map(s);
        ui->lab_pixmap->setPixmap(map);
        ui->lab_pixmap->setScaledContents(true);
    }
    event->accept();
}


void MainWindow::on_tbtn_play_clicked(bool checked)
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(item!=nullptr)
    {
        auto row = ui->listWidget->currentRow();
        player->setSource(m_music[row].url);
        player->play();
        ui->statusbar->showMessage(m_music[row].title + "-" + m_music[row].Author + "-" + m_music[row].Album);
        loopplay=false;
    }
    else
    {
        QMessageBox::information(this, "提示信息", "放不起");
    }
}


void MainWindow::on_tbtn_pause_clicked(bool checked)
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(item!=nullptr)
    {
        player->pause();
    }
    else
    {
        QMessageBox::information(this, "提示信息", "没法儿暂停");
    }
}


void MainWindow::on_tbtn_stop_clicked(bool checked)
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(item!=nullptr)
    {
        player->stop();
    }
    else
    {
        QMessageBox::information(this, "提示信息", "电脑坏了");
    }
}


void MainWindow::on_tbtn_next_clicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(item!=nullptr)
    {
        int count = ui->listWidget->count(), row = ui->listWidget->currentRow();
        row++;
        row %= count;
        ui->listWidget->setCurrentRow(row);
        player->setSource(m_music[row].url);
        player->play();
        ui->statusbar->showMessage(m_music[row].title + "-" + m_music[row].Author + "-" + m_music[row].Album);
    }
    else
    {
        QMessageBox::information(this, "提示信息", "没有歌了");
    }
}


void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
//    currentrow = index.row();
}


void MainWindow::on_tbtn_last_clicked()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(item!=nullptr)
    {
        int count = ui->listWidget->count(), row = ui->listWidget->currentRow();
        row = (row - 1 + count) % count;
        ui->listWidget->setCurrentRow(row);
        player->setSource(m_music[row].url);
        player->play();
        ui->statusbar->showMessage(m_music[row].title + "-" + m_music[row].Author + "-" + m_music[row].Album);
    }
    else
    {
        QMessageBox::information(this, "提示信息", "没有歌了");
    }
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
    QString filname = QFileDialog::getOpenFileName(this, "open a file",
                                                   "D:\\CloudMusic\\WAVmusic",
                                                   "所有文件(*.*);;音频文件(*.mp3 *.wav *wma);;视频文件(*.mp4)");
    QListWidgetItem* aItem=new QListWidgetItem(filname); //创建一个项
    ui->listWidget->insertItem(ui->listWidget->currentRow(),aItem); //在当前行的前面插入一个项
}


void MainWindow::on_action_remove_triggered()
{
    int row=ui->listWidget->currentRow();   //当前行号
    QListWidgetItem* aItem=ui->listWidget->takeItem(row); //移除指定行的项，但不delete
    delete aItem;   //需要手工删除对象
}


void MainWindow::on_action_clear_triggered()
{
    ui->listWidget->clear();
}


void MainWindow::on_action_exit_triggered()
{
    this->close();
    player->pause();
}


void MainWindow::on_Btn_Search_clicked()
{
    QString str = ui->lineEdit->text();
    m_network->search(str);
    for (auto &c:m_music)
    {
        My_Item *item = new My_Item(c.title, c.Author, c.Album);
        QListWidgetItem *aitem = new QListWidgetItem();
        ui->listWidget->addItem(aitem);
        ui->listWidget->setItemWidget(aitem, item);
    }
}


void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ui->statusbar->showMessage(m_music[currentRow].title + "-" + m_music[currentRow].Author + "-" + m_music[currentRow].Album);
    player->setSource(m_music[currentRow].url);
    player->play();
}

