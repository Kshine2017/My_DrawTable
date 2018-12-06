#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <vector>  //动态数组
#include <QPoint>

//using namespace std; //vector所在的命名空间

class MyFrame : public QFrame
{
    Q_OBJECT
private:
    std::vector<QPoint> points; //动态数组，存储所有的点
public:
    int type_painter;
    explicit MyFrame(QWidget *parent = 0);
    void type(int num);
public slots:
    void slot_preview();
protected:
    virtual void mousePressEvent(QMouseEvent* ev);
    virtual void mouseMoveEvent(QMouseEvent* ev);
    virtual void mouseReleaseEvent(QMouseEvent* ev);

    virtual void paintEvent(QPaintEvent *ev);  //控件重绘
signals:

public slots:

};

#endif // MYFRAME_H
