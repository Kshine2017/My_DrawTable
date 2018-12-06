#include "placeinfodaoimp.h"
#include "databaseconnect.h"
#include <QDebug>
#include <QSqlQuery>
PlaceInfoDaoImp::PlaceInfoDaoImp()
{

}

//重载函数
bool PlaceInfoDaoImp::insertPlaceInfo()
{
     qDebug()<<">>>>> 进行 增加操作 <<<<<";
     DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
     dbhelper->createconnect();






     dbhelper->destoryconnect();
    return true;
}

bool PlaceInfoDaoImp::selectallPlaceInfo()
{

    qDebug()<<">>>>> 进行 查找操作 - 全部 <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();






    dbhelper->destoryconnect();
    return true;
}

bool PlaceInfoDaoImp::updatePlaceInfo()
{
    qDebug()<<">>>>> 进行 更改操作 <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();






    dbhelper->destoryconnect();
    return true;
}

bool PlaceInfoDaoImp::deletePlaceInfo()
{
    qDebug()<<">>>>> 进行 删除操作 <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();






    dbhelper->destoryconnect();
    return true;
}

bool PlaceInfoDaoImp::isOneExist()
{
    return false;
}

bool PlaceInfoDaoImp::isOneExist(QString &placename)
{
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("select * from tb_place where placename = :placename;");
    query.bindValue(":placename",(const QVariant)placename);
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


//-----------------------根据 场地名称 查找-----------------------------
bool PlaceInfoDaoImp::selectPlaceInfoBy_Name()
{
    return true;
}

bool PlaceInfoDaoImp::selectPlaceInfoBy_keynumber()
{
    return true;
}



bool PlaceInfoDaoImp::insertPlaceInfoBy_name(const char* placeName,const char* placeMan=NULL,const char* telephone=NULL)
{
     qDebug()<<">>>>> 进行 增加操作(场地名，负责人，电话) <<<<<";
     DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
     dbhelper->createconnect();
     //------------------------------------------------------------------
     QSqlQuery query;
     query.prepare("insert into tb_place("
                   "placename,"
                   "placeman,"
                   "telephone"
                   ")values("
                   ":placename,"
                   ":placeman,"
                   ":telephone"
                   ");");
     query.bindValue(":placename",(const QVariant)placeName);
     query.bindValue(":placeman",(const QVariant)placeMan);
     query.bindValue(":telephone",(const QVariant)telephone);
     bool ret = query.exec();
    //------------------------------------------------------------------
     dbhelper->destoryconnect();
     if(!ret)
     {
         qDebug()<<"### 增加场地信息-SQL语句执行失败！###";
         return false;
     }
     qDebug()<<"成功";
     return true;
}

bool PlaceInfoDaoImp::deletePlaceInfoBy_id_name(int keynumber, const char *placeName)
{
    qDebug()<<">>>>> 进行 删除操作(编号，场地名) <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("delete from tb_place where keynumber = :keynumber or placename = :placename ;");
    query.bindValue(":keynumber",(const QVariant&)keynumber);
    query.bindValue(":placename",(const QVariant)placeName);
    bool ret = query.exec();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"### 删除场地信息-SQL语句执行失败！###";
        return false;
    }
    qDebug()<<"成功";
    return true;
}

bool PlaceInfoDaoImp::updatePlaceInfoBy_id_name(int keynumber, const char *placeName, const char *placeMan, const char *telephone)
{

    qDebug()<<">>>>> 进行 更新操作(编号，场地名，负责人，电话) <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("update tb_place set placename = :placename, placeman = :placeman, telephone = :telephone where keynumber = :keynumber;");

    query.bindValue(":keynumber",(const QVariant&)keynumber);
    query.bindValue(":placename",(const QVariant)placeName);
    query.bindValue(":placeman",(const QVariant)placeMan);
    query.bindValue(":telephone",(const QVariant)telephone);
    bool ret = query.exec();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"### 更新场地信息-SQL语句执行失败！###";
        return false;
    }
    qDebug()<<"成功";
    return true;

}

bool PlaceInfoDaoImp::selectallPlaceInfo_model(QSqlQueryModel* model)
{

    qDebug()<<">>>>> 进行 查询所有操作(编号，场地名，负责人，电话) <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    model->setQuery("select keynumber,placename,placeman,telephone from tb_place;");
    model->setHeaderData(0, Qt::Orientation::Horizontal, "编号");
    model->setHeaderData(1, Qt::Orientation::Horizontal, "场地名称");
    model->setHeaderData(2, Qt::Orientation::Horizontal, "负责人");
    model->setHeaderData(3, Qt::Orientation::Horizontal, "联系电话");

//    if (model.lastError())
//     {
//          qDebug() << model.lastError();
//          return false;
//     }

    qDebug()<<"[成功] - 执行查询所有场地信息";
    return true;
}

QString PlaceInfoDaoImp::selectallPlaceInfo_one(QString &placename, int flag)
{
    qDebug()<<"[数据库操作] --场地信息 --查询某一个数据";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("select keynumber, placename, placeman, telephone from tb_place where placename = :placename;");
    query.bindValue(":placename",(const QVariant)placename);
    bool ret = query.exec();
    query.next();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"### 更新场地信息-SQL语句执行失败！###";
        return "false";
    }
    qDebug()<<"找到数据："<<query.value(flag).toString();
    return query.value(flag).toString();
}
