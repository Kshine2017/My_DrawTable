#ifndef WELCOMPAGE_H
#define WELCOMPAGE_H
/*
该类用于欢迎界面
可放置各种小游戏等等

*/
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
class WelcomPage : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomPage(QWidget *parent = 0);
    QLabel* lb_Kshine;
    QLabel* background_Label_pic;
    QGridLayout* ly_G_all;


protected:
    void resizeEvent(QResizeEvent* size);


signals:

public slots:
};

#endif // WELCOMPAGE_H
