#include "homepagewindow.h"
#include <QDebug>
#include <QPainter>
#include "funcation.h"
#include <QFrame>
#include "placeinfodaoimp.h"
#include "carinfodaoimp.h"
#include "typedaoimp.h"
//#include <QSqlTableModel>
#include <QListView>
#include "AnalzyPage/recorddaoimp.h"
#include <QDateTime>
#include <QMessageBox>
HomePageWindow::HomePageWindow(QWidget *parent) :
    QWidget(parent)
{
    //背景
    background_pic = new QLabel(this);
    background_pic->setFixedSize(1000/5*4,500);
    //QPixmap pix_background(":/picture/homepage_background.jpg");
    QPixmap pix_background(":/picture/cube.jpg");

    pix_background.scaled(background_pic->size(), Qt::IgnoreAspectRatio);
    background_pic->setScaledContents(true);
    background_pic->setPixmap(pix_background);
    background_pic->setGeometry(0,0,1000/5*4,500);

    //background_pic->

    //初始化 按钮
    init_Button();

    //初始化 标签和输入框
    init_Label_LineEdit();

    connect_lineEdit();

    //测试，数据初始化
//    lineEdit_totalWeight->setText("52.8");
//    lineEdit_truckWeight->setText("17.55");
//    lineEdit_thingsWeight->setText("35.25");
    lineEdit_price->setText("0");

    //测试时间格式
    QString tem = getYMDhms();
    qDebug()<<"登录首页的时间："<<tem;
    //更新下拉框数据
    getPlaceDataFromDB();
    getCarDataFromDB();
    getTypeDataFromDB();
    init_checkbox();

}

void HomePageWindow::init_Button()
{

    //打印按钮
    btn_print=new QPushButton(this);
    btn_print->setFixedSize(150,40);
    btn_print->setStyleSheet("QPushButton{border-image: url(:/picture/printBtn-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/printBtn-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/printBtn-down.png);}");
    btn_print->setFlat(true);
    btn_print->setGeometry(20,20,150,40);
    connect(btn_print,SIGNAL(clicked()),this,SLOT(slot_print()));

    //场地信息维护按钮
    btn_place_maintain = new QPushButton(this);
    btn_place_maintain->setFixedSize(150,40);
    btn_place_maintain->setStyleSheet("QPushButton{border-image: url(:/picture/place-up.png);}"
                                      "QPushButton:hover{border-image: url(:/picture/place-up.png);}"
                                      "QPushButton:pressed{border-image: url(:/picture/place-down.png);}");
    btn_place_maintain->setFlat(true);
    btn_place_maintain->setGeometry(200,20,150,40);
    connect(btn_place_maintain,SIGNAL(clicked()),this,SLOT(slot_createPlaceMaintain()));

    //车辆信息维护按钮
    btn_Car_maintain = new QPushButton(this);
    btn_Car_maintain->setFixedSize(150,40);
    btn_Car_maintain->setStyleSheet("QPushButton{border-image: url(:/picture/Car-up.png);}"
                                    "QPushButton:hover{border-image: url(:/picture/Car-up.png);}"
                                    "QPushButton:pressed{border-image: url(:/picture/Car-down.png);}");
    btn_Car_maintain->setFlat(true);
    btn_Car_maintain->setGeometry(380,20,150,40);
    connect(btn_Car_maintain,SIGNAL(clicked()),this,SLOT(slot_createCarMaintain()));


    //类型信息维护按钮
    btn_Type_maintain = new QPushButton(this);
    btn_Type_maintain->setFixedSize(150,40);
    btn_Type_maintain->setStyleSheet("QPushButton{border-image: url(:/picture/type-up.png);}"
                                    "QPushButton:hover{border-image: url(:/picture/type-up.png);}"
                                    "QPushButton:pressed{border-image: url(:/picture/type-down.png);}");
    btn_Type_maintain->setFlat(true);
    btn_Type_maintain->setGeometry(560,20,150,40);
    connect(btn_Type_maintain,SIGNAL(clicked()),this,SLOT(slot_createTypeMaintain()));



    btn_saveCar =new QPushButton(this);
    btn_saveCar->setIcon(QIcon(":/picture/save.png"));
    btn_saveCar->setText("更新入库");
    //btn_place_maintain->setFixedSize(30,30);
    btn_saveCar->setGeometry(705,142,80,30);
    connect(btn_saveCar,SIGNAL(clicked()),this,SLOT(slot_update_carinfo()));
}




void HomePageWindow::slot_createPlaceMaintain()
{
    qDebug()<<"1.2 - 创建场地维护界面";
    placeWidget =new PlaceMaintainWidget(this);
    //关闭维护页面之后，重新装载数据
    connect(placeWidget,SIGNAL(destroyed()),this,SLOT(slot_roloadComboBox_place()));
}


void HomePageWindow::slot_createCarMaintain()
{

    qDebug()<<"1.3 - 创建车辆维护界面";
    carWidget =new CarMaintainWidget(this);
    //关闭维护页面之后，重新装载数据
    connect(carWidget,SIGNAL(destroyed()),this,SLOT(slot_roloadComboBox_car()));

}

void HomePageWindow::slot_createTypeMaintain()
{
    qDebug()<<"1.4 - 创建品名维护界面";
    typeWidget =new TypeMaintainWidget(this);
    //关闭维护页面之后，重新装载数据
    connect(typeWidget,SIGNAL(destroyed()),this,SLOT(slot_roloadComboBox_Type()));
}

void HomePageWindow::slot_roloadComboBox_place()
{
    qDebug()<<"清空下拉框数据-场地信息";
    combox_place->clear();
    qDebug()<<"重新装载下拉框数据-场地信息！";
    getPlaceDataFromDB();
}

void HomePageWindow::slot_roloadComboBox_car()
{
    qDebug()<<"清空下拉框数据-车辆信息";
    combox_truck_number->clear();
    qDebug()<<"重新装载下拉框数据-车辆信息！";
    getCarDataFromDB();


}

void HomePageWindow::slot_roloadComboBox_Type()
{
    qDebug()<<"清空下拉框数据-品种信息";
    combox_type->clear();
    qDebug()<<"重新装载下拉框数据-品种信息！";
    getTypeDataFromDB();
}

void HomePageWindow::slot_getThingsWeightFromDB(QString text)
{
    //qDebug()<<text;//这个就是车牌号
    CarInfoDaoImp op;
    //根据车牌号，得到车重
    lineEdit_truckWeight->setText(op.selectallCarInfo_one(text,2)); //2 对应车重
    emit lineEdit_totalWeight->editingFinished();//发送 皮重改变的信号，进行自动计算
    lineEdit_man_driver->setText(op.selectallCarInfo_one(text,1)); //1对应驾驶员

    //根据车牌号，搜索全部信息
    //    qDebug()<<"flag=0"<<op.selectallCarInfo_one(text,0); //车牌号0
    //    qDebug()<<"flag=1"<<op.selectallCarInfo_one(text,1); //驾驶员1
    //    qDebug()<<"flag=2"<<op.selectallCarInfo_one(text,2); //车重2
    //    qDebug()<<"flag=3"<<op.selectallCarInfo_one(text,3); //电话3

}



void HomePageWindow::slot_update_carinfo()
{

    if(combox_truck_number->currentText().isEmpty())
    {
        QMessageBox* msg =new QMessageBox(this);
        msg->setText("车牌号不可以为空！");
        msg->setWindowTitle("提示框：");
        msg->setStandardButtons(QMessageBox::Ok);
        msg->exec();
        return;
    }

    qDebug()<<"更新入库---车辆信息";
    QString carnumber=combox_truck_number->currentText();
    QString dirver=lineEdit_man_driver->text();
    double weight=lineEdit_truckWeight->text().toDouble();
    QString telephone="暂无";
    //查找是否有该数据的主键
    CarInfoDaoImp op;
    if(op.isOneExist(carnumber))//如果有
    {
        //carnumber,dirver,weight,telephone;
        op.updateCarInfoBy_id_only_weight(carnumber,weight);
        qDebug()<<"已更改";
    }
    else
    {
        //如果没有
        //插入
        op.insertCarInfoBy_name(carnumber,dirver,weight,telephone);
        qDebug()<<"已新增";
    }
}



void HomePageWindow::connect_lineEdit()
{
    //    connect(lineEdit_totalWeight,SIGNAL(selectionChanged()),this,SLOT(slot_calculate_weight()));
    //    connect(lineEdit_truckWeight,SIGNAL(selectionChanged()),this,SLOT(slot_calculate_weight()));

    //当修改了毛重之后，自动计算
    connect(lineEdit_totalWeight,SIGNAL(editingFinished()),this,SLOT(slot_calculate_weight()));
    //当修改了皮重之后，自动计算
    connect(lineEdit_truckWeight,SIGNAL(editingFinished()),this,SLOT(slot_calculate_weight()));

}
void HomePageWindow::slot_getPlaceInfoFromDB(QString text)
{
    PlaceInfoDaoImp opp;
    lineEdit_man_recever->setText(opp.selectallPlaceInfo_one(text,2));
    //        qDebug()<<"flag=0"<<op.selectallPlaceInfo_one(text,0); //
    //        qDebug()<<"flag=1"<<op.selectallPlaceInfo_one(text,1); //
    //        qDebug()<<"flag=2"<<op.selectallPlaceInfo_one(text,2); //
    //        qDebug()<<"flag=3"<<op.selectallPlaceInfo_one(text,3); //

}
//从数据库里面获取场地信息
void HomePageWindow::getPlaceDataFromDB()
{
    qDebug()<<"---刷新下拉框---场地信息";
    model = new QSqlTableModel(this);
    PlaceInfoDaoImp op;
    op.selectallPlaceInfo_model(model);

    for(int i=0;i<model->rowCount();i++)
    {
        //qDebug()<<model->data(model->index(i,1)).toString();
        combox_place->insertItem(i,model->data(model->index(i,1)).toString());
    }


}

void HomePageWindow::getCarDataFromDB()
{
    qDebug()<<"---刷新下拉框---汽车信息";
    model = new QSqlTableModel(this);
    CarInfoDaoImp op;
    op.selectallCarInfo_model(model);

    for(int i=0;i<model->rowCount();i++)
    {
        //qDebug()<<model->data(model->index(i,1)).toString();
        combox_truck_number->insertItem(i,model->data(model->index(i,0)).toString());
    }


}

void HomePageWindow::getTypeDataFromDB()
{
    qDebug()<<"---刷新下拉框---类型信息";
    model = new QSqlTableModel(this);
    TypeDaoImp op;
    op.selectallTypeInfo(model);

    for(int i=0;i<model->rowCount();i++)
    {
        //qDebug()<<model->data(model->index(i,1)).toString();
        combox_type->insertItem(i,model->data(model->index(i,0)).toString());
    }

}



void HomePageWindow::init_checkbox()
{
    ckb_dirver = new QCheckBox(this);
    ckb_receiver=new QCheckBox(this);
    ckb_watcher=new QCheckBox(this);
    ckb_watcher->setCheckState(Qt::Checked);


    //ckb_dirver->setText("12321321");
    ckb_dirver->setStyleSheet(
                "QCheckBox {spacing: 0px;}"
                "QCheckBox::indicator {width: 20px;height: 20px;}"
                "QCheckBox::indicator:unchecked {image: url(:/picture/unchecked.png);} "
                "QCheckBox::indicator:checked   {image: url(:/picture/checked.png); }"
                );

    ckb_receiver->setStyleSheet(
                "QCheckBox {spacing: 0px;}"
                "QCheckBox::indicator {width: 20px;height: 20px;}"
                "QCheckBox::indicator:unchecked {image: url(:/picture/unchecked.png);} "
                "QCheckBox::indicator:checked   {image: url(:/picture/checked.png); }"
                );

    ckb_watcher->setStyleSheet(
                "QCheckBox {spacing: 0px;}"
                "QCheckBox::indicator {width: 20px;height: 20px;}"
                "QCheckBox::indicator:unchecked {image: url(:/picture/unchecked.png);} "
                "QCheckBox::indicator:checked   {image: url(:/picture/checked.png); }"
                );

    ckb_receiver->setGeometry(label_man_recever->x(),label_man_recever->y(),30,30);
    ckb_dirver->setGeometry(label_man_driver->x(),label_man_driver->y(),30,30);
    ckb_watcher->setGeometry(label_man_watcher->x(),label_man_watcher->y(),30,30);

}

void HomePageWindow::slot_calculate_weight()
{
    qDebug()<<"编辑结束";
    if(lineEdit_totalWeight->text().isEmpty() || lineEdit_truckWeight->text().isEmpty())
    {
        lineEdit_thingsWeight->setText("");
        return;
    }
    //毛重
    double numTotal = lineEdit_totalWeight->text().toDouble();
    //皮重
    double numTruck = lineEdit_truckWeight->text().toDouble();
    //净重
    lineEdit_thingsWeight->setText(QString::number(numTotal-numTruck));

    label_BigCN->setText("净重大写:  "+number_Transfer_BigChinese(numTotal-numTruck));
    qDebug()<<"净重大写："<<number_Transfer_BigChinese(numTotal-numTruck);

}

HomePageWindow::~HomePageWindow()
{
    qDebug()<<"1 - 已销毁首页";
}

void HomePageWindow::init_Label_LineEdit()
{

    //标签名
    label_totalWeight =new QLabel(this);
    label_totalWeight->setFont(QFont("楷体",15,QFont::Bold));
    /*
 “Microsoft YaHei”, 10, 75
常见权重
QFont::Light - 25 高亮
QFont::Normal - 50 正常
QFont::DemiBold - 63 半粗体
QFont::Bold - 75 粗体
QFont::Black - 87 黑体
*/
    // QRegExp rx("^(?:[1-9][0-9]*.[0-9]+|0.(?!0+$)[0-9]+|0)$"); //正浮点数，含0


    label_totalWeight->setText("毛重（吨）：");
    //输入框
    lineEdit_totalWeight = new QLineEdit(this);
    lineEdit_totalWeight->setFixedHeight(30);
    lineEdit_totalWeight->setFont(QFont("宋体",13,75));
    lineEdit_totalWeight->setPlaceholderText("货车总重");
    lineEdit_totalWeight->setClearButtonEnabled(true);

    // lineEdit_totalWeight->setValidator(new QRegExpValidator(rx,lineEdit_totalWeight));
    //标签名
    label_truckWeight =new QLabel(this);
    label_truckWeight->setFont(QFont("楷体",15,QFont::Bold));
    label_truckWeight->setText("皮量（吨）：");

    //输入框
    lineEdit_truckWeight = new QLineEdit(this);
    lineEdit_truckWeight->setFixedHeight(30);
    lineEdit_truckWeight->setFont(QFont("宋体",13,75));
    lineEdit_truckWeight->setPlaceholderText("车身重量");
    lineEdit_truckWeight->setClearButtonEnabled(true);

    // lineEdit_truckWeight->setValidator(new QRegExpValidator(rx,lineEdit_truckWeight));
    //标签名
    label_thingsWeight =new QLabel(this);
    label_thingsWeight->setFont(QFont("楷体",15,QFont::Bold));
    label_thingsWeight->setText("净重（吨）：");
    //输入框
    lineEdit_thingsWeight = new QLineEdit(this);
    lineEdit_thingsWeight->setFixedHeight(30);
    lineEdit_thingsWeight->setFont(QFont("宋体",13,75));
    lineEdit_thingsWeight->setPlaceholderText("货物重量");
    // lineEdit_thingsWeight->setClearButtonEnabled(true);
    lineEdit_thingsWeight->setDisabled(true);

    //单价
    label_price =new QLabel(this);
    label_price->setFont(QFont("楷体",15,QFont::Bold));
    label_price->setText("单价（元/吨）:");
    //输入框
    lineEdit_price = new QLineEdit(this);
    lineEdit_price->setFixedHeight(30);
    lineEdit_price->setFont(QFont("宋体",13,75));
    lineEdit_price->setPlaceholderText("货物单价");
    //lineEdit_price->setClearButtonEnabled(true);

    // lineEdit_price->setValidator(new QRegExpValidator(rx,lineEdit_price));

    //布局
    nameLayout_V =new QVBoxLayout;
    valueLayout_V = new QVBoxLayout;
    //--------
    nameLayout_V->addWidget(label_totalWeight);
    nameLayout_V->addWidget(label_truckWeight);
    nameLayout_V->addWidget(label_thingsWeight);
    nameLayout_V->addWidget(label_price);
    //--------
    valueLayout_V->addWidget(lineEdit_totalWeight);
    valueLayout_V->addWidget(lineEdit_truckWeight);
    valueLayout_V->addWidget(lineEdit_thingsWeight);
    valueLayout_V->addWidget(lineEdit_price);

    //大布局
    dataLayout_H = new QHBoxLayout;
    dataLayout_H->addLayout(nameLayout_V);
    dataLayout_H->addLayout(valueLayout_V);
    dataLayout_H->setGeometry(QRect(400,100,300,150));




    //======================================第二部分============================================
    //流水号
    label_number = new QLabel(this);
    label_number->setFont(QFont("楷体",15,QFont::Bold));
    label_number->setText("流水号：");

    lineEdit_number = new QLineEdit(this);
    lineEdit_number->setFixedHeight(30);
    lineEdit_number->setFont(QFont("宋体",13,75));
    lineEdit_number->setText(readNumberSetting()); //获取最新的流水号(不自增)
    lineEdit_number->setDisabled(true);

    //品名
    label_type = new QLabel(this);
    label_type->setFont(QFont("楷体",15,QFont::Bold));
    label_type->setText("品 名：");
    combox_type = new QComboBox(this);
    combox_type->setFixedHeight(30);
    combox_type->setFont(QFont("宋体",13,75));
    combox_type->setEditable(true);



    //场地
    label_place = new QLabel(this);
    label_place->setFont(QFont("楷体",15,QFont::Bold));
    label_place->setText("场地信息：");

    combox_place = new QComboBox(this);
    combox_place->setFixedHeight(30);
    combox_place->setFont(QFont("宋体",13,75));
    combox_place->setEditable(true);

    connect(combox_place,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_getPlaceInfoFromDB(QString)));

    //    combox_place->setStyleSheet("QComboBox QAbstractItemView::item{height:40px;}");
    //    combox_place->setView(new QListView());
    //combox_place->autoCompletion();//自动补全
    //临时添加数据
    //    combox_place->insertItem(0,"六围");
    //    combox_place->insertItem(1,"新民洲");
    //    combox_place->insertItem(2,"八里");


    //车牌号
    label_truck_number =new QLabel(this);
    label_truck_number->setFont(QFont("楷体",15,QFont::Bold));
    label_truck_number->setText("车牌号：");

    combox_truck_number = new QComboBox(this);
    combox_truck_number->setFixedHeight(30);

    combox_truck_number->setFont(QFont("宋体",13,75));
    combox_truck_number->setEditable(true);

    //    combox_truck_number->setStyleSheet("QComboBox QAbstractItemView::item{height:35px;}");
    //    combox_truck_number->setView(new QListView());

    connect(combox_truck_number,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_getThingsWeightFromDB(QString)));
    //    combox_truck_number->insertItem(0,"苏KME666");
    //    combox_truck_number->insertItem(1,"苏KMA777");
    //    combox_truck_number->insertItem(2,"苏KMA888");

    //标签 竖直布局
    left_name_LV = new QVBoxLayout;
    left_name_LV->addWidget(label_number);
    left_name_LV->addWidget(label_type);
    left_name_LV->addWidget(label_place);
    left_name_LV->addWidget(label_truck_number);


    left_value_LV = new QVBoxLayout;
    left_value_LV->addWidget(lineEdit_number);
    left_value_LV->addWidget(combox_type);
    left_value_LV->addWidget(combox_place);
    left_value_LV->addWidget(combox_truck_number);


    Left_LV = new QHBoxLayout;
    Left_LV->addLayout(left_name_LV);
    Left_LV->addLayout(left_value_LV);
    Left_LV->setGeometry(QRect(10,100,300,150));



    //第三部分

    label_BigCN = new QLabel(this);
    //label_BigCN->setText("显示净重中文大写");
    label_BigCN->setGeometry(10,250,400,30);
    //label_BigCN->setFrameShape(QFrame::WinPanel);//用于观测位置



    //第四部分 人员信息
    label_man_recever = new QLabel(this);
    label_man_driver  = new QLabel(this);
    label_man_watcher = new QLabel(this);


    label_man_recever->setFont(QFont("楷体",15,QFont::Bold));
    label_man_driver->setFont(QFont("楷体",15,QFont::Bold));
    label_man_watcher->setFont(QFont("楷体",15,QFont::Bold));

    label_man_recever->setText("  收货人：");
    label_man_driver->setText("  驾驶员：");
    label_man_watcher->setText("  过磅员：");


    lineEdit_man_recever= new QLineEdit(this);
    lineEdit_man_driver = new QLineEdit(this);
    lineEdit_man_watcher= new QLineEdit(this);

    lineEdit_man_recever->setFixedHeight(30);
    lineEdit_man_recever->setFixedWidth(100);
    lineEdit_man_recever->setFont(QFont("宋体",13,75));
    lineEdit_man_driver->setFixedHeight(30);
    lineEdit_man_driver->setFixedWidth(100);
    lineEdit_man_driver->setFont(QFont("宋体",13,75));
    lineEdit_man_watcher->setFixedHeight(30);
    lineEdit_man_watcher->setFixedWidth(100);
    lineEdit_man_watcher->setFont(QFont("宋体",13,75));


    lineEdit_man_recever->setPlaceholderText("无需填写");
    lineEdit_man_driver->setPlaceholderText("无需填写");
    lineEdit_man_watcher->setPlaceholderText("必填");

    QString account;
    QString name;
    QString password;
    QString status;
    getCurrent_UserInfo(account,password,name,status);
    lineEdit_man_watcher->setText(name);


    man_info_H = new QHBoxLayout;
    man_info_H->addWidget(label_man_recever);
    man_info_H->addWidget(lineEdit_man_recever);
    man_info_H->addSpacing(40);
    man_info_H->addWidget(label_man_driver);
    man_info_H->addWidget(lineEdit_man_driver);
    man_info_H->addSpacing(40);
    man_info_H->addWidget(label_man_watcher);
    man_info_H->addWidget(lineEdit_man_watcher);
    man_info_H->addSpacing(40);

    man_info_H->setGeometry(QRect(10,460,700,30));



}




void HomePageWindow::slot_print()
{
    qDebug()<<"点击打印按钮";
    qDebug()<<"流水号："<<lineEdit_number->text();

    //qDebug()<<combox_place->currentText();
    //1,创建打印机
    QPrinter printer(QPrinter::HighResolution);

    //2,自定义纸张大小
    printer.setPageSize(QPrinter::Custom);//页
    printer.setPaperSize(QSizeF(600,230),QPrinter::Point);//纸张大小


    //3，创建预览窗口
    QPrintPreviewDialog preview(&printer, this);
    preview.setMinimumSize(841,400);//841==100%显示比例


    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreviewSlot(QPrinter*)));
    if(preview.exec ()==QDialog::Accepted)
    {

        RecordDaoImp op;
        QString number      =lineEdit_number->text();
        QString type        =combox_type->currentText();
        QString placename   =combox_place->currentText();
        QString receiver    =lineEdit_man_recever->text();
        QString carnumber   =combox_truck_number->currentText();
        QString dirver      =lineEdit_man_driver->text();
        double totalweight  =lineEdit_totalWeight->text().toDouble();
        double carweight    =lineEdit_truckWeight->text().toDouble();
        double thingsweight =lineEdit_thingsWeight->text().toDouble();
        double price        =lineEdit_price->text().toDouble();
        QDateTime dateTime=QDateTime::currentDateTime();
        QString ticketTime      =dateTime.toString("yyyy-M-d hh:mm:ss");
        QString originalTime    =dateTime.toString("yyyy-MM-dd hh:mm:ss");
        QString watcher     =lineEdit_man_watcher->text();
        op.insertRecordInfo_v3(number,type,placename,receiver,carnumber,dirver,ticketTime,originalTime,watcher,"无","无",totalweight,carweight,thingsweight,price);
        //刷新新的流水号
        lineEdit_number->setText(getNumberSetting());
    }

}



void HomePageWindow::printPreviewSlot(QPrinter *printer)
{
    //4，创建画家
    QPainter painter(printer);//继承打印
    float PPP = readPrinterDpiRate();
    //5,参数
    int Text_WH=120/PPP;
    int Title_WH=180/PPP;
    int explain_WH = 80/PPP;

    char column[10][20]={"品名","单位","毛重","皮重","净重","单价","金额","车号","备注",""};
    //----------------------------------------------
    int border_left = 100/PPP;
    int title_up = 100/PPP;
    //-----------------------------------------------
    int border_up = 510/PPP+title_up;//目前先定420，之后可以根据 上方文字的字号 自动得出距离
    int table_width=4158/PPP;
    int min_margin = 20/PPP; //最小边距，文字距离表格线
    int table_V[4]={(int)(224/PPP),(int)(354/PPP),(int)(280/PPP),(int)(0/PPP)};//水平线间隔
    int table_H[10]={(int)(750/PPP) ,(int)(254/PPP) ,(int)(406/PPP) ,(int)(406/PPP) ,(int)(450/PPP) ,(int)(424/PPP) ,(int)(548/PPP) ,(int)(510/PPP) ,(int)(420/PPP) , (int)(0/PPP)};//竖线间隔距离

    int datePosition=border_left+min_margin; //日期的起始位
    for(int i=0;i<6;i++)
        datePosition+=table_H[i];

    int NO_position = datePosition + table_H[6]+table_H[7]+min_margin;//流水号的起始位置
    //6，开始绘制
    //（1）----------标题“送货通知单”
    //-------------字体
    QFont font("宋体",22);
    painter.setFont(font);
    //-----------------文本
    painter.drawText(QRect(border_left+table_width/2-Title_WH*5/2,title_up,Text_WH*10,300),"送货通知单",QTextOption());

    //（2）----------流水号
    //-------------字体
    QFont font_NO("宋体",9);
    painter.setFont(font_NO);
    //-----------------文本
    painter.drawText(QRect(NO_position,border_up-Text_WH*2-min_margin*2,600,100),lineEdit_number->text(),QTextOption());//"20180210-0008"

    //(3)-----------场地和时间
    //-------------字体
    QFont font_Text("宋体",14);
    painter.setFont(font_Text);

    //-----------------文本
    painter.drawText(QRect(border_left+min_margin,border_up-Text_WH-min_margin,Text_WH*16,Text_WH),"收货单位： "+combox_place->currentText(),QTextOption());
    painter.drawText(QRect(datePosition,border_up-Text_WH-min_margin,Text_WH*5,Text_WH),"日期时间：",QTextOption());
    QFont font_date("宋体",12);
    painter.setFont(font_date);
    painter.drawText(QRect(datePosition+Text_WH*4.5,border_up-Text_WH-min_margin,Text_WH*10,Text_WH),getYMDhms(),QTextOption());//"2018-2-10 23:12:59"


    //(4)-----------表格信息
    //字体
    //QFont font_Text("宋体",14);
    painter.setFont(font_Text);
    //绘制表格框架
    QPen pen;
    pen.setWidthF(5/PPP);//5
    painter.setPen(pen);


    //------------------绘制水平线
    int sumV = border_up;
    for(int i=0;i<4;i++)
    {
        painter.drawLine(QPointF(border_left,sumV),QPointF(table_width+border_left,sumV));
        sumV+=table_V[i];
    }
    int sumH=border_left;
    int Y_1 =border_up+table_V[0]/2-Text_WH/2; //居中调节后，第一行文字所在的实际位置
    //------------------绘制竖直线
    for(int i =0;i<10;i++)
    {

        if(i!=9)//最后一竖线，不需要添加文字
            painter.drawText(QRect(sumH+table_H[i]/2-Text_WH,Y_1,240,Text_WH),column[i],QTextOption());

        if(i==0||i==9)//表格的左右边界竖线
        {
            //V1
            painter.drawLine(QPointF(sumH,border_up),QPointF(sumH,sumV));
        }
        else
        {
            //V2 ~ V9
            painter.drawLine(QPointF(sumH,border_up),QPointF(sumH,sumV-table_V[2]));
        }

        sumH+=table_H[i];
    }

    //(5)第二行文字
    //  QString totalWeight,truckWeight,thingsWeight,price,totalMoney,truckNumber,tips,things_BIG,accepter,driver,watcher;

    int Y_2 =border_up+table_V[0]+table_V[1]/2-Text_WH/2;//居中调节后第二行文字所在的位置

    //水稳碎石
    int sumHHH=border_left;
    //painter.drawText(QRect(sumHHH+table_H[0]/2-Text_WH*2,Y_2,480,Text_WH),"水稳碎石",QTextOption());
    painter.drawText(QRect(sumHHH+table_H[0]/2-Text_WH*strlen(combox_type->currentText().toStdString().c_str())/6,Y_2,480,Text_WH),combox_type->currentText(),QTextOption());
    //吨
    sumHHH+=table_H[0];
    painter.drawText(QRect(sumHHH+table_H[1]/2-Text_WH/2,Y_2,480,Text_WH),"吨",QTextOption());
    // qDebug()<<"吨"<<strlen("吨");//3

    //毛重
    sumHHH+=table_H[1];
    painter.drawText(QRect(sumHHH+table_H[2]/2-Text_WH*strlen(lineEdit_totalWeight->text().toStdString().c_str())/4,Y_2,480,Text_WH),lineEdit_totalWeight->text(),QTextOption());
    //qDebug()<<strlen(lineEdit_totalWeight->text().toStdString().c_str());
    //皮重
    sumHHH+=table_H[2];
    painter.drawText(QRect(sumHHH+table_H[3]/2-Text_WH*strlen(lineEdit_truckWeight->text().toStdString().c_str())/4,Y_2,480,Text_WH),lineEdit_truckWeight->text(),QTextOption());
    //净重
    sumHHH+=table_H[3];
    painter.drawText(QRect(sumHHH+table_H[4]/2-Text_WH*strlen(lineEdit_thingsWeight->text().toStdString().c_str())/4,Y_2,480,Text_WH),lineEdit_thingsWeight->text(),QTextOption());
    //单价
    sumHHH+=table_H[4];
    painter.drawText(QRect(sumHHH+table_H[5]/2-Text_WH*strlen(lineEdit_price->text().toStdString().c_str())/4,Y_2,480,Text_WH),lineEdit_price->text(),QTextOption());

    //金额
    sumHHH+=table_H[5];
    QString money=QString::number(lineEdit_price->text().toDouble()*lineEdit_thingsWeight->text().toDouble());
    painter.drawText(QRect(sumHHH+table_H[6]/2-Text_WH*strlen(money.toStdString().c_str())/4,Y_2,480,Text_WH),money,QTextOption());
    //车牌号
    sumHHH+=table_H[6];
    painter.drawText(QRect(sumHHH+table_H[7]/2-Text_WH*2,Y_2,480,Text_WH),combox_truck_number->currentText(),QTextOption());
    //备注


    //（6）第三行文字
    int Y_3 = border_up+table_V[0]+table_V[1]+table_V[2]/2-Text_WH/2;//居中调节后第三行文字所在的位置
    //净重大写：
    QString Bigcn="净重大写： "+number_Transfer_BigChinese(lineEdit_thingsWeight->text().toDouble());
    painter.drawText(QRect(border_left+min_margin,Y_3,table_width-2*min_margin,Text_WH),Bigcn,QTextOption());


    //（7）底端文字
    int Y_4 =  border_up+table_V[0]+table_V[1]+table_V[2]+min_margin*3;//
    //收货人:
    if(ckb_receiver->checkState()==Qt::Checked)
        painter.drawText(QRect(border_left+min_margin,Y_4,8*Text_WH,Text_WH),"收货人："+lineEdit_man_recever->text(),QTextOption());
    else
        painter.drawText(QRect(border_left+min_margin,Y_4,8*Text_WH,Text_WH),"收货人：",QTextOption());
    //驾驶员:
    if(ckb_dirver->checkState()==Qt::Checked)
        painter.drawText(QRect(border_left+table_width/2-Title_WH*5/2,Y_4,8*Text_WH,Text_WH),"驾驶员："+lineEdit_man_driver->text(),QTextOption());
    else
        painter.drawText(QRect(border_left+table_width/2-Title_WH*5/2,Y_4,8*Text_WH,Text_WH),"驾驶员：",QTextOption());
    //过磅员:
    if(ckb_watcher->checkState()==Qt::Checked)
        painter.drawText(QRect(datePosition+Text_WH*4.5,Y_4,8*Text_WH,Text_WH),"过磅员："+lineEdit_man_watcher->text(),QTextOption());
    else
        painter.drawText(QRect(datePosition+Text_WH*4.5,Y_4,8*Text_WH,Text_WH),"过磅员：",QTextOption());
    //(8)右侧票据说明文字
    QFont font_explain("宋体",9);
    painter.setFont(font_explain);
    painter.drawText(QRect(border_left+table_width+min_margin*2+Text_WH*0,border_up+min_margin,explain_WH,explain_WH*12),QString("第一联/存根/白").split("", QString::SkipEmptyParts).join("\n"),QTextOption());
    painter.drawText(QRect(border_left+table_width+min_margin*2+Text_WH*1,border_up+min_margin,explain_WH,explain_WH*12),QString("第二联/结算/粉").split("", QString::SkipEmptyParts).join("\n"),QTextOption());
    painter.drawText(QRect(border_left+table_width+min_margin*2+Text_WH*2,border_up+min_margin,explain_WH,explain_WH*12),QString("第三联/客户/蓝").split("", QString::SkipEmptyParts).join("\n"),QTextOption());
    painter.drawText(QRect(border_left+table_width+min_margin*2+Text_WH*3,border_up+min_margin,explain_WH,explain_WH*12),QString("第四联/运输/黄").split("", QString::SkipEmptyParts).join("\n"),QTextOption());

    painter.end();


}






