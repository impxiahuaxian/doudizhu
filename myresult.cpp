#include "myresult.h"
#include "ui_myresult.h"
//此项为结算页面

myresult::myresult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myresult)
{
    ui->setupUi(this);
}

myresult::~myresult()
{
    delete ui;
}

void myresult::showjiesuan(double_QStringstu done, double_QStringstu dtwo, double_QStringstu dthree)
{
    //借用此结构体，在此处one为头像路径，two为人员名，defen为得分；
    ui->pushButton_2->setIcon(QIcon(done.one));
    ui->pushButton_2->setIconSize(QSize(55,55));
    ui->label_2->setText(done.two);
    ui->label_5->setText(done.defen);
    ui->pushButton_3->setIcon(QIcon(dtwo.one));
    ui->pushButton_3->setIconSize(QSize(55,55));
    ui->label_3->setText(done.two);
    ui->label_7->setText(done.defen);
    ui->pushButton_4->setIcon(QIcon(dthree.one));
    ui->pushButton_4->setIconSize(QSize(55,55));
    ui->label_4->setText(done.two);
    ui->label_6->setText(done.defen);

    shuchu<<"Dadadad";
    this->show();
}

void myresult::initsys(int a)
{
    ui->stackedWidget->setCurrentIndex(a);
    if(a==1)
    {
        ui->label_13->setText("12");
        ui->label_14->setText("1");
        ui->label_15->setText("2");
        ui->label_16->setText("3");
    }
    show();
}

void myresult::on_pushButton_clicked()
{
    hide();
}

void myresult::on_pushButton_5_clicked()
{
    hide();
}
