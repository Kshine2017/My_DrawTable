#ifndef HOMEPAGEWINDOW_H
#define HOMEPAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QTextEdit>
#include <QPrinter>
#include <QPrintPreviewDialog>

#include "HomePage/placemaintainwidget.h"
#include "HomePage/carmaintainwidget.h"
#include "HomePage/typemaintainwidget.h"
#include <QCheckBox>
#include <QSqlTableModel>
//首页 定义成一个类
class HomePageWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HomePageWindow(QWidget *parent = 0);
    ~HomePageWindow();
    void init_Label_LineEdit();
    void init_Button();
    void connect_lineEdit();
    void getPlaceDataFromDB();//从数据库里面获取场地信息
    void getCarDataFromDB();//从数据库里面获取车辆信息
    void getTypeDataFromDB();

    QSqlTableModel* model;
    /*布局*/
    QGridLayout* ly_G_all;
    //竖直布局
    QVBoxLayout* nameLayout_V;//名称
    QVBoxLayout* valueLayout_V;//数值


    QVBoxLayout* left_name_LV;
    QVBoxLayout* left_value_LV;

    //水平布局
    QHBoxLayout* dataLayout_H;

    QHBoxLayout* Left_LV;


    QHBoxLayout* man_info_H;
    /*背景图片*/
    QLabel* background_pic;

    //按钮
    QPushButton* btn_print;
    QPushButton* btn_place_maintain;//场地信息维护
    QPushButton* btn_Car_maintain;//汽车信息维护
    QPushButton* btn_Type_maintain;//汽车信息维护

    QPushButton* btn_savePlace;
    QPushButton* btn_saveCar;

    PlaceMaintainWidget* placeWidget;
    CarMaintainWidget* carWidget;
    TypeMaintainWidget* typeWidget;
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


    //备注输入框
    QLabel* label_otherInformation;
    QTextEdit* te_otherInformation;

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

//    QLabel* label_ckb_dirver;
//    QLabel* label_ckb_receiver;

    QHBoxLayout* layout_ckbH;
    void init_checkbox();
protected:
    void resizeEvent(QResizeEvent* size);


public slots:
    void slot_print();
    void slot_calculate_weight();
    void slot_createPlaceMaintain();
    void slot_createCarMaintain();
    void slot_createTypeMaintain();
    void slot_roloadComboBox_place();
    void slot_roloadComboBox_car();
    void slot_roloadComboBox_Type();

    void slot_getThingsWeightFromDB(QString text);
    void slot_getPlaceInfoFromDB(QString text);
    //更新临时数据
    void slot_update_carinfo();

};

#endif // HOMEPAGEWINDOW_H
