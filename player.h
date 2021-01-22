#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>

class player : public QWidget
{
    Q_OBJECT
public:
    explicit player(QWidget *parent = nullptr);

signals:
    void sig_value(int);
public slots:
    void initsys();

    void bofang_file(int state);

    void slot_value(int Cvalue);

private:
    QMediaPlayer *play;
    QString filename;

    int Cvalue_va;
};

#endif // PLAYER_H
