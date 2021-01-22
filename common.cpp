#include "common.h"

common::common(QObject *parent) : QObject(parent)
{

}

void common::my_sort(QList<paidui> &my_list)
{
    std::sort(my_list.begin(),my_list.end(),[=](paidui temp1,paidui temp2)
    {
        return temp1.number>temp2.number;
    });
}

QString common::get_getIP()
{

    QString hostAddr = "";
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
    //排除虚拟机地址
    for(int i = 0; i < nCnt; i ++) {
        if (  nets[i].hardwareAddress() == "00:50:56:C0:00:01" ) {
            nets.removeAt( i );
            break;
        }
    }
    nCnt = nets.count();
    for(int i = 0; i < nCnt; i ++) {
        if (  nets[i].hardwareAddress() == "00:50:56:C0:00:08" ) {
            nets.removeAt( i );
            break;
        }
    }
    foreach(QNetworkInterface interface,nets) {
        //排除不在活动的IP
        if( interface.flags().testFlag(QNetworkInterface::IsUp) && interface.flags().testFlag(QNetworkInterface::IsRunning ) ){
            QList<QNetworkAddressEntry> entryList = interface.addressEntries();
            foreach(QNetworkAddressEntry entry,entryList) {
                QHostAddress hostAddress = entry.ip();

                if ( hostAddr.isEmpty() ) {
                    //排除本地地址
                    if ( hostAddress != QHostAddress::LocalHost && hostAddress.toIPv4Address() ) {
                        quint32 nIPV4 = hostAddress.toIPv4Address();
                        //本地链路地址
                        quint32 nMinRange = QHostAddress("169.254.1.0").toIPv4Address();
                        quint32 nMaxRange = QHostAddress("169.254.254.255").toIPv4Address();
                        //排除链路地址
                        if ( ( nIPV4 >= nMinRange ) && ( nIPV4 <= nMaxRange ) )
                            continue;
                        hostAddr = hostAddress.toString();
                        return hostAddr;
                    }
                }
            }
        }
    }
    return "";
}

QStringList common::get_allgetIP()
{
    QString loc = QHostInfo::localHostName();
    QHostInfo info = QHostInfo::fromName(loc);
    QStringList lis;
    foreach (QHostAddress add, info.addresses()) {
        if(add.protocol()==QAbstractSocket::IPv4Protocol)
        {
            lis.append(add.toString());
        }
    }
    return lis;
}

QByteArray common::picTodata(QString fromPic)
{

    QImage img(fromPic);
    QByteArray ba;
    QBuffer buf(&ba);
    img.save(&buf,"png");
    QByteArray cc=qCompress(ba,1);
    QByteArray hh;
    hh = cc.toBase64();
    //hh就是数据
}

void common::dataToPic(QString formData, QString toPic)
{
    QByteArray bty = QByteArray::fromBase64(formData.toUtf8());
    QByteArray rcd = qUncompress(bty);
    QImage img;
    img.loadFromData(rcd);
    img.save(toPic);
}

QString common::get_CPUID()
{
    QString cpu_id = "";
    QProcess p;
    p.start("wmic CPU get ProcessorID"); //查看cpu序列号
    p.waitForStarted();
    p.waitForFinished();
    cpu_id = QString::fromLocal8Bit(p.readAllStandardOutput());
    cpu_id = cpu_id.remove("ProcessorId").trimmed();
    return cpu_id;
}

QByteArray common::mytoByteArray(int num)
{
    char *len = (char *)(&num);
    QByteArray ba;
    ba.resize(sizeof(int));
    memcpy(ba.data(),len,sizeof(int));
    return ba;
}

int common::mytoInt(QByteArray byts)
{
    if(byts.length()<4)
    {
        return 0;
    }
    return (byts[0]& 0x000000FF)|((byts[1]<<8)&0x0000FF00)|((byts[2]<<16)&0x00FF0000)|((byts[3]<<24)&0xFF000000);
}

