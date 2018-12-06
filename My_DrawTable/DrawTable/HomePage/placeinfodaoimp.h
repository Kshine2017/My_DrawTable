#ifndef PLACEINFODAOIMP_H
#define PLACEINFODAOIMP_H
#include "HomePage/placeinfodao.h"
#include <QSqlQueryModel>
#include <QString>
class PlaceInfoDaoImp:public PlaceInfoDao //sqlite数据库
{
public:
    PlaceInfoDaoImp();

    //根据数据库不同，进行重载
    bool insertPlaceInfo();
    bool selectallPlaceInfo();
    bool updatePlaceInfo();
    bool deletePlaceInfo();
    bool isOneExist();
    bool isOneExist(QString& placename);            //是否存在

    //自定义操作函数
    bool selectPlaceInfoBy_Name();
    bool selectPlaceInfoBy_keynumber();
    bool insertPlaceInfoBy_name(const char *placeName, const char *placeMan, const char *telephone);
    bool deletePlaceInfoBy_id_name(int keynumber,const char *placeName);
    bool updatePlaceInfoBy_id_name(int keynumber,const char *placeName, const char *placeMan, const char *telephone);
    bool selectallPlaceInfo_model(QSqlQueryModel *model);

    QString selectallPlaceInfo_one(QString& placename,int flag);
};

#endif // PLACEINFODAOIMP_H
