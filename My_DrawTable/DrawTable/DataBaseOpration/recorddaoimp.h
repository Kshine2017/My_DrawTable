#ifndef RECORDDAOIMP_H
#define RECORDDAOIMP_H
#include <QString>
#include <QSqlTableModel>
class RecordDaoImp
{
public:
    RecordDaoImp();
    //插入新数据
    bool insertRecordInfo(const QString& number, \
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
                          double price,
                          const QString& otherInformation,
                          const QString& record_flag="正常出单"
            );
    bool selectallRecordInfo(QSqlQueryModel *model);
    //根据日期条件搜索
    bool selectRecordInfo_date(const QString& date_S,
                               const QString& date_E,
                               const QString& type,
                               const QString& place,
                               const QString& car,
                               QSqlQueryModel *model);
    //根据月份条件搜索
    bool selectRecordInfo_Month(const QString& date_S,
                                const QString& date_E,
                                const QString& place,
                                const QString& car,
                                QSqlQueryModel *model);

    //更新数据
    bool updateRecordInfo(const QString& number, \
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
                          double price,
                          const QString& otherInformation,
                          const QString& record_flag="已被修改");

    //根据单据号码删除
    bool deleteRecordInfo(const QString& number);

    //判断是否存在
    bool isOneExist(const QString& number);                //是否存在

};

#endif // RECORDDAOIMP_H
