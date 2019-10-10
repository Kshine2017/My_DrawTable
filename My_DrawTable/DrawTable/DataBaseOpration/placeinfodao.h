#ifndef PLACEINFODAO_H
#define PLACEINFODAO_H

#include "DataBaseOpration/placeinfo.h"
class PlaceInfoDao                              //数据库操作（抽象类），用于适应不同的数据库
{
public:
    PlaceInfoDao();
    virtual bool insertPlaceInfo()=0;
    virtual bool selectallPlaceInfo()=0;
    virtual bool updatePlaceInfo()=0;
    virtual bool deletePlaceInfo()=0;
    virtual bool isOneExist()=0;                //是否存在

    virtual ~PlaceInfoDao();


};

#endif // PLACEINFODAO_H
