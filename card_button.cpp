#include "card_button.h"
#include <QDebug>

//button的设置页面
card_button::card_button(QWidget *parent) : QPushButton(parent)
{

}

card_button::card_button(QString cardnumber, QString huase)
{
    B_cardnumber =  cardnumber;
    B_huase = huase;
    my_icon.addFile(QString(":/image/"+huase+"_"+cardnumber+".png"));
}

void card_button::setPic(QString str1, QString str2)
{
    QIcon my_icon;
    my_icon.addFile(QString(str1+"_"+str2+".png"));
    this->setIcon(my_icon);
}

QString card_button::currhuase()
{
    return B_huase;
}

QString card_button::currnumb()
{
    return B_cardnumber;
}

void card_button::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    this->setIcon(my_icon);
    this->setIconSize(QSize(this->width(),this->height()));
}
