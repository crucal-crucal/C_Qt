
#include "recvfile.h"

RecvFile::RecvFile(QTcpSocket *tcp, QObject *parent)
    : QThread{parent}
{
    m_tcpSocket = tcp;
}

void RecvFile::deleteData()
{
    //    qDebug()<<"deleteData!";
    if(m_file.isOpen()){
        m_file.close();
    }
    if(m_tcpSocket != NULL){
        m_tcpSocket->disconnectFromHost();
        m_tcpSocket->close();
        m_tcpSocket->deleteLater();
        m_tcpSocket = NULL;
    }
    if(m_timer.isActive())
        m_timer.stop();
}

void RecvFile::dealReadyRead()
{
    //    qDebug()<<"ServerThread dealReadyRead:";
    if(m_isStart){
        /*先接收文件名和文件大小信息*/
        m_isStart = false;
        char buf[4*1024] = {0};
        m_tcpSocket->read(buf,1024);
        qDebug()<<"buf:"<<buf;
        /*其它连接*/
        QStringList list = QString("%1").arg(buf).split("##");
        if(list.length()<2){
            emit sigOver(m_tcpSocket,m_fileName,false);
        }
        m_fileName = QString("%1").arg(buf).section("##",0,0);
        m_fileSize = QString("%1").arg(buf).section("##",1,1).toInt();

        QString filePath = m_filePath + m_fileName;
        filePath = getFilePath(filePath);/*名字去重*/
        QFileInfo info(filePath);
        m_fileName = info.fileName();

//        qDebug()<<"m_fileName:"<<m_fileName<<"m_fileSize:"<<m_fileSize;
        m_file.setFileName(filePath);
        bool isOk = m_file.open(QIODevice::WriteOnly);
        if(!isOk){
            qDebug()<<"open error!";
            returnReceice(false);
        }
        /*在文件名后加时间，区别*/
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("MMddhhmmsszzz");

        qDebug()<<"time:"<<current_date;
        m_fileName = m_fileName+"##"+current_date;
        m_timer.start(1000);
    }
    /*接收文件*/
    QByteArray array = m_tcpSocket->readAll();
    qint64 len = m_file.write(array);
    m_recSize+=len;
    //    qDebug()<<m_recSize<<"/"<<m_fileSize;
    /*更新接收大小*/
    if(len>0){
        emit sigFileInfo(m_fileName,m_filePath,m_fileSize,m_recSize);
    }
    if(m_recSize == m_fileSize){
        qDebug()<<"rec sucess!";
        returnReceice(true);
    }

}

void RecvFile::dealDisconnected()
{
    qDebug()<<"dealDisconnected!";
    if(!m_dealOver){
        if(m_fileSize != m_recSize){
            emit sigOver(m_tcpSocket,m_fileName,false);
        }else{
            emit sigOver(m_tcpSocket,m_fileName,true);
        }
    }
}

void RecvFile::dealTimeout()
{
    static qint64 preSize =0;
    qDebug()<<this<<":"<<preSize<<":"<<m_recSize;
    if(preSize == m_recSize){
        returnReceice(false);
    }
    preSize = m_recSize;
}

void RecvFile::returnReceice(bool bl)
{
    qDebug()<<"returnReceice:"<<bl;
    m_dealOver = true;
    /*回复客户端是否接收成功！*/
    if(bl || m_fileSize == m_recSize){
        m_tcpSocket->write(QString("sucess").toUtf8().data(),1024);
        QApplication::processEvents();/*实时发送*/
        emit sigOver(m_tcpSocket,m_fileName,true);
    }else{
        m_tcpSocket->write(QString("error").toUtf8().data(),1024);
        QApplication::processEvents();/*实时发送*/
        emit sigOver(m_tcpSocket,m_fileName,false);
    }
}

QString RecvFile::getFilePath(QString filePath)
{
    /*判断文件名是否重复，重复则重命名*/
    QFile file(filePath);
    if (file.exists()){
        QFileInfo info(filePath);
        return getFilePath(m_filePath+info.completeBaseName()+"(1)."+info.completeSuffix());
    }else{
        return filePath;
    }
}


void RecvFile::run()
{
//    qDebug()<<"run:";
//    connect(&m_timer, &QTimer::timeout, this, &RecvFile::dealTimeout);
//    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &RecvFile::dealReadyRead);
//    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &RecvFile::dealDisconnected);

    //进入事件循环
//    exec();
    QFile *file = new QFile("Recv.txt");
    file->open(QFile::WriteOnly);

    //接受数据
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, [=](){
        //读取次数
        static int cnt = 0;
        //文件大小
        static int filesize = 0;
        if(!cnt)
        {
            m_tcpSocket->read((char*)&filesize, 4);
        }
        //读出剩余数据
        QByteArray all = m_tcpSocket->readAll();
        cnt += all.size();
        file->write(all);

        qDebug()<<"cnt:"<<cnt<<"\nfilesize"<<filesize;
        //接受完毕
        if(cnt == filesize)
        {
            m_tcpSocket->close();
            m_tcpSocket->deleteLater();
            file->close();
            file->deleteLater();
            emit over();
        }
    });

    //进入事件循环,子线程进入后台，一直检测是否需要接收文件
    exec();
}

