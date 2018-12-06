#include "mybarchart.h"
#include <QDebug>
#include <qwt_legend.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_column_symbol.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_renderer.h>
#include <qwt_plot_canvas.h>
#include <QDate>
#include <AnalzyPage/recorddaoimp.h>
#include <QDateTime>
#include <QDesktopWidget>
#include <QApplication>
#include "HomePage/placeinfodaoimp.h"
#include "HomePage/carinfodaoimp.h"
#include <QLine>
#include "myframe.h"
//横坐标显示月份
class YearScaleDraw: public QwtScaleDraw
{
public:
    YearScaleDraw()
    {
        setTickLength( QwtScaleDiv::MajorTick, 0 );
        setTickLength( QwtScaleDiv::MinorTick, 0 );
        setTickLength( QwtScaleDiv::MediumTick, 20 );
        setLabelRotation( -45.0 );
        setLabelAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
        setSpacing( 20 );
    }
/*
    最小时间 ==> QString 2017.
                QString  06 07 08 09 10 11 12 01
                          0  1  2  3 4   5  6
                          diata =6
*/
    int year=2017;//起始年
    int diata=1;//起始月
    virtual QwtText label( double value ) const//0 1 2 3 4  ==// 2017.06  ----2018.03
    {
        //return QDate::longMonthName( int( value / 30 ) + 1 );
        //return QDate::longMonthName( int( value ) + 1 );// 一月 二月 三月 。。。
        char mon[20]="";
        if(((int(value)+diata)%12)!=0)
            sprintf(mon,".%02d",(int(value)+diata)%12);
        else
            sprintf(mon,".%02d",12);
        return QString::number(year+(int(value)+diata)/12)+QString(mon);
    }


};


MyBarChart::MyBarChart(QWidget * parent)
    :QDialog( parent )
{

    setWindowModality(Qt::ApplicationModal);//模态显示
    setAttribute(Qt::WA_DeleteOnClose); //在关闭该窗口时，自主调用析构函数
    //界面大小
    QDesktopWidget* desktop = QApplication::desktop();
    int www=0;
    int hhh=0;
    if(desktop->width()>=1920)
        www=1920;
    else
        www=desktop->width();

    if(desktop->height()>=1080)
        hhh=1080;
    else
        hhh=desktop->height();
    setFixedSize(www,hhh);//最大显示 不超过 1920* 1080
    //设置调色板(背景色)
    setPalette( Qt::white );

//    //背景
//    background_pic = new QLabel(this);
//    background_pic->setFixedSize(www,hhh);
//    //QPixmap pix_background(":/picture/homepage_background.jpg");
//    QPixmap pix_background(":/picture/pgy.jpg");

//    pix_background.scaled(background_pic->size(), Qt::IgnoreAspectRatio);
//    background_pic->setScaledContents(true);
//    background_pic->setPixmap(pix_background);
//    background_pic->setGeometry(0,0,www,hhh);


    //==================================================================
    cbx1=new QCheckBox(this);cbx1->setText("净重");cbx1->setCheckState(Qt::Checked);
    cbx1->setStyleSheet("QCheckBox{color:rgb(0,0,0);background-color:rgb(153,50,204)}"); //设定前景颜色，就是字体颜色"DarkOrchid"
    cbx2=new QCheckBox(this);cbx2->setText("车数");
    cbx2->setStyleSheet("QCheckBox{color:rgb(0,0,0);background-color:rgb(70,130,180)}"); //设定前景颜色，就是字体颜色"SteelBlue"
    cbx3=new QCheckBox(this);cbx3->setText("净重增长");
    cbx3->setStyleSheet("QCheckBox{color:rgb(0,0,0);background-color:rgb(255,215,0)}");  //设定前景颜色，就是字体颜色"Gold"




    //cbx1->setCheckState(Qt::Checked);
    connect(cbx1,SIGNAL(clicked()),this,SLOT(rerererePLot()));
    connect(cbx2,SIGNAL(clicked()),this,SLOT(rerererePLot()));
    connect(cbx3,SIGNAL(clicked()),this,SLOT(rerererePLot()));

    //==================================================================
    cmbx_orientation = new QComboBox(this);
    cmbx_orientation->insertItem(0,"竖直方向");
    cmbx_orientation->insertItem(1,"水平方向");
    //====================================================================
    QFont font("宋体",16,75);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::black);

    lb_S = new QLabel(this);
    lb_S->setFont(font);
    lb_S->setPalette(pa);
    lb_S->setText("起始日期：");
    lb_S->setFixedHeight(30);
    dateEdit_S = new QDateEdit(this);
    dateEdit_S->setFont(font);
    dateEdit_S->setCalendarPopup(true);
    dateEdit_S->setDateTime(QDateTime::fromString("2017-01-01 00:00:00","yyyy-MM-dd hh:mm:ss"));
    dateEdit_S->setDisplayFormat("yyyy-MM-dd");    //qt5.9需要设置
    dateEdit_S->setFixedWidth(150);
    lyV_S = new QVBoxLayout();
    lyV_S->addWidget(lb_S);
    lyV_S->addWidget(dateEdit_S);

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
    lyV_E = new QVBoxLayout();
    lyV_E->addWidget(lb_E);
    lyV_E->addWidget(dateEdit_E);

    lb_cbx_place= new QLabel(this);
    lb_cbx_place->setFont(font);
    lb_cbx_place->setPalette(pa);
    lb_cbx_place->setText("目标场地：");
    cbx_place = new QComboBox(this);
    cbx_place->setFixedSize(150,30);
    cbx_place->insertItem(0,"全部");
    cbx_place->setFont(QFont("宋体",13,75));
    cbx_place->setEditable(true);

    lyV_P = new QVBoxLayout();
    lyV_P->addWidget(lb_cbx_place);
    lyV_P->addWidget(cbx_place);

    lb_cbx_car= new QLabel(this);
    lb_cbx_car->setFont(font);
    lb_cbx_car->setPalette(pa);
    lb_cbx_car->setText("指定车辆：");
    cbx_car = new QComboBox(this);
    cbx_car->setFixedSize(150,30);
    cbx_car->setFont(QFont("宋体",13,75));
    cbx_car->setEditable(true);
    cbx_car->insertItem(0,"全部");
    lyV_C = new QVBoxLayout();
    lyV_C->addWidget(lb_cbx_car);
    lyV_C->addWidget(cbx_car);

    btn_select = new QPushButton(this);
    btn_select->setFixedSize(150,40);
    btn_select->setStyleSheet(  "QPushButton{border-image: url(:/picture/query-up.png);}"
                                "QPushButton:hover{border-image: url(:/picture/query-up.png);}"
                                "QPushButton:pressed{border-image: url(:/picture/query-down.png);}");
    btn_select->setFlat(true);
    connect(btn_select,SIGNAL(clicked()),this,SLOT(rerererePLot()));
    lyH_select = new QHBoxLayout();
    lyH_select->addLayout(lyV_S);
    lyH_select->addLayout(lyV_E);
    lyH_select->addLayout(lyV_P);
    lyH_select->addLayout(lyV_C);
    lyH_select->addWidget(btn_select);
    lyH_select->setGeometry(QRect(100,0,www-100,50));
    getPlaceDataFromDB();
    getCarDataFromDB();
    //====================================================================
    qwtP1 = new QwtPlot(this);
    //画布-设置颜色
    qwtP1->canvas()->setPalette( QColor( "LemonChiffon" ) );
    qwtP1->setAutoFillBackground( true );
    //设置右边标注
    //qwtP1->insertLegend(new QwtLegend(), QwtPlot::RightLegend);//不要显示，因为柱形图显示的项目不定
//    qwtP1->setGeometry(10,60,www-80,hhh*4/5);
    qwtP1->setGeometry(10,60,www*2/5,hhh*2/5);

    lyV_cbx=new QVBoxLayout;
    lyV_cbx->addWidget(cbx1);
    lyV_cbx->addWidget(cbx2);
    lyV_cbx->addWidget(cbx3);
    lyV_cbx->setGeometry(QRect(qwtP1->x()+qwtP1->width(),qwtP1->y()+30,80,90));


//    qwtP1->setAxisTitle(QwtPlot::xBottom, "月 份");
//    qwtP1->setAxisTitle(QwtPlot::yLeft, "数 量");

    //设置坐标轴的范围（此处设置无效，因为后面的绘图会改变）
//    qwtP1->setAxisScale(QwtPlot::xBottom, 1, 12);
//    qwtP1->setAxisScale(QwtPlot::yLeft, 0, 200);
    //使用滚轮放大/缩小
    (void) new QwtPlotMagnifier( qwtP1->canvas() );
    //使用鼠标左键平移
    (void) new QwtPlotPanner( qwtP1->canvas());

    //-----------------------------------------
    multiBarChart = new QwtPlotMultiBarChart("Kshine");
    multiBarChart->setLayoutPolicy( QwtPlotMultiBarChart::AutoAdjustSamples );//设置自动调节采样数据点
    multiBarChart->setSpacing( 20 );//设置间隔距离
    multiBarChart->setMargin( 3 );//设置边距
    //multiBarChart->setVisible(true);//是否可见

    multiBarChart->attach(qwtP1);//继承

    //====================================================================


    tableview =  new QTableView(this);
    tableview->setGeometry(qwtP1->x(),qwtP1->y()+qwtP1->height(),qwtP1->width()+90,hhh*2/5);
    tablemodel =new QStandardItemModel(this);
    tableview->setModel(tablemodel);
    //============================================================

    //detail_qwtp1();
    emit btn_select->clicked();

    //===============================================================
    frame = new MyFrame(this); //相当于ui文件里面的提升
    frame->setGeometry(tableview->x()+tableview->width(),qwtP1->y(),www*3/5,qwtP1->height()+tableview->height());
    frame->setStyleSheet("background-color:rgb(230,230,230)");

    show();
}

MyBarChart::~MyBarChart()
{
    qDebug()<<"barChart 关闭！";
}


//设置显示的数据
void MyBarChart::detail_qwtp1()
{

        const char *colors[] = { "DarkOrchid", "SteelBlue", "Gold"};
        //const char *TTT[]={"净重总数","出单数","暂缺"};
        //const int numSamples = 13;//12组数据
        const int numBars = sizeof( colors ) / sizeof( colors[0] );//每组3个成员



        //============
        int rrrow=model.rowCount();         //条件内所有的数据的条数
        qDebug()<<"最小年月"<<model.data(model.index(0,4)).toInt()<<model.data(model.index(0,5)).toInt();
        qDebug()<<"最大年月"<<model.data(model.index(rrrow-1,4)).toInt()<<model.data(model.index(rrrow-1,5)).toInt();

        int startYear =model.data(model.index(0,4)).toInt();
        int startMonth=model.data(model.index(0,5)).toInt();

        //月份跨度（年相减*12 +月相减）
        int numSamples =(model.data(model.index(rrrow-1,4)).toInt()-model.data(model.index(0,4)).toInt())*12+model.data(model.index(rrrow-1,5)).toInt()-model.data(model.index(0,5)).toInt()+1;
        if(numSamples<0)numSamples=0;



        QVector<int> counter_month_truck_times;//每月车次
        QVector<double> counter_month_truck_things;//每月净重总数
        QVector<double> counter_month_things_speed;//净重增速
        int temStartMonth=startMonth;
        int temStartYear =startYear;
        for(int i =0;i < numSamples;i++)
        {
            int num=0;
            double weight=0;
            for(int j=0;j<rrrow;j++)//所有数据遍历一遍
            {
               //0 totalweight 1  carweight 2 thingsweight 3 price 4 year 5 month
              if(model.data(model.index(j,5)).toInt() == temStartMonth%12 && model.data(model.index(j,4)).toInt() ==(temStartYear+(temStartMonth-1)/12) ) //判断出 该条数据是同一个月的数据
  //          if(model.data(model.index(j,5)).toInt() == temStartMonth%12) //判断出 该条数据是同一个月的数据
                {
                   num++;//记录次数
                   weight+=model.data(model.index(j,2)).toDouble();//记录净重
                   //qDebug()<<weight;
                }
            }

            if(!counter_month_truck_things.isEmpty())
                counter_month_things_speed+=weight-counter_month_truck_things.last();
            else
                counter_month_things_speed+=weight;
            counter_month_truck_things+=weight;//存储净重
            counter_month_truck_times+=num; //存储该月的 次数
            qDebug()<<temStartMonth%12<<"月  "<<num;
            temStartMonth++;
        }
        qDebug()<<"每月次数"<<counter_month_truck_times;
        qDebug()<<"每月净重"<<counter_month_truck_things;
        qDebug()<<"每月增速"<<counter_month_things_speed;


        //柱形图指示性文字
//        QList<QwtText> titles;
//        for ( int i = 0; i < numBars; i++ )
//        {
//            QString title(TTT[i]);
//            titles += title;
//        }
//        multiBarChart->setBarTitles( titles );
//        multiBarChart->setLegendIconSize( QSize( 10, 14 ) );

        //颜色
        qDebug()<<"设置颜色";
        int ttt=0;
        for ( int i = 0; i < numBars; i++ )
        {
            if(i==0&&cbx1->checkState()==Qt::Unchecked)i=1;
            if(i==1&&cbx2->checkState()==Qt::Unchecked)i=2;
            if(i==2&&cbx3->checkState()==Qt::Unchecked)break;
            QwtColumnSymbol *symbol = new QwtColumnSymbol( QwtColumnSymbol::Box );
            symbol->setLineWidth( 2 );//设置线宽
            symbol->setFrameStyle( QwtColumnSymbol::Raised);//凸起风格
            symbol->setPalette( QPalette( colors[i] ) );//设置颜色
            multiBarChart->setSymbol( ttt++, symbol );
        }

        //数据
        qDebug()<<"装在数据";
        QVector< QVector<double> > series;
        double all_times=0;
        double all_weight=0;
        ttt=0;
        for ( int i = 0; i < numSamples; i++ )//12
        {
            QVector<double> values;

            qDebug()<<"i="<<i;
            if(cbx1->checkState()==Qt::Checked)values += counter_month_truck_things.at(i);
            if(cbx2->checkState()==Qt::Checked)values += counter_month_truck_times.at(i);
            if(cbx3->checkState()==Qt::Checked)values += counter_month_things_speed.at(i);
            series += values;

            //tableview中显示数据---弥补图中不显示数据的缺点----------------
            //次数不为0 的月
            if(counter_month_truck_times.at(i) != 0)
            {
                QString yearmonth=QString::number(startYear+(startMonth+i-1)/12)+"."+QString::number((startMonth+i)%12);
                QString times=QString::number(counter_month_truck_times.at(i));
                QString wweight =QString::number(counter_month_truck_things.at(i));
                tablemodel->setItem(ttt,0,new QStandardItem(yearmonth));//写入第一列数据 年月
                tablemodel->setItem(ttt,1,new QStandardItem(times));//写入第二列数据 车次
                tablemodel->setItem(ttt,2,new QStandardItem(wweight));//写入第三列数据 重
                ttt++;all_times+=counter_month_truck_times.at(i);all_weight+=counter_month_truck_things.at(i);
                //tablemodel->item(ttt,0)->setForeground(QBrush(QColor(255, 153, 22))); //设置字符颜色
                //tablemodel->item(ttt,0)->setTextAlignment(Qt::AlignCenter);
               // tablemodel->item(ttt,1)->setForeground(QBrush(QColor(200, 123, 160))); //设置字符颜色
               // tablemodel->item(ttt,1)->setTextAlignment(Qt::AlignCenter);
                //tablemodel->item(ttt,2)->setForeground(QBrush(QColor(255, 153, 22))); //设置字符颜色
               // tablemodel->item(ttt,2)->setTextAlignment(Qt::AlignCenter);

            }
        }
        //----------------------------------
        tablemodel->setItem(ttt,0,new QStandardItem("总计"));//写入第一列数据 年月
        tablemodel->setItem(ttt,1,new QStandardItem(QString::number(all_times)));//写入第二列数据 车次
        tablemodel->setItem(ttt,2,new QStandardItem(QString::number(all_weight)));//写入第三列数据 重
//        tablemodel->item(ttt,0)->setForeground(QBrush(QColor(255, 153, 22)));
//        tablemodel->item(ttt,1)->setForeground(QBrush(QColor(255, 153, 22)));
//        tablemodel->item(ttt,2)->setForeground(QBrush(QColor(255, 153, 22)));

        tablemodel->item(ttt,0)->setBackground(QBrush(QColor(255, 153, 22)));
        tablemodel->item(ttt,1)->setBackground(QBrush(QColor(255, 153, 22)));
        tablemodel->item(ttt,2)->setBackground(QBrush(QColor(255, 153, 22)));
        if(numSamples<12)
        {
            for(int i=0;i<12-numSamples;i++)
            {
                QVector<double> values;
                qDebug()<<"i="<<i;
                if(cbx1->checkState()==Qt::Checked)values +=0;  //月净重总数
                if(cbx2->checkState()==Qt::Checked)values +=0;
                if(cbx3->checkState()==Qt::Checked)values +=0;
                series += values;
            }

        }





        if(cbx1->checkState()==Qt::Unchecked&&cbx2->checkState()==Qt::Unchecked&&cbx3->checkState()==Qt::Unchecked)
        series.clear();
            multiBarChart->setSamples( series);

           //方向
            int orientation =cmbx_orientation->currentIndex();
            QwtPlot::Axis axis1, axis2;

            if ( orientation == 0 )
            {
                axis1 = QwtPlot::xBottom;
                axis2 = QwtPlot::yLeft;

                multiBarChart->setOrientation( Qt::Vertical );//柱状图的方向
            }
            else
            {
                axis1 = QwtPlot::yLeft;
                axis2 = QwtPlot::xBottom;

                multiBarChart->setOrientation( Qt::Horizontal );
            }

            //坐标轴标志,min,max,step
            qwtP1->setAxisScale( axis1, 0, multiBarChart->dataSize() - 1, 1.0);
            //qwtP1->setAxisScale( axis2,0,12,1);

            YearScaleDraw* ysd =new YearScaleDraw();
            ysd->year=startYear;
            ysd->diata=startMonth;
            qwtP1->setAxisScaleDraw( axis1, ysd );

            QwtScaleDraw* qsd =new QwtScaleDraw();
            qwtP1->setAxisScaleDraw( axis2, qsd );
            qwtP1->setAxisAutoScale( axis2 );//自动设置数据范围

            qwtP1->setAxisTitle(axis1, "月 份");
            qwtP1->setAxisTitle(axis2, "数 量");

            QwtScaleDraw *scaleDraw1 =qwtP1->axisScaleDraw( axis1 );
            scaleDraw1->enableComponent( QwtScaleDraw::Backbone, false );
            scaleDraw1->enableComponent( QwtScaleDraw::Ticks, false );

            QwtScaleDraw *scaleDraw2 = qwtP1->axisScaleDraw( axis2 );
            scaleDraw2->enableComponent( QwtScaleDraw::Backbone, true );
            scaleDraw2->enableComponent( QwtScaleDraw::Ticks, true );

            qwtP1->plotLayout()->setAlignCanvasToScale( axis1, true );
            qwtP1->plotLayout()->setAlignCanvasToScale( axis2, false );

            qwtP1->plotLayout()->setCanvasMargin( 0 );
            qwtP1->updateCanvasMargins();

            qwtP1->replot();
}

void MyBarChart::getPlaceDataFromDB()
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

void MyBarChart::getCarDataFromDB()
{ qDebug()<<"---刷新下拉框---汽车信息";
    QSqlTableModel modellll(this);
    CarInfoDaoImp op;
    op.selectallCarInfo_model(&modellll);

    for(int i=0;i<modellll.rowCount();i++)
    {
        //多一个“全部”
        cbx_car->insertItem(i+1,modellll.data(modellll.index(i,0)).toString());
    }


}


void MyBarChart::rerererePLot()
{
    qDebug()<<"重新绘图";
    //数据准备=====================
    QString dates=dateEdit_S->date().toString("yyyy-MM-dd")+" 00:00:00";
    QString datee=dateEdit_E->date().toString("yyyy-MM-dd")+" 23:59:59";
    QString place=cbx_place->currentText();
    QString car=cbx_car->currentText();
    RecordDaoImp rdi;
    rdi.selectRecordInfo_Month(dates,datee,place,car,&model);
    tablemodel->clear();
    tablemodel->setColumnCount(3);
    tablemodel->setHeaderData(0,Qt::Horizontal,"年月");
    tablemodel->setHeaderData(1,Qt::Horizontal,"车次");
    tablemodel->setHeaderData(2,Qt::Horizontal,"净重总数(吨)");
    //重新绘制折线图
    detail_qwtp1();//使用model

    tableview->setColumnWidth(0,tableview->width()/3-20);
    tableview->setColumnWidth(1,tableview->width()/3);
    tableview->setColumnWidth(2,tableview->width()/3);

}
