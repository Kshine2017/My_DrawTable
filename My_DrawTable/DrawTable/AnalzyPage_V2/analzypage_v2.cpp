#include "analzypage_v2.h"
#include <QDebug>
#include "../AnalzyPage/recorddaoimp.h"
#include "HomePage/placeinfodaoimp.h"
#include "HomePage/carinfodaoimp.h"
#include "typedaoimp.h"
#include "printdialog.h"
#include <QHeaderView>
AnalzyPage_V2::AnalzyPage_V2(QWidget *parent) : QWidget(parent)
{
    background_pic = new QLabel(this);
    background_pic->setFixedSize(1000/5*4,500);
//  QPixmap pix_background(":/picture/analzypage_background.jpg");
    QPixmap pix_background(":/picture/lz.jpg");
    pix_background.scaled(background_pic->size(), Qt::IgnoreAspectRatio);
    background_pic->setScaledContents(true);
    background_pic->setPixmap(pix_background);
    background_pic->setGeometry(0,0,1000/5*4,500);

    init_widget1();
    init_widget2();
    ly_V_all = new QVBoxLayout();
    ly_V_all->addWidget(widget1);
    ly_V_all->addWidget(widget2);
    ly_V_all->setGeometry(QRect(0,0,800,500));

    //------------------
    model = new QSqlQueryModel(widget1);
    slot_select_all();
    getPlaceDataFromDB();
    getCarDataFromDB();
    getTypeDataFromDB();
}

void AnalzyPage_V2::init_widget1()
{
    widget1 = new QWidget(this);widget1->setFixedSize(800,300);
    //背景图片
    table_back_pic = new QLabel(widget1);
    table_back_pic->setFixedSize(1000/5*4,300);
    QPixmap pix_background(":/picture/table_back_blue.png");
    pix_background.scaled(table_back_pic->size(), Qt::IgnoreAspectRatio);
    table_back_pic->setScaledContents(true);
    table_back_pic->setPixmap(pix_background);
    //table_back_pic->setGeometry(0,0,1000/5*4,500);
    //表格
    tableview =new QTableView(widget1);
    tableview->setSelectionBehavior(QAbstractItemView::SelectRows);//选择行
    //tableview->setStyleSheet("background-color:transparent;");
    //tableview->verticalHeader()->setStyleSheet("QHeaderView::section {background-color: rgba(232, 255, 213, 5);}");
    connect(tableview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slot_print(QModelIndex)));
    tableview->setGeometry(10,10,780,280);

}

void AnalzyPage_V2::init_widget2()
{
    widget2 = new QWidget(this);widget2->setFixedSize(800,200);
    QFont font("宋体",16,75);
    QPalette pa;pa.setColor(QPalette::WindowText,Qt::blue);
    //左
    ly_V_Left = new QVBoxLayout();
    lb_time_scale = new QLabel(widget2);
    lb_time_scale->setFixedSize(200,30);lb_time_scale->setText("时间范围：");//“时间范围”
    lb_time_scale->setFont(font);
    lb_time_scale->setPalette(pa);
    //品类
    ly_H_Left1 = new QHBoxLayout();lb_cbx_type = new QLabel(widget2); cbx_type = new QComboBox(widget2);
    lb_cbx_type->setFixedSize(50,30);lb_cbx_type->setText("品类：");
    ly_H_Left1->addWidget(lb_cbx_type);ly_H_Left1->addWidget(cbx_type);ly_H_Left1->addStretch();
    lb_cbx_type->setFont(font);
    lb_cbx_type->setPalette(pa);
    cbx_type->setFont(QFont("宋体",13,75));
    cbx_type->setEditable(true);
    cbx_type->setFixedSize(150,30);
    cbx_type->insertItem(0,"全部");
    //场地
    ly_H_Left2 = new QHBoxLayout();lb_cbx_place = new QLabel(widget2);   cbx_place = new QComboBox(widget2);
    lb_cbx_place->setFixedSize(50,30);lb_cbx_place->setText("场地：");
    ly_H_Left2->addWidget(lb_cbx_place);ly_H_Left2->addWidget(cbx_place);ly_H_Left2->addStretch();
    lb_cbx_place->setFont(font);
    lb_cbx_place->setPalette(pa);
    cbx_place->setFont(QFont("宋体",13,75));
    cbx_place->setEditable(true);
    cbx_place->setFixedSize(150,30);
    cbx_place->insertItem(0,"全部");
    //车辆
    ly_H_Left3 = new QHBoxLayout();lb_cbx_car = new QLabel(widget2);     cbx_car = new QComboBox(widget2);
    lb_cbx_car->setFixedSize(50,30);lb_cbx_car->setText("车辆：");
    ly_H_Left3->addWidget(lb_cbx_car);ly_H_Left3->addWidget(cbx_car);ly_H_Left3->addStretch();
    lb_cbx_car->setFont(font);
    lb_cbx_car->setPalette(pa);
    cbx_car->setFont(QFont("宋体",13,75));
    cbx_car->setEditable(true);
    cbx_car->setFixedSize(150,30);
    cbx_car->insertItem(0,"全部");
    //起始时间标签//起始日期              //截止时间标签//截止日期
    ly_H_Left4 = new QHBoxLayout();lb_S = new QLabel(widget2);dateEdit_S = new QDateEdit(widget2); lb_E = new QLabel(widget2);dateEdit_E = new QDateEdit(widget2);
    lb_S->setFixedSize(30,30);lb_E->setFixedSize(30,30);lb_S->setText("从");lb_E->setText("至");
    ly_H_Left4->addSpacing(20);ly_H_Left4->addWidget(lb_S);ly_H_Left4->addWidget(dateEdit_S);ly_H_Left4->addWidget(lb_E);ly_H_Left4->addWidget(dateEdit_E);ly_H_Left4->addStretch();
    lb_S->setFont(font);
    lb_S->setPalette(pa);
    lb_E->setFont(font);
    lb_E->setPalette(pa);
    dateEdit_S->setFont(font);
    dateEdit_S->setCalendarPopup(true);
    dateEdit_S->setDateTime(QDateTime::currentDateTime());//20181203开启
    dateEdit_S->setDisplayFormat("yyyy-MM-dd");    //qt5.9需要设置
    dateEdit_S->setFixedWidth(150);
    dateEdit_E->setFont(font);
    dateEdit_E->setCalendarPopup(true);
    dateEdit_E->setDateTime(QDateTime::currentDateTime());//20181203开启
    dateEdit_E->setDisplayFormat("yyyy-MM-dd");    //qt5.9需要设置
    dateEdit_E->setFixedWidth(150);

    ly_V_Left->addWidget(lb_time_scale);
    ly_V_Left->addLayout(ly_H_Left4);
    ly_V_Left->addLayout(ly_H_Left1);
    ly_V_Left->addLayout(ly_H_Left2);
    ly_V_Left->addLayout(ly_H_Left3);


    //中
    ly_V_mid = new QVBoxLayout();
    btn_select = new QPushButton(this);
    btn_select->setFixedSize(150,40);
    btn_select->setStyleSheet(  "QPushButton{border-image: url(:/picture/query-up.png);}"
                                "QPushButton:hover{border-image: url(:/picture/query-up.png);}"
                                "QPushButton:pressed{border-image: url(:/picture/query-down.png);}");
    btn_select->setFlat(true);

    btn_display = new QPushButton(this);
    btn_display->setFixedSize(150,40);
    btn_display->setStyleSheet(  "QPushButton{border-image: url(:/picture/display_png-up.png);}"
                                "QPushButton:hover{border-image: url(:/picture/display_png-up.png);}"
                                "QPushButton:pressed{border-image: url(:/picture/display_png-down.png);}");
    btn_display->setFlat(true);
    connect(btn_select,SIGNAL(clicked()),this,SLOT(slot_select()));
    //connect(btn_print,SIGNAL(clicked()),this,SLOT(slot_print()));
    connect(btn_display,SIGNAL(clicked()),this,SLOT(slot_display()));
    ly_V_mid->addStretch();
    ly_V_mid->addWidget(btn_select);
    ly_V_mid->addWidget(btn_display);


    //右
    ly_V_right = new QVBoxLayout();
    lb_result = new QLabel(widget2);lb_result->setFixedSize(200,30);lb_result->setText("查询结果");//“查询结果”
    lb_result->setFont(QFont("宋体",13,75));
    lb_car_times = new QLabel(widget2);lb_car_times->setFixedSize(200,30);lb_car_times->setText("车次：");//车次:
    lb_car_times->setFont(QFont("宋体",13,75));
    //lb_allweight = new QLabel(widget2);lb_allweight->setFixedSize(200,30);lb_allweight->setText("毛重：");//毛重：
    //lb_allweight->setFont(QFont("宋体",13,75));
    lb_thingsweight = new QLabel(widget2);lb_thingsweight->setFixedSize(200,30);lb_thingsweight->setText("净重：");//净重：
    lb_thingsweight->setFont(QFont("宋体",13,75));
    ly_V_right->addWidget(lb_result);
    ly_V_right->addWidget(lb_car_times);
    //ly_V_right->addWidget(lb_allweight);
    ly_V_right->addWidget(lb_thingsweight);


    //总
    ly_H_widget2 = new QHBoxLayout();
    ly_H_widget2->addLayout(ly_V_Left);
    ly_H_widget2->addLayout(ly_V_mid);
    ly_H_widget2->addLayout(ly_V_right);
    widget2->setLayout(ly_H_widget2);
}

void AnalzyPage_V2::getPlaceDataFromDB()
{
    qDebug()<<"---刷新下拉框---场地信息";
    QSqlTableModel modellll(this);
    PlaceInfoDaoImp op;
    op.selectallPlaceInfo_model(&modellll);

    for(int i=0;i<modellll.rowCount();i++)
    {
        //多一个“全部”
        cbx_place->insertItem(i+1,modellll.data(modellll.index(i,1)).toString());
    }
}

void AnalzyPage_V2::getCarDataFromDB()
{
    qDebug()<<"---刷新下拉框---汽车信息";
    QSqlTableModel modellll(this);
    CarInfoDaoImp op;
    op.selectallCarInfo_model(&modellll);

    for(int i=0;i<modellll.rowCount();i++)
    {
        //多一个“全部”
        cbx_car->insertItem(i+1,modellll.data(modellll.index(i,0)).toString());
    }
}

void AnalzyPage_V2::getTypeDataFromDB()
{
    qDebug()<<"---刷新下拉框---类型信息";
    //model = new QSqlTableModel(this);
    QSqlTableModel modellll(this);
    TypeDaoImp op;
    op.selectallTypeInfo(&modellll);

    for(int i=0;i<modellll.rowCount();i++)
    {
        //多一个“全部”
        cbx_type->insertItem(i+1,modellll.data(modellll.index(i,0)).toString());
    }
}

void AnalzyPage_V2::slot_select_all()
{
    RecordDaoImp op;
    op.selectallRecordInfo_v3(model);
    tableview->setModel(model);
    QString QScar="累计车次：(未查询)";
    QString QSthings="累计净重: (未查询)";
    lb_car_times->setText(QScar);
    lb_thingsweight->setText(QSthings);
}

void AnalzyPage_V2::slot_select()
{
    qDebug()<<"分析---查询";
    QString dates=dateEdit_S->date().toString("yyyy-MM-dd");
    QString datee=dateEdit_E->date().toString("yyyy-MM-dd");
    if(dates<=datee)//小日期到大日期
    {
        dates+=" 00:00:00";
        datee+=" 23:59:59";
    }
    else            //大日期到小日期
    {
        QString tem=dates;
        dates=datee;
        datee=tem;
        dates+=" 00:00:00";
        datee+=" 23:59:59";
    }
    QString type=cbx_type->currentText();
    QString place=cbx_place->currentText();
    QString car=cbx_car->currentText();
    RecordDaoImp op;
    op.selectRecordInfo_date_v3(dates,datee,type,place,car,model);
    tableview->setModel(model);
    //---计算数量---------------------------
    double things=0;//total=0,
    int Ncar=0;
    Ncar=model->rowCount();//这里的car是车数
    //毛重是5 6
    //皮重是6 7
    //净重是7 8
    for(int i=0;i<Ncar;i++)
    {
        //total+=model->index(i,6).data().toDouble();
        things+=model->index(i,8).data().toDouble();
    }
    QString QScar="累计车次："+QString::number(Ncar)+"次";
    //QString QStotal="累计毛重: "+QString::number(total)+"吨";
    QString QSthings="累计净重: "+QString::number(things)+"吨";
    lb_car_times->setText(QScar);
    //lb_allweight->setText(QStotal);
    lb_thingsweight->setText(QSthings);
}

void AnalzyPage_V2::slot_print(QModelIndex index)
{
    qDebug()<<"分析---打印页面";
    int row = index.row();
    QStringList str;
    for(int i=0;i<tableview->model()->columnCount();i++)
        str.append(tableview->model()->data(tableview->model()->index(row,i)).toString());

   PrintDialog* pd= new PrintDialog(str,this);

   //connect(pd,SIGNAL(destroyed()),this,SLOT(slot_select()));//如果使用条件查询，可能会在修改后，一时间找不到修改的条目
   connect(pd,SIGNAL(destroyed()),this,SLOT(slot_select_all()));
}

void AnalzyPage_V2::slot_display()
{
/*
1、显示图表生成图片
2、生成报告
从XXXX到XXXX时间内：车牌号出单情况

*/


}
