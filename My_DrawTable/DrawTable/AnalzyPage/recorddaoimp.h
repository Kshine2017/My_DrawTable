#ifndef RECORDDAOIMP_H
#define RECORDDAOIMP_H
#include <QString>
#include <QSqlTableModel>
class RecordDaoImp
{
public:
    RecordDaoImp();


    bool insertRecordInfo(const QString& number, \
                          const QString& placename, \
                          const QString& receiver, \
                          const QString& carnumber, \
                          const QString& dirver, \
                          const QString& ticketTime, const QString &originalTime, \
                          const QString& watcher, const QString &modefyTime, const QString &modefier, \
                          double totalweight, \
                          double carweight, \
                          double thingsweight, \
                          double price, const QString& record_flag="正常出单");
    bool insertRecordInfo_v3(const QString& number, \
                          const QString& type, \
                          const QString& placename, \
                          const QString& receiver, \
                          const QString& carnumber, \
                          const QString& dirver, \
                          const QString& ticketTime, const QString &originalTime, \
                          const QString& watcher, const QString &modefyTime, const QString &modefier, \
                          double totalweight, \
                          double carweight, \
                          double thingsweight, \
                          double price, const QString& record_flag="正常出单");
    bool selectallRecordInfo(QSqlQueryModel *model);
    bool selectallRecordInfo_v3(QSqlQueryModel *model);
    bool selectRecordInfo_date(const QString& date_S,const QString& date_E,const QString& place,const QString& car,QSqlQueryModel *model);
    bool selectRecordInfo_date_v3(const QString& date_S,const QString& date_E,const QString& type,const QString& place,const QString& car,QSqlQueryModel *model);
    bool selectRecordInfo_Month(const QString& date_S,const QString& date_E,const QString& place,const QString& car,QSqlQueryModel *model);


    bool updateRecordInfo(const QString& number, \
                          const QString& placename, \
                          const QString& receiver, \
                          const QString& carnumber, \
                          const QString& dirver, \
                          const QString& modefyTime, \
                          const QString& modefier, \
                          double totalweight, \
                          double carweight, \
                          double thingsweight, \
                          double price, const QString& record_flag="已被修改");
    bool updateRecordInfo_v3(const QString& number, \
                          const QString& thingstype, \
                          const QString& placename, \
                          const QString& receiver, \
                          const QString& carnumber, \
                          const QString& dirver, \
                          const QString& modefyTime, \
                          const QString& modefier, \
                          double totalweight, \
                          double carweight, \
                          double thingsweight, \
                          double price, const QString& record_flag="已被修改");
    bool deleteRecordInfo(const QString& number);
    bool deleteRecordInfo_v3(const QString& number);
    bool isOneExist(const QString& number);                //是否存在

};

#endif // RECORDDAOIMP_H
