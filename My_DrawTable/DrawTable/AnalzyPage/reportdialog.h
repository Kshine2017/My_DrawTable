#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
class ReportDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReportDialog(QWidget *parent = nullptr);
    QLabel* lb_background;

signals:

public slots:
};

#endif // REPORTDIALOG_H
