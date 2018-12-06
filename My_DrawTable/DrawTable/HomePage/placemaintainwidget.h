#ifndef PLACEMAINTAINWIDGET_H
#define PLACEMAINTAINWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
class PlaceMaintainWidget: public QDialog
{

    Q_OBJECT


public:
    explicit PlaceMaintainWidget(QWidget *parent = 0);
    ~PlaceMaintainWidget();

    //文字
    QLabel* label_BigTitle;
    QLabel* label_keynumber;
    QLabel* label_placeName;
    QLabel* label_placeMan;
    QLabel* label_telephone;
    QLabel* background_pic;
    //按钮
    QPushButton* btn_test; //测试
    QPushButton* btn_add;   //增
    QPushButton* btn_delete;//删
    QPushButton* btn_update;//改
    QPushButton* btn_select;//查

    //输入框
    QLineEdit* lineEdit_keynumber;//录入编号
    QLineEdit* lineEdit_placeName;//场地名称
    QLineEdit* lineEdit_placeMan;//场地负责人
    QLineEdit* lineEdit_telephone;//联系电话

    //表格
    QTableWidget* table;
    QTableView* tableView;

    //布局
    QHBoxLayout* layout_btn;
    QVBoxLayout* layout_lineEditV;
    QVBoxLayout* layout_label;


    //函数
    void init_button();
    void init_lineEdit();
    void init_label();
    void init_table();

    void init_button_connection();

public slots:
    void slot_btn_add();
    void slot_btn_del();
    void slot_btn_upd();
    void slot_btn_sel();
    void slot_table_doubleClick(const QModelIndex &index);


};

#endif // PLACEMAINTAINWIDGET_H
