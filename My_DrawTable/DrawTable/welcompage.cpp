#include "welcompage.h"
#include <QMovie>
#include <QDebug>
#include "GAME/snake/snakewindow.h"

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
    btn_snake = new QPushButton(this);
    btn_snake->setText("贪吃蛇");
    connect(btn_snake,SIGNAL(clicked()),this,SLOT(slot_startSnakeGame()));

//    btn_magicTower =  new QPushButton(this);
//    btn_magicTower->setText("魔塔");
//    connect(btn_magicTower,SIGNAL(clicked()),this,SLOT(slot_startMagicTower()));




    //布局
    ly_G_all = new QGridLayout();
    ly_G_all->addWidget(btn_snake,0,0,Qt::AlignCenter);
//    ly_G_all->addWidget(btn_magicTower,1,0,Qt::AlignCenter);
    ly_G_all->setColumnStretch(1,10);
    ly_G_all->setRowStretch(10,10);

    setLayout(ly_G_all);
    show();
    qDebug()<<this->width()<<this->height();
}

void WelcomPage::resizeEvent(QResizeEvent *size)
{
    Q_UNUSED(size)
    //刷新背景图片
    background_Label_pic->resize(this->size());
    background_Label_pic->movie()->setScaledSize(this->size());
    qDebug()<<"welcome"<<this->size();
}

void WelcomPage::slot_startSnakeGame()
{
    qDebug()<<"贪吃蛇";
    new SnakeWindow(this);

}

void WelcomPage::slot_startMagicTower()
{
    qDebug()<<"魔塔";

}
