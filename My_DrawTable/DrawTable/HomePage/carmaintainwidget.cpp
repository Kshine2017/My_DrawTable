#include "carmaintainwidget.h"
#include <QDebug>
#include "carinfodaoimp.h"
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QMessageBox>
CarMaintainWidget::CarMaintainWidget(QWidget *parent)
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
void CarMaintainWidget::init_button_connection()
{
    connect(btn_add,SIGNAL(clicked(bool)),this,SLOT(slot_btn_add()));
    connect(btn_delete,SIGNAL(clicked(bool)),this,SLOT(slot_btn_del()));
    connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(slot_btn_upd()));
    connect(btn_select,SIGNAL(clicked(bool)),this,SLOT(slot_btn_sel()));
}

void CarMaintainWidget::slot_btn_add()
{
    qDebug()<<"1.3.1 - 按钮 - add";
    if(lineEdit_carnumber->text().isEmpty()||lineEdit_weight->text().isEmpty())
    {
        qDebug()<<"警告：未输入车牌号或者皮重！";
        //消息框
        QMessageBox* msg =new QMessageBox(this);
        msg->setText("必须填写 “车牌号和皮重”！");
        msg->setWindowTitle("提示框：");
        msg->setStandardButtons(QMessageBox::Ok);
        msg->exec();
        return;
    }
    QString carnumber=lineEdit_carnumber->text();
    QString dirver=lineEdit_dirver->text();
    double weight=lineEdit_weight->text().toDouble();
    QString telephone=lineEdit_telephone->text();
    CarInfoDaoImp op;
    op.insertCarInfoBy_name(carnumber,dirver,weight,telephone);

    QSqlTableModel* model = new QSqlTableModel(this);
    op.selectallCarInfo_model(model);
    tableView->setModel(model);

    //增加完之后，自动清空输入框数据
    lineEdit_carnumber->clear();
    lineEdit_dirver->clear();
    lineEdit_weight->clear();
    lineEdit_telephone->clear();
}

void CarMaintainWidget::slot_btn_del()
{
    qDebug()<<"1.3.2 - 按钮 - delete";
    //消息框
    QMessageBox* msg =new QMessageBox(this);
    msg->setText(QString("确定要删除相关的所有信息吗？\n    车牌号：%1").arg(lineEdit_carnumber->text()));
    msg->setWindowTitle("提示框：");
    msg->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msg->button(QMessageBox::Ok)->setText("确  定");
    msg->button(QMessageBox::Cancel)->setText("取  消");
    if(msg->exec() == QMessageBox::Ok)
    {

     CarInfoDaoImp op;
     op.deleteCarInfoBy_id_name(lineEdit_carnumber->text().toStdString().c_str());

     QSqlTableModel* model = new QSqlTableModel(this);
     op.selectallCarInfo_model(model);
     tableView->setModel(model);
     //增加完之后，自动清空输入框数据
     lineEdit_carnumber->clear();
     lineEdit_dirver->clear();
     lineEdit_weight->clear();
     lineEdit_telephone->clear();
    }
    else
    {
        qDebug()<<"已取消 删除命令！";
    }
}

void CarMaintainWidget::slot_btn_upd()
{
    qDebug()<<"1.3.3 - 按钮 - update";

    if(lineEdit_carnumber->text().isEmpty())
    {

            qDebug()<<"警告：未输入车牌号！";
            //消息框
            QMessageBox* msg =new QMessageBox(this);
            msg->setText("必须填写 “车牌号”！\n    请双击右侧表格数据或者手动指定编号，进行数据修改！");
            msg->setWindowTitle("提示框：");
            msg->setStandardButtons(QMessageBox::Ok);
            msg->exec();
            return;

    }
    QString carnumber=lineEdit_carnumber->text();
    QString dirver=lineEdit_dirver->text();
    double weight=lineEdit_weight->text().toDouble();
    QString telephone=lineEdit_telephone->text();
    CarInfoDaoImp op;
   // op.updateCarInfoBy_id_name(lineEdit_carnumber->text().toStdString().c_str(),lineEdit_dirver->text().toStdString().c_str(),lineEdit_weight->text().toDouble(),lineEdit_telephone->text().toStdString().c_str());
    op.updateCarInfoBy_id_name(carnumber,dirver,weight,telephone);

    //立刻刷新把表格数据
    QSqlTableModel* model = new QSqlTableModel(this);
    op.selectallCarInfo_model(model);
    tableView->setModel(model);

    //更新完之后，自动清空输入框数据
    lineEdit_carnumber->clear();
    lineEdit_dirver->clear();
    lineEdit_weight->clear();
    lineEdit_telephone->clear();

}

void CarMaintainWidget::slot_btn_sel()
{
    qDebug()<<"1.3.4 - 按钮 - select";
    CarInfoDaoImp op;
    QSqlTableModel* model = new QSqlTableModel(this);
    op.selectallCarInfo_model(model);
    tableView->setModel(model);

}

void CarMaintainWidget::slot_table_doubleClick(const QModelIndex &index)
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
    lineEdit_carnumber->setText(str0);
    lineEdit_dirver->setText(str1);
    lineEdit_weight ->setText(str2);
    lineEdit_telephone->setText(str3);


}
CarMaintainWidget::~CarMaintainWidget()
{
    qDebug()<<"1.3 - 已销毁车辆维护界面";



}

void CarMaintainWidget::init_button()
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

void CarMaintainWidget::init_lineEdit()
{
    lineEdit_carnumber=new QLineEdit(this);
    lineEdit_dirver=new QLineEdit(this);
    lineEdit_weight=new QLineEdit(this);
    lineEdit_telephone=new QLineEdit(this);

        lineEdit_carnumber->setFixedHeight(30);
        lineEdit_dirver->setFixedHeight(30);
        lineEdit_weight->setFixedHeight(30);
        lineEdit_telephone->setFixedHeight(30);

    layout_lineEditV =new QVBoxLayout;
    layout_lineEditV->addWidget(lineEdit_carnumber);
    layout_lineEditV->addWidget(lineEdit_dirver);
    layout_lineEditV->addWidget(lineEdit_weight);
    layout_lineEditV->addWidget(lineEdit_telephone);

    layout_lineEditV->setGeometry(QRect(80,80,200,160));

}

void CarMaintainWidget::init_label()
{
    label_BigTitle = new QLabel(this);

    label_carnumber = new QLabel(this);
    label_dirver = new QLabel(this);
    label_weight = new QLabel(this);
    label_telephone = new QLabel(this);



    label_carnumber->setText("车牌号：");
    label_dirver->setText("驾驶员：");
    label_weight->setText("车重：");
    label_telephone->setText("联系电话：");

    QFont font("宋体",32,75);
    label_BigTitle->setFont(font);
    label_BigTitle->setText("车辆信息维护");


    layout_label =new  QVBoxLayout;
    layout_label->addWidget(label_carnumber);
    layout_label->addWidget(label_dirver);
    layout_label->addWidget(label_weight);
    layout_label->addWidget(label_telephone);

    layout_label->setGeometry(QRect(10,80,70,160));



}

void CarMaintainWidget::init_table()
{
    tableView =new QTableView(this);
    QStandardItemModel  *model =new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHeaderData(0,Qt::Horizontal,"车牌号");
    model->setHeaderData(1,Qt::Horizontal,"驾驶员");
    model->setHeaderData(2,Qt::Horizontal,"车重");
    model->setHeaderData(3,Qt::Horizontal,"联系电话");
    tableView->setModel(model);
    tableView->setColumnWidth(0,100);
    tableView->setColumnWidth(1,100);
    tableView->setColumnWidth(2,40);
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
}
