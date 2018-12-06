#ifndef QIR_PIC_H
#define QIR_PIC_H

#include <QWidget>
#include <QFrame>
#include <QPixmap>
class QIR_PIC : public QFrame
{
    Q_OBJECT
public:
    explicit QIR_PIC(QWidget *parent = 0,QString pic=NULL);
    QPixmap pix;
    unsigned int thisWidth;
    unsigned int thisHeight;
protected:
    virtual void mousePressEvent(QMouseEvent* ev);
    virtual void mouseMoveEvent(QMouseEvent* ev);
    virtual void mouseReleaseEvent(QMouseEvent* ev);

    virtual void paintEvent(QPaintEvent *ev);  //控件重绘
signals:

public slots:
};

#endif // QIR_PIC_H
