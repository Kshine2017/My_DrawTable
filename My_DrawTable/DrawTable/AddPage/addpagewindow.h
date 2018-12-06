#ifndef ADDPAGEWINDOW_H
#define ADDPAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QSqlTableModel>
class AddPageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AddPageWindow(QWidget *parent = 0);
    ~AddPageWindow();

    QSqlTableModel* model;
    //------
    QLabel* background_pic;


    //-----日历----
    QLabel* label_date;
    QLabel* label_time;
    QDateEdit *dateEdit;     //日期
    QTimeEdit *timeEdit;    //时间
    QDateTimeEdit* datetimeEdit;//x
    QHBoxLayout* layout_timeH;
    void init_dateEdit();


    //-----
    //总重（毛重）：
    QLabel* label_totalWeight;
    QLineEdit* lineEdit_totalWeight;

    //皮重：
    QLabel* label_truckWeight;
    QLineEdit* lineEdit_truckWeight;

    //净重：
    QLabel* label_thingsWeight;
    QLineEdit* lineEdit_thingsWeight;

    //场地
    QLabel* label_place;
    QComboBox* combox_place;


    //流水号
    QLabel* label_number;
    QLineEdit* lineEdit_number;

    //品名
    QLabel* label_type;
    QComboBox* combox_type;

    //车牌号
    QLabel* label_truck_number;
    QComboBox* combox_truck_number;


    //单价
    QLabel* label_price;
    QLineEdit* lineEdit_price;

    //界面显示中文大写
    QLabel* label_BigCN;

    //收货人
    QLabel* label_man_recever;
    QLineEdit* lineEdit_man_recever;
    //驾驶员
    QLabel* label_man_driver;
    QLineEdit* lineEdit_man_driver;
    //过磅员
    QLabel* label_man_watcher;
    QLineEdit* lineEdit_man_watcher;

    //勾选
    QCheckBox* ckb_dirver;
    QCheckBox* ckb_receiver;
    QCheckBox* ckb_watcher;

    QHBoxLayout* layout_ckbH;

    /*布局*/
    //竖直布局
    QVBoxLayout* nameLayout_V;//名称
    QVBoxLayout* valueLayout_V;//数值


    QVBoxLayout* left_name_LV;
    QVBoxLayout* left_value_LV;

    //水平布局
    QHBoxLayout* dataLayout_H;

    QHBoxLayout* Left_LV;


    QHBoxLayout* man_info_H;

    QPushButton* btn_print;
    void init_lineEdit_label_combobox();
    void init_checkbox();
    void getPlaceDataFromDB();//从数据库里面获取场地信息
    void getCarDataFromDB();//从数据库里面获取车辆信息
    void getTypeDataFromDB();
signals:

public slots:
    void slot_getNumberFromDateTime(QDateTime datetime);
    void slot_calculate_weight();
//    void slot_roloadComboBox_place();
//    void slot_roloadComboBox_car();
    void slot_getThingsWeightFromDB(QString text);
    void slot_getPlaceInfoFromDB(QString text);
    //更新临时数据
//    void slot_update_carinfo();
    void slot_print();
};

#endif // ADDPAGEWINDOW_H
