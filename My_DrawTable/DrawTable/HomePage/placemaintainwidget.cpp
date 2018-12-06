#include "placemaintainwidget.h"
#include <QDebug>
#include "placeinfodaoimp.h"
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QMessageBox>
PlaceMaintainWidget::PlaceMaintainWidget(QWidget *parent)
    :QDialog(parent)
{

    setAttribute(Qt::WA_DeleteOnClose); //在关闭该窗口时，自主调用析构函数
    setWindowModality(Qt::ApplicationModal);//模态显示
    //this->setStyleSheet("background-color:grey;");
    this->setFixedSize(640,400);
    //背景
    background_pic = new QLabel(this);
    background_pic->setFixedSize(640,400);
    //QPixmap pix_background(":/picture/homepage_background.jpg");
    QPixmap pix_background(":/picture/timg.jpg");
    pix_background.scaled(background_pic->size(), Qt::IgnoreAspectRatio);
    background_pic->setScaledContents(true);
    background_pic->setPixmap(pix_background);
    background_pic->setGeometry(0,0,640,400);

    init_button();
    init_button_connection();
    init_label();
    init_lineEdit();
    init_table();
    this->show();

    emit btn_select->click();
}

PlaceMaintainWidget::~PlaceMaintainWidget()
{

    qDebug()<<"1.2 - 已销毁场地维护界面";

}



//按钮初始化
void PlaceMaintainWidget::init_button()
{
       btn_add =new QPushButton(this);
       btn_delete =new QPushButton(this);
       btn_update =new QPushButton(this);
       btn_select=new QPushButton(this);

       btn_add->setFixedSize(50,50);
       btn_delete->setFixedSize(50,50);
       btn_update->setFixedSize(50,50);
       btn_select->setFixedSize(50,50);

       btn_add->setText("增加");
       btn_delete->setText("删除");
       btn_update->setText("修改");
       btn_select->setText("查找");

       layout_btn =new QHBoxLayout;
       layout_btn->addWidget(btn_add);
       layout_btn->addWidget(btn_delete);
       layout_btn->addWidget(btn_update);
       layout_btn->addWidget(btn_select);

       layout_btn->setGeometry(QRect(8,240,290,106));

}

//初始化输入框
void PlaceMaintainWidget::init_lineEdit()
{


    lineEdit_keynumber=new QLineEdit(this);
    lineEdit_placeName=new QLineEdit(this);
    lineEdit_placeMan=new QLineEdit(this);
    lineEdit_telephone=new QLineEdit(this);

        lineEdit_keynumber->setFixedHeight(30);
        lineEdit_placeMan->setFixedHeight(30);
        lineEdit_placeName->setFixedHeight(30);
        lineEdit_telephone->setFixedHeight(30);

        lineEdit_keynumber->hide();
    layout_lineEditV =new QVBoxLayout;
  //layout_lineEditV->addWidget(lineEdit_keynumber);
    layout_lineEditV->addWidget(lineEdit_placeName);
    layout_lineEditV->addWidget(lineEdit_placeMan);
    layout_lineEditV->addWidget(lineEdit_telephone);

    layout_lineEditV->setGeometry(QRect(80,80,200,160));


}

void PlaceMaintainWidget::init_label()
{
    label_BigTitle = new QLabel(this);
   // label_keynumber = new QLabel(this);
    label_placeMan = new QLabel(this);
    label_placeName = new QLabel(this);
    label_telephone = new QLabel(this);



   // label_keynumber->setText("编号：");
    label_placeName->setText("场地名称：");
    label_placeMan->setText("负责人：");
    label_telephone->setText("联系电话：");

    QFont font("宋体",32,75);
    label_BigTitle->setFont(font);
    label_BigTitle->setText("场地信息维护");


    layout_label =new  QVBoxLayout;
    //layout_label->addWidget(label_keynumber);
    layout_label->addWidget(label_placeName);
    layout_label->addWidget(label_placeMan);
    layout_label->addWidget(label_telephone);

    layout_label->setGeometry(QRect(10,80,70,160));

}

void PlaceMaintainWidget::init_table()
{
#if 0
    table = new QTableWidget(this);


    //属性
    table->setSelectionMode(QAbstractItemView::ExtendedSelection);//可多选（Ctrl、Shift、  Ctrl+A都可以）

    //样式
    table->setColumnCount(4);
    table->setColumnWidth(0,30);
    table->setColumnWidth(1,100);
    table->setColumnWidth(2,100);
    table->setColumnWidth(3,100);

    QStringList header;
    header<<tr("编号")<<tr("场地名称")<<tr("负责人")<<tr("联系电话");
    table->setHorizontalHeaderLabels(header);

    //table->setFixedSize(280,360);
    table->setGeometry(QRect(300,20,332,360));


#elif 1

    tableView =new QTableView(this);
    QStandardItemModel  *model =new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,"编号");
    model->setHeaderData(1,Qt::Horizontal,"场地名称");
    model->setHeaderData(2,Qt::Horizontal,"负责人");
    model->setHeaderData(3,Qt::Horizontal,"联系电话");
    tableView->setModel(model);
    tableView->setColumnWidth(0,40);
    tableView->setColumnWidth(1,100);
    tableView->setColumnWidth(2,100);
    tableView->setColumnWidth(3,90);
    tableView->setGeometry(QRect(300,20,332,360));
    QHeaderView* headerView = tableView->verticalHeader();
    headerView->setHidden(true);

    //不可编辑
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //选择行
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //双击槽
    connect(tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slot_table_doubleClick(QModelIndex)));

#endif
}

void PlaceMaintainWidget::init_button_connection()
{
    connect(btn_add,SIGNAL(clicked(bool)),this,SLOT(slot_btn_add()));
    connect(btn_delete,SIGNAL(clicked(bool)),this,SLOT(slot_btn_del()));
    connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(slot_btn_upd()));
    connect(btn_select,SIGNAL(clicked(bool)),this,SLOT(slot_btn_sel()));
}

void PlaceMaintainWidget::slot_btn_add()
{
    qDebug()<<"1.2.1 - 按钮 - add";
    if(lineEdit_placeName->text().isEmpty())
    {
        qDebug()<<"警告：未输入场地名称！";
        //消息框
        QMessageBox* msg =new QMessageBox(this);
        msg->setText("必须填写 “场地名称”！");
        msg->setWindowTitle("提示框：");
        msg->setStandardButtons(QMessageBox::Ok);
        msg->exec();
        return;
    }

    PlaceInfoDaoImp op;

   // op.insertPlaceInfo();
   // op.insertPlaceInfoBy_name("八里","王凯祥","123");
    op.insertPlaceInfoBy_name(lineEdit_placeName->text().toStdString().c_str(),lineEdit_placeMan->text().toStdString().c_str(),lineEdit_telephone->text().toStdString().c_str());

    QSqlTableModel* model = new QSqlTableModel(this);
    op.selectallPlaceInfo_model(model);
    tableView->setModel(model);

    //增加完之后，自动清空输入框数据
    lineEdit_keynumber->clear();
    lineEdit_placeName->clear();
    lineEdit_placeMan->clear();
    lineEdit_telephone->clear();

}

void PlaceMaintainWidget::slot_btn_del()
{
    qDebug()<<"1.2.2 - 按钮 - delete";
    //消息框
    QMessageBox* msg =new QMessageBox(this);
    msg->setText(QString("确定要删除相关的所有信息吗？\n    编号：%1 \n或者\n    场地名称：%2 ").arg(lineEdit_keynumber->text()).arg(lineEdit_placeName->text()));
    msg->setWindowTitle("提示框：");
    msg->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msg->button(QMessageBox::Ok)->setText("确  定");
    msg->button(QMessageBox::Cancel)->setText("取  消");
    if(msg->exec() == QMessageBox::Ok)
    {

     PlaceInfoDaoImp op;
     op.deletePlaceInfoBy_id_name(lineEdit_keynumber->text().toInt(),lineEdit_placeName->text().toStdString().c_str());

     QSqlTableModel* model = new QSqlTableModel(this);
     op.selectallPlaceInfo_model(model);
     tableView->setModel(model);
     //删除完之后，自动清空输入框数据
     lineEdit_keynumber->clear();
     lineEdit_placeName->clear();
     lineEdit_placeMan->clear();
     lineEdit_telephone->clear();
    }
    else
    {
        qDebug()<<"已取消 删除命令！";
    }

}

void PlaceMaintainWidget::slot_btn_upd()
{
    qDebug()<<"1.2.3 - 按钮 - update";
    if(lineEdit_keynumber->text().isEmpty())
    {

            qDebug()<<"警告：未输入编号！";
            //消息框
            QMessageBox* msg =new QMessageBox(this);
            msg->setText("必须填写 “编号”！\n    请双击右侧表格数据或者手动指定编号，进行数据修改！");
            msg->setWindowTitle("提示框：");
            msg->setStandardButtons(QMessageBox::Ok);
            msg->exec();
            return;

    }
    PlaceInfoDaoImp op;
    op.updatePlaceInfoBy_id_name(lineEdit_keynumber->text().toInt(),lineEdit_placeName->text().toStdString().c_str(),lineEdit_placeMan->text().toStdString().c_str(),lineEdit_telephone->text().toStdString().c_str());

    //立刻刷新把表格数据
    QSqlTableModel* model = new QSqlTableModel(this);
    op.selectallPlaceInfo_model(model);
    tableView->setModel(model);

    //更新完之后，自动清空输入框数据
    lineEdit_keynumber->clear();
    lineEdit_placeName->clear();
    lineEdit_placeMan->clear();
    lineEdit_telephone->clear();


}

void PlaceMaintainWidget::slot_btn_sel()
{
    qDebug()<<"1.2.4 - 按钮 - select";

     QSqlTableModel* model = new QSqlTableModel(this);
     PlaceInfoDaoImp op;
     op.selectallPlaceInfo_model(model);
     tableView->setModel(model);

}

void PlaceMaintainWidget::slot_table_doubleClick(const QModelIndex &index)
{
    qDebug()<<"双击表格 第"<<index.row()<<"行";

    QAbstractItemModel* model = tableView->model();
    //int colum = index.column();
    int row = index.row();
    QString str0=model->data(model->index(row,0)).toString();//第row行第0列的内容
    QString str1=model->data(model->index(row,1)).toString();//第row行第1列的内容
    QString str2=model->data(model->index(row,2)).toString();//第row行第2列的内容
    QString str3=model->data(model->index(row,3)).toString();//第row行第3列的内容

    qDebug()<<str0<<str1<<str2<<str3;
    lineEdit_keynumber->setText(str0);
    lineEdit_placeName->setText(str1);
    lineEdit_placeMan ->setText(str2);
    lineEdit_telephone->setText(str3);


}





