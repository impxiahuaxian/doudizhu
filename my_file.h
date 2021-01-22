#ifndef MY_FILE_H
#define MY_FILE_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include "mystruct.h"
#include "common.h"

class my_file : public QWidget
{
    Q_OBJECT
public:
    explicit my_file(QWidget *parent = nullptr);

    File_State read_file();
    bool writer_file(File_State state);
};

#endif // MY_FILE_H
