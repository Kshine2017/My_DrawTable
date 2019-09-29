#-------------------------------------------------
#
# Project created by QtCreator 2018-02-01T23:21:31
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
QT       += sql
#QT       += charts  #绘制饼图

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
    funcation.cpp \
    HomePage/placemaintainwidget.cpp \
    HomePage/carmaintainwidget.cpp \
    HomePage/placeinfo.cpp \
    HomePage/placeinfodao.cpp \
    HomePage/placeinfodaoimp.cpp \
    databaseconnect.cpp \
    HomePage/carinfo.cpp \
    HomePage/carinfodao.cpp \
    HomePage/carinfodaoimp.cpp \
    loginwidget.cpp \
    UserPage/user.cpp \
    UserPage/userdao.cpp \
    UserPage/userdaoimp.cpp \
    registwidget.cpp \
    AnalzyPage/recorddaoimp.cpp \
    AnalzyPage/plotbar.cpp \
    printdialog.cpp \
    printticket.cpp \
    UserPage/userpage.cpp \
    UserPage/usermanagerdialog.cpp \
    AnalzyPage/myframe.cpp \
    UserPage/exportimportexcel.cpp \
    UserPage/setconfig.cpp \
    typedaoimp.cpp \
    HomePage/typemaintainwidget.cpp \
    Quality_inspection_reportPage/qualitypage.cpp \
    Quality_inspection_reportPage/widget_test.cpp \
    Quality_inspection_reportPage/qir_pic.cpp \
    AnalzyPage_V2/analzypage_v2.cpp

HEADERS  += mainwindow.h \
    HomePage/homepagewindow.h \
    AddPage/addpagewindow.h \
    funcation.h \
    HomePage/placemaintainwidget.h \
    HomePage/carmaintainwidget.h \
    HomePage/placeinfo.h \
    HomePage/placeinfodao.h \
    HomePage/placeinfodaoimp.h \
    databaseconnect.h \
    HomePage/carinfo.h \
    HomePage/carinfodao.h \
    HomePage/carinfodaoimp.h \
    loginwidget.h \
    UserPage/user.h \
    UserPage/userdao.h \
    UserPage/userdaoimp.h \
    registwidget.h \
    AnalzyPage/recorddaoimp.h \
    AnalzyPage/plotbar.h \
    printdialog.h \
    printticket.h \
    UserPage/userpage.h \
    UserPage/usermanagerdialog.h \
    AnalzyPage/myframe.h \
    UserPage/exportimportexcel.h \
    UserPage/setconfig.h \
    typedaoimp.h \
    HomePage/typemaintainwidget.h \
    Quality_inspection_reportPage/qualitypage.h \
    Quality_inspection_reportPage/widget_test.h \
    Quality_inspection_reportPage/qir_pic.h \
    AnalzyPage_V2/analzypage_v2.h

FORMS    +=

RESOURCES += \
            pic.qrc


#RC_FILE += myapp.rc
