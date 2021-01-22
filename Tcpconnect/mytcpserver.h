#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include "mystruct.h"
#include "common.h"
class Threadtcpsoc;

class mytcpserver : public QTcpServer
{
    Q_OBJECT
public:
    explicit mytcpserver(QWidget *parent = nullptr);

public slots:
    void slot_message_TCP(Info *inf, int state);

private :
    QList <Threadtcpsoc *> Tredtcpsoclis;
     void message_TCP(QByteArray bty, int state);
     int state_size = 0;

private slots:
    void slot_disconnected(Threadtcpsoc *e);
    void slot_Appendthreadsoc(Threadtcpsoc *e);

    void slot_message_chu_pai(Threadtcpsoc *soc, QList<paidui> pailis, QString str1, QString str2, QString str3,QByteArray bty);//收到的消息——接收扑克牌信息（出的牌）  客户端和服务器  转发
    void slot_message_buchu_pai(Threadtcpsoc *soc, QString str1, QString str2,QByteArray bty);//收到的消息——接收扑克牌信息（不出，跳过）      客户端和服务器 转发
    void slot_message_gane_score(Threadtcpsoc *soc, QString str1, QString str2,QByteArray bty);//收到的消息——接收结束的分数            客户端和服务器 转发
    void slot_message_choose_score(Threadtcpsoc *soc, QString str1, QString str2, QString str3,QByteArray bty);//收到的消息——接收叫地主的分数     客户端和服务器 转发
    void slot_message_my_dizhu(Threadtcpsoc *soc, QString str1,QByteArray bty);//接收谁是地主                          客户端和服务器 转发
    void slot_message_jiben(Threadtcpsoc *soc, Use_stu us, QByteArray bty);

    void slot_message_home_Yes(Threadtcpsoc *soc, QString str);
protected:
    void incomingConnection(qintptr handle);
signals:
    void sig_startthread(Threadtcpsoc *,qintptr);
    void sig_finish();  //两个人已经连接上
    void sig_message_soc(Threadtcpsoc *,QByteArray);

    void sig_message_chu_pai(Threadtcpsoc *,QList<paidui>,QString,QString,QString);//收到的消息——接收扑克牌信息（出的牌）  客户端和服务器  转发
    void sig_message_buchu_pai(Threadtcpsoc *,QString,QString);//收到的消息——接收扑克牌信息（不出，跳过）      客户端和服务器 转发
    void sig_message_gane_score(Threadtcpsoc *,QString,QString);//收到的消息——接收结束的分数            客户端和服务器 转发
    void sig_message_choose_score(Threadtcpsoc *,QString,QString,QString);//收到的消息——接收叫地主的分数     客户端和服务器 转发
    void sig_message_my_dizhu(Threadtcpsoc *,QString);//接收谁是地主                          客户端和服务器 转发
    void sig_message_jiben(Threadtcpsoc *,Use_stu);

    void sig_home_yes();


};

#endif // MYTCPSERVER_H
