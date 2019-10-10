#include "registwidget.h"
#include <Qdebug>
#include <QMessageBox>
#include "DataBaseOpration/userdaoimp.h"
RegistWidget::RegistWidget(QWidget *parent):QDialog(parent)
{
    qDebug()<<"打开用户注册页面";

    setWindowModality(Qt::ApplicationModal);//只能创建一个
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(300,200);

    init_label_lineEdit_btn();


    show();
}

RegistWidget::~RegistWidget()
{
    qDebug()<<"已销毁注册页面";
}

void RegistWidget::init_label_lineEdit_btn()
{
    lb_regist_title =new QLabel();
    lb_account =new QLabel();
    lb_password =new QLabel();
    lb_name =new QLabel();


    lb_regist_title->setFont(QFont("宋体",24,75));
    lb_regist_title->setText("用户注册：");
    lb_account->setText("用户账号：");
    lb_password->setText("登录密码：");
    lb_name->setText("真实姓名：");


    le_account = new QLineEdit();
    le_password = new QLineEdit();
    le_name = new QLineEdit();

    btn_sure = new QPushButton();
    btn_cancel = new QPushButton();
    connect(btn_sure,SIGNAL(clicked()),this,SLOT(slot_btn_sure()));
    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(slot_btn_cancel()));

    btn_sure->setText("注册");
    btn_cancel->setText("取消");

    //--------------------------------
    lyH_account = new QHBoxLayout();
    lyH_password  = new QHBoxLayout();
    lyH_name = new QHBoxLayout();
    lyH_btn = new QHBoxLayout();

    lyH_account->addWidget(lb_account);
    lyH_account->addWidget(le_account);

    lyH_password->addWidget(lb_password);
    lyH_password->addWidget(le_password);

    lyH_name->addWidget(lb_name);
    lyH_name->addWidget(le_name);

    lyH_btn->addWidget(btn_sure);
    lyH_btn->addWidget(btn_cancel);
    //---------------------------------
    lyV_all =new QVBoxLayout(this);
    lyV_all->addWidget(lb_regist_title);
    lyV_all->addSpacing(40);
    lyV_all->addLayout(lyH_account);
    lyV_all->addLayout(lyH_password);
    lyV_all->addLayout(lyH_name);
    lyV_all->addLayout(lyH_btn);

    lyV_all->setGeometry(QRect(0,0,300,200));


}

void RegistWidget::slot_btn_sure()
{
    //--------------输入检测------------------
    if(le_account->text().isEmpty())
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("请输入用户账号！"));
        return;
    }
    if(le_password->text().isEmpty())
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("请输入登录密码！"));
        return;
    }
    if(le_name->text().isEmpty())
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("请输入真实姓名！"));
        return;
    }
    //-------------数据查重------------------
    QString account=le_account->text();
    QString password=le_password->text();
    QString name=le_name->text();
    QString status ="一级用户";
    UserDaoImp op;
    if(op.isOneExist(account))
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("已存在该账号，请重新命名"));
        return;
    }

    //--------------------------------------
    qDebug()<<"点击注册按钮，准备注册";

    bool ret =op.insertUserInfo(account,password,name,status);
    if(!ret)
    {

        QMessageBox::critical(this,QObject::tr("错误！"),QObject::tr("数据写入失败"));
        return;
    }

    QMessageBox::information(this,QObject::tr("注册成功"),QObject::tr("注册成功，请在关闭后尝试登陆登录！"));
    this->close();

    return;

}

void RegistWidget::slot_btn_cancel()
{
    close();
}
