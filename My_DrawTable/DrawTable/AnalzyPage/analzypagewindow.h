#ifndef ANALZYPAGEWINDOW_H
#define ANALZYPAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTableView>
#include <QSqlQueryModel>
#include <QPushButton>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include "plotbar.h"

#include "mybarchart.h"
class AnalzyPageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AnalzyPageWindow(QWidget *parent = 0);
    ~AnalzyPageWindow();

    QLabel* background_pic;
    QLabel* lb_weight_total;
    QLabel* lb_weight_car;
    QLabel* lb_weight_things;
    void init_weight_label();
    //---------------------
    QTableView* tableview;
    QSqlQueryModel *model;
    void init_tableview();
    //--------------------

    QPushButton* btn_display;
    QPushButton* btn_select;
    //---------------------
    QHBoxLayout* lyH_S;
    QHBoxLayout* lyH_E;
    QHBoxLayout* lyH_P;
    QHBoxLayout* lyH_C;
    QVBoxLayout* lyV_select;
    QVBoxLayout* lyV_button;
    QVBoxLayout* lyV_label_weight;
    //-------------------
    QLabel* lb_S;
    QLabel* lb_E;
    QDateEdit *dateEdit_S;     //起始日期
    QDateEdit *dateEdit_E;     //截止日期

    QLabel* lb_cbx_car;
    QComboBox* cbx_car;//列出所有
    QLabel* lb_cbx_place;
    QComboBox* cbx_place;//列出所有

    void init_select();//日期1，日期2，查询
    void getPlaceDataFromDB();
    void getCarDataFromDB();

    PlotBar* pb;
    MyBarChart* mbc;
signals:

public slots:
    void slot_select();
    void slot_print(QModelIndex index);
    void slot_display();
};

#endif // ANALZYPAGEWINDOW_H
