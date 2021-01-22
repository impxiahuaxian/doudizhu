#ifndef SELECTKIND_H
#define SELECTKIND_H

#include <QWidget>
#include <QSlider>
#include <QDialog>
#include "mystruct.h"
#include "my_file.h"
#include <QInputDialog>

namespace Ui {
class selectkind;
}

class selectkind : public QDialog
{
    Q_OBJECT
public:
    explicit selectkind(QWidget *parent = 0);
    ~selectkind();
    void initsys();

    void btn_pic_Or_test(int state ,Use_stu stu);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_tou_1_clicked();
    void on_pushButton_4_clicked();
    void slot_valueChanged(int Cvalue);//横条的改变信号
    void on_pushButton_2_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::selectkind *ui;
    void showEvent(QShowEvent *event);

private:
    QSlider *verQSlider;

signals:
    void sig_selectkind(int);
    void sig_join_Create(bool);   //加入房间and创建房间 true创建false加入
    void sig_valueChanged(int);
    void sig_myresult_numb(int);
};

#endif // SELECTKIND_H
