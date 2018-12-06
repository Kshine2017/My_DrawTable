#include "userpage.h"
#include <QDebug>
#include <QHeaderView>
#include "userdaoimp.h"
//#include <QSqlQueryModel>
#include "exportimportexcel.h"
#include "usermanagerdialog.h"
#include "setconfig.h"
UserPage::UserPage(QWidget *parent) : QWidget(parent)
{
    //背景
    background_pic = new QLabel(this);
    background_pic->setFixedSize(1000/5*4,500);
    //QPixmap pix_background(":/picture/homepage_background.jpg");
    QPixmap pix_background(":/picture/pgy.jpg");

    pix_background.scaled(background_pic->size(), Qt::IgnoreAspectRatio);
    background_pic->setScaledContents(true);
    background_pic->setPixmap(pix_background);
    background_pic->setGeometry(0,0,1000/5*4,500);

    tableview = new QTableView(this);
    connect(tableview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slot_doubleClicked(QModelIndex)));

    tableview->setGeometry(10,10,1000/5*4-20,400-20);
    tableview->setSelectionBehavior(QAbstractItemView::SelectRows);//选择行
    tableview->setStyleSheet("background-color:transparent;");
    tableview->verticalHeader()->setStyleSheet("QHeaderView::section {background-color: rgba(232, 255, 213, 5);}");
    tableview->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: rgba(232, 255, 213, 5);}");

    UserDaoImp op;
    querymodel = new QSqlQueryModel(this); //a read-only data model

    op.selectallUserInfo(querymodel);
//    tablemodel = new QSqlTableModel(this);
//    mend_MODEL_data();//修改数据

    tableview->setModel(querymodel);
    tableview->setColumnWidth(0,150);
    tableview->setColumnWidth(1,150);
    tableview->setColumnWidth(2,300);
    tableview->setColumnWidth(3,150);

    //=======================================
    btn_set = new QPushButton(this);
    btn_set->setFixedSize(78,32);
    btn_set->setStyleSheet("QPushButton{border-image: url(:/picture/set-up.png);}"
                                      "QPushButton:hover{border-image: url(:/picture/set-up.png);}"
                                      "QPushButton:pressed{border-image: url(:/picture/set-down.png);}");

    btn_set->setFlat(true);
  //btn_AddUser->setGeometry(200,20,150,40);
    connect(btn_set,SIGNAL(clicked()),this,SLOT(slot_set()));


    btn_export = new QPushButton(this);
    btn_export->setFixedSize(78,32);
    btn_export->setStyleSheet("QPushButton{border-image: url(:/picture/export-up.png);}"
                                      "QPushButton:hover{border-image: url(:/picture/export-up.png);}"
                                      "QPushButton:pressed{border-image: url(:/picture/export-down.png);}");
    btn_export->setFlat(true);
  //btn_AddUser->setGeometry(200,20,150,40);
    connect(btn_export,SIGNAL(clicked()),this,SLOT(slot_export()));

    btn_import = new QPushButton(this);
    btn_import->setFixedSize(78,32);
    btn_import->setStyleSheet("QPushButton{border-image: url(:/picture/import-up.png);}"
                                      "QPushButton:hover{border-image: url(:/picture/import-up.png);}"
                                      "QPushButton:pressed{border-image: url(:/picture/import-down.png);}");
    btn_import->setFlat(true);
  //btn_AddUser->setGeometry(200,20,150,40);
    connect(btn_import,SIGNAL(clicked()),this,SLOT(slot_import()));

    btn_manage = new QPushButton(this);
    btn_manage->setFixedSize(116,32);
    btn_manage->setStyleSheet("QPushButton{border-image: url(:/picture/manage-up.png);}"
                                      "QPushButton:hover{border-image: url(:/picture/manage-up.png);}"
                                      "QPushButton:pressed{border-image: url(:/picture/manage-down.png);}");
    btn_manage->setFlat(true);
  //btn_AddUser->setGeometry(200,20,150,40);
    connect(btn_manage,SIGNAL(clicked()),this,SLOT(slot_manage()));

    lay_btn = new QHBoxLayout();
    lay_btn->addWidget(btn_set);lay_btn->addWidget(btn_export);lay_btn->addWidget(btn_import);lay_btn->addWidget(btn_manage);

    lay_btn->setGeometry(QRect(400,tableview->y()/2+tableview->height()/2+230,400,60));//800 500
}

UserPage::~UserPage()
{
    qDebug()<<"已销毁用户页面";
}

void UserPage::mend_MODEL_data()
{
    //遍历model数据，修改其中的 权限显示
    //0   一级用户
    //10  二级用户
    //50  权限用户
    //80  超级用户
    //100 管理用户

    for(int i =0;i<querymodel->rowCount();i++)
    {
        qDebug()<<"--------------"<<querymodel->index(i,0).data().toString()
                                    <<querymodel->index(i,1).data().toString()
                                        <<querymodel->index(i,2).data().toString()
                                            <<querymodel->index(i,3).data().toInt();

        tablemodel->setData(tablemodel->index(i,0),QVariant("123"));//QVariant("普通用户"));
        tablemodel->setData(tablemodel->index(i,1),QVariant("123"));//QVariant("普通用户"));
        tablemodel->setData(tablemodel->index(i,2),querymodel->index(i,2).data());//QVariant("普通用户"));

        if(querymodel->index(i,3).data().toInt()>=100)//超级管理员
            tablemodel->setData(tablemodel->index(i,3),QVariant("管理员"));
        else if(querymodel->index(i,3).data().toInt()>=80) //超级用户
            tablemodel->setData(tablemodel->index(i,3),QVariant("超级用户"));
        else if(querymodel->index(i,3).data().toInt()>=50) //超级用户
            tablemodel->setData(tablemodel->index(i,3),QVariant("权限用户"));
        else if(querymodel->index(i,3).data().toInt()>=10) //超级用户
            tablemodel->setData(tablemodel->index(i,3),QVariant("二级用户"));
        else if(querymodel->index(i,3).data().toInt()>=0) //超级用户
            tablemodel->setData(tablemodel->index(i,3),QVariant("一级用户"));

        qDebug()<<"++++++++++++++"<<tablemodel->index(i,0).data().toString()
                                    <<tablemodel->index(i,1).data().toString()
                                     <<tablemodel->index(i,2).data().toString()
                                        <<tablemodel->index(i,3).data().toString();
    }


}

void UserPage::slot_doubleClicked(QModelIndex index)
{

    int row = index.row();
    QString account = tableview->model()->index(row,0).data().toString();
    qDebug()<<account;
    UserManagerDialog * UMD =new UserManagerDialog(this,account);

    //关闭维护页面之后，重新装载数据
    connect(UMD,SIGNAL(destroyed()),this,SLOT(slot_freshUserData()));
}

void UserPage::slot_freshUserData()
{
    qDebug()<<"自动刷新用户表格数据";

    UserDaoImp op;
    //querymodel = new QSqlQueryModel(this); //a read-only data model
    op.selectallUserInfo(querymodel);
//    tablemodel = new QSqlTableModel(this);
//    mend_MODEL_data();//修改数据
//    tableview->setModel(querymodel);
//    tableview->setColumnWidth(0,150);
//    tableview->setColumnWidth(1,150);
//    tableview->setColumnWidth(2,300);
    //    tableview->setColumnWidth(3,150);
}

void UserPage::slot_set()
{
    qDebug()<<"set";
    new SetConfig(this);
}

void UserPage::slot_export()
{
    ExportImportExcel eie(this);
    eie.ExportDialog();
}

void UserPage::slot_import()
{
    ExportImportExcel eie(this);
    eie.ImportDialog();
}

void UserPage::slot_manage()
{
    UserManagerDialog * UMD =new UserManagerDialog(this,NULL);

    //关闭维护页面之后，重新装载数据
    connect(UMD,SIGNAL(destroyed()),this,SLOT(slot_freshUserData()));



}


