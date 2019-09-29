#include "qir_pic.h"
#include <QDebug>
#include <QPainter>
QIR_PIC::QIR_PIC(QWidget *parent, QString pic) : QFrame(parent)
{
    //必须得到图片的地址
    if(pic==NULL){qDebug()<<"未指定图片路径名称\n";}
    pix.load(pic);
    //由图片的长宽，决定非让frame的长宽，并保存下来
    thisWidth = pix.size().width();
    thisHeight= pix.size().height();
    setFixedSize(thisWidth,thisHeight);
}

void QIR_PIC::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
}

void QIR_PIC::mouseMoveEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
}

void QIR_PIC::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
}

void QIR_PIC::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);
    QPainter painter(this);
    painter.drawPixmap(0,0,thisWidth,thisHeight,pix);

    QPixmap ppix;
    ppix.load("E:/fat.png");
    painter.drawPixmap(0,0,ppix.width(),ppix.height(),ppix);

}
