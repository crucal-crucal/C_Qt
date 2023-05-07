#include "lgoin.h"
#include "ui_lgoin.h"
#include <QMovie>

Lgoin::Lgoin(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Lgoin)
    , m_label(new QLabel)
{
    //去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);
    //背景透明
    setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);

    //给Label设置动画
    QMovie *movie = new QMovie(this);//用来播放gif图片
    movie->setFileName(":/images/01e9d25debe9e7a801213853a781cd.gif");
    movie->start();
    ui->Label_top->setMovie(movie);

    //username提示
    ui->username->lineEdit()->setPlaceholderText("QQ号码/手机/邮箱");
    m_label->setPixmap(QPixmap(":/images/1 (2).jpg"));
    //m_label->resize(300, 300);//300,300的窗口
    m_label->setScaledContents(1);//自适应图片大小

    //设置头像为圆形
    ui->Lab_portrait->setMask(QRegion(ui->Lab_portrait->rect(), QRegion::RegionType::Ellipse));
}

Lgoin::~Lgoin()
{
    delete ui;
}


void Lgoin::on_Btn_min_clicked()
{
    //最小化窗口
    this->showMinimized();
}


void Lgoin::on_Btn_close_clicked()
{
    this->close();
}

//点击登录按钮处理函数
void Lgoin::on_Btn_login_clicked()
{
    this->hide();
    mydig = new My_Dialog(this);
    mydig->show();
    mydig->exec();
}



void Lgoin::on_Btn_Qrcode_clicked()
{
    //this->hide();
    m_label->show();
}


void Lgoin::on_Btn_Register_clicked()
{
    this->hide();
    my_res = new My_register(this);
    my_res->show();
    my_res->exec();
}


void Lgoin::on_Btn_findpasswd_clicked()
{
    this->hide();
    findp = new My_findpasswd(this);
    findp->show();
    findp->exec();
}

