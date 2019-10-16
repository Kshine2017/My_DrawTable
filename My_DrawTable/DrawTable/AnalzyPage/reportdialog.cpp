#include "reportdialog.h"

ReportDialog::ReportDialog(QWidget *parent) : QDialog(parent)
{

    setAttribute(Qt::WA_DeleteOnClose); //在关闭该窗口时，自主调用析构函数
    setWindowModality(Qt::ApplicationModal);//模态显示
    setFixedSize(200,100);
    lb_background = new QLabel(this);
    lb_background->setText("很抱歉，尚未开发该功能:(\n请期待下一个版本！");
    lb_background->setGeometry(20,10,200,60);


    show();


}
