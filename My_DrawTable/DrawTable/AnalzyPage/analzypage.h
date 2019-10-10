#ifndef ANALZYPAGE_H
#define ANALZYPAGE_H

#include <QWidget>
#include <QLabel>
#include <QTableView>
#include <QSqlQueryModel>
#include <QPushButton>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

class ANALZYPAGE : public QWidget
{
    Q_OBJECT
public:
    explicit ANALZYPAGE(QWidget *parent = 0);
    QLabel* background_pic;
    QVBoxLayout* ly_V_all;

    //widget1 上半部分
    QWidget* widget1;
    QLabel* table_back_pic; //表格背景图
    QTableView* tableview;  //表格
    QSqlQueryModel *model;  //表格model


    //widget2 下半部分
    QWidget* widget2;
    QHBoxLayout* ly_H_widget2;
    //左
    QVBoxLayout* ly_V_Left;
    QLabel* lb_time_scale;//“时间范围”
    QHBoxLayout* ly_H_Left1;QLabel* lb_cbx_type; QComboBox* cbx_type;//品类
    QHBoxLayout* ly_H_Left2;QLabel* lb_cbx_place;   QComboBox* cbx_place;//场地
    QHBoxLayout* ly_H_Left3;QLabel* lb_cbx_car;     QComboBox* cbx_car;//车辆
    //起始时间标签//起始日期              //截止时间标签//截止日期
    QHBoxLayout* ly_H_Left4;QLabel* lb_S;QDateEdit *dateEdit_S; QLabel* lb_E;QDateEdit *dateEdit_E;

    //中
    QVBoxLayout* ly_V_mid;
    QPushButton* btn_select;    //查询
    QPushButton* btn_display;   //显示


    //右
    QVBoxLayout* ly_V_right;
    QLabel* lb_result;//“查询结果”
    QLabel* lb_car_times;//车次:
    QLabel* lb_allweight;//毛重：
    QLabel* lb_thingsweight;//净重：

    //init funcation
    void init_widget1();
    void init_widget2();
    //从数据库里拉出数据
    void getPlaceDataFromDB();
    void getCarDataFromDB();
    void getTypeDataFromDB();
signals:

public slots:
    void slot_select_all();
    void slot_select();
    void slot_print(QModelIndex index);
    void slot_display();
};

#endif // ANALZYPAGE_H
