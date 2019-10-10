#include "exportimportexcel.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QDateTime>
//#include <sapi.h>
#include "qt_windows.h"

#include <QMessageBox>

#include "DataBaseOpration/carinfodaoimp.h"            //汽车
#include "DataBaseOpration/placeinfodaoimp.h"          //场地
#include "DataBaseOpration/recorddaoimp.h"        //记录
#include "DataBaseOpration/userdaoimp.h"                     //用户
#include "DataBaseOpration/typedaoimp.h"
#include <QDesktopWidget>
#include <QApplication>
#include "DataBaseOpration/typedaoimp.h"
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
    QAxObject *cell ;
    int columnNumber,rowNumber;
    //---------------------------------------
    QAxObject *work_sheets = work_book->querySubObject("Sheets");//默认有一张表1 //品类信息
    work_sheets->querySubObject("Add()");//表2
    work_sheets->querySubObject("Add()");//表3
    work_sheets->querySubObject("Add()");//表4
    work_sheets->querySubObject("Add()");//表5  //用户信息

    //---------------------------------------
    QAxObject *first_sheet = work_sheets->querySubObject("Item(int)", 1);
    first_sheet->setProperty("Name","品类信息");

    //数据准备
    TypeDaoImp tdi;
    tdi.selectallTypeInfo(&model);
    columnNumber=model.columnCount();
    rowNumber=model.rowCount();


    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = first_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {
            cell = first_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            cell->setProperty("Value", model.data(model.index(i,j)));
        }
    qDebug()<<"已完成第一页表格数据";

    QAxObject *second_sheet = work_sheets->querySubObject("Item(int)", 2);
    second_sheet->setProperty("Name","车辆信息");
    //数据准备
    CarInfoDaoImp cd;
    cd.selectallCarInfo_model(&model);
    columnNumber=model.columnCount();
    rowNumber=model.rowCount();

    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = second_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {
            cell = second_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            cell->setProperty("Value", model.data(model.index(i,j)));
        }
    qDebug()<<"已完成第二页表格数据";


    QAxObject *third_sheet = work_sheets->querySubObject("Item(int)", 3);
    third_sheet->setProperty("Name","场地信息");
    //数据准备
    PlaceInfoDaoImp op;
    op.selectallPlaceInfo_model(&model);
    columnNumber=model.columnCount();
    rowNumber=model.rowCount();
    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = third_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {
            cell = third_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            cell->setProperty("Value", model.data(model.index(i,j)));
        }
    qDebug()<<"已完成第三页表格数据";

    QAxObject *fourth_sheet = work_sheets->querySubObject("Item(int)", 4);
    fourth_sheet->setProperty("Name","单据信息");

     //数据准备
     RecordDaoImp rdi;
     rdi.selectallRecordInfo(&model);
    columnNumber=model.columnCount();
    rowNumber=model.rowCount();
    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = fourth_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {
            cell = fourth_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            if(j==10)cell->setProperty("NumberFormatLocal", "yyyy-M-d hh:mm:ss");//票上时间
            if(j==11||j==13)cell->setProperty("NumberFormatLocal", "yyyy-MM-dd hh:mm:ss");//创建时间和修改时间
            cell->setProperty("Value", model.data(model.index(i,j)).toString());
        }
    qDebug()<<"已完成第四页表格数据";


    QAxObject *fifth_sheet = work_sheets->querySubObject("Item(int)", 5);
    fifth_sheet->setProperty("Name","用户信息");

     //数据准备
    UserDaoImp udi;
    udi.selectallUserInfo(&model);
    columnNumber=model.columnCount();
    rowNumber=model.rowCount();
    //写入栏目名
    for(int i=0;i<columnNumber;i++)
    {
        cell = fifth_sheet->querySubObject("Cells(int,int)", 1, i+1);
        cell->setProperty("Value",model.headerData(i,Qt::Horizontal).toString());
    }
    //写入数据
    for(int i=0;i<rowNumber;i++)
        for(int j=0;j<columnNumber;j++)
        {
            cell = fifth_sheet->querySubObject("Cells(int,int)", i+2, j+1);
            if(j==2)cell->setProperty("NumberFormatLocal", "yyyy-MM-dd hh:mm:ss");
            cell->setProperty("Value", model.data(model.index(i,j)));
        }
    qDebug()<<"已完成第五页表格数据";

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
        QAxObject *work_sheet;
        QAxObject *used_range;
        QAxObject *rows;
        int row_number;  //获取行数
        //导入品类=================================================================
        work_sheet = work_book->querySubObject("Sheets(int)", 1);
        used_range = work_sheet->querySubObject("UsedRange");
        rows = used_range->querySubObject("Rows");
        row_number = rows->property("Count").toInt()-1;  //获取行数
        //qDebug()<<"表1有 "<<row_number<<" 个数据";
        if(row_number<0)row_number=0;
        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {
            QString thingtype=work_sheet->querySubObject("Cells(int,int)", i+2, 1)->dynamicCall("Value").toString();
            if(thingtype.isEmpty())continue;
            //判断是否已有
            TypeDaoImp tdi;
            if(tdi.isOneExist(thingtype))
            {
                //只有一个成员，不用更新
            }
            else
                tdi.insertTypeInfo(thingtype);//插入

        }

        //导入车辆=================================================================
        work_sheet = work_book->querySubObject("Sheets(int)", 2);//车辆
        used_range = work_sheet->querySubObject("UsedRange");
        rows = used_range->querySubObject("Rows");
        row_number = rows->property("Count").toInt()-1;  //获取行数
        //qDebug()<<"表1有 "<<row_number<<" 个数据";
        if(row_number<0)row_number=0;
        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {
            QString carnumber=work_sheet->querySubObject("Cells(int,int)", i+2, 1)->dynamicCall("Value").toString();
            if(carnumber.isEmpty())continue;
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

        //导入场地=================================================================
        work_sheet = work_book->querySubObject("Sheets(int)", 3);//场地
        used_range = work_sheet->querySubObject("UsedRange");
        rows = used_range->querySubObject("Rows");
        row_number = rows->property("Count").toInt()-1;  //获取行数
        //qDebug()<<"表2有 "<<row_number<<" 个数据";
        if(row_number<0)row_number=0;

        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {

            int ID=work_sheet->querySubObject("Cells(int,int)", i+2, 1)->dynamicCall("Value").toInt();
            QString placename= work_sheet->querySubObject("Cells(int,int)", i+2, 2)->dynamicCall("Value").toString();
            if(placename.isEmpty())continue;
            QString placeman=work_sheet->querySubObject("Cells(int,int)", i+2, 3)->dynamicCall("Value").toString();;
            QString telephone=work_sheet->querySubObject("Cells(int,int)", i+2,4)->dynamicCall("Value").toString();

            PlaceInfoDaoImp dp;
            if(dp.isOneExist(placename))//已存在
                dp.updatePlaceInfoBy_id_name(ID,placename.toStdString().c_str(),placeman.toStdString().c_str(),telephone.toStdString().c_str());
            else //不存在
                dp.insertPlaceInfoBy_name(placename.toStdString().c_str(),placeman.toStdString().c_str(),telephone.toStdString().c_str());

        }

        //导入票据=================================================================
        work_sheet = work_book->querySubObject("Sheets(int)", 4);//票据
        used_range = work_sheet->querySubObject("UsedRange");
        rows = used_range->querySubObject("Rows");
        row_number = rows->property("Count").toInt()-1;  //获取行数
        if(row_number<0)row_number=0;
        //qDebug()<<"表3有 "<<row_number<<" 个数据";
        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {
            //流水号1	品类	场地	收货人	车牌号	驾驶员6
            //毛重(吨)7	皮重(吨)8	 净重(吨)9	 单价(元)10
            //票据时间11	原始时间12	过磅人13	修改时间14	修改人15	票据类型16	备注信息17

            //流水号1
            QString number=work_sheet->querySubObject("Cells(int,int)", i+2,1)->dynamicCall("Value").toString();
            if(number.isEmpty())continue;
            //品类2
            QString thingtype=work_sheet->querySubObject("Cells(int,int)", i+2,2)->dynamicCall("Value").toString();;
            //场地3
            QString placename=work_sheet->querySubObject("Cells(int,int)", i+2,3)->dynamicCall("Value").toString();
            //收货人4
            QString receiver=work_sheet->querySubObject("Cells(int,int)", i+2,4)->dynamicCall("Value").toString();
            //车牌号5
            QString carnumber=work_sheet->querySubObject("Cells(int,int)", i+2,5)->dynamicCall("Value").toString();
            //驾驶员6
            QString dirver=work_sheet->querySubObject("Cells(int,int)", i+2,7)->dynamicCall("Value").toString();
            //毛重7
            double totalWeight=work_sheet->querySubObject("Cells(int,int)", i+2,7)->dynamicCall("Value").toDouble();
            double carweight=work_sheet->querySubObject("Cells(int,int)", i+2,8)->dynamicCall("Value").toDouble();
            double thingsweight=work_sheet->querySubObject("Cells(int,int)", i+2,9)->dynamicCall("Value").toDouble();
            double price=work_sheet->querySubObject("Cells(int,int)", i+2,10)->dynamicCall("Value").toDouble();

            //票据时间11
            QString ticketTime=work_sheet->querySubObject("Cells(int,int)", i+2,11)->dynamicCall("Value").toDateTime().toString("yyyy-M-d hh:mm:ss");

            //原始时间12
            QString orignalTime=work_sheet->querySubObject("Cells(int,int)", i+2,12)->dynamicCall("Value").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            QString watcher=work_sheet->querySubObject("Cells(int,int)", i+2,13)->dynamicCall("Value").toString();
            //修改时间14
            QString modefytime=work_sheet->querySubObject("Cells(int,int)", i+2,14)->dynamicCall("Value").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            if(modefytime.isEmpty())modefytime="无";
            QString modefier=work_sheet->querySubObject("Cells(int,int)", i+2,15)->dynamicCall("Value").toString();
            QString type=work_sheet->querySubObject("Cells(int,int)", i+2,16)->dynamicCall("Value").toString();
            //备注信息17
            QString otherinformation=work_sheet->querySubObject("Cells(int,int)", i+2,17)->dynamicCall("Value").toString();
            RecordDaoImp dost;
            if(dost.isOneExist(number))//如果已存在，则删除
            {
                dost.deleteRecordInfo(number);
            }
            dost.insertRecordInfo(number,thingtype,placename,receiver,carnumber,dirver,ticketTime,orignalTime,watcher,modefytime,modefier,
                                  totalWeight,carweight,thingsweight,price,otherinformation,type);

        }

        //导入用户=================================================================
        work_sheet = work_book->querySubObject("Sheets(int)", 5);//用户
        used_range = work_sheet->querySubObject("UsedRange");
        rows = used_range->querySubObject("Rows");
        row_number = rows->property("Count").toInt()-1;  //获取行数
        //qDebug()<<"表2有 "<<row_number<<" 个数据";
        if(row_number<0)row_number=0;
        for(int i=0;i<row_number;i++)//多条数据+循环写入
        {
            QString account=work_sheet->querySubObject("Cells(int,int)", i+2, 1)->dynamicCall("Value").toString();
            if(account=="admin"||account.isEmpty())continue;//管理员账号不可以导入
            QString name= work_sheet->querySubObject("Cells(int,int)", i+2, 2)->dynamicCall("Value").toString();
          //  QString time=work_sheet->querySubObject("Cells(int,int)", i+2, 3)->dynamicCall("Value").toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            QString status=work_sheet->querySubObject("Cells(int,int)", i+2,4)->dynamicCall("Value").toString();
            UserDaoImp dp;
            if(dp.isOneExist(account))
                dp.updateUserInfo(account,"123456",name,status);
            else
                dp.insertUserInfo(account,"123456",name,status);

        }


    }

}
