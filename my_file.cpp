#include "my_file.h"

my_file::my_file(QWidget *parent) : QWidget(parent)
{

}

//姓名、、头像路径。。积分。。春天。。炸弹。。战斗场次。。

File_State my_file::read_file()
{
    QString str;
    QFile file("./data.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        return File_one;
    }
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QByteArray bty = in.readAll().toUtf8();
        str = QByteArray::fromBase64(bty);
    }
    file.close();
    QStringList lis = str.split("|");

    if(lis.size()!=7)
    {
        return File_format_error;
    }
    if(lis.at(0)!=CPU_ID)
    {
        return File_format_error;
    }
    if(("姓名"==QString(lis.at(1)).section("#",0,0))&&
            ("头像路径"==QString(lis.at(2)).section("#",0,0))&&
            ("积分"==QString(lis.at(3)).section("#",0,0))&&
            ("春天"==QString(lis.at(4)).section("#",0,0))&&
            ("炸弹"==QString(lis.at(5)).section("#",0,0))&&
            ("战斗场次"==QString(lis.at(6)).section("#",0,0)))
    {
        User_name = QString(lis.at(1)).section("#",1,1);
        User_Pic = QString(lis.at(2)).section("#",1,1);
        CARD_score = QString(lis.at(3)).section("#",1,1);
        CARD_spring = QString(lis.at(4)).section("#",1,1);
        CARD_bomb = QString(lis.at(5)).section("#",1,1);
        CARD_count = QString(lis.at(6)).section("#",1,1);


        shuchu<<User_name;
    }
    else
    {
        return File_format_error;
    }
    return File_success;
}

bool my_file::writer_file(File_State state)
{
    QFile file("./data.txt");
    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }
    QTextStream out(&file);
    QString str;
    switch (state)
    {
    case File_one:{
        str = QString("%1|姓名#%2|头像路径#%3|积分#%4|春天#%5|炸弹#%6|战斗场次#%7").arg(CPU_ID)
                .arg(User_name).arg(User_Pic).arg(CARD_score).arg(CARD_spring)
                .arg(CARD_bomb).arg(CARD_count);
        shuchu<<User_name;
        break;
    }
    case File_format_error:
    {
        str = QString("%1|姓名#%2|头像路径#%3|积分#%4|春天#%5|炸弹#%6|战斗场次#%7").arg(CPU_ID)
                .arg(User_name).arg(User_Pic).arg(CARD_score).arg(CARD_spring)
                .arg(CARD_bomb).arg(CARD_count);
        break;
    }
    }
    QByteArray bty = str.toUtf8();
    out<<bty.toBase64();
    file.close();
}
