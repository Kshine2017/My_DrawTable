#ifndef CARINFODAOIMP_H
#define CARINFODAOIMP_H
#include "HomePage/carinfodao.h"
#include <QSqlQueryModel>
#include <QString>
class CarInfoDaoImp : public CarInfoDao
{
public:
    CarInfoDaoImp();
    //根据数据库不同，进行重载
    bool insertCarInfo();
    bool selectallCarInfo();
    bool updateCarInfo();
    bool deleteCarInfo();
    bool isOneExist();            //是否存在

    //自定义操作函数
    bool insertCarInfoBy_name(const QString &carnumber, QString &dirver, double weight, QString &telephone);
    bool deleteCarInfoBy_id_name(const char*  carnumber);
    bool updateCarInfoBy_id_name(const QString&carnumber, QString&dirver, double weight,QString&telephone);
    bool updateCarInfoBy_id_only_weight(const QString&carnumber, double weight);
    bool selectallCarInfo_model(QSqlQueryModel *model);
    bool isOneExist(const QString& carnumber);
    double selectallCarInfo_weight(const char* carnumber);
    QString selectallCarInfo_one(QString& carnumber,int flag);
};

#endif // CARINFODAOIMP_H
