#include "userdaoimp.h"
#include "databaseconnect.h"
#include <QDateTime>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
UserDaoImp::UserDaoImp()
{

}

bool UserDaoImp::insertUserInfo()
{
return true;
}

bool UserDaoImp::selectallUserInfo()
{
return true;
}

bool UserDaoImp::updateUserInfo()
{
return true;
}

bool UserDaoImp::deleteUserInfo()
{
return true;
}

bool UserDaoImp::isOneExist()
{
    return true;

}

bool UserDaoImp::insertUserInfo(const QString &account, const QString &password, const QString &name, const QString &status)
{
    QString create_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    qDebug()<<"#[数据库操作]-用户表-增加";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("insert into tb_user_v2("
                  "account,"
                  "password,"
                  "name,"
                  "create_time,"
                  "status"
                  ")values("
                  ":account,"
                  ":password,"
                  ":name,"
                  ":create_time,"
                  ":status"
                  ");");
    query.bindValue(":account",(const QVariant)account);
    query.bindValue(":password",(const QVariant)password);
    query.bindValue(":name",(const QVariant)name);
    query.bindValue(":create_time",(const QVariant)create_time);
    query.bindValue(":status",(const QVariant)status);
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

bool UserDaoImp::isOneExist(QString account)
{
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("select * from tb_user_v2 where account = :account;");
    query.bindValue(":account",(const QVariant)account);
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

bool UserDaoImp::updateUserInfo(const QString &account, const QString &password, const QString &name, const QString &status)
{

    qDebug()<<"#[数据库操作]-用户表-更改";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("update tb_user_v2 set password = :password, name = :name, status = :status  where account = :account;");
    query.bindValue(":account",(const QVariant)account);
    query.bindValue(":password",(const QVariant)password);
    query.bindValue(":name",(const QVariant)name);
    //query.bindValue(":create_time",(const QVariant)create_time);
    query.bindValue(":status",(const QVariant)status);
    bool ret = query.exec();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"### 更新用户信息-SQL语句执行失败！###";
        return false;
    }
    qDebug()<<"成功";
    return true;

}

bool UserDaoImp::deleteUserInfo(const QString &account)
{
    qDebug()<<">>>>> 进行 删除操作（用户账号） <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("delete from tb_user_v2 where account = :account;");
    query.bindValue(":account",(const QVariant)account);

    bool ret = query.exec();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"### 删除用户信息-SQL语句执行失败！###";
        return false;
    }
    qDebug()<<"成功";
    return true;

}

bool UserDaoImp::insertUserInfo_admin()
{
    QString create_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("insert into tb_user_v2("
                  "account,"
                  "password,"
                  "name,"
                  "create_time,"
                  "status"
                  ")values("
                  "'admin',"
                  "'wkq123wkq123',"
                  "'管理员',"
                  ":create_time,"
                  "'管理用户'"    //
                  ");");
    query.bindValue(":create_time",(const QVariant)create_time);
    bool ret = query.exec();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"管理员已存在";
        return false;
    }
    qDebug()<<"成功创建管理员";
    return true;

}

bool UserDaoImp::check_account_password(QString &account, QString &password)
{
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("select * from tb_user_v2 where account = :account and password = :password;");
    query.bindValue(":account",(const QVariant)account);
    query.bindValue(":password",(const QVariant)password);
    bool ret = query.exec();

   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"失败";
        return false;
    }
    while(query.next()){
        return true;//true 表示密码正确
    }

    return false;//表示密码错误



}

bool UserDaoImp::getUserInfoByAccount(const QString account, QString &password, QString &name, QString &status)
{
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    QSqlQuery query;
    query.prepare("select password,name,status from tb_user_v2 where account = :account;");
    query.bindValue(":account",(const QVariant)account);
    bool ret = query.exec();
   //------------------------------------------------------------------
    dbhelper->destoryconnect();
    if(!ret)
    {
        qDebug()<<"获取用户信息失败";
        return false;
    }
    query.next();
    password=query.value(0).toString();
    name=query.value(1).toString();
    status=query.value(2).toString();

    return true;


}

/*
    query.exec("create table if not exists tb_user_v2(\
               account  text primary key not null,\
               password  text not null,\
               name  text not null,\
               create_time text not null,\
               status integer not null\
               );");
*/
bool UserDaoImp::selectallUserInfo(QSqlQueryModel *model)
{
    qDebug()<<">>>>> 进行 查询所有操作(用户信息) <<<<<";
    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
    dbhelper->createconnect();
    //------------------------------------------------------------------
    model->setQuery("select account,name,create_time,status from tb_user_v2;");
    model->setHeaderData(0, Qt::Orientation::Horizontal, "账号");
    model->setHeaderData(1, Qt::Orientation::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Orientation::Horizontal, "创建时间");
    model->setHeaderData(3, Qt::Orientation::Horizontal, "权限等级");


//    if (model.lastError())
//     {
//          qDebug() << model.lastError();
//          return false;
//     }

    qDebug()<<"[成功] - 执行查询所有用户信息";
    return true;

}

//bool UserDaoImp::selectallUserInfo(QSqlTableModel *model)
//{
//    qDebug()<<">>>>> 进行 查询所有操作(用户信息) <<<<<";
//    DataBaseConnect* dbhelper = DataBaseConnect::getInstance();
//    dbhelper->createconnect();
//    //------------------------------------------------------------------
//    QSqlQuery str("select account,name,create_time,status from tb_user;");
//    model->setQuery(str);
//    model->setHeaderData(0, Qt::Orientation::Horizontal, "账号");
//    model->setHeaderData(1, Qt::Orientation::Horizontal, "姓名");
//    model->setHeaderData(2, Qt::Orientation::Horizontal, "创建时间");
//    model->setHeaderData(3, Qt::Orientation::Horizontal, "权限等级");
////    if (model.lastError())
////     {
////          qDebug() << model.lastError();
////          return false;
////     }

//    qDebug()<<"[成功] - 执行查询所有用户信息";
//    return true;

//}
