#include "widget_test.h"
#include <QPainter>

Widget_Test::Widget_Test(QWidget *parent, int www, int hhh) : QWidget(parent)
{
    setFixedSize(www,hhh);

    scrollArea = new QScrollArea(this);
    scrollArea->setFixedSize(www,hhh);
    scrollArea->setFrameShape(QFrame::NoFrame); //设置滑动区域无边框
    picframe= new QIR_PIC(this,"C:/Users/Administrator/Desktop/timg.jpg");
    scrollArea->setWidget(picframe); //设置widget
}
