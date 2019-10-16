#ifndef WELCOMPAGE_H
#define WELCOMPAGE_H
/*
该类用于欢迎界面
可放置各种小游戏等等

*/
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
class WelcomPage : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomPage(QWidget *parent = 0);
    QLabel* lb_Kshine;
    QLabel* background_Label_pic;
    QGridLayout* ly_G_all;
    QPushButton* btn_snake;
    QPushButton* btn_magicTower;

protected:
    void resizeEvent(QResizeEvent* size);


signals:

public slots:
    void slot_startSnakeGame();
    void slot_startMagicTower();
};

#endif // WELCOMPAGE_H
