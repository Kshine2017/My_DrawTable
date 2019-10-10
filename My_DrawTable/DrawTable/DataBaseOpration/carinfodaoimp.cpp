#include "carinfodaoimp.h"
#include "databaseconnect.h"
#include <QDebug>
#include <QSqlQuery>

CarInfoDaoImp::CarInfoDaoImp()
{

}

bool CarInfoDaoImp::insertCarInfo()
{
    qDebug()<<">>>>> 进行 增加操作 <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();






    dbhelper->destoryconnect();
   return true;
}

bool CarInfoDaoImp::selectallCarInfo()
{
    qDebug()<<">>>>> 进行 查找操作 - 全部 <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();






    dbhelper->destoryconnect();
    return true;
}

bool CarInfoDaoImp::updateCarInfo()
{
    qDebug()<<">>>>> 进行 更改操作 <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();






    dbhelper->destoryconnect();
    return true;
}

bool CarInfoDaoImp::deleteCarInfo()
{
    qDebug()<<">>>>> 进行 删除操作 <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();






    dbhelper->destoryconnect();
    return true;

}

bool CarInfoDaoImp::isOneExist()
{
    qDebug()<<">>>>> 进行 判空操作 <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();






    dbhelper->destoryconnect();
    return true;
}


/*
create table if not exists tb_car(\
               carnumber  text primary key not null,\
               dirver     text,\
               carweight     double not null,\
               telephone  text\
*/

bool CarInfoDaoImp::insertCarInfoBy_name(const QString&carnumber, QString&dirver, double weight,QString&telephone)
{
     qDebug()<<">>>>> 进行 增加操作(车牌号，驾驶员，车重，电话) <<<<<";
     DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
     dbhelper->createconnect();
     //------------------------------------------------------------------
     QSqlQuery query;
     query.prepare("insert into tb_car("
                   "carnumber,"
                   "dirver,"
                   "carweight,"
                   "telephone"
                   ")values("
                   ":carnumber,"
                   ":dirver,"
                   ":carweight,"
                   ":telephone"
                   ");");
     query.bindValue(":carnumber",(const QVariant)carnumber);
     query.bindValue(":dirver",(const QVariant)dirver);
     query.bindValue(":carweight",(const QVariant&)weight);
     query.bindValue(":telephone",(const QVariant)telephone);
     bool ret = query.exec();
    //------------------------------------------------------------------
     dbhelper->destoryconnect();
     if(!ret)
     {
         qDebug()<<"### 增加车辆信息-SQL语句执行失败！###";
         return false;
     }
     qDebug()<<"[成功] - ";
     return true;
}

bool CarInfoDaoImp::deleteCarInfoBy_id_name(const char *carnumber)
{

    qDebug()<<">>>>> 进行 删除操作(车牌号) <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("delete from tb_car where carnumber = :carnumber;");
    query.bindValue(":carnumber",(const QVariant)carnumber);

    bool ret = query.exec();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"### 删除车辆信息-SQL语句执行失败！###";
        return false;
    }
    qDebug()<<"成功";
    return true;

}

bool CarInfoDaoImp::updateCarInfoBy_id_name(const QString&carnumber, QString&dirver, double weight,QString&telephone)
{
    qDebug()<<">>>>> 进行 更新操作(车牌号，驾驶员，车重，电话) <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("update tb_car set dirver = :dirver, carweight = :weight, telephone = :telephone where carnumber = :carnumber;");

    query.bindValue(":carnumber",(const QVariant)carnumber);
    query.bindValue(":dirver",(const QVariant)dirver);
    query.bindValue(":weight",(const QVariant&)weight);
    query.bindValue(":telephone",(const QVariant)telephone);
    bool ret = query.exec();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"### 更新车辆信息-SQL语句执行失败！###";
        return false;
    }
    qDebug()<<"成功";
    return true;
}

bool CarInfoDaoImp::updateCarInfoBy_id_only_weight(const QString &carnumber, double weight)
{
    qDebug()<<">>>>> 进行 更新操作(车重) <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("update tb_car set carweight = :weight where carnumber = :carnumber;");

    query.bindValue(":carnumber",(const QVariant)carnumber);
//    query.bindValue(":dirver",(const QVariant)dirver);
    query.bindValue(":weight",(const QVariant&)weight);
//    query.bindValue(":telephone",(const QVariant)telephone);
    bool ret = query.exec();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"### 更新车辆信息-SQL语句执行失败！###";
        return false;
    }
    qDebug()<<"成功";
    return true;

}

bool CarInfoDaoImp::selectallCarInfo_model(QSqlQueryModel *model)
{

    qDebug()<<"[数据库操作]>>>>> 进行 查询 - 所有信息(车牌号，驾驶员，车重，电话)";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    model->setQuery("select carnumber,dirver,carweight,telephone from tb_car order  by  carnumber  asc;");
    model->setHeaderData(0, Qt::Orientation::Horizontal, "车牌号");
    model->setHeaderData(1, Qt::Orientation::Horizontal, "驾驶员");
    model->setHeaderData(2, Qt::Orientation::Horizontal, "车重");
    model->setHeaderData(3, Qt::Orientation::Horizontal, "联系电话");

    dbhelper->destoryconnect();


    qDebug()<<"[成功] - 执行查询所有车辆信息";
    return true;

}

bool CarInfoDaoImp::isOneExist(const QString &carnumber)
{
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("select * from tb_car where carnumber = :carnumber;");
    query.bindValue(":carnumber",(const QVariant)carnumber);
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


/*
QSqlQuery返回的数据集，record是停在第一条记录之前的。
所以，你获得数据集后，必须执行next()或first()到第一条记录，这时候record才是有效的。
否则，exec完直接value肯定报这个错
*/
double CarInfoDaoImp::selectallCarInfo_weight(const char *carnumber)
{
    qDebug()<<"[数据库操作]>>>>> 进行 查询 - 车牌号:"<<carnumber;
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    QSqlQuery query;
    query.prepare("select * from tb_car where carnumber = :carnumber;");
    query.bindValue(":carnumber",(const QVariant)carnumber);
    bool ret = query.exec();
    query.next();
    if(!ret)
    {
        qDebug()<<"### 查询-SQL语句执行失败！###";
        return -1;
    }

    qDebug()<<"车重:"<<query.value(2).toDouble();

    dbhelper->destoryconnect();
    return query.value(2).toDouble();
}


QString CarInfoDaoImp::selectallCarInfo_one(QString& carnumber,int flag)
{
    qDebug()<<"[数据库操作]----查找某一个数据----";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    QSqlQuery query;
    query.prepare("select * from tb_car where carnumber = :carnumber;");
    query.bindValue(":carnumber",(const QVariant)carnumber);
    bool ret = query.exec();
    query.next();
    if(!ret)
    {
        qDebug()<<"### 查询-SQL语句执行失败！###";
        return "失败";
    }

    qDebug()<<"找到数据:"<<query.value(flag).toString();

    dbhelper->destoryconnect();
    return query.value(flag).toString();
}


