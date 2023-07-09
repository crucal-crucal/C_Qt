
#include "QMyDataDecompression.h"
#include <QBuffer>
#include <QImageReader>
#include <QMessageBox>

QMyDataDecompression::QMyDataDecompression(QObject *parent): QObject{parent}
{
#ifdef NDEBUG
    qDebug() << "---------------------------------------------------------------------";
    qDebug() << "=================测试文本 utf-8 编码解码=======================================";
    QString text = QString("你是谁，你在哪里，咦咦咦");
    QByteArray textByteArray = packTextData(text);
    startExtractPacked(textByteArray);
    qDebug() << "---------------------------------------------------------------------";
    connect(this, SIGNAL(finished_extractPictrueData(QByteArray)), this, SLOT(testPictrue(QByteArray)));
#endif



#ifdef NDEBUG
    qDebug() << "===========================图片测试============================================";
    widget = new QLabel;
    widget->show();
    QPixmap map("C:\\Users\\MECHREVO\\Desktop\\OIP-C.jpg");
    QByteArray byteArray = changedPixmapToByteArray(map);
    QByteArray byteArrayPack = packPictrueData(byteArray);
    startExtractPacked(byteArrayPack);
#endif

}
QMyDataDecompression::~QMyDataDecompression()
{

}
QByteArray QMyDataDecompression::changedPixmapToByteArray(QPixmap map)
{
    //QPixmap map(path);
    if (map.isNull()) return QByteArray(); //如果图像为空，做转换
    QByteArray byteArray = QByteArray();//初始化QByteArray
    QBuffer buffer;//缓冲区
    buffer.open(QIODevice::ReadWrite);//读写模式
    map.save(&buffer, "jpg", 90); //向buffer里写数据，90代表数据的强度，越高在传输图片时就会越清晰
    byteArray.append(buffer.data());//转变为字节
    return byteArray;//返回处理后的字节数据
}
QPixmap QMyDataDecompression::changedByteArrayToPixmap(QByteArray byteArray)
{

    QBuffer buffer(&byteArray);//将字节加入缓冲区
    buffer.open(QIODevice::ReadOnly);//只读
    QImageReader reader(&buffer, "jpg"); //读取出来的图片的格式
    QImage img = reader.read();//读取图片数据
    QPixmap map = QPixmap::fromImage(img);//转变为QPixap类型
    map.scaled(QSize(300, 300), Qt::KeepAspectRatio, Qt::SmoothTransformation); //缩放，按比例，图片平滑处理
    return QPixmap(map);//返回处理好的图片
}
void QMyDataDecompression::startExtractPacked(QByteArray &pack)
{
    //检查数据包头部，获取数据类型，视频数据长度，音频数据长度 。。。。。。
    receiveData *get_Data;
    QByteArray buffer(pack);
    if (pack.isEmpty())
    {
        return;//枚举
    }
    // memset(&st_receiveTcpData,0,sizeof(st_receiveTcpData));//将st_receiveTcpData里的数据全部置为零
    //                                       -------------------------------------------------------------------------------------
//    get_Data = (receiveData*)buffer.data();//|强制将其转换为receiveData类型 ---无需手动释放空间,因为get_Data是(receiveData*)分配而来的空间|
    get_Data = reinterpret_cast<receiveData*>(buffer.data());
    //|其buffer.data()返回的是指向QByteArray内部的指针                                        |
    //                                       -------------------------------------------------------------------------------------
    /*************************************************判断帧头*****************************************************************/
    //检测数据类型
    if (get_Data->header[0] == 0x01)
    {
        extractTextData(get_Data);//处理文本数据
    }
    else if (get_Data->header[0] == 0x02)
    {
        extractVideoData(get_Data);//处理视频数据
    }
    else if (get_Data->header[0] == 0x03)
    {
        extractPictrueData(get_Data);//处理图片数据

    }
    else if (get_Data->header[0] == 0x04) //用户信息
    {

    }
    else if (get_Data->header[0] == 0x05) //共享桌面数据
    {

    }
}
QByteArray QMyDataDecompression::packVideoData(QByteArray &video_data, QByteArray &audio_data)//打包要发送的视频数据
{
    if (video_data.length() + audio_data.length() > DATA_LEN)
    {
        QMessageBox::warning(nullptr, tr("提示"), tr("数据益处"));
        qDebug() << "音视频数据溢出";
        return QByteArray();
    }
    sendData st_senddata;//先封装好数据包，在将其转换为 QByteArray
    QByteArray sendTcpData;//要发送的数据包
    char *temp;//用作中间拷贝介质
    /**************************************************封装帧头*********************************************************/
    st_senddata.header[0] = 0x02;//数据类型:0x02 音视频数据
    if (audio_data.isEmpty())
    {
        st_senddata.audioLength = 0;
        st_senddata.header[1] = 0x02;//音频数据状态:0x02 没有音频数据
    }
    else
    {
        st_senddata.audioLength = audio_data.length();//保存音频字节长度
        st_senddata.header[1] = 0x01;//音频数据状态:0x01 有音频数据
    }
    if (video_data.isEmpty())
    {
        st_senddata.videoLength = 0;
        st_senddata.header[1] = 0x04;//视频数据状态:0x04 没有视频数据
    }
    else
    {
        st_senddata.videoLength = video_data.length();//保存视频字节长度
        st_senddata.header[1] = 0x03;//视频数据状态:0x03 视频数据
    }
    /*******************************************封装音频和视频数据*********************************************************/
    QByteArray video_audio_data(video_data);
    video_audio_data.append(audio_data);//定义一个video_audio_data，先放入视频数据，后放入音频数据，便于下一步拷贝
    temp = video_audio_data.data();//将视频音频数据先转换为char*
    memcpy(st_senddata.data, temp, video_data.length() + audio_data.length()); //拷贝视频音频数据到数组里,
    //第一个参数表示数据拷贝到的地方，第二个参数代表要拷贝的数据，第三参数代表要拷贝的长度
    /*******************************************************************************************************************/
    st_senddata.dataLenth = video_data.length() + audio_data.length(); //数据区域长度
    st_senddata.check_sum = HEAD_LEN + video_data.length() + audio_data.length() + OTHER_LEN; //校验和 = 数据长度 + 数据帧头长度 + 额外长度
    /*@brief
     * HEAD_LEN :帧头字节长度
     * 16       :另外4个int类型，一个int是4字节
     * */
    /*************************************************构造要发送的数据包***************************************************/
    sendTcpData.resize(HEAD_LEN + video_data.length() + audio_data.length() + OTHER_LEN); //开始构造数据包 -- 初始化一个数据包大小
    memcpy(sendTcpData.data(), &st_senddata, HEAD_LEN + st_senddata.dataLenth + OTHER_LEN - 4); //减掉校验和4字节，因为数据区可能会有空闲区域
    sendTcpData.append(st_senddata.check_sum);//在尾巴上加上校验和 --- 避免数据区域和校验和之间有空闲区域
    return sendTcpData;//至此音频和视频数据封装好
}
QByteArray QMyDataDecompression::packTextData(QString &text)
{
    /***************************************************文本数据*********************************************************/
    sendData st_senddata;
    QByteArray get_data , sendTcpData;
    char *temp;
    QString str(text);
    /****************************************************封装帧头*********************************************************/
    st_senddata.header[0] = 0x01; //数据类型 -- 文本数据
    st_senddata.header[1] = 0x02; //音频状态 --- 无音频
    st_senddata.header[1] = 0x04; //视频状态 --- 无视频
    st_senddata.audioLength = 0;
    st_senddata.videoLength = 0;
    // str = str.toLocal8Bit();//()
    get_data = str.toUtf8();//先将QString 转换为 QByteArray
    if (get_data.length() > DATA_LEN)
    {
        QMessageBox::warning(nullptr, tr("提示"), tr("数据益处"));
        qDebug() << "文本数据益出:" << str.length() << " :" << str;
        return QByteArray();
    }
    temp = get_data.data();//将QByteArry转变为char*
    memcpy(st_senddata.data, temp, get_data.length()); //不拷贝内存结构体时只会传一个指针过去
    st_senddata.dataLenth = get_data.length();//填入数据长度
    st_senddata.check_sum = get_data.length() + OTHER_LEN + HEAD_LEN;//校验和 = 数据长 + 帧头(10字节) + 其他四个int -- 16字节
    /****************************************************构造要发送的数据包************************************************/
    sendTcpData.resize((get_data.length() + OTHER_LEN - 4 + HEAD_LEN)); //开始构造数据包 -- 不要加校验和 最后加在尾巴上
    memcpy(sendTcpData.data(), &st_senddata, (get_data.length() + OTHER_LEN - 4 + HEAD_LEN)); //将数据拷贝到数据包sendTcpData，减掉校验和4字节，因为数据区可能会有空闲区域
    sendTcpData.append(st_senddata.check_sum);//在末尾加上校验和
    return sendTcpData;
}
QByteArray QMyDataDecompression::packPictrueData(QByteArray &pictrue_data)
{
    /****************************************************图片数据********************************************************/
    if (pictrue_data.length() > DATA_LEN)
    {
        qDebug() << "图片大小:" << pictrue_data.length();
        QMessageBox::warning(nullptr, tr("提示"), tr("数据益处"));
        qDebug() << "图片数据益出:";
        return QByteArray();
    }
    sendData st_senddata;
    QByteArray  sendTcpData;
    char *temp;
    /*******************************************************封装帧头*******************************************************/
    st_senddata.header[0] = 0x03; //数据类型 -- 图片数据
    st_senddata.header[1] = 0x02; //音频状态 --- 无音频
    st_senddata.header[1] = 0x04; //视频状态 --- 无视频
    st_senddata.audioLength = 0;
    st_senddata.videoLength = 0;
    /**************************************************封装数据包***********************************************************/
    temp = pictrue_data.data();//将QByteArry转变为char*
    memcpy(st_senddata.data, temp, pictrue_data.length()); //不拷贝内存结构体时只会传一个指针过去
    st_senddata.dataLenth = pictrue_data.length();//填入数据长度
    st_senddata.check_sum = pictrue_data.length() + OTHER_LEN + HEAD_LEN;//校验和 = 数据长 + 帧头(10字节) + 其他四个int -- 16字节
    /***********************************************构造要发送的数据包********************************************************/
    sendTcpData.resize((pictrue_data.length() + OTHER_LEN - 4 + HEAD_LEN)); //开始构造数据包 -- 不要加校验和 最后加在尾巴上
    memcpy(sendTcpData.data(), &st_senddata, (pictrue_data.length() + OTHER_LEN - 4 + HEAD_LEN)); //将数据拷贝到数据包sendTcpData，减掉校验和4字节，因为数据区可能会有空闲区域
    sendTcpData.append(st_senddata.check_sum);//在末尾加上校验和
    return sendTcpData;
}
QByteArray QMyDataDecompression::packUserBasicData(QString &basicInformation)
{
    /************************************************用户基本信息打包**********************************************************/
    //姓名，年龄，id,
    //packTextData(basicInformation);
}
void QMyDataDecompression::extractVideoData(receiveData *target_data)
{
    /**************************************************解析视频数据************************************************************/
    //数据 = 视频数据+音频数据，数据长度 = 视频数据长度 + 音频数据长度
    //target_wrap #字节存储排列:帧头(10字节) + 数据长度(4字节) + 视频长度(4字节) + 音频长度(4字节) + 数据 + 校验和(4字节)
    /**************************************解析帧头(10字节) + 数据长度(4字节) + 图片长度(4字节) + 音频长度(4字节)********************/
    //==================================================2.视频数据0x02=========================================================
    //提取视频数据：存储顺序：先视频数据后音频数据
    int pos = 0;
    QByteArray videoArray, audioArray;
//    qDebug()<<"**********"<<target_data->dataLenth;
    if(target_data->header[1]==0x03 || target_data->header[1]==0x04) qDebug()<<"OK!!!";
    if (target_data->header[1] == 0x03) //有视频数据
    {
        int cnt = target_data->videoLength; //计数器--记录读取了多少个字节
        while (cnt)
        {
            videoArray += target_data->data[pos++];
            cnt--;
        }
    }
    if (target_data->header[1] == 0x04) //有音频数据
    {
        int cnt = target_data->audioLength;//计数器--记录读取了多少个字节
        while (cnt)
        {
            audioArray += target_data->data[pos++];
            --cnt;
        }
    }
#ifdef NDEBUG
    qDebug() << "视频数据处理完成";
#endif
    qDebug()<<"videoArray.size():\t"<<videoArray.size();
    qDebug()<<"audioArray.size():\t"<<audioArray.size();
    emit finished_extractVideoData(videoArray, audioArray);
}
void QMyDataDecompression::extractTextData(receiveData *target_data)
{
    /**************************************************解析文本数据***********************************************************/
    //================================================1.文字数据0x01:无音频和视频===============================================
    QByteArray byteArray("");
    int pos = 0;
    int cnt = target_data->dataLenth;//计数器，将会读取多少个数据字节
    while (cnt)
    {
        byteArray += target_data->data[pos++];//读取的字节保存到 byteArray中
        cnt--;//计数器减1
    }
#ifdef NDEBUG
    qDebug() << "文本数据处理完成:" << QString::fromUtf8(byteArray);
#endif
    emit finished_extractTextData(QString::fromUtf8(byteArray));
}
void QMyDataDecompression::extractPictrueData(receiveData *target_data)
{
    /***************************************************解析图片数据***********************************************************/
    //================================================3.图片数据0x03===========================================================
    //提取图片
    QByteArray byteArray;
    int pos = 0;
    int cnt = target_data->dataLenth;
    while (cnt)
    {
        byteArray += target_data->data[pos++];
        cnt--;
    }
#ifdef NDEBUG
    qDebug() << "图片数据处理完成";
    qDebug() << " finished_extractPictrueData(byteArray); 开始";
    qDebug() << "byteArray-size:" << byteArray.size();
#endif
    emit finished_extractPictrueData(byteArray);
#ifdef NDEBUG
    qDebug() << " finished_extractPictrueData(byteArray); 结束";
#endif
}
void QMyDataDecompression::extractUserBasicData(receiveData *target_data)
{

}
void QMyDataDecompression::testPictrue(QByteArray picArray)
{
    qDebug() << "图片数据发送";
    QPixmap map = changedByteArrayToPixmap(picArray);

    widget->setPixmap(map);
}
QByteArray QMyDataDecompression::ChangeIntToQByteArray(int &value)
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream << value;
    return array;
}
int QMyDataDecompression::changeQByteArrayToInt(QByteArray &byteArray)
{
    int value;
    QDataStream stream(byteArray);
    stream >> value;
    return value;
}












