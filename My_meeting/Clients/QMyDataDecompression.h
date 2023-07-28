
#ifndef QMYDATADECOMPRESSION_H
#define QMYDATADECOMPRESSION_H

#include <QByteArray>
#include <QLabel>
#include <QObject>
#include <QPixmap>
/*@brief 对来自服务器的数据进行解压等操作 --- 拿原始数据
 * 1.解压
 * 2.判断解压数据是图片，文本，视频
 * 3.对判断后的数据进行原始数据提取
 * 4.更新原始数据到界面
 * */
// #define DEBUG  //开启调试信息
const int DATA_LEN = 502400; // 数据总长度(字节)
const int HEAD_LEN = 10;     // 帧头总长度(字节)
const int OTHER_LEN =
    16; // 其余4个int 总字节(dataLenth,videoLength,audioLength,check_sum)

/*************************************************************发送包协议****************************************************************/
#pragma pack(1) // 设置结构体为1字节对其
typedef struct sendData {
  uchar header[10];    // 帧头(10字节) uchar存储16进制
  int dataLenth;       // 数据区长度(4字节)
  int videoLength;     // 视频长度(4字节)
  int audioLength;     // 音频长度(4字节)
  char data[DATA_LEN]; // 视频+音频数据 (数据区)
  int check_sum;       // 校验和(4字节)前面字节相加
} senddata;
#pragma pack() // 结束对齐
/*************************************************************接收包协议****************************************************************/
#pragma pack(1)
typedef struct receiveData {
  uchar header[10];    // 帧头(10字节) uchar存储16进制
  int dataLenth;       // 数据区长度(4字节)
  int videoLength;     // 视频长度(4字节)
  int audioLength;     // 音频长度(4字节)
  char data[DATA_LEN]; // 视频+音频数据 (数据区)
  int check_sum;       // 校验和(4字节)前面字节相加
} st_receivedata;
#pragma pack()
/***************************************************************************************************************************************/

class QMyDataDecompression : public QObject {
  Q_OBJECT
public:
  explicit QMyDataDecompression(QObject *parent = nullptr);
  ~QMyDataDecompression();
  static QByteArray changedPixmapToByteArray(QPixmap &map); // 将图片转换为字节
  static QPixmap
  changedByteArrayToPixmap(QByteArray &byteArray); // 将字节转换为图片
  QByteArray ChangeIntToQByteArray(int &value);  // 将int类型转变为字节
  int changeQByteArrayToInt(QByteArray &buffer); // 将字节类型转变为int
  enum DataType {
    NullData, // 无数据
    Video,    // 视频
    Pictrue,  // 图片
    Text,     // 文本
  };          // 数据类型
public slots:
  void startExtractPacked(QByteArray &pack); // 处理服务器分发下来的数据包
  /*@brief
   * void startExtractPacked(QByteArray &pack);
   * 此函数是处理服务器发送下来的
   *字节数据包，内部将会自动解析视频，文本，图片等数据包，并将处理好的原始数据通过信号发送出去
   * 信号：
   *void
   *finished_extractVideoData(QByteArray,QByteArray);//处理完视频包后将视频字节数据和音频字节数据发送出去
   *void
   *finished_extractTextData(QString);//处理完文本数据包后将文本数据发送出去
   *void
   *finished_extractPictrueData(QByteArray);//处理完图片后将图片的字节发送出去
   *void finished_extractUserBasicDaa(QString);//发送用户的基本信息
   * */
  QByteArray packVideoData(QByteArray &video_data,
                           QByteArray &audio_data); // 打包处理视频和音频数据
  QByteArray packTextData(QString &text); // 打包处理文本数据包
  QByteArray packPictrueData(QByteArray &pictrue_data); // 打包处理图片数据
  QByteArray packUserBasicData(QString &basicInformation); // 打包用户的基本信息
  //-----------------------------------------------解析包---------------------------------------------------------------//
  // 提取视频数据
  void extractVideoData(receiveData *target_data);
  // 提取视频数据
  void extractTextData(receiveData *target_data);
  // 提取图片数据
  void extractPictrueData(receiveData *target_data);
  // 处理用户基本信息
  void extractUserBasicData(receiveData *target_data);
  //------------------------------------------------------------------------------------------------------------------//
private slots:
  void testPictrue(QByteArray &picArray);

private:
  QLabel *widget;
signals:
  // 开始提取数据区信号
  void go_extractVideoData(QByteArray, int,
                           int); // 参数：数据区，视频长度，音频长度
  void go_extractTextData(QByteArray, int); // 参数：数据区，数据区长度
  void go_extractPictrueData(QByteArray, int); // 参数：数据区，数据区长度

  // 数据区提取完毕 -- 将数据送出去
  void finished_extractVideoData(
      QByteArray,
      QByteArray); // 处理完视频包后将视频字节数据和音频字节数据发送出去
  void finished_extractTextData(QString); // 处理完文本数据包后将文本数据发送出去
  void finished_extractPictrueData(
      QByteArray); // 处理完图片后将图片的字节发送出去
  void finished_extractUserBasicDaa(QString); // 发送用户的基本信息
};
#endif // QMYDATADECOMPRESSION_H
/*************************************************帧头协议**********************************************************************************
*|                        # header[10] 一共10字节 , 1个字节8位 ，
1个字节范围[0,255],在存储时需要先转换为16进制                                 |
*
*|                        如 8 的16进制为 0x08,2进制为 0000 1000
，假如将其存入header[0] = 0x08 ,位存储就为 0000 1000(自动转换)                |
*
*---------------------------------------------------------------------------------------------------------------------------------------
*
*------帧头第1个字节header[0] 数据类型----------------------------帧头第2字节
header[1] 数据状态------------------------------------------------* | header[0]
= 0x01 -----> 发送文字信息             | | header[1] = 0x01 ------->
携带音频数据                  |                              * | header[0] =
0x02 -----> 摄像头的数据             | | header[1] = 0x02 -------> 没有音频数据
|                              * | header[0] = 0x03 -----> 单张图片数据 | |
header[1] = 0x03 -------> 携带视频数据                  | * | header[0] = 0x04
-----> 用户信息数据             | | header[1] = 0x04 -------> 没有视频数据 | *
| header[0] = 0x05 -----> 共享桌面数据             | | | *
*-----------------------------------------------------------------------------------------------------------------------------------------*
*******************************************************************************************************************************************
|------帧头第3个字节header[2]
数据来源----------------------------帧头第4个字节header[3]
控制命令------------------------------------------------* | header[2] = 0x01
-----> 主要的演讲者             | | header[3] = 0x01 -------> 全体静音模式 | *
| header[2] = 0x02 -----> 普通的参会者             | | header[3] = 0x02 ------->
限制成员模式                  |                              * | header[2] =
0x03 -----> 会议的创建者             | | header[3] = 0x03 -------> 房主转让模式
|                              * | | | |                              *
------------------------------------------------------------------------------------------------------------------------------------------*
*******************************************************************************************************************************************
*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//================================================header[]
//每个字节用法======================================================================
/* header[] 每个字节用法
 *  第1个字节header[0] 用于检测数据的类型
 *  第2个字节header[1] 用于检测数据的状态
 *  第3个字节header[2] 用于检测数据的来源
 *，服务器根据解析此字节后进行相应的转发数据操作，客户端解析此字节进行相应的显示操作
 *  第4个字节header[3] 用于控制客户端的命令字节，需要根据
 *第3个字节header[2]的类型 来限制命令的使用
 *
 *
 **/
