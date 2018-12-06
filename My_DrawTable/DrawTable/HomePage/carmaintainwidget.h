#ifndef CARMAINTAINWIDGET_H
#define CARMAINTAINWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>


class CarMaintainWidget : public QDialog
{

      Q_OBJECT
public:
    explicit CarMaintainWidget(QWidget *parent = 0);
    ~CarMaintainWidget();

    //文字
    QLabel* label_BigTitle;

    QLabel* label_carnumber;//车牌号
    QLabel* label_dirver;//驾驶员
    QLabel* label_weight;
    QLabel* label_telephone;
    QLabel* background_pic;
    //按钮
    QPushButton* btn_test; //测试
    QPushButton* btn_add;   //增
    QPushButton* btn_delete;//删
    QPushButton* btn_update;//改
    QPushButton* btn_select;//查

    //输入框
    QLineEdit* lineEdit_carnumber;
    QLineEdit* lineEdit_dirver;
    QLineEdit* lineEdit_weight;
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

#endif // CARMAINTAINWIDGET_H
