<<<<<<< HEAD

#include "QMyClients.h"

QMyClients::QMyClients(QObject *parent) : QObject{parent} {
  this->tcpSocket = new QTcpSocket(this);
  this->myAudio = new QMyAudio();
  connect(
      tcpSocket, &QTcpSocket::connected, this,
      &QMyClients::sendUserMessgeToServer); // 服务器连接后向服务器发送一次信息
  connect(tcpSocket, &QTcpSocket::readyRead, this,
          &QMyClients::ReadAllData); // 读取服务器发送过来的数据包
  connect(tcpSocket, &QTcpSocket::disconnected, this, [=]() {
    QMessageBox::warning(nullptr, tr("错误"),
                         tr("亲，你怎么搞得哦，服务器断开了哦！"));
    tcpSocket->close();
  });
  this->decompression = new QMyDataDecompression(this); // 实例化数据处理对象
  //    QMetaObject::invokeMethod(this,"connectToServer",Qt::QueuedConnection);
}

QMyClients::~QMyClients() {}

QString QMyClients::getLocalIP() {
  // 获取本机IPv4地址
  QString hostName = QHostInfo::localHostName(); // 本地主机名
  QHostInfo hostInfo = QHostInfo::fromName(hostName);
  QString localIP = "";

  QList<QHostAddress> addList = hostInfo.addresses(); // 本机IP地址列表
  if (addList.isEmpty())
    return localIP;

  foreach (QHostAddress aHost, addList)
    if (QAbstractSocket::IPv4Protocol == aHost.protocol()) {
      localIP = aHost.toString();
      break;
    }
  return localIP;
}

void QMyClients::ReadAllData() {
#ifdef DEBUG
  qDebug() << "================测试接收服务器：接收数据开始===================="
              "=================";
#endif

  QByteArray data = this->tcpSocket->readAll(); // 读取来自服务器的数据包
  receiveBuffer.push(data);
#ifdef DEBUG
  qDebug() << "================测试接收服务器成功=============================="
              "================";
#endif
}

void QMyClients::sendUserMessgeToServer() {
  QMessageBox::information(nullptr, tr("成功"),
                           tr("宝贝，已成功连接服务器了哦!"));
}

void QMyClients::sendAudiotoServer() {
  myAudio->initMyAudio();  // 初始化音频组件
  myAudio->startMyAudio(); // 开始录音
  connect(myAudio->myIODevice, &QMyIODevice::sendAudioData, this,
          [&](QByteArray array) {
            qDebug() << "send Audio\t";
            QByteArray audio = QByteArray();
            audio.clear();
            array = this->decompression->packVideoData(audio, array);
            tcpSocket->write(array); // 把字节发送给服务器
            //        myAudio->stopMyAudio();//发送完成，暂停录音
          });
}

void QMyClients::sendMessageToSever(QString text) {
#ifdef DEBUG
  qDebug() << "=============================测试客户端发送数据================="
              "=====================";
#endif
  QByteArray str = text.toUtf8();
  str = this->decompression->packTextData(text);
  str.append('\n');
  this->tcpSocket->write(str);
#ifdef DEBUG
  qDebug() << "============================测试客户端发送数据成功=============="
              "======================";
#endif
}

void QMyClients::sendDeskTopToServer(QByteArray target_data) {

//    Q_UNUSED(target_data);
#ifdef DEBUG
  qDebug() << "=========================测试客户端发送数据====================="
              "================";
  qDebug() << "son thread:" << QThread::currentThread()
           << "  id:" << QThread::currentThreadId();
#endif

  QByteArray array = this->decompression->packPictrueData(target_data);
  this->tcpSocket->write(array);
#ifdef DEBUG
  qDebug() << "============================测试客户端发送数据成功=============="
              "======================";
#endif
}

void QMyClients::connectToServer() {
  //    QString serverName = QInputDialog::getText(nullptr, tr("Server Name"),
  //    tr("Enter the name of the server to connect to:")); if
  //    (serverName.isEmpty())
  //        return;
  //    tcpSocket->connectToHost("192.168.92.224", 8989);
  tcpSocket->connectToHost("127.0.0.1", 8989);

  if (!tcpSocket->waitForConnected()) {
    QMessageBox::warning(
        nullptr, tr("错误"),
        tr("亲，服务器可能没开！").arg(tcpSocket->errorString()));
  }
}

void QMyClients::sendVideoToServer(QPixmap map) // 发送视频数据到服务器
{
#ifdef DEBUG
  qDebug() << "=========================测试客户端发送数据====================="
              "================";
#endif
  QByteArray byteArray = QMyDataDecompression::changedPixmapToByteArray(map);
  QByteArray nullbty;
  byteArray = this->decompression->packVideoData(byteArray, nullbty);
  qDebug() << "son thread:" << QThread::currentThread()
           << "  id:" << QThread::currentThreadId();
  tcpSocket->write(byteArray); // 把字节发送给服务器
#ifdef DEBUG
  qDebug() << "============================测试客户端发送数据成功=============="
              "======================";
#endif
}
=======

#include "QMyClients.h"

QMyClients::QMyClients(QObject *parent): QObject{parent}
{
    this->tcpSocket = new QTcpSocket(this);
    this->myAudio = new QMyAudio();
    connect(tcpSocket, &QTcpSocket::connected, this, &QMyClients::sendUserMessgeToServer);//服务器连接后向服务器发送一次信息
    connect(tcpSocket, &QTcpSocket::readyRead, this, &QMyClients::ReadAllData); //读取服务器发送过来的数据包
    connect(tcpSocket, &QTcpSocket::disconnected, this, [ = ]()
    {
        QMessageBox::warning(nullptr, tr("错误"), tr("亲，你怎么搞得哦，服务器断开了哦！"));
        tcpSocket->close();
    });
    this->decompression = new QMyDataDecompression(this);//实例化数据处理对象
//    QMetaObject::invokeMethod(this,"connectToServer",Qt::QueuedConnection);
}
QMyClients::~QMyClients()
{


}
QString QMyClients::getLocalIP()
{
    //获取本机IPv4地址
    QString hostName = QHostInfo::localHostName();    //本地主机名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    QString   localIP = "";

    QList<QHostAddress> addList = hostInfo.addresses(); //本机IP地址列表
    if (addList.isEmpty())
        return localIP;

    foreach (QHostAddress aHost, addList)
        if (QAbstractSocket::IPv4Protocol == aHost.protocol())
        {
            localIP = aHost.toString();
            break;
        }
    return localIP;
}
void QMyClients::ReadAllData()
{
#ifdef DEBUG
    qDebug() << "================测试接收服务器：接收数据开始=====================================";
#endif

        QByteArray data = this->tcpSocket->readAll();//读取来自服务器的数据包
        receiveBuffer.push(data);
#ifdef DEBUG
       qDebug() << "================测试接收服务器成功==============================================";
#endif
}
void QMyClients::sendUserMessgeToServer()
{
    QMessageBox::information(nullptr, tr("成功"), tr("宝贝，已成功连接服务器了哦!"));

}
void QMyClients::sendAudiotoServer()
{
    myAudio->initMyAudio();//初始化音频组件
    myAudio->startMyAudio();//开始录音
    connect(myAudio->myIODevice, &QMyIODevice::sendAudioData, this, [&](QByteArray array)
    {
        qDebug()<<"send Audio\t";
        QByteArray audio = QByteArray();
        audio.clear();
        array = this->decompression->packVideoData(audio, array);
        tcpSocket->write(array);//把字节发送给服务器
//        myAudio->stopMyAudio();//发送完成，暂停录音
    });
}
void QMyClients::sendMessageToSever(QString text)
{
#ifdef DEBUG
    qDebug() << "=============================测试客户端发送数据======================================";
#endif
    QByteArray  str = text.toUtf8();
    str = this->decompression->packTextData(text);
    str.append('\n');
    this->tcpSocket->write(str);
#ifdef DEBUG
    qDebug() << "============================测试客户端发送数据成功====================================";
#endif
}
void QMyClients::sendDeskTopToServer(QByteArray target_data)
{

//    Q_UNUSED(target_data);
#ifdef DEBUG
    qDebug() << "=========================测试客户端发送数据=====================================";
    qDebug()<<"son thread:"<<QThread::currentThread()<<"  id:"<<QThread::currentThreadId();
#endif

    QByteArray array = this->decompression->packPictrueData(target_data);
    this->tcpSocket->write(array);
#ifdef DEBUG
    qDebug() << "============================测试客户端发送数据成功====================================";
#endif
}
void QMyClients::connectToServer()
{
//    QString serverName = QInputDialog::getText(nullptr, tr("Server Name"), tr("Enter the name of the server to connect to:"));
//    if (serverName.isEmpty())
//        return;
//    tcpSocket->connectToHost("192.168.92.224", 8989);
    tcpSocket->connectToHost("127.0.0.1", 8989);

    if (!tcpSocket->waitForConnected())
    {
        QMessageBox::warning(nullptr, tr("错误"), tr("亲，服务器可能没开！").arg(tcpSocket->errorString()));
    }
}
void QMyClients::sendVideoToServer(QPixmap map)//发送视频数据到服务器
{
#ifdef DEBUG
    qDebug() << "=========================测试客户端发送数据=====================================";
#endif
    QByteArray byteArray = QMyDataDecompression::changedPixmapToByteArray(map);
    QByteArray nullbty;
    byteArray = this->decompression->packVideoData(byteArray, nullbty);
    qDebug()<<"son thread:"<<QThread::currentThread()<<"  id:"<<QThread::currentThreadId();
    tcpSocket->write(byteArray);//把字节发送给服务器
#ifdef DEBUG
    qDebug() << "============================测试客户端发送数据成功====================================";
#endif
}

>>>>>>> cdd08f869638039635144f291da04c841be7fc1c
