#ifndef USERDAO_H
#define USERDAO_H

#include "user.h"
class UserDao
{
public:
    UserDao();
    virtual bool insertUserInfo()=0;
    virtual bool selectallUserInfo()=0;
    virtual bool updateUserInfo()=0;
    virtual bool deleteUserInfo()=0;
    virtual bool isOneExist()=0;                //是否存在
};

#endif // USERDAO_H
