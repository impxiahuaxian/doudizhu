#include "my_udp_soc.h"
#include "ui_my_udp_soc.h"

my_udp_soc::my_udp_soc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::my_udp_soc)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose, true);
    zuboinit();
    QStringList lis;
    this->setModal(true);
    lis<<"序号"<<"姓名"<<"IP";
    ui->tableWidget->setColumnCount(lis.size());
    ui->tableWidget->setHorizontalHeaderLabels(lis);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnWidth(0,90);
    ui->tableWidget->setColumnWidth(2,180);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    connect(ui->tableWidget,&QTableWidget::cellClicked,this,&my_udp_soc::slot_cellclick);
}

my_udp_soc::~my_udp_soc()
{
    shuchu<<"haha";
    delete ui;
}

void my_udp_soc::initsys(bool state)  //true是发送也就是服务器
{
    if(state)
    {
        m_time = new QTimer(this);
        m_time->setInterval(4000);
        m_time->start();
        connect(m_time,&QTimer::timeout,this,&my_udp_soc::slot_sendmessage);
        connect(m_udp,&QUdpSocket::readyRead,this,&my_udp_soc::slot_readready);
    }
    else
    {
        connect(m_udp,&QUdpSocket::readyRead,this,&my_udp_soc::slot_readready);
    }
}

void my_udp_soc::zuboinit()
{
     m_udp = new QUdpSocket(this);
     m_udp->bind(9999,QUdpSocket::ShareAddress);
}

void my_udp_soc::slot_sendmessage()
{
    QByteArray byt;
    QString str = "UDP_Name_IP|"+User_name+"|"+common::get_getIP();
    byt = str.toUtf8();
    m_udp->writeDatagram(byt.data(),QHostAddress::Broadcast,9999);
}

void my_udp_soc::slot_readready()
{
    QByteArray byt;
    byt.resize(m_udp->pendingDatagramSize());
    m_udp->readDatagram(byt.data(),byt.size());
    QString str = QString(byt);
    shuchu<<str;
    QStringList lis = str.split("|");
    if(lis.size()<3)
    {
        return;
    }
    for(int a=0;a<dou_stulis.size();a++)
    {
        if(dou_stulis.at(a).one==lis.at(1))
        {
            return;
        }
    }
    double_QStringstu doub_string;
    doub_string.one = lis.at(1);
    doub_string.two = lis.at(2);
    dou_stulis.append(doub_string);
    ui->tableWidget->setRowCount(dou_stulis.size());
    for(int a=0;a<dou_stulis.size();a++)
    {
        ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString::number(a)));
        ui->tableWidget->setItem(0,1,new QTableWidgetItem(dou_stulis.at(a).one));
        ui->tableWidget->setItem(0,2,new QTableWidgetItem(dou_stulis.at(a).two));
    }
}

void my_udp_soc::on_pushButton_clicked()
{
    if(roow<0)
    {
        m_wanning->show_wanning("未选择行数");
    }
    else
    {
        emit sig_Ipdizhi(ui->tableWidget->item(roow,2)->text());
        hide();
    }

}

void my_udp_soc::slot_cellclick(int ro, int com)
{
    Q_UNUSED(com);
    roow = ro;
}

void my_udp_soc::on_pushButton_2_clicked()
{
    close();
}
