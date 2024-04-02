
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videowidget.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

bool MainWindow::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    QString dbname = "mymusic";

    db.setHostName("localhost");
    db.setUserName(dbusername);
    db.setPassword(dbpasswd);
    db.setDatabaseName(dbname);

    if(!db.open())
    {
        QString str = "连接数据库失败：" + db.lastError().text();
        QMessageBox::information(this, "打开数据库", str);
        return false;
    }
    else
    {
        QMessageBox::information(this, "打开数据库", QString("连接数据库%1成功！！！！").arg(dbname));
        return true;
    }
}

//从一个StringList 获取数据，初始化数据Model
void MainWindow::openDataFile(QString aFileName)
{
    QStringList aFileContent;
    QFile aFile(aFileName);
    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //以只读文本方式打开文件
    {
        QTextStream aStream(&aFile);  //用文本流读取文件
//        ui->plainTextEdit->clear();
        while (!aStream.atEnd())
        {
            QString str=aStream.readLine();     //读取文件的一行
//            ui->plainTextEdit->appendPlainText(str);
            aFileContent.append(str);
        }
        aFile.close();

//        labCurFile->setText("当前文件："+aFileName);   //状态栏显示
//        ui->actAppend->setEnabled(true);
//        ui->actInsert->setEnabled(true);
//        ui->actDelete->setEnabled(true);
//        ui->actSave->setEnabled(true);
        iniModelData(aFileContent);   //从StringList的内容初始化数据模型
    }
}


void MainWindow::iniModelData(QStringList &aFileContent)
{
    int rowCnt=aFileContent.size();    //文本行数，第1行是标题
    m_model->setRowCount(rowCnt-1);    //实际数据行数

    //设置表头
    QString header=aFileContent.at(0);  //第1行是表头
    QStringList headerList=header.split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);
    m_model->setHorizontalHeaderLabels(headerList);    //设置表头文字

    //设置表格数据
    int j;
    QStandardItem   *aItem;
    for (int i =1;i < rowCnt; i++)
    {
        QString aLineText = aFileContent.at(i);   //获取 数据区 的一行
        //一个或多个空格、TAB等分隔符隔开的字符串， 分解为一个StringList
        QStringList tmpList=aLineText.split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);
        for (j=0;j<FixedColumnCount;j++)
        { //不包含最后一列
            aItem=new QStandardItem(tmpList.at(j)); //创建item
            m_model->setItem(i-1,j,aItem);          //设置Item
        }
    }
}

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

    connect(m_net, &MyNetWork::SearchFinished, this, [this](QVector<music> v){
        for (auto &c:v)
        {
            m_music.emplace_back(c);
            auto str = c.url.toString();
            musicPath.emplace_back(str);
            aItem = new QStandardItem(str);       //创建Item

            m_model->insertRow(m_model->rowCount(),aItem);    //插入一行
            QModelIndex curIndex=m_model->index(m_model->rowCount()-1,0); //创建最后一行的ModelIndex
            m_selection->clearSelection(); //清空选择项
            m_selection->setCurrentIndex(curIndex,QItemSelectionModel::Select);    //设置刚插入的行为当前选择行
        }
    });

    m_model = new QStandardItemModel(0, 0, this); //创建数据模型
    m_selection = new QItemSelectionModel(m_model,this);           //创建选择模型

//    //选择当前单元格变化时的信号与槽
//    connect(m_selection,&QItemSelectionModel::currentChanged,
//            this,&MainWindow::do_currentChanged);

    ui->tableView->setModel(m_model);  //设置数据模型
    ui->tableView->setSelectionModel(m_selection); //设置选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑

    this->resize(700, 400);
//    this->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口边框
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

//void MainWindow::saveFile(QString url, QString time)
//{
//    //保存为文件
//    QString curPath=QCoreApplication::applicationDirPath(); //获取应用程序的路径
//    //调用打开文件对话框选择一个文件
//    //    QString aFileName=QFileDialog::getSaveFileName(this,tr("选择一个文件"),curPath,
//    //                                                     "井斜数据文件(*.txt);;所有文件(*.*)");
//    QString aFileName = "E:\\QT\\MyQt\\QMediaPlayer(tableview\\1.txt";
//    if (aFileName.isEmpty()) //未选择文件，退出
//        return;

//    QFile aFile(aFileName);
//    if (!(aFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)))
//        return; //以读写、覆盖原有内容方式打开文件

//    QTextStream aStream(&aFile); //用文本流读取文件
//    QString str;
//    str=url+"\t\t" + time+"\t\t";  //以TAB见隔开
//    aStream<<str<<"\n";  //文件里需要加入换行符 \n
//}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() != QEvent::KeyPress)      //不是KeyPress事件，退出
        return QWidget::eventFilter(watched,event);

    QKeyEvent *keyEvent=static_cast<QKeyEvent *>(event);
    if (keyEvent->key() != Qt::Key_Delete)      //按下的不是Delete键，退出
        return QWidget::eventFilter(watched,event);
    return true;    //表示事件已经被处理
}


void MainWindow::do_stateChanged(QMediaPlayer::PlaybackState state)
{//播放器状态变化时执行，更新按钮状态，或播放下一曲
    ui->tbtn_play->setEnabled(state!=QMediaPlayer::PlayingState);
    ui->tbtn_pause->setEnabled(state==QMediaPlayer::PlayingState);
    ui->tbtn_stop->setEnabled(state==QMediaPlayer::PlayingState);

    //播放完一曲后停止了，如果loopPlay为true，自动播放下一曲
    if (loopplay && (state ==QMediaPlayer::StoppedState))
    {
//        on_tbtn_next_clicked();
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
//        m_strlist.emplaceBack(path);
//        m_model->setStringList(m_strlist);
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
//        m_strlist.emplaceBack(path);
//        m_model->setStringList(m_strlist);
        player->setSource(url);
        player->play();
    }
    event->accept();
}


void MainWindow::on_tbtn_play_clicked(bool checked)
{
    auto curidx = ui->tableView->currentIndex();
    QString filname = ui->tableView->model()->data(curidx).toString();

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
    QModelIndex curidx = ui->tableView->currentIndex();
    int currow = curidx.row()+1;
    currow %= m_model->rowCount();

    curidx = curidx.sibling(currow, curidx.column());//获取当前项的下一项
    ui->tableView->setCurrentIndex(curidx);
    QString filname = ui->tableView->model()->data(ui->tableView->currentIndex()).toString();
    ui->statusbar->showMessage(filname.section("/", -1, -1));
    player->setSource(QUrl::fromLocalFile(filname));
    player->play();
}


void MainWindow::on_tbtn_last_clicked()
{
    QModelIndex curidx = ui->tableView->currentIndex();
    int currow = (curidx.row()+m_model->rowCount()-1)%m_model->rowCount();

    curidx = curidx.sibling(currow, curidx.column());//获取当前项的下一项
    ui->tableView->setCurrentIndex(curidx);
    QString filname = ui->tableView->model()->data(ui->tableView->currentIndex()).toString();
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
    {
        musicPath.emplace_back(c);
        aItem = new QStandardItem(c);       //创建Item

        m_model->insertRow(m_model->rowCount(),aItem);    //插入一行
        QModelIndex curIndex=m_model->index(m_model->rowCount()-1,0); //创建最后一行的ModelIndex
        m_selection->clearSelection(); //清空选择项
        m_selection->setCurrentIndex(curIndex,QItemSelectionModel::Select);    //设置刚插入的行为当前选择行
    }
    ui->tableView->setModel(m_model);
}


void MainWindow::on_action_remove_triggered()
{
    //删除当前项
    QModelIndex index=ui->tableView->currentIndex();  //获取当前项的模型索引
    m_model->removeRow(index.row());       //删除当前项
}


void MainWindow::on_action_clear_triggered()
{
//    QAbstractItemModel *model = ui->tableView->model();
//    auto cnt = model->rowCount();
//    for (int i=cnt-1;i>=0;i--)
//    {
//        model->removeRow(i);
//    }

    //清除列表
    m_model->removeRows(0,m_model->rowCount());   //清除数据模型的所有项
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
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    loopplay = true;
//    qDebug()<<ui->tableView->currentIndex()<<"---\n---"<<index;
    auto idx = index.row();
    auto str = index.data(Qt::DisplayRole).toString();
    auto s = str.right(3);
    if (s == "mp4")
    {
        if(!ui->m_widget->isVisible())
            ui->m_widget->show();
    }
    else
    {
        if(ui->m_widget->isVisible())
            ui->m_widget->hide();
    }
    player->setSource(QUrl::fromLocalFile(str));
    player->play();
}


void MainWindow::on_act_openfile_triggered()
{
    QString curPath=QCoreApplication::applicationDirPath();
    QString aFileName=QFileDialog::getOpenFileName(this,"打开一个文件",curPath,
                                                     "井数据文件(*.txt);;所有文件(*.*)");
    QFile file(aFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Failed to open file: " + file.errorString());
        return;
    }

    // 读取文本文件并将每一行的文件路径添加到 QStringList 中
    QStringList fileList;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        fileList.append(line);
    }

    // 关闭文本文件
    file.close();

    QList<QStandardItem *> list;
    for (const QString &filePath : fileList) {
        // 创建文件路径项
        QStandardItem *pathItem = new QStandardItem(filePath);
        list.emplaceBack(pathItem);
    }
    m_model->clear();
    m_model->appendColumn(list);
    ui->tableView->setModel(m_model);
}


void MainWindow::on_act_save_triggered()
{
    //保存为文件
    QString curPath=QCoreApplication::applicationDirPath(); //获取应用程序的路径
    //调用打开文件对话框选择一个文件
    QString aFileName=QFileDialog::getSaveFileName(this,tr("选择一个文件"),curPath,
                                                     "井斜数据文件(*.txt);;所有文件(*.*)");

    if (aFileName.isEmpty()) //未选择文件，退出
        return;

    QFile aFile(aFileName);
    if (!(aFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)))
        return; //以读写、覆盖原有内容方式打开文件

    QTextStream aStream(&aFile); //用文本流读取文件

    for (int i=0;i<m_model->rowCount();i++)
    {
        QString s = m_model->item(i, 0)->text();
        aStream<<s<<"\n";
    }
    aFile.close();

    return;
}


void MainWindow::on_act_mysqlquery_triggered()
{
    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    model->setQuery("select *from music_1");
    //    model->setHeaderData(0, Qt::Horizontal, tr("id"));
    //    model->setHeaderData(1, Qt::Horizontal, tr("name"));
    ui->tableView->setModel(model);
}


void MainWindow::on_act_mysqlinsert_triggered()
{
    QSqlQuery query;//这里不能用指针，它是一个值类型，因此不能使用指针进行声明和分配内存
    for (int i=0;i<m_model->rowCount();i++)
    {
        QString s = m_model->item(i, 0)->text();
        qDebug()<<s;
        query.prepare("insert into music_1 (URL) "
                      "values (:url)");
        query.bindValue(":url", s);
        query.exec();
    }
}

