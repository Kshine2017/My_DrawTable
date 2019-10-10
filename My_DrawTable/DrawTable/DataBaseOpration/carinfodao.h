#ifndef CARINFODAO_H
#define CARINFODAO_H
#include "DataBaseOpration/carinfo.h"

class CarInfoDao
{
public:
    CarInfoDao();  
    virtual bool insertCarInfo()=0;
    virtual bool selectallCarInfo()=0;
    virtual bool updateCarInfo()=0;
    virtual bool deleteCarInfo()=0;
    virtual bool isOneExist()=0;                //是否存在

    virtual ~CarInfoDao();
};

#endif // CARINFODAO_H
