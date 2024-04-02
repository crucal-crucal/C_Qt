#include "QMyChat.h"
<<<<<<< HEAD

=======
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
#include "ui_QMyChat.h"

QMyChat::QMyChat(QWidget *parent, QString name) :
    QDialog(parent),
    ui(new Ui::QMyChat)
{
    ui->setupUi(this);
    myName = name;
    ui->tbtn_overbold->setToolTip("加粗");
    ui->tbtn_clear->setToolTip("清空");
    ui->tbtn_color->setToolTip("更改颜色");
    ui->tbtn_save->setToolTip("保存");
    ui->tbtn_tilt->setToolTip("倾斜");
    ui->tbtn_underline->setToolTip("下划线");
    this->port = 9999; // 初始化端口
    this->udpSocket = new QUdpSocket(this);

    // 绑定端口
    // 采用ShareAddress模式（即允许其他的服务器连接到相同的地址和端口
    // 特别是用在多客户端监听同一个服务器端接口时特别有效），和ReuseAddresshint模式（重新连接服务器
    this->udpSocket->bind(this->port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    //监听信号
    connect(this->udpSocket, &QUdpSocket::readyRead, this, &QMyChat::RecvMessage);

    // 发送
    connect(ui->btn_send, &QPushButton::clicked, this, &QMyChat::sendMessage);

    // 新用户进入
    sendMsg(UserEnter);

<<<<<<< HEAD
    connect(ui->btn_exit, &QPushButton::clicked, this, [ = ]() {
=======
    connect(ui->btn_exit, &QPushButton::clicked, this, [=](){
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
        this->close();
    });

    // 设置字体
<<<<<<< HEAD
    connect(ui->fontComboBox, &QFontComboBox::currentFontChanged, this, [&](const QFont & font) {
=======
    connect(ui->fontComboBox, &QFontComboBox::currentFontChanged, this, [&](const QFont& font){
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
        ui->textEdit->setCurrentFont(font);
        ui->textBrowser->setCurrentFont(font);
        ui->textEdit->setFocus();
        ui->textBrowser->setFocus();
    });

    // 设置字体大小
<<<<<<< HEAD
    connect(ui->font_Size, &QComboBox::currentTextChanged, this, [ = ](const QString & text) {
=======
    connect(ui->font_Size, &QComboBox::currentTextChanged, this, [=](const QString& text){
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
        ui->textEdit->setFontPointSize(text.toDouble());
        ui->textBrowser->setFontPointSize(text.toDouble());
        ui->textEdit->setFocus();
        ui->textBrowser->setFocus();
    });

    // 加粗文本
<<<<<<< HEAD
    connect(ui->tbtn_overbold, &QToolButton::clicked, this, [ = ](bool bl) {
=======
    connect(ui->tbtn_overbold, &QToolButton::clicked, this, [=](bool bl){
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
        if (bl) {
            ui->textEdit->setFontWeight(QFont::Bold);
            ui->textBrowser->setFontWeight(QFont::Bold);
        } else {
            ui->textEdit->setFontWeight(QFont::Normal);
            ui->textBrowser->setFontWeight(QFont::Normal);
        }
        // 获取焦点，在用户界面中突出显示一个控件，以表示当前控件是活动的
        // 能够接受用户的输入，当一个控件获取焦点时，用户可以通过键盘输入来与该控件交互，而不必使用鼠标将光标
        // 移动到该控件上
        ui->textEdit->setFocus();
        ui->textBrowser->setFocus();
    });

    // 字体倾斜
<<<<<<< HEAD
    connect(ui->tbtn_tilt, &QToolButton::clicked, this, [ = ](bool bl) {
=======
    connect(ui->tbtn_tilt, &QToolButton::clicked, this, [=](bool bl){
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
        ui->textEdit->setFontItalic(bl);
        ui->textEdit->setFocus();

        ui->textBrowser->setFontItalic(bl);
        ui->textBrowser->setFocus();
    });

    // 下划线
<<<<<<< HEAD
    connect(ui->tbtn_underline, &QToolButton::clicked, this, [ = ](bool bl) {
=======
    connect(ui->tbtn_underline, &QToolButton::clicked, this, [=](bool bl){
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
        ui->textEdit->setFontUnderline(bl);
        ui->textEdit->setFocus();

        ui->textBrowser->setFontUnderline(bl);
        ui->textBrowser->setFocus();
    });


    // 设置文本颜色
<<<<<<< HEAD
    connect(ui->tbtn_color, &QToolButton::clicked, this, [ = ]() {
=======
    connect(ui->tbtn_color, &QToolButton::clicked, this, [=](){
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
        // 获取当前选择的颜色
        QColor curColor = QColorDialog::getColor(nullptr, this);
        ui->textEdit->setTextColor(curColor);
        ui->textBrowser->setTextColor(curColor);
    });

    // 清空聊天记录
<<<<<<< HEAD
    connect(ui->tbtn_clear, &QToolButton::clicked, this, [ = ]() {
=======
    connect(ui->tbtn_clear, &QToolButton::clicked, this, [=](){
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
        ui->textBrowser->clear();
    });

    // 保存聊天记录
<<<<<<< HEAD
    connect(ui->tbtn_save, &QToolButton::clicked, this, [ = ]() {
=======
    connect(ui->tbtn_save, &QToolButton::clicked, this, [=](){
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
        if (ui->textBrowser->document()->isEmpty()) {
            QMessageBox::warning(this, "警告", "保存的文本不能为空");
        } else {
            QString filename = QFileDialog::getSaveFileName(this, "保存聊天记录", "聊天记录", "(*.txt)");
            if (!filename.isEmpty()) {
                // 保证名称不能为空，才能进行保存
                QFile file(filename);
                file.open(QIODevice::WriteOnly | QFile::Text);
                QTextStream stream(&file);
                stream << ui->textBrowser->toPlainText();
                file.close();
            } else {
                QMessageBox::warning(this, "警告", "保存文件名不能为空！");
            }
        }
    });
<<<<<<< HEAD

    // 发送图片
    connect(ui->tbtn_picTure, &QToolButton::clicked, this, &QMyChat::sendPicture);
=======
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
}

// 广播信号
void QMyChat::sendMsg(QMyChat::Msgtype type)
{
    QByteArray array;
    // 创建流  好处：可以分段
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << type << this->getName(); //流入 类型和用户姓名
    switch (type) {
    case Msg:
<<<<<<< HEAD
        if (this->ui->textEdit->toPlainText() == "") {
=======
        if (this->ui->textEdit->toPlainText() == ""){
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
            QMessageBox::information(this, "警告", "发送内容不能为空!");
            return;
        }
        stream << this->getMeg(); // 流入 普通聊天信息
        break;
<<<<<<< HEAD
    case Picture:
        for (auto &c : this->getPicture()) {
            stream << c;
        }
        break;
=======
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
    case UserEnter:
        break;
    case UserLeft:
        break;
    default:
        break;
    }

    // 书写报文
    this->udpSocket->writeDatagram(array.data(), array.size(), QHostAddress::Broadcast, this->port);
}

QString QMyChat::getName()
{
    return this->myName;
}

QString QMyChat::getMeg()
{
    QString msg = ui->textEdit->toHtml(); // 获取输入框的内容
    ui->textEdit->clear(); // 将内容清空
    ui->textEdit->setFocus(); // 设置光标
    return msg;
}

<<<<<<< HEAD
QVector<QString> QMyChat::getPicture()
{
    QStringList files = QFileDialog::getOpenFileNames(this,
                        "选择文件", "C:\\Windows\\Web\\Wallpaper\\Lenovo",
                        "Images(*.jpg *.png *.xpm)");
    if (files.isEmpty()) {
        QMessageBox::information(this, "选择文件", "请选择至少一张图片");
        return QVector<QString>();
    }

    for (auto &c : files) {
        picture.emplaceBack(c);
    }

    return picture;
}

=======
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
// 用户进入处理
void QMyChat::userEnter(QString username)
{
    bool isEmpty = ui->tableWidget->findItems(username, Qt::MatchExactly).isEmpty();
    if (isEmpty) {
        QTableWidgetItem *user = new QTableWidgetItem(username);
        ui->tableWidget->insertRow(0);
        ui->tableWidget->setItem(0, 0, user);
//        ui->textBrowser->setTextColor();
        ui->textBrowser->append(username + "用户已上线！");
        ui->lab_num->setText(QString("在线人数：%1人").arg(ui->tableWidget->rowCount()));

        sendMsg(QMyChat::UserEnter);
    }
}

// 用户离开处理
void QMyChat::userLeft(QString username, QString time)
{
    bool isEmpty = ui->tableWidget->findItems(username, Qt::MatchExactly).isEmpty();
    if (!isEmpty) {
        // 寻找行
        int row = ui->tableWidget->findItems(username, Qt::MatchExactly).constFirst()->row();
        // 移除改行
        ui->tableWidget->removeRow(row);

//        ui->textBrowser->setTextColor();
        ui->textBrowser->append(username + "用户于 " + time + "下线");
        ui->lab_num->setText(QString("在线人数：%1人").arg(ui->tableWidget->rowCount()));
    }
}

// 接收信息
void QMyChat::RecvMessage()
{
    // 接受udp套接字中数据包的大小
    qint64 size = this->udpSocket->pendingDatagramSize();

    int mySize = static_cast<int>(size);

    QByteArray array = QByteArray(mySize, 0); // 初始化为0
    // 将信息读取到array中
    this->udpSocket->readDatagram(array.data(), size);
    QDataStream stream(&array, QIODevice::ReadOnly);
    int msgtype;
    stream >> msgtype; // 读取类型
<<<<<<< HEAD
    QString name, msg, pixmap; // 用户名, 聊天信息, 图片
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
//    QTextDocument *doc = ui->textBrowser->document(); // 获取textBrowser的文档
    QTextCursor cursor(ui->textBrowser->textCursor());

    switch (msgtype) {
    case Msg: {// 普通聊天
        stream >> name >> msg;
=======
    QString name, msg; // 用户名和聊天信息
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    switch (msgtype) {
    case Msg: // 普通聊天
        stream >> name >> msg;

>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
        // 增加聊天记录
//        ui->textBrowser->setTextColor();
        ui->textBrowser->setCurrentFont(QFont("Times New Roman", 12));
        ui->textBrowser->append("[" + name + "]" + time);
        ui->textBrowser->append(msg);
        break;
<<<<<<< HEAD
    }
    case Picture: { // 图片
        stream >> name >> pixmap;
        QSize size(100, 100);
//        使用Qt::KeepAspectRatio参数来保持图像的宽高比
        QPixmap scaledPixmap = QPixmap(pixmap).scaled(size, Qt::KeepAspectRatio);
        ui->textBrowser->append("[" + name + "]" + time);
        cursor.insertText("\n"); // 需要加入换行操作符，否则会出现紧跟在名字后面的情况
        cursor.insertImage(scaledPixmap.toImage());
        break;
    }
    case UserEnter: {
        stream >> name;
        userEnter(name);
        break;
    }
    case UserLeft: {
        stream >> name;
        userLeft(name, time);
        break;
    }
=======
    case UserEnter:
        stream >> name;
        userEnter(name);
        break;
    case UserLeft:
        stream >> name;
        userLeft(name, time);
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
    default:
        break;
    }
}

// 发送按钮
void QMyChat::sendMessage()
{
    sendMsg(QMyChat::Msg);
}

<<<<<<< HEAD
void QMyChat::sendPicture()
{
    sendMsg(QMyChat::Picture);
}

=======
>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
QMyChat::~QMyChat()
{
    delete ui;
}

// 关闭窗口事件
void QMyChat::closeEvent(QCloseEvent *event)
{
    emit closeWidget();

    sendMsg(QMyChat::UserLeft);

    this->udpSocket->close();
    this->udpSocket->deleteLater();
    event->accept();
}

// 键盘事件响应
void QMyChat::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        sendMessage();
    }
}
