#ifndef REGISTWIDGET_H
#define REGISTWIDGET_H
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialog>
class RegistWidget : public QDialog
{
      Q_OBJECT
public:
    RegistWidget(QWidget* parent=0);
    ~RegistWidget();
    QLabel* lb_regist_title;

    QLabel* lb_account;
    QLabel* lb_password;
    QLabel* lb_name;

    QLineEdit* le_account;
    QLineEdit* le_password;
    QLineEdit* le_name;

    QPushButton* btn_sure;
    QPushButton* btn_cancel;

    QHBoxLayout* lyH_account;
    QHBoxLayout* lyH_password;
    QHBoxLayout* lyH_name;
    QHBoxLayout* lyH_btn;

    QVBoxLayout* lyV_all;


void init_label_lineEdit_btn();

public slots:
void slot_btn_sure();
void slot_btn_cancel();

};

#endif // REGISTWIDGET_H
