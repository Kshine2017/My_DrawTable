#include "addpagewindow.h"
#include <QDebug>
#include <QSqlTableModel>
#include "DataBaseOpration/placeinfodaoimp.h"
#include "DataBaseOpration/carinfodaoimp.h"
#include "DataBaseOpration/typedaoimp.h"
#include "Common/funcation.h"
#include "Common/printticket.h"
AddPageWindow::AddPageWindow(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(762, 386);
    //背景
    background_pic = new QLabel(this);
    QPixmap pix_background(":/picture/ys.jpg");

    background_pic->setScaledContents(true);
    background_pic->setPixmap(pix_background);

    background_pic->pixmap()->scaled(this->size(), Qt::IgnoreAspectRatio);
    background_pic->resize(this->size());

    model = new QSqlTableModel(this);
    init_dateEdit();
    init_lineEdit_label_combobox();
    init_checkbox();
    //打印按钮
    btn_print=new QPushButton(this);
    btn_print->setFixedSize(150,40);
    btn_print->setStyleSheet("QPushButton{border-image: url(:/picture/printBtn-up.png);}"
                             "QPushButton:hover{border-image: url(:/picture/printBtn-up.png);}"
                             "QPushButton:pressed{border-image: url(:/picture/printBtn-down.png);}");
    btn_print->setFlat(true);
    btn_print->setGeometry(550,330,150,40);
    connect(btn_print,SIGNAL(clicked()),this,SLOT(slot_print()));

    //布局

    ly_G_all = new QGridLayout();
    //上方
    ly_G_all->setRowMinimumHeight(0,10);
    ly_G_all->addWidget(label_date,1,1,1,4);
    ly_G_all->addWidget(dateEdit,1,7,1,4);
    ly_G_all->addWidget(label_time,1,13,1,4);
    ly_G_all->addWidget(timeEdit,1,19,1,4);
    //中间
    ly_G_all->setRowStretch(3,10);
    ly_G_all->addWidget(label_number,4,1,1,4);
    ly_G_all->addWidget(label_type,5,1,1,4);
    ly_G_all->addWidget(label_place,6,1,1,4);
    ly_G_all->addWidget(label_truck_number,7,1,1,4);

    ly_G_all->addWidget(lineEdit_number,4,5,1,6);
    ly_G_all->addWidget(combox_type,5,5,1,6);
    ly_G_all->addWidget(combox_place,6,5,1,6);
    ly_G_all->addWidget(combox_truck_number,7,5,1,6);

    ly_G_all->addWidget(label_totalWeight,4,13,1,4);
    ly_G_all->addWidget(label_truckWeight,5,13,1,4);
    ly_G_all->addWidget(label_thingsWeight,6,13,1,4);
    ly_G_all->addWidget(label_price,7,13,1,4);

    ly_G_all->addWidget(lineEdit_totalWeight,4,17,1,6);
    ly_G_all->addWidget(lineEdit_truckWeight,5,17,1,6);
    ly_G_all->addWidget(lineEdit_thingsWeight,6,17,1,6);
    ly_G_all->addWidget(lineEdit_price,7,17,1,6);

    //中文大写
    ly_G_all->addWidget(label_BigCN,9,1,1,10);

    //备注
    ly_G_all->setRowStretch(10,10);
    ly_G_all->addWidget(label_otherInformation,11,1,1,2);
    ly_G_all->addWidget(te_otherInformation,12,1,2,10,Qt::AlignTop);
    ly_G_all->setRowStretch(14,30);
    //打印按钮
    ly_G_all->addWidget(btn_print,12,17,1,6);

    //下方勾选框
    ly_G_all->addWidget(ckb_receiver,18,1,1,1);
    ly_G_all->addWidget(label_man_recever,18,2,1,1,Qt::AlignLeft);
    ly_G_all->addWidget(lineEdit_man_recever,19,1,1,3);

    ly_G_all->addWidget(ckb_dirver,18,7,1,1);
    ly_G_all->addWidget(label_man_driver,18,8,1,1,Qt::AlignLeft);
    ly_G_all->addWidget(lineEdit_man_driver,19,7,1,3);

    ly_G_all->addWidget(ckb_watcher,18,13,1,1);
    ly_G_all->addWidget(label_man_watcher,18,14,1,1,Qt::AlignLeft);
    ly_G_all->addWidget(lineEdit_man_watcher,19,13,1,3);

    ly_G_all->setColumnStretch(25,50);

    setLayout(ly_G_all);


    getPlaceDataFromDB();
    getCarDataFromDB();
    getTypeDataFromDB();

}

AddPageWindow::~AddPageWindow()
{
    qDebug()<<"已销毁增加页面";
}
void AddPageWindow::init_checkbox()
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

}
void AddPageWindow::init_dateEdit()
{
    QFont font("宋体",18,75);
    //----------------------------
    label_date = new QLabel(this);
    label_date->setFont(font);
    label_date->setText("出单日期：");
    //---------------------------
    label_time = new QLabel(this);
    label_time->setFont(font);
    label_time->setText("具体时间：");
    //-----------------------------
    dateEdit = new QDateEdit(this);

    dateEdit->setFont(font);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDateTime(QDateTime::currentDateTime());
    dateEdit->setDisplayFormat("yyyy-M-d");    //qt5.9需要设置
    connect(dateEdit,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(slot_getNumberFromDateTime(QDateTime)));
    //----------------------------
    timeEdit = new QTimeEdit(this);


    timeEdit->setFont(font);
    timeEdit->setCalendarPopup(true);
    timeEdit->setDateTime(QDateTime::currentDateTime());
    timeEdit->setDisplayFormat("hh:mm:ss");    //qt5.9需要设置


}

void AddPageWindow::init_lineEdit_label_combobox()
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
    //lineEdit_thingsWeight->setDisabled(true);

    //单价
    label_price =new QLabel(this);
    label_price->setFont(QFont("楷体",15,QFont::Bold));
    label_price->setText("单价（元/吨）:");
    //输入框
    lineEdit_price = new QLineEdit(this);
    lineEdit_price->setFixedHeight(30);
    lineEdit_price->setFont(QFont("宋体",13,75));
    lineEdit_price->setPlaceholderText("货物单价");
    lineEdit_price->setText("0");
    //lineEdit_price->setClearButtonEnabled(true);

   // lineEdit_price->setValidator(new QRegExpValidator(rx,lineEdit_price));





    //======================================第二部分============================================
    //流水号
    label_number = new QLabel(this);
    label_number->setFont(QFont("楷体",15,QFont::Bold));
    label_number->setText("流水号：");

    lineEdit_number = new QLineEdit(this);
    lineEdit_number->setFixedHeight(30);
    lineEdit_number->setFont(QFont("宋体",13,75));
    lineEdit_number->setText(readNumberSetting(dateEdit->dateTime())); //获取最新的流水号
    //lineEdit_number->setDisabled(true);



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
//    combox_place->insertItem(0,"123");
//    combox_place->insertItem(1,"234");
//    combox_place->insertItem(2,"345");
//实现组合框
    combox_place->setEditable(true);//可以手动编辑

    //车牌号
    label_truck_number =new QLabel(this);
    label_truck_number->setFont(QFont("楷体",15,QFont::Bold));
    label_truck_number->setText("车牌号：");

    combox_truck_number = new QComboBox(this);
    combox_truck_number->setFixedHeight(30);
    combox_truck_number->setFont(QFont("宋体",13,75));
    //实现组合框
    combox_truck_number->setEditable(true);//可以手动编辑

    connect(combox_truck_number,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_getThingsWeightFromDB(QString)));
//    combox_truck_number->insertItem(0,"苏KME666");
//    combox_truck_number->insertItem(1,"苏KMA777");
//    combox_truck_number->insertItem(2,"苏KMA888");



    //第三部分
    label_BigCN = new QLabel(this);
    //label_BigCN->setText("显示净重中文大写");
    //label_BigCN->setGeometry(10,250,400,30);
    //label_BigCN->setFrameShape(QFrame::WinPanel);//用于观测位置

    label_otherInformation = new QLabel(this);
    label_otherInformation->setFont(QFont("楷体",15,QFont::Bold));
    label_otherInformation->setText("备注信息：");
    te_otherInformation=new QTextEdit(this);
    te_otherInformation->setPlaceholderText("建议:(英文,数字,符号算半个汉字)\n每行5个汉字\n最多4行。");
    te_otherInformation->setFixedHeight(60);

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
    lineEdit_man_driver= new QLineEdit(this);
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





    //当修改了毛重之后，自动计算
    connect(lineEdit_totalWeight,SIGNAL(editingFinished()),this,SLOT(slot_calculate_weight()));
    //当修改了皮重之后，自动计算
    connect(lineEdit_truckWeight,SIGNAL(editingFinished()),this,SLOT(slot_calculate_weight()));

    connect(combox_place,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_getPlaceInfoFromDB(QString)));
    connect(combox_truck_number,SIGNAL(currentTextChanged(QString)),this,SLOT(slot_getThingsWeightFromDB(QString)));
}

void AddPageWindow::getPlaceDataFromDB()
{

    PlaceInfoDaoImp op;
    op.selectallPlaceInfo_model(model);

    for(int i=0;i<model->rowCount();i++)
    {
        combox_place->insertItem(i,model->data(model->index(i,1)).toString());
    }
}

void AddPageWindow::getCarDataFromDB()
{
    //model = new QSqlTableModel(this);
    CarInfoDaoImp op;
    op.selectallCarInfo_model(model);

    for(int i=0;i<model->rowCount();i++)
    {
        combox_truck_number->insertItem(i,model->data(model->index(i,0)).toString());
    }
}

void AddPageWindow::getTypeDataFromDB()
{
    qDebug()<<"---刷新下拉框---品种信息";
    //model = new QSqlTableModel(this);
    TypeDaoImp op;
    op.selectallTypeInfo(model);

    for(int i=0;i<model->rowCount();i++)
    {
        //qDebug()<<model->data(model->index(i,1)).toString();
        combox_type->insertItem(i,model->data(model->index(i,0)).toString());
    }

}

void AddPageWindow::slot_getNumberFromDateTime(QDateTime datetime)
{
    qDebug()<<"改变日期";
    lineEdit_number->setText(readNumberSetting(datetime)); //获取最新的流水号
}

void AddPageWindow::slot_calculate_weight()
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

void AddPageWindow::slot_getThingsWeightFromDB(QString text)
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

void AddPageWindow::slot_getPlaceInfoFromDB(QString text)
{
    PlaceInfoDaoImp op;
    lineEdit_man_recever->setText(op.selectallPlaceInfo_one(text,2));
    //        qDebug()<<"flag=0"<<op.selectallPlaceInfo_one(text,0); //
    //        qDebug()<<"flag=1"<<op.selectallPlaceInfo_one(text,1); //
    //        qDebug()<<"flag=2"<<op.selectallPlaceInfo_one(text,2); //
    //        qDebug()<<"flag=3"<<op.selectallPlaceInfo_one(text,3); //

}

void AddPageWindow::slot_print()
{
    qDebug()<<"增补---点击打印";
    PrintTicket pt(this);
    //数据准备
    pt.number =lineEdit_number->text();
    pt.type=combox_type->currentText();
    pt.placename =combox_place->currentText();
    pt.receiver = lineEdit_man_recever->text();
    pt.carnumber = combox_truck_number->currentText();
    pt.dirver = lineEdit_man_driver->text();
    pt.totalweight = lineEdit_totalWeight->text().toDouble();
    pt.carweight = lineEdit_truckWeight->text().toDouble();
    pt.thingsweight = lineEdit_thingsWeight->text().toDouble();
    pt.price = lineEdit_price->text().toDouble();
    pt.ticketTime = dateEdit->dateTime().toString("yyyy-M-d ")+timeEdit->dateTime().toString("hh:mm:ss");  ;//创建时间
    pt.originalTime = dateEdit->dateTime().toString("yyyy-MM-dd ")+timeEdit->dateTime().toString("hh:mm:ss");  ;//创建时间
    pt.watcher = lineEdit_man_watcher->text();
    pt.recordflag="增补出单";
    pt.otherinformation=te_otherInformation->toPlainText();
    if(ckb_dirver->checkState()==Qt::Checked)
        pt.flag_dirver=true;
    else
        pt.flag_dirver=false;
    if(ckb_receiver->checkState()==Qt::Checked)
        pt.flag_receiver=true;
    else
        pt.flag_receiver=false;
    if(ckb_watcher->checkState()==Qt::Checked)
        pt.flag_watcher=true;
    else
        pt.flag_watcher=false;
    pt.print();

    lineEdit_number->setText(readNumberSetting(dateEdit->dateTime()));

}

void AddPageWindow::resizeEvent(QResizeEvent *size)
{
    Q_UNUSED(size)
    background_pic->resize(this->size());
    background_pic->pixmap()->scaled(this->size(), Qt::IgnoreAspectRatio);

}
