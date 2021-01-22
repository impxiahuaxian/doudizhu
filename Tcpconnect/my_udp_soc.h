#ifndef MY_UDP_SOC_H
#define MY_UDP_SOC_H

#include <QDialog>
#include <QtNetwork>
#include "common.h"
#include <QTimer>
#include "mystruct.h"

namespace Ui {
class my_udp_soc;
}

class my_udp_soc : public QDialog
{
    Q_OBJECT

public:
    explicit my_udp_soc(QWidget *parent = 0);
    ~my_udp_soc();

    void initsys(bool state);

private:
    Ui::my_udp_soc *ui;
    void zuboinit();

    QHostAddress groupAddress;
    quint16 gro = 35320;
    QUdpSocket *m_udp;
    QTimer *m_time;
    int roow = -1;
    QList<double_QStringstu> dou_stulis;

private slots:
    void slot_sendmessage();
    void slot_readready();
    void on_pushButton_clicked();
    void slot_cellclick(int ro,int com);

    void on_pushButton_2_clicked();

signals:
    void sig_Ipdizhi(QString);
};

#endif // MY_UDP_SOC_H
