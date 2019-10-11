#-------------------------------------------------
#
# Project created by QtCreator 2018-02-01T23:21:31
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
QT       += sql
#QT       += charts  #缁樺埗楗煎浘

#CONFIG += qwt #20190723
#CONFIG   += qaxcontainer
QT += axcontainer
DEFINES += QT_DLL #QWT_DLL

##LIBS += -L"D:\Qt\Qt5.9.1\5.9.1\mingw53_32\lib" -lqwtd
##LIBS += -L"D:\Qt\Qt5.9.1\5.9.1\mingw53_32\lib" -lqwt
##INCLUDEPATH += D:\Qt\Qt5.9.1\5.9.1\mingw53_32\include\QWT

#LIBS += -L"D:\Qt\Qt5.7.0\5.7\mingw53_32\lib" -lqwtd
#LIBS += -L"D:\Qt\Qt5.7.0\5.7\mingw53_32\lib" -lqwt #20190723
#LIBS += -L"E:\DrawTable\lib" -lqwt
#INCLUDEPATH += D:\Qt\Qt5.7.0\5.7\mingw53_32\include\QWT #20190723

#LIBS += -L"D:\Qt\Qt5.9.2\5.9.2\mingw53_32\lib" -lqwtd
#LIBS += -L"D:\Qt\Qt5.9.2\5.9.2\mingw53_32\lib" -lqwt
#INCLUDEPATH += D:\Qt\Qt5.9.2\5.9.2\mingw53_32\include\QWT

#LIBS += -L"E:\Qt\Qt5.9.2\5.9.2\mingw53_32\lib" -lqwtd
#LIBS += -L"E:\Qt\Qt5.9.2\5.9.2\mingw53_32\lib" -lqwt
#INCLUDEPATH += E:\Qt\Qt5.9.2\5.9.2\mingw53_32\include\QWT


#LIBS += -L$$PWD\lib\  -lqwt
#LIBS += -L$$PWD\lib\  -lqwtd
#CONFIG(debug,debug|release) {
# unix|win32: LIBS += -lQtCored4
# unix|win32: LIBS += -lQtGuid4
# unix|win32: LIBS += -lQtNetworkd4
#} else {
# unix|win32: LIBS += -lQtCore4
# unix|win32: LIBS += -lQtGui4
# unix|win32: LIBS += -lQtNetwork4
#}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DrawTable
TEMPLATE = app



SOURCES += main.cpp\
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


#RC_FILE += myapp.rc

DISTFILES += \
    lib/qwt.dll \
    lib/qwtd.dll \
    AnalzyPage/AnalzyPage.rar \
    design/03e3417f77dbefa3573a0fc1f622aa58.jpg \
    design/393047af42fb9a9c5e2b1bb033876043.jpg \
    design/u=4133702964,4126049183&fm=27&gp=0.jpg \
    picture/homepage_background - 副本.jpg \
    design/Car-down.png \
    design/Car-up.png \
    design/down.png \
    design/finishPng-down.png \
    design/finishPng-up.png \
    design/homepage-border.png \
    design/up.png \
    design/表单.png \
    design/表单2.png \
    design/页面3布局设计.png \
    design/首页布局.png \
    picture/myappico.ico \
    ico.ico \
    myappico.ico \
    config/current_user.ini \
    config/liushuihao.ini \
    design/数据库.txt \
    picture/myapp.rc \
    myapp.rc \
    picture/homepage_background - 副本.jpg \
    picture/homepage_background - 副本.jpg \
    picture/homepage_background - 副本.jpg \
    picture/homepage_background - 副本.jpg \
    picture/homepage_background - 副本.jpg
