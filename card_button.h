#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include <QWidget>
#include <QPushButton>

class card_button : public QPushButton
{
    Q_OBJECT
public:
    explicit card_button(QWidget *parent = nullptr);
    explicit card_button(QString cardnumber, QString huase);
    void setPic(QString str1,QString str2);

    QString currhuase();
    QString currnumb();
public slots:
protected:
    void showEvent(QShowEvent *event);
private:
    QIcon my_icon;
    QString B_cardnumber;
    QString B_huase;
};

#endif // CARD_BUTTON_H
