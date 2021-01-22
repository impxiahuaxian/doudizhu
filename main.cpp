#include "mycontrol.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mycontrol w;
    w.starting_items(2);
    return a.exec();
}
