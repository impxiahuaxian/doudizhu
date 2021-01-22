#include "selectkind.h"
#include "ui_selectkind.h"
#include <QFileDialog>

//选择模式界面

selectkind::selectkind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectkind)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    connect(ui->horizontalSlider,&QSlider::valueChanged,this,&selectkind::slot_valueChanged);
    connect(this,&selectkind::sig_valueChanged,m_player,&player::slot_value);
    initsys();
}

selectkind::~selectkind()
{
    delete ui;
}

void selectkind::initsys()
{
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setValue(100);
    ui->lineEdit->setText(CARD_score);
    ui->horizontalSlider->hide();
    ui->label->hide();
    ui->label_name->setText(User_name);
    ui->pushButton_tou_1->setIcon(QIcon(User_Pic));
    ui->pushButton_tou_1->setIconSize(QSize(55,55));
}

void selectkind::btn_pic_Or_test(int state, Use_stu stu)
{
    shuchu<<stu.name<<"----->>"<<stu.lunhuannumb;
    if(state == 0)
    {
        QString filename = stu.pic_lujing;
        QIcon ico = QIcon(filename);
        ui->pushButton_6->setIcon(ico);
        ui->pushButton_6->setIconSize(QSize(105,105));
        ui->label_3->setText(stu.name);

        if(!xitongfuwuqiORkehuduan)
        {
            ui->label_5->setText("这是房主！");
        }
    }
    else if(state == 1)
    {
        QString filename = stu.pic_lujing;
        QIcon ico = QIcon(filename);
        ui->pushButton_7->setIcon(ico);
        ui->pushButton_7->setIconSize(QSize(105,105));
        ui->label_4->setText(stu.name);
    }
    else if(state == 2)
    {
        QString filename = stu.pic_lujing;
        QIcon ico = QIcon(filename);
        ui->pushButton_5->setIcon(ico);
        ui->pushButton_5->setIconSize(QSize(105,105));
        ui->label_name_2->setText(stu.name);
        if(xitongfuwuqiORkehuduan)
        {
            ui->label_7->setText("这是房主！");
        }
    }
}

void selectkind::on_pushButton_clicked()  //经典玩法
{
    emit sig_selectkind(3);
}

void selectkind::on_pushButton_8_clicked() //创建
{
    ui->label_6->setText("等待连接。。。。");
    emit sig_join_Create(true);
}

void selectkind::on_pushButton_9_clicked()//加入
{
    emit sig_join_Create(false);
}

void selectkind::showEvent(QShowEvent *event)
{
//    ui->label_name->setText(User_name);
}

void selectkind::on_pushButton_tou_1_clicked()
{
    QString str = QFileDialog::getOpenFileName(this,tr("设置头像"),"D:/",tr("图片文件(*.png)"));
    if(str=="")
    {
        return;
    }
    QFileInfo fi(str);
    QString filename = fi.fileName();
    QString hiuzhui = fi.suffix();
    QString sss = QDir::currentPath()+QDir::separator()+filename;
    if(str.remove(QDir::currentPath())!=("/"+filename))
    {
        bool bol = QFile::exists(sss);
        if(bol)
        {
            QFile::remove(sss);
        }
        QFile::copy(str,sss);
    }
    QIcon ico = QIcon(filename);
    ui->pushButton_tou_1->setIcon(ico);
    ui->pushButton_tou_1->setIconSize(QSize(55,55));
    User_Pic = filename;
    my_file m_file;
    m_file.writer_file(File_one);
}

void selectkind::on_pushButton_4_clicked()
{
    if(ui->horizontalSlider->isVisible())
    {
        ui->horizontalSlider->hide();
        ui->label->hide();
    }
    else
    {
        ui->horizontalSlider->show();
        ui->label->show();
    }
}

void selectkind::slot_valueChanged(int Cvalue)
{
    ui->label->setText(QString::number(Cvalue));
    emit sig_valueChanged(Cvalue);
}

void selectkind::on_pushButton_2_clicked()
{
    emit sig_myresult_numb(1);
    my_file m_file;
    m_file.writer_file(File_one);
}

void selectkind::on_pushButton_10_clicked()
{
    QString str = QInputDialog::getText(this,tr("输入姓名对话框！"),tr("请输入姓名！"),QLineEdit::Normal);
    if(str=="")
    {
        m_wanning->show_wanning("输入名字不能为空！");
        return;
    }
    my_file m_file;
    User_name = str;
    m_file.writer_file(File_one);
    ui->label_name->setText(str);
}

void selectkind::on_pushButton_3_clicked()
{
    close();
}
