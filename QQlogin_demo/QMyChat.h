#ifndef QMYCHAT_H
#define QMYCHAT_H

#include <QDialog>
#include <QUdpSocket>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDateTime>
#include <QFont>
#include <QColorDialog>
#include <QFileDialog>
#include <QFile>

namespace Ui {
class QMyChat;
}

/*
 每一个用户单独的界面，需要广播udp消息
 此处用的是数据流读入方法实现
 */
class QMyChat : public QDialog
{
    Q_OBJECT

public:
    enum Msgtype{
        Msg, UserEnter, UserLeft
    }; // 分别代表普通信息，用户进入，用户离开
    explicit QMyChat(QWidget *parent = nullptr, QString name = "");
    void sendMsg(Msgtype type); // 广播udp信息
    QString getName(); //获取名字
    QString getMeg(); //获取聊天信息
    void userEnter(QString username); //处理用户进入
    void userLeft(QString username, QString time); //处理用户离开
    void RecvMessage(); // 接受udp信息
    void sendMessage(); // 发送信息按钮
    ~QMyChat();

signals:
    void closeWidget();

private:
    Ui::QMyChat *ui;
    quint16 port; // 端口
    QString uName; // 名字
    QUdpSocket *udpSocket; // udp套接字
    QString myName;

    // 重写关闭事件
    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // QMYCHAT_H
