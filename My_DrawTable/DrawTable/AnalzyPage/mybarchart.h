#ifndef MYBARCHART_H
#define MYBARCHART_H

#include <qwt_plot.h>
#include <qwt_plot_multi_barchart.h>
#include <QDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableView>
//#include <QSqlTableModel>
#include <QStandardItemModel>
//#include <QtWidgets>
//#include <QtCharts>
#include <QFrame>

class MyBarChart: public QDialog
{
    Q_OBJECT
public:
    MyBarChart(QWidget * parent = NULL );
    ~MyBarChart();

    QwtPlot* qwtP1;
    QwtPlot* qwtP2;
    QwtPlot* qwtP3;
    QwtPlot* qwtP4;
    QwtPlotMultiBarChart* multiBarChart;

    QCheckBox* cbx1;
    QCheckBox* cbx2;
    QCheckBox* cbx3;
    QVBoxLayout* lyV_cbx;

    QComboBox* cmbx_orientation;
    QSqlQueryModel model;
    QStandardItemModel* tablemodel;


    //---------------------
    QVBoxLayout* lyV_S;
    QVBoxLayout* lyV_E;
    QVBoxLayout* lyV_P;
    QVBoxLayout* lyV_C;
    QHBoxLayout* lyH_select;
    QHBoxLayout* lyH_button;
    //-------------------
    QLabel* lb_S;
    QLabel* lb_E;
    QDateEdit *dateEdit_S;     //起始日期
    QDateEdit *dateEdit_E;     //截止日期

    QLabel* lb_cbx_car;
    QComboBox* cbx_car;//列出所有
    QLabel* lb_cbx_place;
    QComboBox* cbx_place;//列出所有
    QPushButton* btn_select;
    void detail_qwtp1();
    void getPlaceDataFromDB();
    void getCarDataFromDB();

    QLabel* background_pic;
    QTableView* tableview;
QFrame *frame;
private slots:
    void rerererePLot();
};
#endif // MYBARCHART_H
