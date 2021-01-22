#ifndef MYCONTROL_H
#define MYCONTROL_H

#include <QObject>
#include "Tcpconnect/mytcpserver.h"
#include "Tcpconnect/my_udp_soc.h"
#include "Tcpconnect/threadtcpsoc.h"
#include "widget.h"
#include "selectkind.h"
#include "my_file.h"
#include "myresult.h"

class mycontrol : public QObject
{
    Q_OBJECT
public:
    explicit mycontrol(QObject *parent = nullptr);
    ~mycontrol();
public slots:
    void starting_items(int a);

private:
    Widget *my_Widget = nullptr;
    selectkind *my_select = nullptr;
    mytcpserver *Tcpserver = nullptr;
    my_udp_soc *udp_start = nullptr;
    Threadtcpsoc *treadsoc = nullptr;
    QList<Use_stu> use_stulis;
    myresult * my_result;
    choose cho;

private:
    void slot_join_Create(bool bol);
    void initfile();
    void fasong_home();//发送房间信息
    void fasong_Yes();//发送成功进入
    choose xipai_CARD();
    choose my_chose(QList<paidui> my_list);

    void init_dizhu(int state, QString str1);  //初始化的结构体中的地主信息
private slots:
    void slot_Ipdizhi(QString str);   //初始化客户端的地方
    void slot_finish();  //当服务器时接收到两人都连接上时发出开始传输信号接收

    void slot_connected();

    void slot_start_game();//接收开始游戏的信号
    void slot_fenshu_push(QString str);
    void slot_One_dizhu(QString str);//接收第一个选地主的人
    void slot_chupai_card(QList<paidui> pailis);//接收出的牌
    void slot_win_game(int co , int mo);//接收倍数和底分
    void slot_myresult_numb(int a);


    //服务器和客户端公用接收
    void slot_message_jiben(Threadtcpsoc *e, Use_stu st);//收到的消息——基本信息
    void slot_message_chu_pai(Threadtcpsoc *soc,QList<paidui> pailis, QString str1, QString str2, QString str3);//接收扑克牌信息（出的牌）
    void slot_message_buchu_pai(Threadtcpsoc *soc,QString str1, QString str2);//接收扑克牌信息（不出，跳过）
    void slot_message_gane_score(Threadtcpsoc *soc,QString str1, QString srr2);//接收结束的分数
    void slot_message_choose_score(Threadtcpsoc *soc,QString str1, QString str2, QString str3);//接收叫地主的分数
    void slot_message_my_dizhu(Threadtcpsoc *soc,QString str1);//接收谁是地主
    void slot_home_yes();
    //客户端专用接收
    void slot_message_fa_pai(Threadtcpsoc *e, QList<paidui> pailis, QString str);//收到的消息——接收扑克牌信息（发的牌）
    void slot_message_game_start(Threadtcpsoc *e);//收到的消息——接收开始游戏信息
    void slot_message_home(Threadtcpsoc *e, QString str);//收到的消息——房间信息
    void slot_message_yourone_choose(Threadtcpsoc *e);//收到的消息——接收第一个叫地主报文


signals:
    void init_T_cp(QString);
    void sig_message_TCP(Info *,int);
    void sig_message_tcpsoc(Info *);
    void sig_your_is_dizhu();
};

#endif // MYCONTROL_H
