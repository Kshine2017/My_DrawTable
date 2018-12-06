#include "recorddaoimp.h"
#include "databaseconnect.h"
#include <QDateTime>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
RecordDaoImp::RecordDaoImp()
{

}

bool RecordDaoImp::insertRecordInfo(
        const QString &number,
        const QString &placename,
        const QString &receiver,
        const QString &carnumber,
        const QString &dirver,
        const QString &ticketTime,
        const QString& originalTime,
        const QString &watcher,
        const QString &modefyTime,
        const QString &modefier,
        double totalweight,
        double carweight,
        double thingsweight,
        double price,
        const QString& record_flag)
{


   // qDebug()<<"#[数据库操作]-记录表-增加";

    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("insert into tb_record_v2(\
                  number,\
                  placename,\
                  receiver,\
                  carnumber,\
                  dirver,\
                  totalweight,\
                  carweight,\
                  thingsweight,\
                  price,\
                  ticketTime,\
                  originalTime,\
                  watcher,\
                  modefyTime,\
                  modefier,\
                  record_flag\
                  )values(\
                :number,\
                :placename,\
                :receiver,\
                :carnumber,\
                :dirver,\
                :totalweight,\
                :carweight,\
                :thingsweight,\
                :price,\
                :ticketTime,\
                :originalTime,\
                :watcher,\
                :modefyTime,\
                :modefier,\
                :record_flag\
                );");
    query.bindValue(":number",(const QVariant)number);
    query.bindValue(":placename",(const QVariant)placename);
    query.bindValue(":receiver",(const QVariant)receiver);
    query.bindValue(":carnumber",(const QVariant)carnumber);
    query.bindValue(":dirver",(const QVariant)dirver);
    query.bindValue(":totalweight",(const QVariant&)totalweight);
    query.bindValue(":carweight",(const QVariant&)carweight);
    query.bindValue(":thingsweight",(const QVariant&)thingsweight);
    query.bindValue(":price",(const QVariant&)price);
    query.bindValue(":ticketTime",(const QVariant)ticketTime);
    query.bindValue(":originalTime",(const QVariant)originalTime);
    query.bindValue(":watcher",(const QVariant)watcher);
    query.bindValue(":modefyTime",(const QVariant)modefyTime);
    query.bindValue(":modefier",(const QVariant)modefier);
    query.bindValue(":record_flag",(const QVariant)record_flag);
    bool ret = query.exec();
    //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"sql---新增---失败";
        return false;
    }
    qDebug()<<"sql---新增---成功";
    return true;

}

bool RecordDaoImp::selectallRecordInfo(QSqlQueryModel *model)
{
    //qDebug()<<"#[数据库操作]-记录表-查询全部";

    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();

    model->setQuery("select * from tb_record_v2 order by ticketTime asc;");
    model->setHeaderData(0, Qt::Orientation::Horizontal, "流水号");
    model->setHeaderData(1, Qt::Orientation::Horizontal, "场地");
    model->setHeaderData(2, Qt::Orientation::Horizontal, "收货人");
    model->setHeaderData(3, Qt::Orientation::Horizontal, "车牌号");
    model->setHeaderData(4, Qt::Orientation::Horizontal, "驾驶员");
    model->setHeaderData(5, Qt::Orientation::Horizontal, "毛重");
    model->setHeaderData(6, Qt::Orientation::Horizontal, "皮重");
    model->setHeaderData(7, Qt::Orientation::Horizontal, "净重");
    model->setHeaderData(8, Qt::Orientation::Horizontal, "单价");
    model->setHeaderData(9, Qt::Orientation::Horizontal, "票据时间");
    model->setHeaderData(10, Qt::Orientation::Horizontal, "原始时间");
    model->setHeaderData(11, Qt::Orientation::Horizontal, "过磅人");
    model->setHeaderData(12, Qt::Orientation::Horizontal, "修改时间");
    model->setHeaderData(13, Qt::Orientation::Horizontal, "修改人");
    model->setHeaderData(14, Qt::Orientation::Horizontal, "类型");

    dbhelper->destoryconnect();
    qDebug()<<"sql---查询(全部)---完成";
    return true;
}

bool RecordDaoImp::selectRecordInfo_date(const QString &date_S, const QString &date_E, const QString &place, const QString &car, QSqlQueryModel *model)
{
   // qDebug()<<"#[数据库操作]-记录表-条件查询";//substr(time,0,8)//字符串截取查询（还有很多用法）
    QString sss="select \
                                number,\
                                placename,\
                                receiver,\
                                carnumber,\
                                dirver,\
                                totalweight,\
                                carweight,\
                                thingsweight,\
                                price,\
                                ticketTime,\
                                originalTime,\
                                watcher,\
                                modefyTime,\
                                modefier,\
                                record_flag\
                                               from tb_record_v2 ";
    sss+=" where originalTime between '"+date_S+"' and '"+date_E+"'";
    if(place!="全部")
    {
        sss+=" and placename = '"+place+"'";
    }
    if(car!="全部")
    {
        sss+=" and carnumber = '"+car+"'";
    }
    sss+=";";
    //qDebug()<<"<SQL> "<<sss;

    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    model->setQuery(sss);
    model->setHeaderData(0, Qt::Orientation::Horizontal, "流水号");
    model->setHeaderData(1, Qt::Orientation::Horizontal, "场地");
    model->setHeaderData(2, Qt::Orientation::Horizontal, "收货人");
    model->setHeaderData(3, Qt::Orientation::Horizontal, "车牌号");
    model->setHeaderData(4, Qt::Orientation::Horizontal, "驾驶员");
    model->setHeaderData(5, Qt::Orientation::Horizontal, "毛重");
    model->setHeaderData(6, Qt::Orientation::Horizontal, "皮重");
    model->setHeaderData(7, Qt::Orientation::Horizontal, "净重");
    model->setHeaderData(8, Qt::Orientation::Horizontal, "单价");
    model->setHeaderData(9, Qt::Orientation::Horizontal, "票据时间");
    model->setHeaderData(10, Qt::Orientation::Horizontal, "原始时间");
    model->setHeaderData(11, Qt::Orientation::Horizontal, "过磅人");
    model->setHeaderData(12, Qt::Orientation::Horizontal, "修改时间");
    model->setHeaderData(13, Qt::Orientation::Horizontal, "修改人");
    model->setHeaderData(14, Qt::Orientation::Horizontal, "类型");
    dbhelper->destoryconnect();

    qDebug()<<"sql---查询(日)---完成";
    return true;
}

bool RecordDaoImp::selectRecordInfo_Month(const QString &date_S, const QString &date_E, const QString &place, const QString &car, QSqlQueryModel *model)
{
   // qDebug()<<"#[数据库操作]-记录表-条件查询";//substr(time,0,8)//字符串截取查询（还有很多用法）
    QString sss="select \
                  totalweight,\
                  carweight,\
                  thingsweight,\
                  price,\
                  substr(originalTime,0,5),\
                  substr(originalTime,6,2)\
                  from tb_record_v2 ";
    sss+=" where originalTime between '"+date_S+"' and '"+date_E+"'";
    if(place!="全部")
    {
        sss+=" and placename = '"+place+"'";
    }

    if(car!="全部")
    {
        sss+=" and carnumber = '"+car+"'";
    }

    sss+=" order by originalTime asc;";
   // qDebug()<<"<SQL> "<<sss;

    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
      model->setQuery(sss);
    dbhelper->destoryconnect();
    qDebug()<<"sql---查询(月)---完成";
    return true;
}

bool RecordDaoImp::updateRecordInfo(const QString &number, const QString &placename, const QString &receiver, const QString &carnumber, const QString &dirver, const QString &modefyTime, const QString &modefier, double totalweight, double carweight, double thingsweight, double price, const QString &record_flag)
{

    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    QSqlQuery query;
    query.prepare("update tb_record_v2 set \
                  placename = ?,\
                  receiver = ?,\
                  carnumber = ?,\
                  dirver = ?,\
                  totalweight = ?,\
                  carweight = ?,\
                  thingsweight = ?,\
                  price = ?,\
                  modefyTime= ?,\
                  modefier= ?,\
                  record_flag= ?\
                  where number = ? ; ");

    query.bindValue(0,placename,QSql::Out);
    query.bindValue(1,receiver,QSql::Out);
    query.bindValue(2,carnumber,QSql::Out);
    query.bindValue(3,dirver,QSql::Out);
    query.bindValue(4,totalweight,QSql::Out);
    query.bindValue(5,carweight,QSql::Out);
    query.bindValue(6,thingsweight,QSql::Out);
    query.bindValue(7,price,QSql::Out);
    query.bindValue(8,modefyTime,QSql::Out);
    query.bindValue(9,modefier,QSql::Out);
    query.bindValue(10,record_flag,QSql::Out);
    query.bindValue(11,number,QSql::Out);

    bool ret=query.exec();
    dbhelper->destoryconnect();
    if(!ret)qDebug()<<"sql---更新---失败";
    else qDebug()<<"sql---更新---成功";

    return ret;
}

bool RecordDaoImp::deleteRecordInfo(const QString &number)
{
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    QSqlQuery query;
    query.exec("delete from tb_record_v2 where number = ?;"); //账号
    query.bindValue(0,number,QSql::Out);
    bool ret=query.exec();
    dbhelper->destoryconnect();
    if(!ret)qDebug()<<"sql---删除---失败";
    else qDebug()<<"sql---删除---成功";
    return ret;
}

bool RecordDaoImp::isOneExist(const QString &number)
{
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("select * from tb_record_v2 where number = :number;");
    query.bindValue(":number",(const QVariant)number);
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

