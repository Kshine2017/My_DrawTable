#include "welcompage.h"
#include <QMovie>
#include <QDebug>
WelcomPage::WelcomPage(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(762, 386);
    //resize(parent->size().width()-200,parent->size().height());
    //背景图片
    QMovie *mov =new QMovie(":/picture/backgroundgif.gif");
    background_Label_pic = new QLabel(this);
    background_Label_pic->setMovie(mov);
    background_Label_pic->resize(this->size());
    background_Label_pic->move(0,0);
    mov->setScaledSize(this->size());
    mov->start();

    //组成
//    lb_Kshine = new QLabel(this);
//    lb_Kshine->setFixedSize(100,30);
//    lb_Kshine->setScaledContents(true);
//    QPixmap pix_logo;
//    pix_logo.load(":/picture/Kshine.png");
//    pix_logo.scaled(lb_Kshine->size(), Qt::IgnoreAspectRatio);
//    lb_Kshine->setPixmap(pix_logo);



    //布局
    //ly_G_all = new QGridLayout();
    //ly_G_all->addWidget(lb_Kshine,0,0,Qt::AlignCenter);


    //setLayout(ly_G_all);
    show();
    qDebug()<<this->width()<<this->height();
}

void WelcomPage::resizeEvent(QResizeEvent *size)
{
    //刷新背景图片
    background_Label_pic->resize(this->size());
    background_Label_pic->movie()->setScaledSize(this->size());
    qDebug()<<"welcome"<<this->size();
}
