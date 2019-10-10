#include "printticket.h"
#include <QPrintPreviewDialog>
#include "DataBaseOpration/recorddaoimp.h"
#include <QPainter>
#include "funcation.h"
#include <QDebug>
PrintTicket::PrintTicket(QWidget *parent)
    :QDialog(parent)
{
    number="20180101-0001";
    type="水稳碎石";
    placename="测试场地";
    receiver="习近平";
    carnumber="京A99999";
    dirver="李小龙";
    totalweight=50.42;
    carweight=21.02;
    thingsweight=29.4;
    price=0;
    ticketTime="2018-1-1 00:00:00";
    originalTime="2018-01-01 00:00:00";//按照该格式固定保存时间，可以用在sql语句的比较中
    watcher="马化腾";
    recordflag="正常出单";
    flag_dirver=false;
    flag_receiver=false;
    flag_watcher=true;
}

bool PrintTicket::print()
{
    //1,创建打印机
    QPrinter printer(QPrinter::HighResolution);
    //2,自定义纸张大小
    printer.setPageSize(QPrinter::Custom);//页
    printer.setPaperSize(QSizeF(600,230),QPrinter::Point);//纸张大小
    //3，创建预览窗口
    QPrintPreviewDialog preview(&printer, this);
    preview.setMinimumSize(841,400);//841==100%显示比例

    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreviewSlot(QPrinter*)));
    if(preview.exec ()==QDialog::Accepted)
    {
        getNumberSetting();//刷新流水号
        if(recordflag!="丢失补印")//丢失补印不需要再次写入数据（当然写也写不进去）
        {
            RecordDaoImp op;
            op.insertRecordInfo(number,type,placename,receiver,carnumber,dirver,ticketTime,originalTime,watcher,"无","无",totalweight,carweight,thingsweight,price,otherinformation,recordflag);
        }
    }
    return true;
}

void PrintTicket::printPreviewSlot(QPrinter *printer)
{
    //4，创建画家
    QPainter painter(printer);//继承打印

    //5,参数
    float PPP = readPrinterDpiRate();
    //5,参数
    int Text_WH=120/PPP;
    int Title_WH=180/PPP;
    int explain_WH = 80/PPP;

    char column[10][20]={"品名","单位","毛重","皮重","净重","单价","金额","车号","备注",""};
    //----------------------------------------------
    int border_left = 100/PPP;
    int title_up = 100/PPP;
    //-----------------------------------------------
    int border_up = 510/PPP+title_up;//目前先定420，之后可以根据 上方文字的字号 自动得出距离
    int table_width=4158/PPP;
    int min_margin = 20/PPP; //最小边距，文字距离表格线
    int table_V[4]={(int)(224/PPP),(int)(354/PPP),(int)(280/PPP),(int)(0/PPP)};//水平线间隔
    int table_H[10]={(int)(750/PPP) ,(int)(254/PPP) ,(int)(406/PPP) ,(int)(406/PPP) ,(int)(450/PPP) ,(int)(424/PPP) ,(int)(548/PPP) ,(int)(510/PPP) ,(int)(420/PPP) , (int)(0/PPP)};//竖线间隔距离


    int datePosition=border_left+min_margin; //日期的起始位
    for(int i=0;i<6;i++)
        datePosition+=table_H[i];

    int NO_position = datePosition + table_H[6]+table_H[7]+min_margin;//流水号的起始位置
    //6，开始绘制
    //（1）----------标题“送货通知单”
    //-------------字体
    QFont font("宋体",22);
    painter.setFont(font);
    //-----------------文本
    painter.drawText(QRect(border_left+table_width/2-Title_WH*5/2,title_up,Text_WH*10,300),"送货通知单",QTextOption());

    //（2）----------流水号
    //-------------字体
    QFont font_NO("宋体",9);
    painter.setFont(font_NO);
    //-----------------文本
    painter.drawText(QRect(NO_position,border_up-Text_WH*2-min_margin*2,600,100),number,QTextOption());//"20180210-0008"

    //(3)-----------场地和时间
    //-------------字体
    QFont font_Text("宋体",14);
    painter.setFont(font_Text);

    //-----------------文本
    painter.drawText(QRect(border_left+min_margin,border_up-Text_WH-min_margin,Text_WH*16,Text_WH),"收货单位： "+placename,QTextOption());
    painter.drawText(QRect(datePosition,border_up-Text_WH-min_margin,Text_WH*5,Text_WH),"日期时间：",QTextOption());
    QFont font_date("宋体",12);
    painter.setFont(font_date);
    painter.drawText(QRect(datePosition+Text_WH*4.5,border_up-Text_WH-min_margin,Text_WH*10,Text_WH),ticketTime,QTextOption());//"2018-2-10 23:12:59"


    //(4)-----------表格信息
    //字体
    //QFont font_Text("宋体",14);
    painter.setFont(font_Text);
    //绘制表格框架
    QPen pen;
    pen.setWidthF(5/PPP);
    painter.setPen(pen);


    //------------------绘制水平线
    int sumV = border_up;
    for(int i=0;i<4;i++)
    {
        painter.drawLine(QPointF(border_left,sumV),QPointF(table_width+border_left,sumV));
        sumV+=table_V[i];
    }
    int sumH=border_left;
    int Y_1 =border_up+table_V[0]/2-Text_WH/2; //居中调节后，第一行文字所在的实际位置
    //------------------绘制竖直线
    for(int i =0;i<10;i++)
    {

        if(i!=9)//最后一竖线，不需要添加文字
            painter.drawText(QRect(sumH+table_H[i]/2-Text_WH,Y_1,240,Text_WH),column[i],QTextOption());

        if(i==0||i==9)//表格的左右边界竖线
        {
            //V1
            painter.drawLine(QPointF(sumH,border_up),QPointF(sumH,sumV));
        }
        else
        {
            //V2 ~ V9
            painter.drawLine(QPointF(sumH,border_up),QPointF(sumH,sumV-table_V[2]));
        }

        sumH+=table_H[i];
    }

    //(5)第二行文字
    //  QString totalWeight,truckWeight,thingsWeight,price,totalMoney,truckNumber,tips,things_BIG,accepter,driver,watcher;

    int Y_2 =border_up+table_V[0]+table_V[1]/2-Text_WH/2;//居中调节后第二行文字所在的位置

    //水稳碎石
    int sumHHH=border_left;
    //painter.drawText(QRect(sumHHH+table_H[0]/2-Text_WH*2,Y_2,480,Text_WH),"水稳碎石",QTextOption());
    painter.drawText(QRect(sumHHH+table_H[0]/2-Text_WH*strlen(type.toStdString().c_str())/6,Y_2,480,Text_WH),type,QTextOption());

    //吨
    sumHHH+=table_H[0];
    painter.drawText(QRect(sumHHH+table_H[1]/2-Text_WH/2,Y_2,480,Text_WH),"吨",QTextOption());
    // qDebug()<<"吨"<<strlen("吨");//3

    //毛重
    sumHHH+=table_H[1];
    painter.drawText(QRect(sumHHH+table_H[2]/2-Text_WH*strlen(QString::number(totalweight).toStdString().c_str())/4,Y_2,480,Text_WH),QString::number(totalweight),QTextOption());

    //皮重
    sumHHH+=table_H[2];
    painter.drawText(QRect(sumHHH+table_H[3]/2-Text_WH*strlen(QString::number(carweight).toStdString().c_str())/4,Y_2,480,Text_WH),QString::number(carweight),QTextOption());
    //净重
    sumHHH+=table_H[3];
    painter.drawText(QRect(sumHHH+table_H[4]/2-Text_WH*strlen(QString::number(thingsweight).toStdString().c_str())/4,Y_2,480,Text_WH),QString::number(thingsweight),QTextOption());
    //单价
    sumHHH+=table_H[4];
    painter.drawText(QRect(sumHHH+table_H[5]/2-Text_WH*strlen(QString::number(price).toStdString().c_str())/4,Y_2,480,Text_WH),QString::number(price),QTextOption());

    //金额
    sumHHH+=table_H[5];
    QString money=QString::number(price*thingsweight);
    painter.drawText(QRect(sumHHH+table_H[6]/2-Text_WH*strlen(money.toStdString().c_str())/4,Y_2,480,Text_WH),money,QTextOption());
    //车牌号
    sumHHH+=table_H[6];
    int carnum_W=getTextRectWidth(carnumber,font_Text);//车牌号内容总长度
    painter.drawText(QRect(sumHHH+table_H[7]/2-carnum_W/PPP/2,Y_2,carnum_W+100,Text_WH),carnumber,QTextOption());
    qDebug()<<carnumber.length();
    //备注
    QFont font_other("宋体",10);
    painter.setFont(font_other);
    sumHHH+=table_H[7];
    int other_W=getTextRectWidth(otherinformation,font_other);//备注内容总长度
    int other_H=getTextRectHeight(otherinformation,font_other);//备注内容总高度
    int Y_other =border_up+table_V[0]+table_V[1]/2;
    painter.drawText(QRect(sumHHH+table_H[8]/2-other_W/PPP/2,Y_other-other_H/PPP/2,other_W+100,other_H),otherinformation,QTextOption());//+100是因为pdf打印时，\n也占用了一定的宽度
    //qDebug()<<"Other:"<<other_W<<other_H;


    painter.setFont(font_Text);
    //（6）第三行文字
    int Y_3 = border_up+table_V[0]+table_V[1]+table_V[2]/2-Text_WH/2;//居中调节后第三行文字所在的位置
    //净重大写：
    QString Bigcn="净重大写： "+number_Transfer_BigChinese(thingsweight);
    painter.drawText(QRect(border_left+min_margin,Y_3,table_width-2*min_margin,Text_WH),Bigcn,QTextOption());


    //（7）底端文字
    int Y_4 =  border_up+table_V[0]+table_V[1]+table_V[2]+min_margin*3;//
    //收货人:
    if(flag_receiver)
        painter.drawText(QRect(border_left+min_margin,Y_4,8*Text_WH,Text_WH),"收货人："+receiver,QTextOption());
    else
        painter.drawText(QRect(border_left+min_margin,Y_4,8*Text_WH,Text_WH),"收货人：",QTextOption());
    //驾驶员:
    if(flag_dirver)
        painter.drawText(QRect(border_left+table_width/2-Title_WH*5/2,Y_4,8*Text_WH,Text_WH),"驾驶员："+dirver,QTextOption());
    else
        painter.drawText(QRect(border_left+table_width/2-Title_WH*5/2,Y_4,8*Text_WH,Text_WH),"驾驶员：",QTextOption());
    //过磅员:
    if(flag_watcher)
        painter.drawText(QRect(datePosition+Text_WH*4.5,Y_4,8*Text_WH,Text_WH),"过磅员："+watcher,QTextOption());
    else
        painter.drawText(QRect(datePosition+Text_WH*4.5,Y_4,8*Text_WH,Text_WH),"过磅员：",QTextOption());
    //(8)右侧票据说明文字
    QFont font_explain("宋体",9);
    painter.setFont(font_explain);
    painter.drawText(QRect(border_left+table_width+min_margin*2+Text_WH*0,border_up+min_margin,explain_WH,explain_WH*12),QString("第一联/存根/白").split("", QString::SkipEmptyParts).join("\n"),QTextOption());
    painter.drawText(QRect(border_left+table_width+min_margin*2+Text_WH*1,border_up+min_margin,explain_WH,explain_WH*12),QString("第二联/结算/粉").split("", QString::SkipEmptyParts).join("\n"),QTextOption());
    painter.drawText(QRect(border_left+table_width+min_margin*2+Text_WH*2,border_up+min_margin,explain_WH,explain_WH*12),QString("第三联/客户/蓝").split("", QString::SkipEmptyParts).join("\n"),QTextOption());
    painter.drawText(QRect(border_left+table_width+min_margin*2+Text_WH*3,border_up+min_margin,explain_WH,explain_WH*12),QString("第四联/运输/黄").split("", QString::SkipEmptyParts).join("\n"),QTextOption());

    painter.end();


}

