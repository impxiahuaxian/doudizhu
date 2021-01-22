#ifndef MYRESULT_H
#define MYRESULT_H

#include <QDialog>
#include "mystruct.h"

namespace Ui {
class myresult;
}

class myresult : public QDialog
{
    Q_OBJECT

public:
    explicit myresult(QWidget *parent = 0);
    ~myresult();

    void showjiesuan(double_QStringstu done,double_QStringstu dtwo,double_QStringstu dthree);

    void initsys(int a);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::myresult *ui;
};

#endif // MYRESULT_H
