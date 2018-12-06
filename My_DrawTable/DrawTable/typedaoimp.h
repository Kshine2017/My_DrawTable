#ifndef TYPEDAOIMP_H
#define TYPEDAOIMP_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlTableModel>
class TypeDaoImp
{
public:
    TypeDaoImp();
    bool insertTypeInfo(QString& type);
    bool selectallTypeInfo(QSqlQueryModel* model);
   //bool updateTypeInfo();
    bool deleteTypeInfo(QString& type);
    bool isOneExist(QString& type);                //是否存在
};

#endif // TYPEDAOIMP_H
