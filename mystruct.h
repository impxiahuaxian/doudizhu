#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <QObject>
#include "my_wanning.h"
#include "player.h"
#include "mypopup.h"

extern my_wanning *m_wanning;
extern myPopup *my_popup;
extern QString CPU_ID;

//姓名、、头像路径。。积分。。春天。。炸弹。。战斗场次。。
extern QString User_name;
extern QString User_Pic;
extern QString CARD_score;
extern QString CARD_spring;
extern QString CARD_bomb;
extern QString CARD_count;

extern bool xitongfuwuqiORkehuduan;//服务器true，客户端false
extern player *m_player;
extern int lunhuanbiaohao;  //轮换编号

extern QString my_this_dizhu;


class card_button;

enum CARD_TPE{  //各类牌型
    one_CARD,//一张
    Double_CARD,//一对
    Three_CARD,//三张
    Bomb_CARD,//炸弹
    Bomb_Ww_CARD,//王炸
    Three_one_CARD,//三代一
    Three_Two_CARD,//三代二
    Shun_CARD,//顺子
    Liandui_CARD,//连对
    four_Two_CARD,//四代二
    four_Twodouble_CARD,//四代两对
    fly_budai_CARD,//飞机不带
    fly_One_CARD,//飞机带一
    fly_two_CARD,//飞机带对
    error_CARD//错误牌型

};

struct check_error_stu
{
    CARD_TPE enum_card;
    int numb;
    int size;
    check_error_stu() {
        numb = -1;
        size = 0;
    }
};


enum File_State{
    File_one,            //第一次进程序，也就是打不开TXT文件（打开失败）
    File_success,        //打开成功
    File_format_error    // 打开后发现格式错误
};

struct paidui{
    QString huase;
    int number;
};

struct paidui_Count
{
    paidui pai;
    int is_size;
    paidui_Count() {
        is_size=0;
    }
};

struct push
{
    card_button *pushptr;
    bool bol;
    push() {
        pushptr = nullptr;
        bol = true;
    }
};

struct choose
{
    QList<paidui> lis1;
    QList<paidui> lis2;
    QList<paidui> lis3;
    QList<paidui> sanzhang;
};

struct Use_stu
{
    QString name;
    QString pic_lujing;
    QString IP_dizhi;
    int lunhuannumb;  //轮换编号

    bool dizhu = false;//true是地主，false不是
    Use_stu() {}
};

class Info  //Tcp基类
{
public:
    Info() {}
    QString biaozhi;
    virtual QByteArray str_to_Bty()=0;
};


//Init_Info_TCP|name|本机IP|发送轮换编号|头像名|头像的数据流  客户端收发和服务器收发
class Init_Info_TCP : public Info       //init
{
public:
    Init_Info_TCP() {
        biaozhi = "Init_Info_TCP";
    }
    QString my_name;//name
    QString my_TP;//本机IP
    QString lunhuannumb;//发送轮换编号
    QString pic;//头像名
    QByteArray pic_bty;//头像数据流
    QByteArray str_to_Bty()
    {
        QByteArray bty;
        bty = QString(biaozhi+"|"+my_name+"|"+my_TP+"|"+lunhuannumb+"|"+pic+"|").toUtf8();
        return bty;
    }
};
//Home_Info_TCP|房间信息        客户端收和服务器发

class Home_Info_TCP : public Info
{
public:
    Home_Info_TCP() {
        biaozhi = "Home_Info_TCP";
    }
    QString homemassage;
    QByteArray str_to_Bty()
    {
        QString str = biaozhi+"|"+homemassage;
        return str.toUtf8();
    }
};

//Home_Info_TCP_Yes|name        客户端发和服务器收

class Home_Info_TCP_Yes : public Info
{
public:
    Home_Info_TCP_Yes() {
        biaozhi = "Home_Info_TCP_Yes";
    }
    QString name;
    QByteArray str_to_Bty()
    {
        return QString(biaozhi+"|"+name).toUtf8();
    }
};

//Start_Info_TCP_start      客户端收和服务器发

class Start_Info_TCP_start : public Info
{
public:
    Start_Info_TCP_start() {
        biaozhi = "Start_Info_TCP_start";
    }
    QByteArray str_to_Bty()
    {
        return QString(biaozhi).toUtf8();
    }
};

//Card_fa_Info_TCP|花色#数字|花色#数字|…|发牌数            客户端收和服务器发

class Card_fa_Info_TCP : public Info
{
public:
    Card_fa_Info_TCP() {
        biaozhi = "Card_fa_Info_TCP";
    }
    QList<paidui> paiduilis;
    QString fapainumber;
    QByteArray str_to_Bty()
    {
        QString str;
        for(int i=0;i<paiduilis.size();i++)
        {
            if(i==0)
            {
                str+=biaozhi+"|"+paiduilis.at(i).huase+"#"+QString::number(paiduilis.at(i).number);
            }
            else
            {
                str+="|"+paiduilis.at(i).huase+"#"+QString::number(paiduilis.at(i).number);
            }
        }
        str = str+"|"+fapainumber;
        return str.toUtf8();
    }
};

//Card_chu_Info_TCP|name|花色#数字;花色#数字|…|出牌数|轮换编号     客户端收发和服务器收发

class Card_chu_Info_TCP : public Info
{
public:
    Card_chu_Info_TCP() {
        biaozhi = "Card_chu_Info_TCP";
    }

    QString name;

    QString chupainumber;
    QList<paidui> paiduilis;
    QString numb;

    QByteArray str_to_Bty()
    {
        QString str;
        for(int i=0;i<paiduilis.size();i++)
        {
            if(i==0)
            {
                str+=biaozhi+"|"+name+"|"+paiduilis.at(i).huase+"#"+QString::number(paiduilis.at(i).number);
            }
            else
            {
                str+=";"+paiduilis.at(i).huase+"#"+QString::number(paiduilis.at(i).number);
            }
        }
        str = str+"|"+chupainumber+"|"+numb;
        return str.toUtf8();
    }
};


//Card_NO_Info_TCP|name|轮换编号        客户端收发和服务器收发

class Card_NO_Info_TCP : public Info
{
public:
    Card_NO_Info_TCP() {
        biaozhi = "Card_NO_Info_TCP";
    }
    QString name;
    QString numb;

    QByteArray str_to_Bty()
    {
        return QString(biaozhi+"|"+name+"|"+numb).toUtf8();
    }
};
//Win_Info_TCP|地主or农民|分数        客户端收发和服务器收发
class Win_Info_TCP : public Info
{
public:
    Win_Info_TCP() {
        biaozhi = "Win_Info_TCP";
    }
    QString winuser;
    QString score;
    QByteArray str_to_Bty()
    {
        return QString(biaozhi+"|"+winuser+"|"+score).toUtf8();
    }
};

//Choose_Info_TCP|name|分数|轮换编号      客户端收发和服务器收发
class Choose_Info_TCP : public Info
{
public:
    Choose_Info_TCP() {
        biaozhi = "Choose_Info_TCP";
    }
    QString name;
    QString fenshu;
    QString numb;

    QByteArray str_to_Bty()
    {
        return QString(biaozhi+"|"+name+"|"+fenshu+"|"+numb).toUtf8();
    }
};

//Your_One_Info_TCP  第一个选地主的        客户端收和服务器发

class Your_One_Info_TCP : public Info
{
public:
    Your_One_Info_TCP() {
        biaozhi = "Your_One_Info_TCP";
    }
    QByteArray str_to_Bty()
    {
        return biaozhi.toUtf8();
    }
};

//MY_Info_Buf_TCP|轮换编号      客户端收发和服务器收发

class MY_Info_Buf_TCP : public Info
{
public:
    MY_Info_Buf_TCP() {
        biaozhi = "MY_Info_Buf_TCP";
    }
    QString numb;
    QByteArray str_to_Bty()
    {
        return QString(biaozhi+"|"+numb).toUtf8();
    }
};

struct double_QStringstu
{
    QString one;
    QString two;
    QString defen;
    double_QStringstu() {
        QString one="";
        QString two="";
        QString defen = "";
    }
};













#endif // MYSTRUCT_H
