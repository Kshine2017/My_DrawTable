#ifndef PLOTBAR_H
#define PLOTBAR_H
#include <QDialog>

class PlotBar : public QDialog
{
    Q_OBJECT
public:
    PlotBar(QWidget* parent=0);
    ~PlotBar();
};

#endif // PLOTBAR_H
