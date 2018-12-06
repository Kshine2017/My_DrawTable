#ifndef QUALITYPAGE_H
#define QUALITYPAGE_H

#include <QWidget>
#include <QTabWidget>
#include "widget_test.h"

class QualityPage : public QWidget
{
    Q_OBJECT
public:
    explicit QualityPage(QWidget *parent = 0);
    ~QualityPage();
     QTabWidget* tabwidget;              //切换类
     Widget_Test* widget_1;                  //待修改图片所在界面1
     QWidget* widget_2;            //2
     QWidget* widget_3;        //3

    void init_component();
    void init_layout();

signals:

public slots:
};

#endif // QUALITYPAGE_H
