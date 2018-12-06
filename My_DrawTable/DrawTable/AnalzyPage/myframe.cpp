#include "myframe.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>     //画笔
MyFrame::MyFrame(QWidget *parent) :
    QFrame(parent)
{
    type_painter=1;
}

void MyFrame::type(int num)
{
    type_painter=num;
}

void MyFrame::slot_preview()
{
    type_painter=2;
    update();
}

void MyFrame::mousePressEvent(QMouseEvent* ev)
{
    if(type_painter!=1)return;
    qDebug()<<"press"<<"xy("<<ev->x()<<","<<ev->y()<<"), globalxy("<<ev->globalX()<<","<<ev->globalY()<<")";
    //--------
    QPoint point(ev->x(),ev->y());
    points.push_back(point);
    update();
}
void MyFrame::mouseMoveEvent(QMouseEvent* ev)
{
    if(type_painter!=1)return;
    qDebug()<<"move";
    //--------------
    QPoint point(ev->x(),ev->y());
    points.push_back(point);
    update();                       //chonghui,diaoyonghuizhihanshu
}
void MyFrame::mouseReleaseEvent(QMouseEvent* ev)
{
    if(type_painter!=1)return;
    qDebug()<<"relese";
    //---------------------------
    QPoint point(ev->x(),ev->y());
    points.push_back(point);
    update();
    //---------- 松手之后添加一个断点--------------
    QPoint breakpoint(-223,-223);
    points.push_back(breakpoint);
}

 void MyFrame::paintEvent(QPaintEvent *ev)
 {
    Q_UNUSED(ev);
     if(type_painter==1)
     {
         QPainter painter;
         std::vector<QPoint>::iterator it;
         if(points.size()<=1)
         {
             return;
         }
         painter.begin(this);
         QPoint start =points[0];
         for(it=points.begin();it!=points.end();it++)
         {
             if(start==QPoint(-223,-223)||*it==QPoint(-223,-223))
             {
                 start = *it;
                 continue;
             }
             painter.drawLine(start,*it);
             start = *it;
         }
         painter.end();
    }
     else if(type_painter==2)
     {

         QPixmap pix;
         pix.load("C:/Users/Administrator/Desktop/timg.jpg");
         QSize picSize(700,400);
         //将pixmap缩放成picSize大小然后保存在scaledPixmap中;
         //按比例缩放：
         QPixmap scaledPixmap = pix.scaled(picSize, Qt::KeepAspectRatio);
         //不按照比例缩放：
         //QPixmap scaledPixmap = pix.scaled(picSize);
         QPainter painter(this);
         //painter.drawLine(QPoint(0, 0), QPoint(100, 100));
         //painter.drawImage(0,0,QImage("C:/Users/Administrator/Desktop/timg.jpg"));
         painter.drawPixmap(0,0,700,400,scaledPixmap);
         painter.drawText(QRect(10,100,50,30),"100");
         painter.drawText(QRect(10,200,50,30),"200");
         painter.drawText(QRect(10,300,50,30),"300");
         painter.drawText(QRect(10,400,50,30),"400");
         painter.drawLine(QPoint(0, 100), QPoint(800, 100));
         painter.drawLine(QPoint(0, 200), QPoint(800, 200));
         painter.drawLine(QPoint(0, 300), QPoint(800, 300));
         painter.drawLine(QPoint(0, 400), QPoint(800, 400));

         painter.drawText(QRect(100,10,50,30),"100");
         painter.drawText(QRect(200,10,50,30),"200");
         painter.drawText(QRect(300,10,50,30),"300");
         painter.drawText(QRect(400,10,50,30),"400");
         painter.drawText(QRect(500,10,50,30),"500");
         painter.drawText(QRect(600,10,50,30),"600");
         painter.drawText(QRect(700,10,50,30),"700");

         painter.drawLine(QPoint(100, 0), QPoint(100, 500));
         painter.drawLine(QPoint(200, 0), QPoint(200, 500));
         painter.drawLine(QPoint(300, 0), QPoint(300, 500));
         painter.drawLine(QPoint(400, 0), QPoint(400, 500));
         painter.drawLine(QPoint(500, 0), QPoint(500, 500));
         painter.drawLine(QPoint(600, 0), QPoint(600, 500));
         painter.drawLine(QPoint(700, 0), QPoint(700, 500));

         painter.drawRect(100,400,100,30);

     }
 }
