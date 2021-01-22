#ifndef COMMON_H
#define COMMON_H

#include <QObject>
#include "mystruct.h"
#include <QNetworkInterface>
#include <QHostInfo>
#include <QBuffer>
#include <QProcess>

class common : public QObject
{
    Q_OBJECT
public:
    explicit common(QObject *parent = nullptr);
    static void my_sort(QList<paidui> &my_list);
    static QString get_getIP();
    static QStringList get_allgetIP();
    static QByteArray picTodata(QString fromPic);  //将图片转化为64位QByteArray
    static void dataToPic(QString formData,QString toPic);//将64位QByteArray转化为图片
    static QString get_CPUID();//查看cpu序列号
    static QByteArray mytoByteArray(int num);
    static int mytoInt(QByteArray byts);
signals:

public slots:
};

#endif // COMMON_H
