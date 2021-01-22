#include "mypopup.h"
#include "ui_mypopup.h"
#include <QTimer>
#include "mystruct.h"

myPopup::myPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myPopup)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()| Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
}

myPopup::~myPopup()
{
    delete ui;
}

void myPopup::Text_show(QString str)
{
    ui->label->setText(str);
    this->show();
    QTimer::singleShot(3000,[=](){this->hide();});
}
