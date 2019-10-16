#-------------------------------------------------
#
# Project created by QtCreator 2018-02-01T23:21:31
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport #打印
QT       += sql #数据库
#QT       += charts  #绘制饼图
QT += axcontainer #excel
#QT +=multimedia
DEFINES += QT_DLL

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DrawTable
TEMPLATE = app

SOURCES += main.cpp\
    AnalzyPage/reportdialog.cpp \
    GAME/snake/food.cpp \
    GAME/snake/gamecontroller.cpp \
    GAME/snake/snake.cpp \
    GAME/snake/snakewindow.cpp \
    GAME/snake/wall.cpp \
        mainwindow.cpp \
    HomePage/homepagewindow.cpp \
    AddPage/addpagewindow.cpp \
    HomePage/placemaintainwidget.cpp \
    HomePage/carmaintainwidget.cpp \
    loginwidget.cpp \
    registwidget.cpp \
    UserPage/userpage.cpp \
    UserPage/usermanagerdialog.cpp \
    UserPage/exportimportexcel.cpp \
    UserPage/setconfig.cpp \
    HomePage/typemaintainwidget.cpp \
    DataBaseOpration/carinfo.cpp \
    DataBaseOpration/carinfodao.cpp \
    DataBaseOpration/carinfodaoimp.cpp \
    DataBaseOpration/placeinfo.cpp \
    DataBaseOpration/placeinfodao.cpp \
    DataBaseOpration/placeinfodaoimp.cpp \
    DataBaseOpration/recorddaoimp.cpp \
    DataBaseOpration/typedaoimp.cpp \
    DataBaseOpration/user.cpp \
    DataBaseOpration/userdao.cpp \
    DataBaseOpration/userdaoimp.cpp \
    AnalzyPage/analzypage.cpp \
    DataBaseOpration/databaseconnect.cpp \
    Common/funcation.cpp \
    Common/printdialog.cpp \
    Common/printticket.cpp \
    welcompage.cpp

HEADERS  += mainwindow.h \
    AnalzyPage/reportdialog.h \
    GAME/snake/constants.h \
    GAME/snake/food.h \
    GAME/snake/gamecontroller.h \
    GAME/snake/snake.h \
    GAME/snake/snakewindow.h \
    GAME/snake/wall.h \
    HomePage/homepagewindow.h \
    AddPage/addpagewindow.h \
    HomePage/placemaintainwidget.h \
    HomePage/carmaintainwidget.h \
    loginwidget.h \
    registwidget.h \
    UserPage/userpage.h \
    UserPage/usermanagerdialog.h \
    UserPage/exportimportexcel.h \
    UserPage/setconfig.h \
    HomePage/typemaintainwidget.h \
    DataBaseOpration/placeinfodao.h \
    DataBaseOpration/placeinfodaoimp.h \
    DataBaseOpration/recorddaoimp.h \
    DataBaseOpration/typedaoimp.h \
    DataBaseOpration/user.h \
    DataBaseOpration/userdao.h \
    DataBaseOpration/userdaoimp.h \
    DataBaseOpration/carinfo.h \
    DataBaseOpration/carinfodao.h \
    DataBaseOpration/carinfodaoimp.h \
    DataBaseOpration/placeinfo.h \
    AnalzyPage/analzypage.h \
    DataBaseOpration/databaseconnect.h \
    Common/funcation.h \
    Common/printdialog.h \
    Common/printticket.h \
    welcompage.h

FORMS    +=

RESOURCES += \
            pic.qrc
#------------------------------------------------------------------
VERSION = 1.1.1.001
QMAKE_TARGET_COMPANY ="Kshine"
QMAKE_TARGET_DESCRIPTION ="打印单据 on Qt5.9/5.13,2019.10.12"
QMAKE_TARGET_COPYRIGHT = "all rights reserved"
QMAKE_TARGET_PRODUCT = "运货出单"
#RC_CODEPAGE
RC_LANG = 0x0004 #“中文（简体）”
RC_ICONS = ico.ico  #换用Qt 5.13可以正常
#------------------------------------------------------------------
#RC_FILE
#RES_FILE


#------------------------------------------------------------------



