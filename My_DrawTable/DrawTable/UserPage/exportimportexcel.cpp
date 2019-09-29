#include "exportimportexcel.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QModelIndex>

//#include <sapi.h>
#include "qt_windows.h"

#include <QMessageBox>

#include "HomePage/carinfodaoimp.h"            //汽车
#include "HomePage/placeinfodaoimp.h"          //场地
#include "AnalzyPage/recorddaoimp.h"        //记录
#include "userdaoimp.h"                     //用户
#include <QDesktopWidget>
#include <QApplication>

ExportImportExcel::ExportImportExcel(QWidget *parent)
:QDialog(parent)
{

    QDesktopWidget* desktop = QApplication::desktop();

    qDebug()<<"创建导出导入文件的对象";
    this->move(-desktop->width(),-desktop->height());
    //设置透明度
   this->setWindowOpacity(0.6);
    //取消对话框标题
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setStyleSheet("background-color:transparent;");
//    HRESULT r = OleInitialize(0);
//    if (r != S_OK && r != S_FALSE)
//    {qWarning("Qt:初始化Ole失败（error %x）",(unsigned int)r);}

    //设置背景色为淡蓝色,顶层窗口做不出圆角来
    background = new QFrame(this);
    background->setStyleSheet("background-color: rgb(200, 200,200);border-radius:10px;");
    background->setGeometry(0, 0, desktop->width(),desktop->height());

//    label = new QLabel(background);
//   label->setStyleSheet("background-color:transparent;");
//   label->setGeometry(0, 0, 1920, 1080);
//    movie = new QMovie(":/picture/menu/waitgif.gif");
//   label->setScaledContents(true);
//   label->setMovie(movie);

   tip_label = new QLabel(background);
   tip_label->setText("等待执行命令。。。");
   tip_label->setStyleSheet("color: black;background-color: transparent;");
   tip_label->setGeometry(0,0, 120, 80);
   show();
}
void ExportImportExcel::ExportDialog()
{
    qDebug()<<"【点击按钮】---导出文件";
    QString fileName = QFileDialog::getSaveFileName(this,tr("导出"),"",tr("Excel 2007 (*.xlsx);;Excel 97-2003 (*.xls);;CSV (*.csv)"));
    if(!fileName.isNull())
    {
        this->move(0,0);
        onExportExcel(fileName);
    }
    else //取消
    {

    }

}

void ExportImportExcel::ImportDialog()
{
    qDebug()<<"【点击按钮】---导入文件";
    QString fileName = QFileDialog::getOpenFileName(this,tr("导入"),"",tr("Excel 2007 (*.xlsx);;Excel 97-2003 (*.xls);;CSV (*.csv)"));
    if(!fileName.isNull())
    {
        this->move(0,0);
        onImportExcel(fileName);
    }
    else //取消
    {

    }


}

ExportImportExcel::~ExportImportExcel()
{
    qDebug()<<"释放导出导入文件的对象";

}

void ExportImportExcel::onImportExcel(QString filePath)
{
    QAxObject excel;//("Excel.Application");
    bool ret = excel.setControl("Excel.Application");
    qDebug()<<"----"<<ret;
    if(!ret)//如果连接excel空间失败
    {

        QMessageBox::critical(this,tr("提示"),tr("连接Excel控件失败，建议 安装WPS个人版 或者 购买安装正版微软office！"));
        return;

    }
    excel.setProperty("Visible", false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    work_books->dynamicCall("Open (const QString&)",  QDir::toNativeSeparators(filePath));
    QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
    DATAtoBase(work_book);
    work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
    excel.dynamicCall("Quit(void)");  //退出
}

void ExportImportExcel::onExportExcel(QString filePath)
{
//    HRESULT r = OleInitialize(0);
//    if (r != S_OK && r != S_FALSE) {
//        qWarning("Qt: Could not initialize OLE (error %x)", (unsigned int)r);
//    }
    QAxObject excel;//("Excel.Application");
    bool ret = excel.setControl("Excel.Application");
    qDebug()<<"1、Excel控件 连接情况："<<ret;
    if(!ret)//如果连接excel空间失败
    {

        QMessageBox::critical(this,tr("提示"),tr("连接Excel控件失败，建议 安装WPS个人版 或者 购买安装正版微软office！"));
        return;

    }
//  OleUninitialize();
    excel.setProperty("Visible", false);
    excel.setProperty("DisplayAlerts", false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    QAxObject *work_book = NULL;

    QFile xlsFile(filePath);
    qDebug()<<filePath;
    if (xlsFile.exists())
    {
        work_book = work_books->querySubObject("Open(const QString &)", QDir::toNativeSeparators(filePath));
    }
    else
    {
        work_books->dynamicCall("Add");
        work_book = excel.querySubObject("ActiveWorkBook");
    }
    DATAtoExcel(work_book);
    qDebug()<<"数据已写入excel!";
    //===============================================================================================
    work_book->dynamicCall("SaveAs(const QString &)", QDir::toNativeSeparators(filePath));
    qDebug()<<"已保存";
    work_book->dynamicCall("Close(Boolean)", false);  //关闭文件
    qDebug()<<"已关闭文件";
    excel.dynamicCall("Quit(void)");  //退出
    qDebug()<<"已退出Excel控件";
}

void ExportImportExcel::DATAtoExcel(QAxObject *work_book)
{
    if(work_book==NULL)
    {
        qDebug()<<"work_book is NULL!";
        return;
    }
    qDebug()<<"2、work_book is "<<work_book;
    QSqlQueryModel model;
    //model.setQuery("select * from reagent_info_v2;");

    //----------得到标题名称-------------------
    //qDebug()<<model.headerData(2,Qt::Horizontal).toString();
    //---------------------------------------
    QAxObject *work_sheets = work_book->querySubObject("Sheets");//默认有一张表1
    work_sheets->querySubObject("Add()");//表2
    work_sheets->querySubObject("Add()");//表3
    work_sheets->querySubObject("Add()");//表4  //用户信息
    qDebug()<<"3、work_sheets is "<<work_sheets;
    QAxObject *first_sheet = work_sheets->querySubObject("Item(int)", 1);
    qDebug()<<"3.1、first_sheet is "<<first_sheet;
    first_sheet->setProperty("Name","车辆信息");
    //数据准备
    CarInfoDaoImp cd;
    cd.selectallCarInfo_model(&model);
    int columnNumber=model.columnCount();
    int rowNumber=model.rowCount();

    QAxObject *cell ;
    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = first_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
        cell->dynamicCall("SetValue(const QVariant&)",model.headerData(i,Qt::Horizontal));
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {

            cell = first_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            cell->setProperty("Value", model.data(model.index(i,j)));
            cell->dynamicCall("SetValue(const QVariant&)",model.data(model.index(i,j)));
        }

    qDebug()<<"已完成第一页表格数据";
    QAxObject *second_sheet = work_sheets->querySubObject("Item(int)", 2);
    second_sheet->setProperty("Name","场地信息");
    qDebug()<<"3.2、second_sheet is "<<second_sheet;
    //数据准备
    PlaceInfoDaoImp op;
    op.selectallPlaceInfo_model(&model);
    //model.setQuery("select * from reagent_movement_v2;");
    columnNumber=model.columnCount();
    rowNumber=model.rowCount();
    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = second_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
        cell->dynamicCall("SetValue(const QVariant&)",model.headerData(i,Qt::Horizontal));
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {
            cell = second_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            cell->setProperty("Value", model.data(model.index(i,j)));
            cell->dynamicCall("SetValue(const QVariant&)",model.data(model.index(i,j)));
        }

    qDebug()<<"已完成第二页表格数据";
    QAxObject *third_sheet = work_sheets->querySubObject("Item(int)", 3);
    third_sheet->setProperty("Name","单据信息");
     qDebug()<<"3.3、third_sheet is "<<third_sheet;

     //数据准备
     RecordDaoImp rdi;
     rdi.selectallRecordInfo(&model);
    //model.setQuery("select * from standard_info_v2;");
    columnNumber=model.columnCount();
    rowNumber=model.rowCount();
    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = third_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
        cell->dynamicCall("SetValue(const QVariant&)",model.headerData(i,Qt::Horizontal));
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {
            cell = third_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            cell->setProperty("Value", model.data(model.index(i,j)).toString());
            cell->dynamicCall("SetValue(const QVariant&)",model.data(model.index(i,j)));


        }
    qDebug()<<"已完成第三页表格数据";


    QAxObject *forth_sheet = work_sheets->querySubObject("Item(int)", 4);
    forth_sheet->setProperty("Name","用户信息");
     qDebug()<<"3.4、forth_sheet is "<<forth_sheet;

     //数据准备
    UserDaoImp udi;
    udi.selectallUserInfo(&model);
    //model.setQuery("select * from standard_info_v2;");
    columnNumber=model.columnCount();
    rowNumber=model.rowCount();
    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = forth_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
        cell->dynamicCall("SetValue(const QVariant&)",model.headerData(i,Qt::Horizontal));
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {
            cell = forth_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            cell->setProperty("Value", model.data(model.index(i,j)));
            cell->dynamicCall("SetValue(const QVariant&)",model.data(model.index(i,j)));
        }
    qDebug()<<"已完成第四页表格数据";


}

void ExportImportExcel::DATAtoBase(QAxObject *work_book)
{
    if(work_book==NULL)
    {
        qDebug()<<"work_book is NULL!";
        return;
    }
    qDebug()<<"work_book is "<<work_book;
    QAxObject *work_sheets = work_book->querySubObject("Sheets");
    int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
    if(sheet_count > 0)
    {
        QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);//车辆
        QAxObject *used_range = work_sheet->querySubObject("UsedRange");
        QAxObject *rows = used_range->querySubObject("Rows");
        int row_number = rows->property("Count").toInt()-1;  //获取行数
        //qDebug()<<"表1有 "<<row_number<<" 个数据";
        if(row_number<0)row_number=0;
        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {
            QString carnumber=work_sheet->querySubObject("Cells(int,int)", i+2, 1)->dynamicCall("Value").toString();
            QString dirver=work_sheet->querySubObject("Cells(int,int)", i+2, 2)->dynamicCall("Value").toString();
            double truckweight=work_sheet->querySubObject("Cells(int,int)", i+2, 3)->dynamicCall("Value").toDouble();
            QString telephone =work_sheet->querySubObject("Cells(int,int)", i+2, 4)->dynamicCall("Value").toString();

            //判断是否已有
            //qDebug()<<"FILE_SHORT_NAME = "<<FILE_SHORT_NAME;
            CarInfoDaoImp cidi;
            if(cidi.isOneExist(carnumber))
            {
                cidi.updateCarInfoBy_id_name(carnumber,dirver,truckweight,telephone);//存在更新
            }
            else
                cidi.insertCarInfoBy_name(carnumber,dirver,truckweight,telephone);//插入

        }

        work_sheet = work_book->querySubObject("Sheets(int)", 2);//场地
        used_range = work_sheet->querySubObject("UsedRange");
        rows = used_range->querySubObject("Rows");
        row_number = rows->property("Count").toInt()-1;  //获取行数
        //qDebug()<<"表2有 "<<row_number<<" 个数据";
        if(row_number<0)row_number=0;

        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {

            int ID=work_sheet->querySubObject("Cells(int,int)", i+2, 1)->dynamicCall("Value").toInt();
            QString placename= work_sheet->querySubObject("Cells(int,int)", i+2, 2)->dynamicCall("Value").toString();
            QString placeman=work_sheet->querySubObject("Cells(int,int)", i+2, 3)->dynamicCall("Value").toString();;
            QString telephone=work_sheet->querySubObject("Cells(int,int)", i+2,4)->dynamicCall("Value").toString();

            PlaceInfoDaoImp dp;
            if(dp.isOneExist(placename))//已存在
                dp.updatePlaceInfoBy_id_name(ID,placename.toStdString().c_str(),placeman.toStdString().c_str(),telephone.toStdString().c_str());
            else //不存在
                dp.insertPlaceInfoBy_name(placename.toStdString().c_str(),placeman.toStdString().c_str(),telephone.toStdString().c_str());

        }

        work_sheet = work_book->querySubObject("Sheets(int)", 3);//票据
        used_range = work_sheet->querySubObject("UsedRange");
        rows = used_range->querySubObject("Rows");
        row_number = rows->property("Count").toInt()-1;  //获取行数
        if(row_number<0)row_number=0;
        //qDebug()<<"表3有 "<<row_number<<" 个数据";
        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {
            QString number=work_sheet->querySubObject("Cells(int,int)", i+2,1)->dynamicCall("Value").toString();
            QString placename=work_sheet->querySubObject("Cells(int,int)", i+2,2)->dynamicCall("Value").toString();
            QString receiver=work_sheet->querySubObject("Cells(int,int)", i+2,3)->dynamicCall("Value").toString();
            QString carnumber=work_sheet->querySubObject("Cells(int,int)", i+2,4)->dynamicCall("Value").toString();
            QString dirver=work_sheet->querySubObject("Cells(int,int)", i+2,5)->dynamicCall("Value").toString();

            double totalWeight=work_sheet->querySubObject("Cells(int,int)", i+2,6)->dynamicCall("Value").toDouble();
            double carweight=work_sheet->querySubObject("Cells(int,int)", i+2,7)->dynamicCall("Value").toDouble();
            double thingsweight=work_sheet->querySubObject("Cells(int,int)", i+2,8)->dynamicCall("Value").toDouble();
            double price=work_sheet->querySubObject("Cells(int,int)", i+2,9)->dynamicCall("Value").toDouble();

            QString ticketTime=work_sheet->querySubObject("Cells(int,int)", i+2,10)->dynamicCall("Value").toString();
            QString orignalTime=work_sheet->querySubObject("Cells(int,int)", i+2,11)->dynamicCall("Value").toString();
            QString watcher=work_sheet->querySubObject("Cells(int,int)", i+2,12)->dynamicCall("Value").toString();
            QString modefytime=work_sheet->querySubObject("Cells(int,int)", i+2,13)->dynamicCall("Value").toString();
            QString modefier=work_sheet->querySubObject("Cells(int,int)", i+2,14)->dynamicCall("Value").toString();
            QString type=work_sheet->querySubObject("Cells(int,int)", i+2,15)->dynamicCall("Value").toString();

            RecordDaoImp dost;
            if(dost.isOneExist(number))
            {
                dost.deleteRecordInfo(number);
            }
            dost.insertRecordInfo(number,placename,receiver,carnumber,dirver,ticketTime,orignalTime,watcher,modefytime,modefier,
                                  totalWeight,carweight,thingsweight,price,type);

        }

        work_sheet = work_book->querySubObject("Sheets(int)", 4);//用户
        used_range = work_sheet->querySubObject("UsedRange");
        rows = used_range->querySubObject("Rows");
        row_number = rows->property("Count").toInt()-1;  //获取行数
        //qDebug()<<"表2有 "<<row_number<<" 个数据";
        if(row_number<0)row_number=0;
        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {
            QString account=work_sheet->querySubObject("Cells(int,int)", i+2, 1)->dynamicCall("Value").toString();
            QString name= work_sheet->querySubObject("Cells(int,int)", i+2, 2)->dynamicCall("Value").toString();
          //  QString time=work_sheet->querySubObject("Cells(int,int)", i+2, 3)->dynamicCall("Value").toString();;
            QString status=work_sheet->querySubObject("Cells(int,int)", i+2,4)->dynamicCall("Value").toString();
            UserDaoImp dp;
            if(dp.isOneExist(account))
                dp.updateUserInfo(account,"123456",name,status);
            else
                dp.insertUserInfo(account,"123456",name,status);

        }


    }

}
