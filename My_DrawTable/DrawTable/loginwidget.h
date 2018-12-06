#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include "registwidget.h"
class LoginWidgett : public QDialog
{
    Q_OBJECT
public:
    explicit LoginWidgett(QWidget *parent = nullptr);
    ~LoginWidgett();

    QLabel* lb_title;
    QCheckBox* ckb_savepwd;
    QLabel* lb_account;
    QLabel* lb_pwd;
    QLabel* background_pic;

    QLineEdit* le_account;
    QLineEdit* le_pwd;
    QHBoxLayout* ly_account;
    QHBoxLayout* ly_pwd;

    void init_label_Lineedit();

    QPushButton* btn_load;
    QPushButton* btn_quit;
    QPushButton* btn_regist;
    QHBoxLayout* ly_btnH;

    RegistWidget* regW;

    void init_button();
    void init_create_administrator();
signals:

public slots:
    void slot_load();
    void slot_quit();
    void slot_reg();
};

#endif // LOGINWIDGET_H
