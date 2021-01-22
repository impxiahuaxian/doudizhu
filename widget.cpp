#include "widget.h"
#include "ui_widget.h"
#include "card_button.h"
//从3到13；14为A；16为2；19为小王；20为大王
//游戏界面
Widget::Widget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initsys();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initsys()
{
    jiaodizhu_push(true);
    chupai_push(true,true);
}

void Widget::chupai_push(bool bol, bool bol2)
{
    if(bol)
    {
        ui->pushButton->hide();//出
        ui->pushButton_2->hide();//不出
        ui->label_9->hide();
    }
    else
    {
        if(bol2)
        {
            ui->pushButton->show();
            ui->pushButton_2->hide();
            ui->label_9->show();
        }
        else
        {
            ui->pushButton->show();
            ui->pushButton_2->show();
            ui->label_9->show();
        }
    }
}

void Widget::jiaodizhu_push(bool bol)
{
    if(bol)
    {
        ui->pushButton_9->hide();
        ui->pushButton_10->hide();
        ui->pushButton_11->hide();
        ui->pushButton_12->hide();
    }
    else
    {
        ui->pushButton_9->show();
        ui->pushButton_10->show();
        ui->pushButton_11->show();
        ui->pushButton_12->show();
    }
}

void Widget::my_sorc(QList<paidui> &list)
{
    std::sort(list.begin(),list.end(),[=](paidui temp1,paidui temp2){
        return temp1.number>temp2.number;
    });
}

void Widget::my_sorc(QList<paidui_Count> &list)
{
    std::sort(list.begin(),list.end(),[=](paidui_Count temp1,paidui_Count temp2){
        return temp1.is_size>temp2.is_size;
    });
}

QList<paidui_Count> Widget::my_count(QList<paidui> list)
{
    int cou=1,a=0;
    paidui_Count cout_1;
    QList<paidui_Count> strcol;
    while (a<list.size()) {
        for(int b=a+1;b<list.size();b++)
        {
            if(list.at(a).number==list.at(b).number)
            {
                cou++;
                list.removeAt(b);
                b--;
            }
        }
        cout_1.pai = list.at(a);
        cout_1.is_size = cou;
        strcol.append(cout_1);
        cou=1;
        list.removeAt(a);
    }
    return strcol;
}

bool Widget::check_pai_error(QList<paidui> list)
{
    check_error_stu stru;
    stru = check_pair(list);
    if(stru.enum_card==error_CARD)
    {
        return false;
    }
    return true;
}

check_error_stu Widget::check_pair(QList<paidui> list)
{
    check_error_stu stru;
    QList<paidui_Count> coutlis;
    coutlis = my_count(list);
    my_sorc(coutlis);

    for(int a=0;a<coutlis.size();a++)
    {
        shuchu<<coutlis.at(a).is_size<<"paixing "<<coutlis.at(a).pai.huase<<coutlis.at(a).pai.number;
    }

    int size_1 = list.size();
    shuchu<<size_1;
    switch(size_1)
    {
    case 1:
    {
        stru.enum_card = one_CARD;
        stru.numb = coutlis.at(0).pai.number;
        stru.size = size_1;
        return stru;
    }
    case 2:
    {
        if(coutlis.size()==1)
        {
            stru.enum_card = Double_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
        else if((list.at(0).number==20)&&(list.at(0).number==19))
        {
            stru.enum_card = Bomb_Ww_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
        else
        {
            stru.enum_card = error_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
    }
    case 3:
    {
        if(coutlis.size()==1)
        {
            stru.enum_card = Three_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
        else
        {
            stru.enum_card = error_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
    }
    case 4:
    {
        if(coutlis.size()==1)
        {
            stru.enum_card = Bomb_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
        else if(coutlis.at(0).is_size==3)
        {
            stru.enum_card = Three_one_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
        else
        {
            stru.enum_card = error_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
    }
    case 5:
    {
        if(coutlis.size()==2)
        {
            if(coutlis.at(0).is_size==3)
            {
                stru.enum_card = Three_Two_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
        }
        else if(coutlis.size()==5)
        {
            if(bol_continuous(coutlis))
            {
                stru.enum_card = Shun_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
            else
            {
                stru.enum_card = error_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
        }
        else
        {
            stru.enum_card = error_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
    }
    case 6:
    {
        if(coutlis.size()==2)
        {
            if(coutlis.at(0).is_size==4)
            {
                stru.enum_card = four_Two_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
            else
            {
                stru.enum_card = fly_budai_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
        }
        else if(coutlis.size()==3)
        {
            if(coutlis.at(0).is_size==coutlis.at(1).is_size)
            {
                stru.enum_card = Liandui_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
            else if(coutlis.at(0).is_size==4)
            {
                stru.enum_card = four_Two_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
        }
        else if(coutlis.size()==6)
        {
            if(bol_continuous(coutlis))
            {
                stru.enum_card = Shun_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
            else
            {
                stru.enum_card = error_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
        }
        else
        {
            stru.enum_card = error_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
    }
    case 7:
    {
        if(coutlis.size()==7)
        {
            if(bol_continuous(coutlis))
            {
                stru.enum_card = Shun_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
            else
            {
                stru.enum_card = error_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
        }
        else
        {
            stru.enum_card = error_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
    }
    case 8:
    {
        if(coutlis.size()==3)
        {
            if((coutlis.at(0).is_size==4)&&(coutlis.at(1).is_size==2)&&(coutlis.at(2).is_size==2))
            {
                stru.enum_card = four_Two_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
            else
            {
                stru.enum_card = error_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
        }
        else if(coutlis.size()==4)
        {
            if((coutlis.at(0).is_size==2)&&(coutlis.at(1).is_size==2)&&(coutlis.at(2).is_size==2)&&(coutlis.at(3).is_size==2))
            {
                if(bol_continuous(coutlis))
                {
                    stru.enum_card = Liandui_CARD;
                    stru.numb = coutlis.at(0).pai.number;
                    stru.size = size_1;
                    return stru;
                }
            }
            else if((coutlis.at(0).is_size==3)&&(coutlis.at(1).is_size==3))
            {
                if(coutlis.at(0).pai.number==(coutlis.at(1).pai.number+1))
                {
                    stru.enum_card = fly_One_CARD;
                    stru.numb = coutlis.at(0).pai.number;
                    stru.size = size_1;
                    return stru;
                }
                else
                {
                    stru.enum_card = error_CARD;
                    stru.numb = coutlis.at(0).pai.number;
                    stru.size = size_1;
                    return stru;
                }
            }
            else
            {
                stru.enum_card = error_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
        }
        else if(coutlis.size()==8)
        {
            if(bol_continuous(coutlis))
            {
                stru.enum_card = Shun_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
            else
            {
                stru.enum_card = error_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
        }
        else
        {
            stru.enum_card = error_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
    }
    case 9:
    {
        if(coutlis.size()==3)
        {
            if((coutlis.at(0).is_size==3)&&(coutlis.at(1).is_size==3)&&(coutlis.at(1).is_size==3))
            {
                if((coutlis.at(0).pai.number==(coutlis.at(1).pai.number+1))&&(coutlis.at(1).pai.number==(coutlis.at(2).pai.number+1)))
                {
                    stru.enum_card = fly_budai_CARD;
                    stru.numb = coutlis.at(0).pai.number;
                    stru.size = size_1;
                    return stru;
                }
                else
                {
                    stru.enum_card = error_CARD;
                    stru.numb = coutlis.at(0).pai.number;
                    stru.size = size_1;
                    return stru;
                }
            }
            else
            {
                stru.enum_card = error_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
        }
        else if(coutlis.size()==9)
        {
            if(bol_continuous(coutlis))
            {
                stru.enum_card = Shun_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
            else
            {
                stru.enum_card = error_CARD;
                stru.numb = coutlis.at(0).pai.number;
                stru.size = size_1;
                return stru;
            }
        }
        else
        {
            stru.enum_card = error_CARD;
            stru.numb = coutlis.at(0).pai.number;
            stru.size = size_1;
            return stru;
        }
    }
    default:
    {
        stru.enum_card = error_CARD;
        stru.numb = coutlis.at(0).pai.number;
        stru.size = size_1;
        return stru;
    }
    }
}

bool Widget::bol_continuous(QList<paidui_Count> list)
{
    bool bol = true;
    for(int a=0;a<list.size()-1;a++)
    {
        if(list.at(a).pai.number!=(list.at(a+1).pai.number+1))
        {
            bol = false;
            return bol;
        }
    }
    return bol;
}

void Widget::pus_6_show(bool bol)
{
    if(bol)
    {
        ui->pushButton_6->hide();
    }
    else
    {
        ui->pushButton_6->show();
    }
}

void Widget::xianshi_pus(QList<paidui> list,int state)
{
    emit sig_delet_pus();
    int xx1=60;
    int hh1=125;
    int ww1=80;
    for(int a=0;a<list.size();a++)
    {
        card_button *pus = new card_button(QString::number(list.at(a).number),list.at(a).huase);
        connect(this,&Widget::sig_delet_pus,[=](){
            pus->hide();
        });
        if(lunhuanbiaohao==1)
        {
            if(state==2)
            {
                pus->setParent(ui->widget_2);
            }
            else if(state==3)
            {
                pus->setParent(ui->widget_3);
            }
            else if(state==1)
            {
                pus->setParent(ui->widget);
            }
        }
        else if(lunhuanbiaohao==2)
        {
            if(state==2)
            {
                pus->setParent(ui->widget);
            }
            else if(state==3)
            {
                pus->setParent(ui->widget_2);
            }
            else if(state==1)
            {
                pus->setParent(ui->widget_3);
            }
        }
        else if(lunhuanbiaohao==3)
        {
            if(state==2)
            {
                pus->setParent(ui->widget_3);
            }
            else if(state==3)
            {
                pus->setParent(ui->widget);
            }
            else if(state==1)
            {
                pus->setParent(ui->widget_2);
            }
        }
        pus->setGeometry(xx1,0,ww1,hh1);
        pus->setMaximumSize(ww1,hh1);
        pus->setMinimumSize(ww1,hh1);
        xx1+=40;
        pus->show();
    }
}

void Widget::xianshi_buchu(int state)
{
    if(lunhuanbiaohao==1)
    {
        if(state==2)
        {
            ui->label_8->setText("不\n出！");
        }
        else if(state==3)
        {
            ui->label_10->setText("不\n出！");
        }
    }
    else if(lunhuanbiaohao==2)
    {
        if(state==3)
        {
            ui->label_8->setText("不\n出！");
        }
        else if(state==1)
        {
            ui->label_10->setText("不\n出！");
        }
    }
    if(lunhuanbiaohao==3)
    {
        if(state==1)
        {
            ui->label_8->setText("不\n出！");
        }
        else if(state==2)
        {
            ui->label_10->setText("不\n出！");
        }
    }
}

void Widget::xuanzefenshu(QString str)
{
    jiaodizhu_push(false);
    int state = str.toInt();
    ui->pushButton_9->setEnabled(true);
    ui->pushButton_10->setEnabled(true);
    switch (state) {
    case 0:
    {
        break;
    }
    case 1:
    {
        ui->pushButton_9->setEnabled(false);
        break;
    }
    case 2:
    {
        ui->pushButton_9->setEnabled(false);
        ui->pushButton_10->setEnabled(false);
        break;
    }
    default:
        break;
    }
}

void Widget::btn_pic_Or_test(int state, Use_stu stu)
{
    //    if(state == 0)
    //    {
    //        QString filename = stu.pic_lujing;
    //        QIcon ico = QIcon(filename);
    //        ui->pushButton_6->setIcon(ico);
    //        ui->pushButton_6->setIconSize(QSize(105,105));
    //        ui->label_3->setText(stu.name);
    //    }
    //    else if(state == 1)
    //    {
    //        QString filename = stu.pic_lujing;
    //        QIcon ico = QIcon(filename);
    //        ui->pushButton_7->setIcon(ico);
    //        ui->pushButton_7->setIconSize(QSize(105,105));
    //        ui->label_4->setText(stu.name);
    //    }
    //    else if(state == 2)
    //    {
    //        QString filename = stu.pic_lujing;
    //        QIcon ico = QIcon(filename);
    //        ui->pushButton_5->setIcon(ico);
    //        ui->pushButton_5->setIconSize(QSize(105,105));
    //        ui->label_name_2->setText(stu.name);
    //    }
}

void Widget::dizhu(int a)
{
    switch (a) {
    case 1:{
        if(lunhuanbiaohao==a)
        {
            ui->label_7->setStyleSheet("border-image: url(:/image/dizhu.png);");
            ui->pushButton_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
            ui->pushButton_8->setStyleSheet("border-image: url(:/image/nongmin1.png);");
        }
        else if(lunhuanbiaohao==2)
        {
            ui->pushButton_7->setStyleSheet("border-image: url(:/image/dizhu.png);");
            ui->label_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
            ui->pushButton_8->setStyleSheet("border-image: url(:/image/nongmin1.png);");
        }
        else if(lunhuanbiaohao==3)
        {
            ui->pushButton_8->setStyleSheet("border-image: url(:/image/dizhu.png);");
            ui->label_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
            ui->pushButton_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
        }
        break;
    }
    case 2:
    {
        if(lunhuanbiaohao==2)
        {
            ui->label_7->setStyleSheet("border-image: url(:/image/dizhu.png);");
            ui->pushButton_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
            ui->pushButton_8->setStyleSheet("border-image: url(:/image/nongmin1.png);");
        }
        else if(lunhuanbiaohao==3)
        {
            ui->pushButton_7->setStyleSheet("border-image: url(:/image/dizhu.png);");
            ui->label_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
            ui->pushButton_8->setStyleSheet("border-image: url(:/image/nongmin1.png);");
        }
        else if(lunhuanbiaohao==1)
        {
            ui->pushButton_8->setStyleSheet("border-image: url(:/image/dizhu.png);");
            ui->label_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
            ui->pushButton_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
        }
        break;
    }
    case 3:
    {
        if(lunhuanbiaohao==3)
        {
            ui->label_7->setStyleSheet("border-image: url(:/image/dizhu.png);");
            ui->pushButton_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
            ui->pushButton_8->setStyleSheet("border-image: url(:/image/nongmin1.png);");
        }
        else if(lunhuanbiaohao==2)
        {
            ui->pushButton_7->setStyleSheet("border-image: url(:/image/dizhu.png);");
            ui->label_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
            ui->pushButton_8->setStyleSheet("border-image: url(:/image/nongmin1.png);");
        }
        else if(lunhuanbiaohao==1)
        {
            ui->pushButton_8->setStyleSheet("border-image: url(:/image/dizhu.png);");
            ui->label_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
            ui->pushButton_7->setStyleSheet("border-image: url(:/image/nongmin1.png);");
        }
        break;
    }
    default:
        break;
    }
}

void Widget::slot_paiduilis(QList<paidui> my_paili)
{
    xx = 60;
    pushlis.clear();
    sig_delet_pus_1();
    my_pailist.clear();
    my_pailist.append(my_paili);

    common::my_sort(my_pailist);

    for(int a=0;a<my_pailist.size();a++)
    {
        card_button *pus = new card_button(QString::number(my_pailist.at(a).number),my_pailist.at(a).huase);
        connect(this,&Widget::sig_delet_pus_1,[=](){
            pus->hide();
        });
        pus->setParent(ui->widget_12);
        pus->setGeometry(xx,yy,ww,hh);
        pus->setMaximumSize(ww,hh);
        pus->setMinimumSize(ww,hh);
        push p;
        p.pushptr = pus;
        pushlis.append(p);
        xx+=40;
        pus->show();
        connect(this,&Widget::pus_hide,[=](push pushe,int sisi){
            if(pushe.pushptr==pus)
            {
                push pp;
                pp.pushptr = pus;
                pus->disconnect();
                puslis.append(pp);
                pus->hide();
                for(int a=sisi+1;a<pushlis.size();a++)
                {
                    QRect rec = pushlis.at(a).pushptr->geometry();
                    rec.setX(rec.x()-40);
                    pushlis.at(a).pushptr->setGeometry(rec);
                }
            }
        });
        connect(pus,&card_button::clicked,[=](){
            int sta;
            for(int x=0;x<pushlis.size();x++)
            {
                if(pushlis.at(x).pushptr==pus)
                {
                    sta = x;
                    break;
                }
            }
            QRect rec = pushlis.at(sta).pushptr->geometry();
            if(pushlis.at(sta).bol)
            {
                rec.setY(rec.y()-30);
                pushlis[sta].bol = false;
                paidui kk;
                kk.huase = pus->currhuase();
                kk.number = pus->currnumb().toInt();
                paiduilis1.append(kk);
            }
            else
            {
                rec.setY(rec.y()+30);
                pushlis[sta].bol = true;
                paidui kk;
                kk.huase = pus->currhuase();
                kk.number = pus->currnumb().toInt();

                for(int m=0;m<paiduilis1.size();m++)
                {
                    if((kk.huase==paiduilis1.at(m).huase)&&(kk.number==paiduilis1.at(m).number))
                    {
                        paiduilis1.removeAt(m);
                    }
                }
            }
            pus->setGeometry(rec);
        });
    }
}

void Widget::slot_paiduilis_1(QList<paidui> my_paili)
{
    xx = 60;
    emit sig_delet_pus_1();
    pushlis.clear();
    my_pailist.append(my_paili);
    common::my_sort(my_pailist);

    for(int a=0;a<my_pailist.size();a++)
    {
        card_button *pus = new card_button(QString::number(my_pailist.at(a).number),my_pailist.at(a).huase);

        connect(this,&Widget::sig_delet_pus_1,[=](){
            pus->hide();
        });
        pus->setParent(ui->widget_12);
        pus->setGeometry(xx,yy,ww,hh);
        pus->setMaximumSize(ww,hh);
        pus->setMinimumSize(ww,hh);
        push p;
        p.pushptr = pus;
        pushlis.append(p);
        xx+=40;
        pus->show();
        connect(this,&Widget::pus_hide,[=](push pushe,int sisi){
            if(pushe.pushptr==pus)
            {
                push pp;
                pp.pushptr = pus;
                pus->disconnect();
                puslis.append(pp);
                pus->hide();
                for(int a=sisi+1;a<pushlis.size();a++)
                {
                    QRect rec = pushlis.at(a).pushptr->geometry();
                    rec.setX(rec.x()-40);
                    pushlis.at(a).pushptr->setGeometry(rec);
                }
            }
        });
        connect(pus,&card_button::clicked,[=](){
            int sta;
            for(int x=0;x<pushlis.size();x++)
            {
                if(pushlis.at(x).pushptr==pus)
                {
                    sta = x;
                    break;
                }
            }
            QRect rec = pushlis.at(sta).pushptr->geometry();
            if(pushlis.at(sta).bol)
            {
                rec.setY(rec.y()-30);
                pushlis[sta].bol = false;
                paidui kk;
                kk.huase = pus->currhuase();
                kk.number = pus->currnumb().toInt();
                paiduilis1.append(kk);
            }
            else
            {
                rec.setY(rec.y()+30);
                pushlis[sta].bol = true;
                paidui kk;
                kk.huase = pus->currhuase();
                kk.number = pus->currnumb().toInt();

                for(int m=0;m<paiduilis1.size();m++)
                {
                    if((kk.huase==paiduilis1.at(m).huase)&&(kk.number==paiduilis1.at(m).number))
                    {
                        paiduilis1.removeAt(m);
                    }
                }
            }
            pus->setGeometry(rec);
        });
    }
}

void Widget::slot_your_is_dizhu()
{
    my_this_dizhu = "3";
    chupai_push(false,true);
}

void Widget::showEvent(QShowEvent *)
{

}

void Widget::on_pushButton_5_clicked()
{
    close();
}

void Widget::on_pushButton_6_clicked()
{
    ui->pushButton_6->hide();
    qsrand((QTime(0,0,0).secsTo(QTime::currentTime())));
    int numb = qrand()%3+1;
    emit sig_start_game();
    emit sig_One_dizhu(QString::number(numb));
}

void Widget::on_pushButton_clicked()  //出牌，在此处判断
{
    if(paiduilis1.size()<=0)
    {
        my_popup->Text_show("您未选择牌，不能出牌！");
        return;
    }
    my_sorc(paiduilis1);
    for(int a=0;a<paiduilis1.size();a++)
    {
        shuchu<<paiduilis1.at(a).number;
    }

    if(!check_pai_error(paiduilis1))
    {
        my_popup->Text_show("您选择的牌错误，不能出牌！");
        return;
    }


    //这里写判断


    //如果正确

    emit sig_delet_pus();

    ui->label_8->setText("");
    ui->label_10->setText("");

    for(int a=0;a<pushlis.size();a++)
    {
        if(!pushlis.at(a).bol)
        {
            emit pus_hide(pushlis.at(a),a);
            pushlis.removeAt(a);
            a--;
        }
    }

    xianshi_pus(paiduilis1,lunhuanbiaohao);
    emit sig_chupai_card(paiduilis1);
    paiduilis1.clear();
    shuchu<<pushlis.size();
    if(pushlis.size()==0)
    {
        emit sig_win_game(difen,beishu);
    }

    //此项控制是否能一直出牌。
    chupai_push(true,true);
}

void Widget::on_pushButton_11_clicked()
{
    difen = 3;
    emit sig_fenshu_push("3");
    jiaodizhu_push(true);
    ui->lineEdit->setText("3");
    Choose_landlord = true;
}

void Widget::on_pushButton_10_clicked()
{
    difen = 2;
    emit sig_fenshu_push("2");
    ui->lineEdit->setText("2");
    jiaodizhu_push(true);
    Choose_landlord = true;
}

void Widget::on_pushButton_9_clicked()
{
    difen = 1;
    emit sig_fenshu_push("1");
    jiaodizhu_push(true);
    ui->lineEdit->setText("1");
    Choose_landlord = true;
}

void Widget::on_pushButton_12_clicked()
{
    difen = 1;
    emit sig_fenshu_push("0");
    ui->lineEdit->setText("0");
    Choose_landlord = true;
}

void Widget::on_pushButton_2_clicked()
{
    ui->label_8->setText("");
    ui->label_10->setText("");
    QList<paidui> lis;
    chupai_push(true,true);
    emit sig_chupai_card(lis);
}
