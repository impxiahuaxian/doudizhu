#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QDialog>
#include <QTime>
#include "common.h"
#include "mystruct.h"


namespace Ui {
class Widget;
}

class Widget : public QDialog
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void pus_6_show(bool bol);
    void xianshi_pus(QList<paidui> list, int state);
    void chupai_push(bool bol , bool bol2);//出牌按钮是否显示 bol2为不出按钮是否显示
    void xianshi_buchu(int state);  //显示不出的按钮
    void xuanzefenshu(QString str);//选择出几分的按钮显示

    void btn_pic_Or_test(int state ,Use_stu stu);

    void dizhu(int a);
private slots:
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    void initsys();
    void jiaodizhu_push(bool bol);//叫分数是否显示'

    void my_sorc(QList<paidui> &list);
    void my_sorc(QList<paidui_Count> &list);
    QList<paidui_Count> my_count(QList<paidui> list);

    bool check_pai_error(QList<paidui> list);
    check_error_stu check_pair(QList<paidui> list);
    bool bol_continuous(QList<paidui_Count> list);

private:
    int xx = 60;
    const int yy = 30;
    const int ww = 100;
    const int hh = 155;
    QList<push> pushlis;
    QList<push> puslis;
    QList<paidui> paiduilis1;
    int difen;    //叫的分数
    int beishu = 1; // 倍数
    bool Choose_landlord = false;
    QList<paidui> my_pailist;
public slots:
    void slot_paiduilis(QList<paidui> my_paili);

    void slot_paiduilis_1(QList<paidui> my_paili);

    void slot_your_is_dizhu();  //我是地主
signals:
    void pus_hide(push,int);//隐藏扑克牌的信号
    void sig_start_game();//开始游戏信号
    void sig_fenshu_push(QString);//发送分数，（选地主得）
    void sig_One_dizhu(QString);//第一个选地主的人
    void sig_chupai_card(QList<paidui>);//发送给控制发送报文
    void sig_delet_pus();//删除按钮
    void sig_delet_pus_1();//删除按钮
    void sig_win_game(int,int);//胜利
protected:
    void showEvent(QShowEvent *);
};

#endif // WIDGET_H
