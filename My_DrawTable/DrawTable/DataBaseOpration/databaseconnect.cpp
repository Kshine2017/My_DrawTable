#include "databaseconnect.h"
#include <QSqlQuery>

DataBaseConnect *DataBaseConnect::instance=0;


DataBaseConnect::DataBaseConnect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");  //确定数据库的类型sqlite
}


DataBaseConnect* DataBaseConnect::getInstance()             //对外接口
{
    if(instance==0)
        instance=new DataBaseConnect();
    return instance;
}

void DataBaseConnect::createconnect()                 //创建数据路的连接
{
    db.setDatabaseName("Kshine.db");              //打开数据库，如果没有，则创建一个
    db.open();

    QSqlQuery query;                            //如果没有表，则创建一个用户表

    //表1
    query.exec("\
               create table if not exists tb_place(\
               keynumber  integer primary key autoincrement,\
               placename  text not null,\
               placeman   text,\
               telephone  text\
               );");

    //表2
    query.exec("create table if not exists tb_car(\
               carnumber  text primary key not null,\
               dirver     text,\
               carweight     double not null,\
               telephone  text\
               );");
    //表3
    //流水编号，品类，场地，收货人，车牌号，驾驶员，总重，皮重，货物重量，单价，票据时间，过磅员,原始时间，修改者，修改时间，备注
    query.exec("create table if not exists tb_record(\
               number  text primary key not null,\
               type text,\
               placename  text,\
               receiver text,\
               carnumber  text,\
               dirver text,\
               totalweight double,\
               carweight  double,\
               thingsweight double,\
               price    double,\
               ticketTime   text,\
               originalTime text,\
               watcher text,\
               modefyTime text,\
               modefier text,\
               record_flag text,\
               otherInformation text\
               );");

    //表4 用户表
    query.exec("create table if not exists tb_user(\
               account                  text primary key not null,\
               password                 text not null,\
               name                     text not null,\
               create_time              text not null,\
               status                   text not null\
               );");
    //表5 品名表
    query.exec("create table if not exists tb_type(\
               type                 text primary key not null\
               );");

}

void DataBaseConnect::destoryconnect()                //断开数据库的连接
{
    db.close();
    db.removeDatabase("Kshine.db");
}

