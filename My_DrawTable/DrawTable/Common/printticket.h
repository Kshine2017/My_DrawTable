#ifndef PRINTTICKET_H
#define PRINTTICKET_H

#include <QPrinter>
#include <QDialog>
class PrintTicket:public QDialog
{
    Q_OBJECT
public:
    PrintTicket(QWidget* parent=0);

    QString number;
    QString type;
    QString placename;
    QString receiver;
    QString carnumber;
    QString dirver;
    double totalweight;
    double carweight;
    double thingsweight;
    double price;
    QString ticketTime;
    QString originalTime;
    QString watcher;
    QString recordflag;
    QString otherinformation;//备注信息 20191009
    bool flag_receiver;
    bool flag_dirver;
    bool flag_watcher;

    bool print();//打印和插入数据库



private slots:
    void printPreviewSlot(QPrinter *printer);

};

#endif // PRINTTICKET_H
