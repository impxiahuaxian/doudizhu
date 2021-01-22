#-------------------------------------------------
#
# Project created by QtCreator 2020-01-30T20:09:50
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = doudizhu
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    mycontrol.cpp \
        widget.cpp \
    mystruct.cpp \
    common.cpp \
    selectkind.cpp \
    my_wanning.cpp \
    myresult.cpp \
    my_judge.cpp \
    Tcpconnect/threadtcpsoc.cpp \
    card_button.cpp \
    my_file.cpp \
    Tcpconnect/mytcpserver.cpp \
    Tcpconnect/my_udp_soc.cpp \
    player.cpp \
    mypopup.cpp

HEADERS += \
    mycontrol.h \
        widget.h \
    mystruct.h \
    common.h \
    selectkind.h \
    my_wanning.h \
    myresult.h \
    my_judge.h \
    Tcpconnect/threadtcpsoc.h \
    card_button.h \
    my_file.h \
    Tcpconnect/mytcpserver.h \
    Tcpconnect/my_udp_soc.h \
    player.h \
    mypopup.h

FORMS += \
        widget.ui \
    selectkind.ui \
    my_wanning.ui \
    myresult.ui \
    Tcpconnect/my_udp_soc.ui \
    mypopup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
