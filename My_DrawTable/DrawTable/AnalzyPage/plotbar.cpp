#include "plotbar.h"
#include <QDebug>
PlotBar::PlotBar(QWidget *parent)
    :QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose); //在关闭该窗口时，自主调用析构函数

    //this->setStyleSheet("background-color:grey;");
    this->setFixedSize(640,400);

    show();
}

PlotBar::~PlotBar()
{
    qDebug()<<"释放柱形图窗口";
}
