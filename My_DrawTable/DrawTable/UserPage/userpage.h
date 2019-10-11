#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <QLabel>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
class UserPage : public QWidget
{
    Q_OBJECT
public:
    explicit UserPage(QWidget *parent = 0);
    ~UserPage();

    QTableView* tableview;
    /*背景图片*/
    QLabel* background_pic;
    QSqlQueryModel* querymodel;
    QSqlTableModel* tablemodel;

    QPushButton* btn_set;
    QPushButton* btn_export;//导出
    QPushButton* btn_import;//导入
    QPushButton* btn_manage;//管理
    QHBoxLayout* lay_btn;
    QVBoxLayout* ly_V_all;
    void mend_MODEL_data();
signals:

public slots:


    void slot_doubleClicked(QModelIndex index);
    void slot_freshUserData();

    void slot_set();
    void slot_export();
    void slot_import();
    void slot_manage();
protected:
    void resizeEvent(QResizeEvent* size);
};

#endif // USERPAGE_H
