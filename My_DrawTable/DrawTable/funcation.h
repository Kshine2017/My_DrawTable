#ifndef FUNCATION_H
#define FUNCATION_H
#include <QString>
#include <QDateTime>
const QString number_Transfer_BigChinese(const double &Fnumber);
const QString getYMDhms();
const QString getNumber();
const QString getNumberChanging();
const QString getNumberSetting(const QDateTime&  current_date_time);
const QString getNumberSetting();
const QString readNumberSetting();
const QString readNumberSetting(const QDateTime&  current_date_time);
void saveCurrent_UserInfo(QString& account, QString& password, QString& name, QString&status);
void getCurrent_UserInfo(QString& account, QString& password, QString& name, QString &status);
void Delay_MSec_Suspend(unsigned int msec);
void Delay_MSec(unsigned int msec);


void savePrinterConfig(QString& printerName, int Ldpi, int Rdpi);
void readPrinterName(QString& printerName);
float readPrinterDpiRate();
#endif // FUNCATION_H
