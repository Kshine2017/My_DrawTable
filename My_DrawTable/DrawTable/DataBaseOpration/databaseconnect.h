#ifndef DATABASECONNECT_H
#define DATABASECONNECT_H

#include <QSqlDatabase>
class DataBaseConnect
{
public:
    static DataBaseConnect* getInstance(); //公开接口，用于得到单例对象
    void createconnect();              //创建数据库的连接
    void destoryconnect();              //断开数据库的连接
private:
    static DataBaseConnect* instance;
    QSqlDatabase db;
    DataBaseConnect();
};

#endif // DATABASECONNECT_H
