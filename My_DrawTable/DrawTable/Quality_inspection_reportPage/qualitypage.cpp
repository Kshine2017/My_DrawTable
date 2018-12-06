#include "qualitypage.h"

QualityPage::QualityPage(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(800,500);
    widget_1 =new Widget_Test();//widget_1->setStyleSheet("background-color:red;");
    widget_2 =new QWidget();widget_2->setStyleSheet("background-color:blue;");
    widget_3 =new QWidget();widget_3->setStyleSheet("background-color:gray;");
    init_component();
    init_layout();
}

QualityPage::~QualityPage()
{
    delete widget_1;
    delete widget_2;
    delete widget_3;
}

void QualityPage::init_component()
{
    tabwidget = new QTabWidget(this);
    QIcon icon1(":/picture/ico.ico");
    QIcon icon2(":/picture/ico.ico");
    QIcon icon3(":/picture/ico.ico");
    tabwidget->addTab(widget_1,icon1,tr("页面1"));
    tabwidget->addTab(widget_2,icon2,tr("页面2"));
    tabwidget->addTab(widget_3,icon3,tr("页面3"));
}

void QualityPage::init_layout()
{
    tabwidget->setFixedSize(800,500);


}
