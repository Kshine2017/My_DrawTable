#ifndef WIDGET_TEST_H
#define WIDGET_TEST_H

#include <QWidget>
//#include "../AnalzyPage/myframe.h"
#include <QScrollArea>
#include "qir_pic.h"
/*
画出图片
指定位置
修改保存值
打印预览
*/
class Widget_Test : public QWidget
{
    Q_OBJECT
public:
    explicit Widget_Test(QWidget *parent = 0,int www=800,int hhh=470);

    QScrollArea* scrollArea;
    QIR_PIC* picframe;
    //按钮，用于更改信息
    //按钮初始位置

    //弹出修改弹窗，返回修改值

    //修改值存储




signals:

public slots:
};

#endif // WIDGET_TEST_H
