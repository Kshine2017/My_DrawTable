#include "typemaintainwidget.h"
#include <QDebug>
#include "typedaoimp.h"

#include <QStandardItemModel>
#include <QHeaderView>
#include <QMessageBox>
TypeMaintainWidget::TypeMaintainWidget(QWidget *parent):QDialog(parent)
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
    emit this->btn_select->click();
}

TypeMaintainWidget::~TypeMaintainWidget()
{
    qDebug()<<"1.4 - 已销毁品名维护界面";
}

void TypeMaintainWidget::init_button()
{
    btn_add =new QPushButton(this);
    btn_delete =new QPushButton(this);
   // btn_update =new QPushButton(this);
    btn_select=new QPushButton(this);

    btn_add->setFixedSize(50,50);
    btn_delete->setFixedSize(50,50);
    //btn_update->setFixedSize(50,50);
    btn_select->setFixedSize(50,50);

    btn_add->setText("增加");
    btn_delete->setText("删除");
   // btn_update->setText("修改");
    btn_select->setText("查找");

    layout_btn =new QHBoxLayout;
    layout_btn->addWidget(btn_add);
    layout_btn->addWidget(btn_delete);
    //layout_btn->addWidget(btn_update);
    layout_btn->addWidget(btn_select);

    layout_btn->setGeometry(QRect(8,240,290,106));
}

void TypeMaintainWidget::init_lineEdit()
{
    lineEdit_type=new QLineEdit(this);
    lineEdit_type->setFixedHeight(30);

    layout_lineEditV =new QVBoxLayout;
    layout_lineEditV->addWidget(lineEdit_type);
    layout_lineEditV->setGeometry(QRect(80,80,200,160));
}

void TypeMaintainWidget::init_label()
{
    label_BigTitle = new QLabel(this);
   // label_keynumber = new QLabel(this);
    label_type = new QLabel(this);
    label_type->setText("品种名称：");

    QFont font("宋体",32,75);
    label_BigTitle->setFont(font);
    label_BigTitle->setText("品名信息维护");

    layout_label =new  QVBoxLayout;

    layout_label->addWidget(label_type);

    layout_label->setGeometry(QRect(10,80,70,160));
}

void TypeMaintainWidget::init_table()
{
    tableView =new QTableView(this);
    model =new QSqlTableModel(this);



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

void TypeMaintainWidget::init_button_connection()
{
    connect(btn_add,SIGNAL(clicked(bool)),this,SLOT(slot_btn_add()));
    connect(btn_delete,SIGNAL(clicked(bool)),this,SLOT(slot_btn_del()));
    //connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(slot_btn_upd()));
    connect(btn_select,SIGNAL(clicked(bool)),this,SLOT(slot_btn_sel()));
}

void TypeMaintainWidget::slot_btn_add()
{
    qDebug()<<"1.4.1 - 按钮 - add";
    if(lineEdit_type->text().isEmpty())
    {
        qDebug()<<"警告：未输入品种名称！";
        //消息框
        QMessageBox* msg =new QMessageBox(this);
        msg->setText("必须填写 “品种名称”！");
        msg->setWindowTitle("提示框：");
        msg->setStandardButtons(QMessageBox::Ok);
        msg->exec();
        return;
    }
    QString type=lineEdit_type->text();
    TypeDaoImp op;
    op.insertTypeInfo(type);
    op.selectallTypeInfo(model);
    tableView->setModel(model);

    //增加完之后，自动清空输入框数据
    lineEdit_type->clear();

}

void TypeMaintainWidget::slot_btn_del()
{
    qDebug()<<"1.4.2 - 按钮 - delete";
    //消息框
    QString type =lineEdit_type->text();
    QMessageBox* msg =new QMessageBox(this);
    msg->setText(QString("确定要删除相关的信息吗？\n    品名：%1 ").arg(type));
    msg->setWindowTitle("提示框：");
    msg->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msg->button(QMessageBox::Ok)->setText("确  定");
    msg->button(QMessageBox::Cancel)->setText("取  消");
    if(msg->exec() == QMessageBox::Ok)
    {

     TypeDaoImp op;
     op.deleteTypeInfo(type);
     op.selectallTypeInfo(model);
     tableView->setModel(model);
     //删除完之后，自动清空输入框数据
     lineEdit_type->clear();
    }
    else
    {
        qDebug()<<"已取消 删除命令！";
    }

}



void TypeMaintainWidget::slot_btn_sel()
{
    qDebug()<<"1.4.4 - 按钮 - select";

     TypeDaoImp op;
     op.selectallTypeInfo(model);
     tableView->setModel(model);
}

void TypeMaintainWidget::slot_table_doubleClick(const QModelIndex &index)
{
    qDebug()<<"双击表格 第"<<index.row()<<"行";

    QAbstractItemModel* model = tableView->model();
    //int colum = index.column();
    int row = index.row();
    QString str0=model->data(model->index(row,0)).toString();//第row行第0列的内容
    qDebug()<<str0;
    lineEdit_type->setText(str0);

}
