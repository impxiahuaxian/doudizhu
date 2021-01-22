#include "my_wanning.h"
#include "ui_my_wanning.h"

//警告界面

my_wanning::my_wanning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::my_wanning)
{
    ui->setupUi(this);
    this->setModal(true);
}

my_wanning::~my_wanning()
{
    delete ui;
}

void my_wanning::show_wanning(QString mwarn)
{
    if(!isVisible())
    {
        ui->textBrowser->clear();
    }
    ui->textBrowser->append(mwarn);
    show();
}
