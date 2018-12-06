#ifndef USERDAOIMP_H
#define USERDAOIMP_H
#include <QString>
#include "userdao.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
class UserDaoImp : public UserDao
{
public:
    UserDaoImp();
    bool insertUserInfo();
    bool selectallUserInfo();
    bool updateUserInfo();
    bool deleteUserInfo();
    bool isOneExist();                //是否存在
    //---------------------------------------------
    bool insertUserInfo(const QString& account,const QString& password,const QString& name,const QString& status);
    bool insertUserInfo_admin();//创建管理员
    bool isOneExist(QString account);
    bool updateUserInfo(const QString& account,const QString& password,const QString& name,const QString& status);
    bool deleteUserInfo(const QString& account);

    bool check_account_password(QString& account,QString& password);//查询账号和密码
    bool getUserInfoByAccount(const QString account, QString &password, QString &name, QString &status);
    bool selectallUserInfo(QSqlQueryModel* model);
   // bool selectallUserInfo(QSqlTableModel* model);


};

#endif // USERDAOIMP_H
