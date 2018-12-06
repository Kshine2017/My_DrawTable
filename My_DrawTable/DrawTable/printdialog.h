#ifndef PRINTDIALOG_H
#define PRINTDIALOG_H

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
class PrintDialog : public QDialog
{
    Q_OBJECT
public:
    PrintDialog(const QStringList &str, QWidget* parent=0);
    ~PrintDialog();
    QLabel* lb_number;
    QLabel* lb_placename;
    QLabel* lb_receiver;
    QLabel* lb_carnumber;
    QLabel* lb_dirver;
    QLabel* lb_totalWeight;
    QLabel* lb_carweight;
    QLabel* lb_thingsweight;
    QLabel* lb_price;
    QLabel* lb_time;
    QLabel* lb_watcher;
    QLabel* lb_type;
    QLineEdit* le_number;
    QLineEdit* le_placename;
    QLineEdit* le_receiver;
    QLineEdit* le_carnumber;
    QLineEdit* le_dirver;
    QLineEdit* le_totalWeight;
    QLineEdit* le_carweight;
    QLineEdit* le_thingsweight;
    QLineEdit* le_price;
    QLineEdit* le_time;
    QLineEdit* le_watcher;
    QLineEdit* le_type;

    QHBoxLayout* lh_1;
    QHBoxLayout* lh_2;
    QHBoxLayout* lh_3;
    QHBoxLayout* lh_4;
    QHBoxLayout* lh_5;
    QHBoxLayout* lh_6;
    QVBoxLayout* lv_all;

    //勾选
    QCheckBox* ckb_dirver;
    QCheckBox* ckb_receiver;
    QCheckBox* ckb_watcher;


    QPushButton* btn_print;
    QPushButton* btn_update;
    QPushButton* btn_delete;
    void init_lb_le();
    void init_data(QStringList str);
signals:
   // void signal_reload_tabelview();//派生类里面不能定义 信号，想要通知父类界面，可以通过自带的destory（）

public slots:
    void slot_delete();
    void slot_update();
    void slot_print();
};

#endif // PRINTDIALOG_H
