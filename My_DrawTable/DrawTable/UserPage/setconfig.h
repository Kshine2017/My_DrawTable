#ifndef SETCONFIG_H
#define SETCONFIG_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
class SetConfig:public QDialog
{
    Q_OBJECT
public:
    SetConfig(QWidget *parent = 0);
    ~SetConfig();
    QLabel* background_pic;

    QLabel* lb_cmbx;
    QComboBox* cmbx;
    QHBoxLayout* ly_cmbx;


public slots:
    void slot_writePrintConfig(int index);
};

#endif // SETCONFIG_H
