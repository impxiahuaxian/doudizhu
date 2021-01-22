#ifndef MY_WANNING_H
#define MY_WANNING_H

#include <QDialog>

#include <QDebug>
#define shuchu qDebug()<<"<文件名: "<<__FILE__<<"行号:"<<__LINE__<<">  "

namespace Ui {
class my_wanning;
}

class my_wanning : public QDialog
{
    Q_OBJECT

public:
    explicit my_wanning(QWidget *parent = 0);
    ~my_wanning();

    void show_wanning(QString mwarn);

private:
    Ui::my_wanning *ui;
};

#endif // MY_WANNING_H
