#ifndef MYPOPUP_H
#define MYPOPUP_H

#include <QDialog>

namespace Ui {
class myPopup;
}

class myPopup : public QDialog
{
    Q_OBJECT

public:
    explicit myPopup(QWidget *parent = 0);
    ~myPopup();
    void Text_show(QString str);

private:
    Ui::myPopup *ui;
};

#endif // MYPOPUP_H
