#include "mycontrol.h"

mycontrol::mycontrol(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<qintptr>("qintptr");
    qRegisterMetaType<Use_stu>("Use_stu");

    qRegisterMetaType<QList<paidui>>("QList<paidui>");


    m_wanning = new my_wanning;
    my_result  = new myresult;
    m_player = new player;
    my_popup = new myPopup;

    m_player->bofang_file(1);
    CPU_ID = common::get_CPUID();
    User_name = "妞妞"+CPU_ID;

    initfile();
    my_select = new selectkind;
    my_Widget = new Widget;
    //my_select
    connect(my_select,&selectkind::sig_selectkind,this,&mycontrol::starting_items);
    connect(my_select,&selectkind::sig_join_Create,this,&mycontrol::slot_join_Create);
    connect(my_select,&selectkind::sig_myresult_numb,this,&mycontrol::slot_myresult_numb);
    //my_Widget
    connect(my_Widget,&Widget::sig_start_game,this,&mycontrol::slot_start_game);
    connect(my_Widget,&Widget::sig_fenshu_push,this,&mycontrol::slot_fenshu_push);
    connect(my_Widget,&Widget::sig_One_dizhu,this,&mycontrol::slot_One_dizhu);
    connect(my_Widget,&Widget::sig_chupai_card,this,&mycontrol::slot_chupai_card);
    connect(my_Widget,&Widget::sig_win_game,this,&mycontrol::slot_win_game);
    connect(this,&mycontrol::sig_your_is_dizhu,my_Widget,&Widget::slot_your_is_dizhu);
}

mycontrol::~mycontrol()
{

}

void mycontrol::initfile()
{
    my_file m_file;
    File_State state = m_file.read_file();
    switch (state) {
    case File_success:{
        shuchu<<"chenggong";
        break;
    }
    case File_one:{
        m_file.writer_file(state);
        m_wanning->show_wanning("系统初始化");
        break;
    }
    case File_format_error:{
        m_file.writer_file(state);
        m_wanning->show_wanning("储存文件遭到修改或破坏，系统初始化");
        break;
    }
    }
}

void mycontrol::fasong_home()
{
    Home_Info_TCP *inf = new Home_Info_TCP();
    inf->homemassage = "1";
    Info *Kinf = (Info *)inf;
    emit sig_message_TCP(Kinf,2);

    Home_Info_TCP *inf2 = new Home_Info_TCP();
    inf2->homemassage = "1";
    Info *Kinf2 = (Info *)inf2;
    emit sig_message_TCP(Kinf2,3);
}

void mycontrol::fasong_Yes()
{
    Home_Info_TCP_Yes *inf = new Home_Info_TCP_Yes();
    inf->name = User_name;
    Info *Kinf2 = (Info *)inf;
    emit sig_message_tcpsoc(Kinf2);
}

choose mycontrol::xipai_CARD()
{
    QList<paidui> my_list;
    for(int a=3;a<17;a++)
    {
        if(a==15)
            continue;
        for(int i=0;i<4;i++)
        {
            int c=i%4;
            paidui pai;
            switch (c) {
            case 0:{
                pai.huase="fangkuai";
                break;
            }
            case 1:{
                pai.huase="meihua";
                break;
            }
            case 2:{
                pai.huase="hongtao";
                break;
            }
            case 3:{
                pai.huase="heitao";
                break;
            }
            }
            pai.number=a;
            my_list.append(pai);
        }
    }
    paidui pai1;
    pai1.huase="xiaowang";
    pai1.number = 19;
    my_list.append(pai1);
    pai1.huase="dawang";
    pai1.number = 20;
    my_list.append(pai1);

    choose pai_huozong;//存放总牌数

    pai_huozong=my_chose(my_list);
    common::my_sort(pai_huozong.lis1);
    common::my_sort(pai_huozong.lis2);
    common::my_sort(pai_huozong.lis3);

    return pai_huozong;
}

choose mycontrol::my_chose(QList<paidui> my_list)
{
    choose m_choose;
    qsrand((QTime(0,0,0).secsTo(QTime::currentTime())));
    while(my_list.size()>3)
    {
        int rand = qrand()%my_list.size();
        m_choose.lis1.append(my_list.takeAt(rand));
        rand = qrand()%my_list.size();
        m_choose.lis2.append(my_list.takeAt(rand));
        rand = qrand()%my_list.size();
        m_choose.lis3.append(my_list.takeAt(rand));
    }
    while(!my_list.isEmpty())
    {
        m_choose.sanzhang.append(my_list.takeAt(0));
    }
    return  m_choose;
}

void mycontrol::init_dizhu(int state,QString str1)
{
    if(state==1)
    {
        for(int a=0;a<use_stulis.size();a++)
        {
            if(use_stulis.at(a).lunhuannumb==str1.toInt())
            {
                use_stulis[a].dizhu = true;
            }
        }
    }
    else
    {
        for(int a=0;a<use_stulis.size();a++)
        {
            use_stulis[a].dizhu = false;
        }
    }
}

void mycontrol::slot_Ipdizhi(QString str)
{
    treadsoc = new Threadtcpsoc(0);
    connect(this,&mycontrol::init_T_cp,treadsoc,&Threadtcpsoc::initconnect);
    connect(treadsoc,&Threadtcpsoc::sig_disconnected,[=](Threadtcpsoc *){
        treadsoc->deleteLater();
        treadsoc = nullptr;
    });
    connect(treadsoc,&Threadtcpsoc::sig_connected,[=](){
        udp_start->deleteLater();
        udp_start = nullptr;
        shuchu<<"shanchule  UDP";
    });
    //发送
    connect(this,&mycontrol::sig_message_tcpsoc,treadsoc,&Threadtcpsoc::slot_tcp_message);
    //这里往下接收信息

    //公有接收
    connect(treadsoc,&Threadtcpsoc::sig_message_jiben,this,&mycontrol::slot_message_jiben);
    connect(treadsoc,&Threadtcpsoc::sig_message_buchu_pai,this,&mycontrol::slot_message_buchu_pai);
    connect(treadsoc,&Threadtcpsoc::sig_message_chu_pai,this,&mycontrol::slot_message_chu_pai);
    connect(treadsoc,&Threadtcpsoc::sig_message_choose_score,this,&mycontrol::slot_message_choose_score);
    connect(treadsoc,&Threadtcpsoc::sig_message_gane_score,this,&mycontrol::slot_message_gane_score);
    connect(treadsoc,&Threadtcpsoc::sig_message_my_dizhu,this,&mycontrol::slot_message_my_dizhu);
    //仅仅客户端接收
    connect(treadsoc,&Threadtcpsoc::sig_message_home,this,&mycontrol::slot_message_home);
    connect(treadsoc,&Threadtcpsoc::sig_message_game_start,this,&mycontrol::slot_message_game_start);
    connect(treadsoc,&Threadtcpsoc::sig_message_fa_pai,this,&mycontrol::slot_message_fa_pai);
    connect(treadsoc,&Threadtcpsoc::sig_message_yourone_choose,this,&mycontrol::slot_message_yourone_choose);

    emit init_T_cp(str);
}

void mycontrol::slot_finish()
{
    shuchu<<"yuniaksdaslk=============================";
    udp_start->deleteLater();
    udp_start = nullptr;
    lunhuanbiaohao = 1;
    int ass = lunhuanbiaohao;
    Init_Info_TCP *Info1 = new Init_Info_TCP();
    Info1->my_name = User_name;
    Info1->my_TP = common::get_getIP();
    Info1->pic = User_Pic;
    Info1->pic_bty = common::picTodata(User_Pic);
    Info1->lunhuannumb = QString::number(ass+1);
    Info *Kinf1 = (Info *)Info1;

    QByteArray syyyu;
    syyyu = Kinf1->str_to_Bty();
    QString str(syyyu);
    shuchu<<str<<"==================================================================";
    emit sig_message_TCP(Kinf1,2);

    Init_Info_TCP *Info2 = new Init_Info_TCP();
    Info2->my_name = User_name;
    Info2->my_TP = common::get_getIP();
    Info2->pic = User_Pic;
    Info2->pic_bty = common::picTodata(User_Pic);
    Info2->lunhuannumb = QString::number(ass+2);
    Info *Kinf2 = (Info *)Info2;
    emit sig_message_TCP(Kinf2,3);
}

void mycontrol::slot_message_jiben(Threadtcpsoc *e, Use_stu st)
{
    Q_UNUSED(e);
    use_stulis.append(st);
    shuchu<<"dadasdadaddddddddddddddddddddddddddddddddddddd";
    if(use_stulis.size()==1)
    {
        shuchu<<xitongfuwuqiORkehuduan;
        if(!xitongfuwuqiORkehuduan)
        {
            lunhuanbiaohao = st.lunhuannumb;

            shuchu<<st.lunhuannumb<<"-----------------------------<<<<<<<<<<<<";
            use_stulis[0].lunhuannumb = 1;
            slot_connected();
        }
    }
    if(use_stulis.size()==2)
    {
        my_select->btn_pic_Or_test(0,use_stulis.at(0));
        my_select->btn_pic_Or_test(1,use_stulis.at(1));
        Use_stu syu;
        syu.name = User_name;
        syu.pic_lujing = User_Pic;
        syu.lunhuannumb = lunhuanbiaohao;
        shuchu<<lunhuanbiaohao<<"--------lllllllllllllllllll======";
        use_stulis.append(syu);
        my_select->btn_pic_Or_test(2,syu);


        my_Widget->btn_pic_Or_test(0,use_stulis.at(0));
        my_Widget->btn_pic_Or_test(1,use_stulis.at(1));
        my_Widget->btn_pic_Or_test(2,use_stulis.at(2));
    }

}

void mycontrol::slot_connected()
{
    Init_Info_TCP *Info1 = new Init_Info_TCP();
    Info1->my_name = User_name;
    Info1->my_TP = common::get_getIP();
    Info1->pic = User_Pic;
    Info1->pic_bty = common::picTodata(User_Pic);
    Info1->lunhuannumb = QString::number(lunhuanbiaohao);

    shuchu<<"_=========================>>"<<lunhuanbiaohao;
    Info *Kinf1 = (Info *)Info1;
    emit sig_message_tcpsoc(Kinf1);
}

void mycontrol::slot_start_game()
{
    cho = xipai_CARD();
    Start_Info_TCP_start *info1 = new  Start_Info_TCP_start();
    Info *Kinf1 = (Info *)info1;
    emit sig_message_TCP(Kinf1,2);
    Start_Info_TCP_start *info2 = new  Start_Info_TCP_start();
    Info *Kinf2 = (Info *)info2;
    emit sig_message_TCP(Kinf2,3);
    //此处写发牌；

    Card_fa_Info_TCP *info11 = new Card_fa_Info_TCP();
    info11->fapainumber = QString::number(cho.lis2.size());
    info11->paiduilis = cho.lis2;
    Info *Kinf11 = (Info *)info11;
    emit sig_message_TCP(Kinf11,2);

    Card_fa_Info_TCP *info22 = new Card_fa_Info_TCP();
    info22->fapainumber = QString::number(cho.lis3.size());
    info22->paiduilis = cho.lis3;
    Info *Kinf22 = (Info *)info22;
    emit sig_message_TCP(Kinf22,3);

    my_Widget->slot_paiduilis(cho.lis1);
}

void mycontrol::slot_fenshu_push(QString str)
{
    if(str=="3")
    {
        emit sig_your_is_dizhu();
        if(xitongfuwuqiORkehuduan)
        {
            MY_Info_Buf_TCP *info1 = new MY_Info_Buf_TCP();
            info1->numb = QString::number(lunhuanbiaohao);
            Info *Kinf1 = (Info *)info1;
            emit sig_message_TCP(Kinf1,2);

            MY_Info_Buf_TCP *info2 = new MY_Info_Buf_TCP();
            info2->numb = QString::number(lunhuanbiaohao);
            Info *Kinf2 = (Info *)info2;
            emit sig_message_TCP(Kinf2,3);

            my_Widget->dizhu(1);
            my_Widget->slot_paiduilis_1(cho.sanzhang);
        }
        else
        {
            MY_Info_Buf_TCP *info1 = new MY_Info_Buf_TCP();
            info1->numb = QString::number(lunhuanbiaohao);
            Info *Kinf1 = (Info *)info1;
            emit sig_message_tcpsoc(Kinf1);
        }
    }
    else
    {
        if(xitongfuwuqiORkehuduan)
        {
            Choose_Info_TCP *info1 = new Choose_Info_TCP();
            info1->fenshu = str;
            info1->name = User_name;
            info1->numb = QString::number(lunhuanbiaohao);
            Info *Kinf1 = (Info *)info1;
            emit sig_message_TCP(Kinf1,2);

            Choose_Info_TCP *info2 = new Choose_Info_TCP();
            info2->fenshu = str;
            info2->name = User_name;
            info2->numb = QString::number(lunhuanbiaohao);
            Info *Kinf2 = (Info *)info2;
            emit sig_message_TCP(Kinf2,3);
        }
        else
        {
            Choose_Info_TCP *info2 = new Choose_Info_TCP();
            info2->fenshu = str;
            info2->name = User_name;
            info2->numb = QString::number(lunhuanbiaohao);
            Info *Kinf2 = (Info *)info2;
            emit sig_message_tcpsoc(Kinf2);
        }
    }
}

void mycontrol::slot_One_dizhu(QString str)
{
    str = "1";
    if(str=="1")
    {
        my_Widget-> xuanzefenshu("0");
        //此处写接收的槽
    }
    else
    {
        Your_One_Info_TCP * Info1 = new Your_One_Info_TCP();
        Info *Kinf1 = (Info *)Info1;
        emit sig_message_TCP(Kinf1,str.toInt());
    }
}

void mycontrol::slot_chupai_card(QList<paidui> pailis)
{
    if(pailis.size()==0)
    {
        if(xitongfuwuqiORkehuduan)
        {
            Card_NO_Info_TCP *info1 = new Card_NO_Info_TCP();
            info1->name = User_name;
            info1->numb = QString::number(lunhuanbiaohao);
            Info *Kinf1 = (Info *)info1;
            emit sig_message_TCP(Kinf1,2);

            Card_NO_Info_TCP *info2 = new Card_NO_Info_TCP();
            info2->name = User_name;
            info2->numb = QString::number(lunhuanbiaohao);
            Info *Kinf2 = (Info *)info2;
            emit sig_message_TCP(Kinf2,3);
        }
        else
        {
            Card_NO_Info_TCP *info2 = new Card_NO_Info_TCP();
            info2->name = User_name;
            info2->numb = QString::number(lunhuanbiaohao);
            Info *Kinf2 = (Info *)info2;
            emit sig_message_tcpsoc(Kinf2);
        }
    }
    else
    {
        if(xitongfuwuqiORkehuduan)
        {
            Card_chu_Info_TCP *info1 = new Card_chu_Info_TCP();
            info1->numb = QString::number(lunhuanbiaohao);
            info1->chupainumber = QString::number(pailis.size());
            info1->name = User_name;
            info1->paiduilis = pailis;
            Info *Kinf1 = (Info *)info1;
            emit sig_message_TCP(Kinf1,2);

            Card_chu_Info_TCP *info2 = new Card_chu_Info_TCP();
            info2->numb = QString::number(lunhuanbiaohao);
            info2->chupainumber = QString::number(pailis.size());
            info2->name = User_name;
            info2->paiduilis = pailis;
            Info *Kinf2 = (Info *)info2;
            emit sig_message_TCP(Kinf2,3);
        }
        else
        {
            Card_chu_Info_TCP *info2 = new Card_chu_Info_TCP();
            info2->numb = QString::number(lunhuanbiaohao);
            info2->chupainumber = QString::number(pailis.size());
            info2->name = User_name;
            info2->paiduilis = pailis;
            Info *Kinf2 = (Info *)info2;
            emit sig_message_tcpsoc(Kinf2);
        }
    }
}

void mycontrol::slot_win_game(int co, int mo)
{
    int score = co*mo;
    double_QStringstu syu1;
    double_QStringstu syu2;
    double_QStringstu syu3;


    if(use_stulis.size()>=3)
    {
        if(my_this_dizhu=="3")
        {
            syu1.defen = QString::number(2*score);
            syu1.one = use_stulis.at(2).pic_lujing;
            syu1.two = use_stulis.at(2).name;

            syu1.defen = QString::number(-score);
            syu1.one = use_stulis.at(0).pic_lujing;
            syu1.two = use_stulis.at(0).name;

            syu2.defen = QString::number(-score);
            syu2.one = use_stulis.at(1).pic_lujing;
            syu2.two = use_stulis.at(1).name;
        }
        else
        {
            syu1.defen = QString::number(score);
            syu1.one = use_stulis.at(2).pic_lujing;
            syu1.two = use_stulis.at(2).name;

            if(use_stulis.at(0).dizhu)
            {
                syu2.defen = QString::number(-2*score);
            }
            else
            {
                syu2.defen = QString::number(score);
            }
            syu2.one = use_stulis.at(0).pic_lujing;
            syu2.two = use_stulis.at(0).name;

            if(use_stulis.at(1).dizhu)
            {
                syu3.defen = QString::number(-2*score);
            }
            else
            {
                syu3.defen = QString::number(score);
            }
            syu3.one = use_stulis.at(1).pic_lujing;
            syu3.two = use_stulis.at(1).name;
        }
        my_result->initsys(0);
        my_result->showjiesuan(syu1,syu2,syu3);
    }
    my_result->show();


    my_file m_file;
    m_file.writer_file(File_one);

    init_dizhu(2,"");
    if(xitongfuwuqiORkehuduan)
    {

        Win_Info_TCP *Info1 = new Win_Info_TCP();
        Info1->score = QString::number(score);
        Info1->winuser = my_this_dizhu;
        Info *Kinf1 = (Info *)Info1;
        emit sig_message_TCP(Kinf1,2);

        Win_Info_TCP *Info2 = new Win_Info_TCP();
        Info2->score = QString::number(score);
        Info2->winuser = my_this_dizhu;
        Info *Kinf2 = (Info *)Info2;
        emit sig_message_TCP(Kinf2,3);
    }
    else
    {
        Win_Info_TCP *Info2 = new Win_Info_TCP();
        Info2->score = QString::number(score);
        Info2->winuser = my_this_dizhu;
        Info *Kinf2 = (Info *)Info2;
        emit sig_message_tcpsoc(Kinf2);
    }
}

void mycontrol::slot_myresult_numb(int a)
{
    my_result->initsys(a);
}

void mycontrol::slot_message_chu_pai(Threadtcpsoc *soc, QList<paidui> pailis, QString str1, QString str2, QString str3)
{
    Q_UNUSED(soc);
    Q_UNUSED(str1);
    Q_UNUSED(str2);
    my_Widget->xianshi_pus(pailis,str3.toInt());
    int size = str3.toInt();
    switch (lunhuanbiaohao) {
    case 1:
    {
        if(size==2)
        {
            my_Widget->chupai_push(false,false);
        }
        break;
    }
    case 2:
    {
        if(size==3)
        {
            my_Widget->chupai_push(false,false);
        }
        break;
    }
    case 3:
    {
        if(size==1)
        {
            my_Widget->chupai_push(false,false);
        }
        break;
    }
    }
}

void mycontrol::slot_message_buchu_pai(Threadtcpsoc *soc, QString str1, QString str2)
{
    Q_UNUSED(soc);
    Q_UNUSED(str1);
    my_Widget->xianshi_buchu(str2.toInt());
    int size = str2.toInt();
    switch (lunhuanbiaohao) {
    case 1:
    {
        if(size==2)
        {
            my_Widget->chupai_push(false,false);
        }
        break;
    }
    case 2:
    {
        if(size==3)
        {
            my_Widget->chupai_push(false,false);
        }
        break;
    }
    case 3:
    {
        if(size==1)
        {
            my_Widget->chupai_push(false,false);
        }
        break;
    }
    }
}

void mycontrol::slot_message_gane_score(Threadtcpsoc *soc, QString str1, QString srr2)
{
    Q_UNUSED(soc);
    //借用此结构体，在此处one为头像路径，two为人员名，defen为得分；
    double_QStringstu syu1;
    double_QStringstu syu2;
    double_QStringstu syu3;
    int score = srr2.toInt();
    if(use_stulis.size()>=3)
    {
        if(str1=="3")
        {
            if(use_stulis.at(0).dizhu)
            {
                syu3.defen = QString::number(2*score);
            }
            else
            {
                syu3.defen = QString::number(-score);
            }
            syu3.one = use_stulis.at(0).pic_lujing;
            syu3.two = use_stulis.at(0).name;
            if(use_stulis.at(2).dizhu)
            {
                syu1.defen = QString::number(2*score);
            }
            else
            {
                syu1.defen = QString::number(-score);
            }
            syu1.one = use_stulis.at(2).pic_lujing;
            syu1.two = use_stulis.at(2).name;
            if(use_stulis.at(1).dizhu)
            {
                syu2.defen = QString::number(2*score);
            }
            else
            {
                syu2.defen = QString::number(-score);
            }
            syu2.one = use_stulis.at(1).pic_lujing;
            syu2.two = use_stulis.at(1).name;
        }
        else
        {
            if(use_stulis.at(0).dizhu)
            {
                syu3.defen = QString::number(-2*score);
            }
            else
            {
                syu3.defen = QString::number(score);
            }
            syu3.one = use_stulis.at(0).pic_lujing;
            syu3.two = use_stulis.at(0).name;
            if(use_stulis.at(2).dizhu)
            {
                syu1.defen = QString::number(-2*score);
            }
            else
            {
                syu1.defen = QString::number(score);
            }
            syu1.one = use_stulis.at(2).pic_lujing;
            syu1.two = use_stulis.at(2).name;
            if(use_stulis.at(1).dizhu)
            {
                syu2.defen = QString::number(-2*score);
            }
            else
            {
                syu2.defen = QString::number(score);
            }
            syu2.one = use_stulis.at(1).pic_lujing;
            syu2.two = use_stulis.at(1).name;
        }
    }
    my_result->initsys(0);
    my_result->showjiesuan(syu1,syu2,syu3);
    init_dizhu(2,"");
    my_file m_file;
    m_file.writer_file(File_one);
}

void mycontrol::slot_message_choose_score(Threadtcpsoc *soc, QString str1, QString str2, QString str3)
{
    Q_UNUSED(soc);
    Q_UNUSED(str1);
    int numb = str3.toInt();//轮换编号
    if((lunhuanbiaohao ==2)&&(numb==1))
    {
        my_Widget->xuanzefenshu(str2);//分数
    }
    else if((lunhuanbiaohao ==3)&&(numb==2))
    {
        my_Widget->xuanzefenshu(str2);
    }
    else if((lunhuanbiaohao ==1)&&(numb==3))
    {
        my_Widget->xuanzefenshu(str2);
    }
}

void mycontrol::slot_message_my_dizhu(Threadtcpsoc *soc, QString str1)
{
    Q_UNUSED(soc);
    init_dizhu(1,str1);

    if(str1.toInt()==lunhuanbiaohao)
    {
        my_Widget->chupai_push(false,true);
    }
    my_Widget->dizhu(str1.toInt());
}

void mycontrol::slot_home_yes()
{
    my_Widget-> pus_6_show(false);
}

void mycontrol::slot_message_fa_pai(Threadtcpsoc * e, QList<paidui> pailis, QString str)
{
    Q_UNUSED(e);
    Q_UNUSED(str);
    my_Widget->slot_paiduilis(pailis);
}

void mycontrol::slot_message_game_start(Threadtcpsoc * e)
{
    Q_UNUSED(e);
    my_popup->Text_show("游戏开始了！");
}

void mycontrol::slot_message_home(Threadtcpsoc *e, QString str)
{
    Q_UNUSED(e);
    Q_UNUSED(str);
    my_popup->Text_show("房主已经进入了房间，请抓紧进入！");
}

void mycontrol::slot_message_yourone_choose(Threadtcpsoc *e)
{
    Q_UNUSED(e);
    my_Widget->xuanzefenshu("0");
}

void mycontrol::starting_items(int a)
{
    if(a==2)
    {
        my_Widget->hide();
        my_select->show();
    }
    else if(a==3)
    {
        my_select->hide();
        my_Widget->show();
        if(xitongfuwuqiORkehuduan)
        {
            fasong_home();
        }
        else
        {
            fasong_Yes();
        }
    }
}

void mycontrol::slot_join_Create(bool bol)  // true创建false加入
{
    udp_start = new my_udp_soc;
    udp_start->initsys(bol);
    if(!bol)
    {
        udp_start->show();
        my_Widget->pus_6_show(true);
        xitongfuwuqiORkehuduan = false;
        connect(udp_start,&my_udp_soc::sig_Ipdizhi,this,&mycontrol::slot_Ipdizhi);
    }
    else
    {
        xitongfuwuqiORkehuduan = true;
        my_Widget->pus_6_show(false);
        Tcpserver = new mytcpserver;
        Tcpserver->listen(QHostAddress::Any,6666);
        connect(Tcpserver,&mytcpserver::sig_finish,this,&mycontrol::slot_finish);
        connect(this,&mycontrol::sig_message_TCP,Tcpserver,&mytcpserver::slot_message_TCP);

        //处理接收的消息，仅仅是接收
        connect(Tcpserver,&mytcpserver::sig_message_jiben,this,&mycontrol::slot_message_jiben);
        connect(Tcpserver,&mytcpserver::sig_message_buchu_pai,this,&mycontrol::slot_message_buchu_pai);
        connect(Tcpserver,&mytcpserver::sig_message_choose_score,this,&mycontrol::slot_message_choose_score);
        connect(Tcpserver,&mytcpserver::sig_message_chu_pai,this,&mycontrol::slot_message_chu_pai);
        connect(Tcpserver,&mytcpserver::sig_message_gane_score,this,&mycontrol::slot_message_gane_score);
        connect(Tcpserver,&mytcpserver::sig_message_my_dizhu,this,&mycontrol::slot_message_my_dizhu);
        connect(Tcpserver,&mytcpserver::sig_home_yes,this,&mycontrol::slot_home_yes);
    }
}
