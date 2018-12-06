#include "funcation.h"
#include <QStringList>
#include <QDebug>

#include <QFile>
#include <QCoreApplication>
#include <QSettings>


void Delay_MSec_Suspend(unsigned int msec)
{
    QTime _Timer = QTime::currentTime();
    QTime _NowTimer;
    do{
              _NowTimer=QTime::currentTime();
    }while (_Timer.msecsTo(_NowTimer)<=msec);
}
void Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < _Timer )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

const QString getYMDhms()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy-M-d hh:mm:ss");
    return current_date;
}



/*
测试用
*/
const QString getNumber()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyyMMdd-");
    return current_date;
}
/*
使用配置文件，记录每一天的编辑情况
*/
const QString getNumberSetting()
{
    //按月分组，每天为成员 ，当日最大流水号作为数据。
    /*
    [Group201802]
    Day21 = 8
    Day22 = 10
    */
    //1读取当前  年月 日
     QDateTime   current_date_time =QDateTime::currentDateTime();
    QString current_YearMonth =current_date_time.toString("yyyyMM");
    QString current_Day =current_date_time.toString("dd");

    //2读取文件中的数据
    QString iniFilePath = "./config/liushuihao.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);

    QString YMD=current_YearMonth+"/Day"+current_Day;
    int number = settings.value(YMD).toInt(); //接收当天的流水号数值，无则返回 0

    number++; //在旧的基础上+1
    //3更新数据
    settings.setValue(YMD,number);
    //4返回流水号
    char strnum[20]="";
    sprintf(strnum,"-%04d",number);
    return current_date_time.toString("yyyyMMdd")+strnum;
}
const QString getNumberSetting(const QDateTime&  current_date_time)
{
    //按月分组，每天为成员 ，当日最大流水号作为数据。
    /*
    [Group201802]
    Day21 = 8
    Day22 = 10
    */
    //1读取当前  年月 日
    // QDateTime   current_date_time =QDateTime::currentDateTime();
    QString current_YearMonth =current_date_time.toString("yyyyMM");
    QString current_Day =current_date_time.toString("dd");

    //2读取文件中的数据
    QString iniFilePath = "./config/liushuihao.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);

    QString YMD=current_YearMonth+"/Day"+current_Day;
    int number = settings.value(YMD).toInt(); //接收当天的流水号数值，无则返回 0

    number++; //在旧的基础上+1
    //3更新数据
    settings.setValue(YMD,number);
    //4返回流水号
    char strnum[20]="";
    sprintf(strnum,"-%04d",number);
    return current_date_time.toString("yyyyMMdd")+strnum;
}

//只是用在切换页面的时候

const QString readNumberSetting(const QDateTime &current_date_time)
{
    QString current_YearMonth =current_date_time.toString("yyyyMM");
    QString current_Day =current_date_time.toString("dd");

    //2读取文件中的数据
    QString iniFilePath = "./config/liushuihao.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);

    QString YMD=current_YearMonth+"/Day"+current_Day;
    int number = settings.value(YMD).toInt(); //接收当天的流水号数值，无则返回 0
    if(number==0)number=1;//从1开始
    //3更新数据
    settings.setValue(YMD,number);
    //4返回流水号
    char strnum[20]="";
    sprintf(strnum,"-%04d",number);//保证从1开始
    return current_date_time.toString("yyyyMMdd")+strnum;

}
const QString readNumberSetting()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_YearMonth =current_date_time.toString("yyyyMM");
    QString current_Day =current_date_time.toString("dd");

    //2读取文件中的数据
    QString iniFilePath = "./config/liushuihao.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);

    QString YMD=current_YearMonth+"/Day"+current_Day;
    int number = settings.value(YMD).toInt(); //接收当天的流水号数值，无则返回 0
    if(number==0)number=1;//从1开始
    //3更新数据
    settings.setValue(YMD,number);
    //4返回流水号
    char strnum[20]="";
    sprintf(strnum,"-%04d",number);//保证从1开始
    return current_date_time.toString("yyyyMMdd")+strnum;
}
void saveCurrent_UserInfo(QString& account, QString& password, QString& name, QString& status)
{
    //Q_UNUSED(password);
    QString iniFilePath = "./config/current_user.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    settings.setValue("账号：",account);
    settings.setValue("密码：",password);
    settings.setValue("真实姓名：",name);
    settings.setValue("身份标志：",status);
}

void getCurrent_UserInfo(QString &account, QString &password, QString &name, QString& status)
{
    //Q_UNUSED(password);
    QString iniFilePath = "./config/current_user.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    account=settings.value("账号：").toString();
    password=settings.value("密码：").toString();
    name=settings.value("真实姓名：").toString();
    status=settings.value("身份标志：").toString();
}
/*
根据日期不同 ，自主控制流水号的增加。
缺陷：之后添加收据，序号会从0 重新开始。导致重复。这就要求 在临时添加单号的时候，需要访问数据库，方法比较麻烦。
*/
const QString getNumberChanging()
 {
     //1、获取绝对路径（弃用）
//         QString applicationFilePath;
//         applicationFilePath = QCoreApplication::applicationFilePath();
//         qDebug()<<"applicationFilePath"<<applicationFilePath;

     //2、读取文件中的日期 和 当前的流水号（考虑到切换页面，或者关闭软件 会重新创建对象，流水号 也需要保存在文件里）
     QFile file("./numberFile.txt");

     QString date;//存储日期
     int nnnum=1; //存储流水号
     if(file.open(QIODevice::ReadOnly)) //只读、二进制方式
     {
             //read的返回值为QByteArray，当赋值给QString变量类型时进行自动转换
             //以下语句也可以写成name = file.read(10);
             date = QString(file.read(strlen("20180223-")));
             file.read(reinterpret_cast<char*>(&nnnum), sizeof(nnnum));
             file.close();
     }

     //判断是否和当前日期一样
     QDateTime current_date_time =QDateTime::currentDateTime();
     QString current_date =current_date_time.toString("yyyyMMdd-");


     //一样，则流水号 自增1
     if(current_date == date)
         nnnum++;
     //不一样，则 流水号 清零
    else
         nnnum=1;

     //保存当前日期 和 流水号
     if (file.open(QIODevice::WriteOnly)) //打开方式：可读、二进制方式
        {
            //按二进制写入时，须进行类型转换，这也是QFile使用上比较麻烦的地方
            file.write(current_date.toStdString().c_str()); //参数为char*，须转换

            file.write(reinterpret_cast<char*>(&nnnum), sizeof(nnnum));


            file.close();
        }


//     qDebug() << date;
//     qDebug() << nnnum;

     //返回
     char strnum[10]="";
     sprintf(strnum,"%04d",nnnum);
     return current_date+ strnum;


 }




const QString number_Transfer_BigChinese(const double &Fnumber)
{

    if(qAbs(Fnumber)<0.01)   //保留2位小数时，近似看作零的情况
        return "零";


    //判断正负号
    QString numberSign;//存储符号
    if(Fnumber<0)
        numberSign = "（负数）";
   //将数据的绝对值 转换成字符串，如-58 转成 “58.00”
   QString number = QString::number(qAbs(Fnumber),'f',2);//qAbs绝对值 ，保留两位小数
   QString Left_of_Point;//整数部分
   int length =number.length()-3;//整数部分的长度，（精确度为2，去除小数和小数点）
   if(length>12)
   {
        //qDebug()<<"输入的数值超过范围！"
        return "输入的数值超过范围！";
   }

   QStringList numerical_unit   =   {"","拾","佰","仟","万","拾", "佰", "仟", "亿", "拾", "佰", "仟"};
   QStringList numerical_value  =   {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};

   //数数整数低位多少个连零
   int counter_0=0;
   for(int i =length-1;i>=0;i--)
   {
       if((number[i].toLatin1()-'0' )==0) //从个位开始，向高位走
           counter_0++;
       else
           break;

   }
   if(length==1 && counter_0==1) //0.x
       counter_0=0; //不进行过滤

   //1400  0.2

   for(int i=0,flag=1;i<length-counter_0;i++)
   {
        //5     8       1    2   3
        //伍 拾 捌       壹佰 贰拾 叁
       if((number[i].toLatin1()-'0')==0)
       {
           if((flag!=0 && (length-1-i)%4 != 0) || length ==1) //flag！=0  表示前一个数值 不为0
           Left_of_Point+="零"; //后面不用添加 单位
           if((length-1-i)%4 == 0) //如果0处于分段处，后面需添加单位
           Left_of_Point+=numerical_unit[length-1-i];//添加数值单位

           flag =0; //标记

       }
       else
       {
        flag =1;
        Left_of_Point+=numerical_value[number[i].toLatin1()-'0']; //'5'-'0'==5
        Left_of_Point+=numerical_unit[length-1-i];//添加数值单位

       }
   }





    //QString Right_of_Point;//小数点右侧，小数部分(保留两位)  xxxx.yy
    int totalLength = number.length();
    if(number[totalLength-2]=='0'&&number[totalLength-1]=='0')
    {
        QString Bigcn=numberSign+Left_of_Point+"吨";
        return Bigcn;
    }
    else if(number[totalLength-2]!='0'&&number[totalLength-1]=='0')
    {
        QString Bigcn=numberSign+Left_of_Point+"点"+numerical_value[number[totalLength-2].toLatin1()-'0']+"吨";
        return Bigcn;
    }
    else
    {
        QString Bigcn=numberSign+Left_of_Point+"点"+numerical_value[number[totalLength-2].toLatin1()-'0']+numerical_value[number[totalLength-1].toLatin1()-'0']+"吨";
        return Bigcn;
    }


    return "异常情况";
}



void savePrinterConfig(QString &printerName, int Ldpi, int Rdpi)
{

  //  Q_UNUSED(password);
    QString iniFilePath = "./config/printerConfig.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    settings.setValue("printerName",printerName);
    settings.setValue("Ldpi",Ldpi);
    settings.setValue("Rdpi",Rdpi);

}

void readPrinterName(QString &printerName)
{
    QString     iniFilePath =   "./config/printerConfig.ini";
    QSettings   settings(iniFilePath,QSettings::IniFormat);
    printerName             =   settings.value("printerName").toString();
}

float readPrinterDpiRate()
{
    int Ldpi, Rdpi;
    float defaultDPI=600.0;
    QString     iniFilePath =   "./config/printerConfig.ini";
    QSettings   settings(iniFilePath,QSettings::IniFormat);
    Ldpi             =   settings.value("Ldpi").toInt();
    Rdpi             =   settings.value("Rdpi").toInt();
    if(Ldpi<Rdpi)
        return defaultDPI/Ldpi;
    return defaultDPI/Rdpi;
}

