#ifndef USERMANAGERDIALOG_H
#define USERMANAGERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

class UserManagerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UserManagerDialog(QWidget *parent = 0,const QString& account="admin");
    ~UserManagerDialog();


    //函数
    void init_button();
    void init_lineEdit();

    QLabel* background_pic;
    QLabel* lb_account; QLineEdit* le_account;      QHBoxLayout* layH_account;
    QLabel* lb_pwd;     QLineEdit* le_pwd;          QHBoxLayout* layH_pwd;
    QLabel* lb_name;    QLineEdit* le_name;         QHBoxLayout* layH_name;
    QLabel* lb_status;  QComboBox* cmbx_status;     QHBoxLayout* layH_status;

    QPushButton* btn_AddUser;QPushButton* btn_Promote;QPushButton* btn_degrade;QPushButton* btn_delete;QHBoxLayout* layH_btn;

    QVBoxLayout* lay_all;

signals:

public slots:

    void slot_addUser();
    void slot_updateInfo();
    void slot_deleteUser();
};

#endif // USERMANAGERDIALOG_H
