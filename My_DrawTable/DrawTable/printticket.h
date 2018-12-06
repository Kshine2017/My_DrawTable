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

    bool flag_receiver;
    bool flag_dirver;
    bool flag_watcher;

    bool print();



private slots:
    void printPreviewSlot(QPrinter *printer);

};

#endif // PRINTTICKET_H
