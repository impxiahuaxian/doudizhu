#ifndef THREADTCPSOC_H
#define THREADTCPSOC_H

#include <QObject>
#include "mystruct.h"
class QThread;
class QTcpSocket;

class Threadtcpsoc : public QObject
{
    Q_OBJECT
public:
    explicit Threadtcpsoc(int stor, QObject *parent = nullptr);
    ~Threadtcpsoc();
    qintptr gainsocketDescriptor();


public slots:
    void slot_initSocket(Threadtcpsoc *e, qintptr ptr);
    void initconnect(QString str);  //初始化
    void slot_message_soc(Threadtcpsoc *so, QByteArray bty);//发送消息
    void slot_tcp_message(Info *inf);   //发送消息
private:

    QTcpSocket *tcpsocket;
    QThread *thisthread;
    QByteArray amdstr;  //tcp返回的字节缓存
    const int lengthint = 4; //报文头的长度
    int socketDescriptor;

    void messageData(QByteArray byt);

private slots:
    void slot_readreay();
signals:
    void sig_appendthreadsoc(Threadtcpsoc *);//将自身指针存放到tcpserver
    void sig_disconnected(Threadtcpsoc *);//断开连接后发出信号去清除自身对象
    void sig_connected();//连接上的信号

    void sig_message_jiben(Threadtcpsoc *,Use_stu,QByteArray);//收到的消息——基本信息                 客户端和服务器 转发
    void sig_message_chu_pai(Threadtcpsoc *,QList<paidui>,QString,QString,QString,QByteArray);//收到的消息——接收扑克牌信息（出的牌）  客户端和服务器  转发
    void sig_message_buchu_pai(Threadtcpsoc *,QString,QString,QByteArray);//收到的消息——接收扑克牌信息（不出，跳过）      客户端和服务器 转发
    void sig_message_gane_score(Threadtcpsoc *,QString,QString,QByteArray);//收到的消息——接收结束的分数            客户端和服务器 转发
    void sig_message_choose_score(Threadtcpsoc *,QString,QString,QString,QByteArray);//收到的消息——接收叫地主的分数     客户端和服务器 转发
    void sig_message_my_dizhu(Threadtcpsoc *,QString,QByteArray);//接收谁是地主                          客户端和服务器 转发


    void sig_message_home_Yes(Threadtcpsoc *,QString);//收到的消息——房间确定进入信息             只有服务器接收


    void sig_message_fa_pai(Threadtcpsoc *,QList<paidui>,QString);//收到的消息——接收扑克牌信息（发的牌）         只有客户端接收
    void sig_message_game_start(Threadtcpsoc *);//收到的消息——接收开始游戏信息                   只有客户端接收
    void sig_message_home(Threadtcpsoc *,QString);//收到的消息——房间信息                     只有客户端接收
    void sig_message_yourone_choose(Threadtcpsoc *);//收到的消息——接收第一个叫地主报文             只有客户端接收
};

#endif // THREADTCPSOC_H
