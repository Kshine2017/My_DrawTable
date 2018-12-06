#include "analzypagewindow.h"
#include <QDebug>
#include "recorddaoimp.h"
#include "HomePage/placeinfodaoimp.h"
#include "HomePage/carinfodaoimp.h"
#include "printdialog.h"
#include <QHeaderView>
AnalzyPageWindow::AnalzyPageWindow(QWidget *parent) : QWidget(parent)
{

    background_pic = new QLabel(this);
    background_pic->setFixedSize(1000/5*4,500);
//    QPixmap pix_background(":/picture/analzypage_background.jpg");
    QPixmap pix_background(":/picture/lz.jpg");

    pix_background.scaled(background_pic->size(), Qt::IgnoreAspectRatio);
    background_pic->setScaledContents(true);
    background_pic->setPixmap(pix_background);
    background_pic->setGeometry(0,0,1000/5*4,500);
    init_weight_label();
    init_tableview();
    init_select();


    //---------------------------------
    getPlaceDataFromDB();
    getCarDataFromDB();
}

AnalzyPageWindow::~AnalzyPageWindow()
{
    qDebug()<<"已销毁分析页面";
}

void AnalzyPageWindow::init_weight_label()
{
    lb_weight_total = new QLabel(this);lb_weight_total->setFixedSize(100,20);
        lb_weight_car = new QLabel(this);lb_weight_car->setFixedSize(100,20);
            lb_weight_things = new QLabel(this);lb_weight_things->setFixedSize(100,20);
    lyV_label_weight = new QVBoxLayout();
    lyV_label_weight->addWidget(lb_weight_car);//总车次
    lyV_label_weight->addWidget(lb_weight_total);
    lyV_label_weight->addWidget(lb_weight_things);
    lyV_label_weight->setGeometry(QRect(0,0,100,60));
}

void AnalzyPageWindow::init_tableview()
{
    tableview =new QTableView(this);
    tableview->setSelectionBehavior(QAbstractItemView::SelectRows);//选择行
    tableview->setStyleSheet("background-color:transparent;");
    //没透明的分别是horizontalHeader和verticalHeader,还有verticalScrollBar和horizontalScrollBar

    /*
background-color: rgba(232, 255, 213, 5);
horizontalHeader
{
background-color: rgba(232, 255, 213, 5)
}

 ui->tableView->verticalHeader()->setStyleSheet
    ("QHeaderView::section {background-color: rgba(232, 255, 213, 5);}");
    ui->tableView->horizontalHeader()->setStyleSheet
    ("QHeaderView::section {background-color: rgba(232, 255, 213, 5);}");
    */
    tableview->verticalHeader()->setStyleSheet("QHeaderView::section {background-color: rgba(232, 255, 213, 5);}");

    connect(tableview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slot_print(QModelIndex)));
    tableview->setGeometry(300,10,490,480);

    RecordDaoImp op;
    model = new QSqlQueryModel(this);
    op.selectallRecordInfo(model);
    tableview->setModel(model);
}

void AnalzyPageWindow::init_select()
{
    QFont font("宋体",16,75);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);

    lb_S = new QLabel(this);
    lb_S->setFont(font);
    lb_S->setPalette(pa);
    lb_S->setText("起始日期：");
    dateEdit_S = new QDateEdit(this);
    dateEdit_S->setFont(font);
    dateEdit_S->setCalendarPopup(true);
    dateEdit_S->setDateTime(QDateTime::currentDateTime());//20181203开启
    dateEdit_S->setDisplayFormat("yyyy-MM-dd");    //qt5.9需要设置
    dateEdit_S->setFixedWidth(150);
    lyH_S = new QHBoxLayout();
    lyH_S->addWidget(lb_S);
    lyH_S->addWidget(dateEdit_S);


    lb_E = new QLabel(this);
    lb_E->setFont(font);
    lb_E->setPalette(pa);
    lb_E->setText("截止日期：");
    dateEdit_E = new QDateEdit(this);
    dateEdit_E->setFont(font);
    dateEdit_E->setCalendarPopup(true);
    dateEdit_E->setDateTime(QDateTime::currentDateTime());
    dateEdit_E->setDisplayFormat("yyyy-MM-dd");    //(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
    dateEdit_E->setFixedWidth(150);
    lyH_E = new QHBoxLayout();
    lyH_E->addWidget(lb_E);
    lyH_E->addWidget(dateEdit_E);

    lb_cbx_place= new QLabel(this);
    lb_cbx_place->setFont(font);
    lb_cbx_place->setPalette(pa);
    lb_cbx_place->setText("目标场地：");
    cbx_place = new QComboBox(this);
    cbx_place->setFont(QFont("宋体",13,75));
    cbx_place->setEditable(true);
    cbx_place->setFixedSize(150,30);
    cbx_place->insertItem(0,"全部");
    lyH_P = new QHBoxLayout();
    lyH_P->addWidget(lb_cbx_place);
    lyH_P->addWidget(cbx_place);

    lb_cbx_car= new QLabel(this);
    lb_cbx_car->setFont(font);
    lb_cbx_car->setPalette(pa);
    lb_cbx_car->setText("指定车辆：");
    cbx_car = new QComboBox(this);
    cbx_car->setFont(QFont("宋体",13,75));
    cbx_car->setEditable(true);
    cbx_car->setFixedSize(150,30);
    cbx_car->insertItem(0,"全部");
    lyH_C = new QHBoxLayout();
    lyH_C->addWidget(lb_cbx_car);
    lyH_C->addWidget(cbx_car);

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



    lyV_select = new QVBoxLayout();

    lyV_select->addLayout(lyH_S);
    lyV_select->addLayout(lyH_E);
    lyV_select->addLayout(lyH_P);
    lyV_select->addLayout(lyH_C);
    lyV_select->addWidget(btn_select);
    lyV_select->addWidget(btn_display);
//    lyV_select->addWidget(btn_print);

    lyV_select->setGeometry(QRect(20,40,220,400));
    connect(btn_select,SIGNAL(clicked()),this,SLOT(slot_select()));
    //connect(btn_print,SIGNAL(clicked()),this,SLOT(slot_print()));
    connect(btn_display,SIGNAL(clicked()),this,SLOT(slot_display()));
}


void AnalzyPageWindow::slot_select()
{
    qDebug()<<"分析---查询";
    QString dates=dateEdit_S->date().toString("yyyy-MM-dd")+" 00:00:00";
    QString datee=dateEdit_E->date().toString("yyyy-MM-dd")+" 23:59:59";
    QString place=cbx_place->currentText();
    QString car=cbx_car->currentText();
    RecordDaoImp op;
    op.selectRecordInfo_date(dates,datee,place,car,model);
    tableview->setModel(model);
    //---计算数量---------------------------
    double total=0,things=0;
    int Ncar=0;
    Ncar=model->rowCount();//这里的car是车数
    //毛重是5
    //皮重是6
    //净重是7
    for(int i=0;i<Ncar;i++)
    {
        total+=model->index(i,5).data().toDouble();
        things+=model->index(i,7).data().toDouble();
    }
    QString QScar="车次总数："+QString::number(Ncar);
    QString QStotal="货物总重:"+QString::number(total);
    QString QSthings="总净重:"+QString::number(things);
    lb_weight_car->setText(QScar);
    lb_weight_things->setText(QSthings);
    lb_weight_total->setText(QStotal);
}

void AnalzyPageWindow::slot_print(QModelIndex index)
{
    qDebug()<<"分析---打印页面";
    int row = index.row();
//    QString number=tableview->model()->data(tableview->model()->index(row,0)).toString();
//    qDebug()<<number;
    QStringList str;
    for(int i=0;i<tableview->model()->columnCount();i++)
        str.append(tableview->model()->data(tableview->model()->index(row,i)).toString());

   PrintDialog* pd= new PrintDialog(str,this);
    connect(pd,SIGNAL(destroyed()),this,SLOT(slot_select()));
}

void AnalzyPageWindow::slot_display()
{
    qDebug()<<"分析---显示";
    //pb= new PlotBar(this);
    mbc = new MyBarChart(this);
}

void AnalzyPageWindow::getPlaceDataFromDB()
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
void AnalzyPageWindow::getCarDataFromDB()
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


