#include "typedaoimp.h"
#include <QDebug>
#include "databaseconnect.h"
#include <QSqlQuery>
#include <QMessageBox>
TypeDaoImp::TypeDaoImp()
{

}

bool TypeDaoImp::insertTypeInfo(QString &type)
{
    qDebug()<<"#[数据库操作]-品名表-增加";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("insert into tb_type(type)values(:type);");
    query.bindValue(":type",(const QVariant)type);
    bool ret = query.exec();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"失败";
        return false;
    }
    qDebug()<<"成功";
    return true;
}

bool TypeDaoImp::selectallTypeInfo(QSqlQueryModel *model)
{
    qDebug()<<">>>>> 进行 查询所有操作(品名信息) <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    model->setQuery("select * from tb_type;");
    model->setHeaderData(0, Qt::Orientation::Horizontal, "品名");

    qDebug()<<"[成功] - 执行查询所有品名信息";
    return true;
}



bool TypeDaoImp::deleteTypeInfo(QString& type)
{
    qDebug()<<"#[数据库操作]-品名表-删除";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("delete from tb_type where type = :type;");
    query.bindValue(":type",(const QVariant)type);
    bool ret = query.exec();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"失败";
        return false;
    }
    qDebug()<<"成功";
    return true;
}

bool TypeDaoImp::isOneExist(QString &type)
{
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("select * from tb_type where type = :type;");
    query.bindValue(":type",(const QVariant)type);
    bool ret = query.exec();

   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"失败";
        return false;
    }
    while(query.next()){
        return true;//true 表示存在
    }

    return false;//表示不存在
}
