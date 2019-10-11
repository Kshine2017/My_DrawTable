#include "setconfig.h"
#include "QDebug"
#include "Common/funcation.h"
SetConfig::SetConfig(QWidget *parent)
: QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose); //在关闭该窗口时，自主调用析构函数
    setWindowModality(Qt::ApplicationModal);//模态显示
    //this->setStyleSheet("background-color:grey;");
    this->setFixedSize(640,400);

    //背景
    background_pic = new QLabel(this);
    background_pic->setFixedSize(640,400);
    //QPixmap pix_background(":/picture/homepage_background.jpg");
    QPixmap pix_background(":/picture/timg.jpg");
    pix_background.scaled(background_pic->size(), Qt::IgnoreAspectRatio);
    background_pic->setScaledContents(true);
    background_pic->setPixmap(pix_background);
    background_pic->setGeometry(0,0,640,400);


    lb_cmbx = new QLabel(this);
    lb_cmbx->setFont(QFont("宋体",22));
    lb_cmbx->setText("打印机属性：");

    cmbx = new QComboBox(this);
    cmbx->setFixedHeight(30);
    cmbx->setFont(QFont("宋体",22));
    //打印机列表
    cmbx->insertItem(0,"EPson LQ-635KII(360x180dpi)");
    cmbx->insertItem(1,"PDF(600x600dpi)");



    connect(cmbx,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_writePrintConfig(int)));

    ly_cmbx= new QHBoxLayout();
    ly_cmbx->addWidget(lb_cmbx);ly_cmbx->addWidget(cmbx);
    ly_cmbx->setGeometry(QRect(10,10,600,40));


    QString printername;
    readPrinterName(printername);
    cmbx->setCurrentText(printername);

    show();

}

SetConfig::~SetConfig()
{
    qDebug()<<"释放设置页面";
}

void SetConfig::slot_writePrintConfig(int index)
{
    qDebug()<<index<<" 写入config文件";
    QString printname=cmbx->currentText();
    int Ldpi,Rdpi;
    if(index==0){Ldpi=360;Rdpi=180;}
    if(index==1){Ldpi=600;Rdpi=600;}

    savePrinterConfig(printname,Ldpi,Rdpi);

}
