#include "loginwidget.h"
#include<QDebug>
#include <QMovie>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include "UserPage/userdaoimp.h"
#include "funcation.h"
LoginWidgett::LoginWidgett(QWidget *parent)
    :QDialog(parent)
{
    setWindowIcon(QIcon(":/picture/ico.ico"));
    this->setFixedSize(500,360);

    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move(desktop->width()/2 - this->width()/2, desktop->height()/2 - this->height()/2);


      background_pic =new QLabel(this);

#if 0
      background_pic->setGeometry(0,0,500,360);
      QPixmap pix_background(":/picture/homepage_background.png");
      pix_background.scaled(background_pic->size(), Qt::IgnoreAspectRatio);
      background_pic->setScaledContents(true);
      background_pic->setPixmap(pix_background);
#elif 1
      QMovie *mov =new QMovie(":/picture/login.gif");
      background_pic = new QLabel(this);
      background_pic->setGeometry(0,0,500,360);
      background_pic->setMovie(mov);
      mov->setScaledSize(background_pic->size());
      mov->start();
#endif
    //-------------------------
    init_label_Lineedit();
    init_button();

    //-----------------------
    this->show();
    //创建后台管理员
    init_create_administrator();
}

LoginWidgett::~LoginWidgett()
{
    qDebug()<<"销毁登陆窗口";
}

void LoginWidgett::init_label_Lineedit()
{
    lb_title =new QLabel(this);
    lb_title->setFont(QFont("宋体",30,75));
    lb_title ->setText("Kshine2018");
    lb_title->setGeometry(140,100,260,60);

    lb_account = new QLabel(this);
    lb_pwd = new QLabel(this);
    lb_account->setText("账号：");
    lb_pwd->setText("密码：");

    le_account = new QLineEdit(this);
    le_account->setClearButtonEnabled(true);
    le_pwd = new QLineEdit(this);
    le_pwd->setClearButtonEnabled(true);

    ly_account = new QHBoxLayout;
    ly_pwd = new QHBoxLayout;

    ly_account->addWidget(lb_account);
    ly_account->addWidget(le_account);

    ly_pwd->addWidget(lb_pwd);
    ly_pwd->addWidget(le_pwd);

    ly_account->setGeometry(QRect(100,200,300,30));
    ly_pwd->setGeometry(QRect(100,230,300,30));


    QString account;
    QString password;
    QString username;
    QString user_status;
    getCurrent_UserInfo(account,password,username,user_status);
    le_account->setText(account);

}

void LoginWidgett::init_button()
{
    btn_load= new QPushButton(this);
    btn_quit= new QPushButton(this);
    btn_regist= new QPushButton(this);
    btn_load->setText("登录");
    btn_quit->setText("退出");
    btn_regist->setText("注册");

    ly_btnH = new QHBoxLayout;
    ly_btnH->addWidget(btn_load);
    ly_btnH->addWidget(btn_quit);
    ly_btnH->setGeometry(QRect(135,260,268,30));

    connect(btn_load,SIGNAL(clicked()),this,SLOT(slot_load()));
    connect(btn_quit,SIGNAL(clicked()),this,SLOT(slot_quit()));
    connect(btn_regist,SIGNAL(clicked()),this,SLOT(slot_reg()));
}

void LoginWidgett::init_create_administrator()
{
    UserDaoImp op;
    op.insertUserInfo_admin();
}

void LoginWidgett::slot_load()
{
    qDebug()<<"-------尝试登陆-------";
    QString account=le_account->text();
    QString password=le_pwd->text();
//----输入检测------
    if(account=="")//账号为空
    {
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("请输入用户账号！"));
        return;
    }
    qDebug()<<"(1)已输入账号！";
    if(password=="")//密码为空
    {
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("请输入登陆密码！"));
        return;
    }
    qDebug()<<"(2)已输入密码！";

//----判断是否存在---
    UserDaoImp op;
    if(!op.isOneExist(account))
    {
        qDebug()<<"(3)该账号:"<<account<<" 未被注册！";
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("该账号未被注册！请检查是否输入错误。"));
        return;
    }
    qDebug()<<"(3)已确认该账号！";

//---密码是否正确----
    if(!op.check_account_password(account,password))
    {
        qDebug()<<"(4)密码:"<<account<<" 错误！";
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("密码错误！"));
        return;
    }
    qDebug()<<"(4)已确认登陆密码！";

//---获取用户姓名和身份
    QString pwd,name, status;
    op.getUserInfoByAccount(account,pwd,name,status);//根据账号获取 密码，姓名，身份
    qDebug()<<account<<pwd<<name<<status;
    saveCurrent_UserInfo(account,pwd,name,status);
    QDialog::accept();

}

void LoginWidgett::slot_quit()
{
    QDialog::reject();
}

void LoginWidgett::slot_reg()
{
    regW =new RegistWidget(this);
}
