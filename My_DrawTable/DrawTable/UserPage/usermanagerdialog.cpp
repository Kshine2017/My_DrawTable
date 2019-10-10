#include "usermanagerdialog.h"
#include <QDebug>
#include "DataBaseOpration/userdaoimp.h"
#include <QMessageBox>
UserManagerDialog::UserManagerDialog(QWidget *parent, const QString &account) : QDialog(parent)
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

    init_button();
    init_lineEdit();
    lay_all = new QVBoxLayout(this);
    lay_all->addLayout(layH_status);
    lay_all->addLayout(layH_account);
    lay_all->addLayout(layH_pwd);
    lay_all->addLayout(layH_name);

    lay_all->addLayout(layH_btn);

    lay_all->setGeometry(QRect(0,0,640,400));

    //查询用户信息：
    if(account!=NULL)
    {
        UserDaoImp udi;
        QString pwd;
        QString name;
        QString status;
        udi.getUserInfoByAccount(account,pwd,name,status);
        le_account->setText(account);
        le_pwd->setText(pwd);
        le_name->setText(name);
        if(status == "管理用户")
        {
            cmbx_status->clear();
            cmbx_status->insertItem(0,"管理用户");
            le_account->setEnabled(false);
            le_pwd->setEnabled(false);
            le_pwd->setEchoMode(QLineEdit::Password);
            le_name->setEnabled(false);
        }
        cmbx_status->setCurrentText(status);
    }
    else
    {
        qDebug()<<"account ==NULL";
    }

    this->show();
}

UserManagerDialog::~UserManagerDialog()
{
    qDebug()<<"释放用户管理对话界面";
}

void UserManagerDialog::init_button()
{
//    QFont font("宋体",20,75);
    btn_AddUser  =  new QPushButton(this);
    btn_AddUser->setFixedSize(150,40);
    btn_AddUser->setStyleSheet("QPushButton{border-image: url(:/picture/adduser-up.png);}"
                                      "QPushButton:hover{border-image: url(:/picture/adduser-up.png);}"
                                      "QPushButton:pressed{border-image: url(:/picture/adduser-down.png);}");
    btn_AddUser->setFlat(true);
   // btn_AddUser->setGeometry(200,20,150,40);
    connect(btn_AddUser,SIGNAL(clicked()),this,SLOT(slot_addUser()));

    btn_Promote   =  new QPushButton(this);
    btn_Promote->setFixedSize(150,40);
    btn_Promote->setStyleSheet("QPushButton{border-image: url(:/picture/updateinfo-up.png);}"
                                      "QPushButton:hover{border-image: url(:/picture/updateinfo-up.png);}"
                                      "QPushButton:pressed{border-image: url(:/picture/updateinfo-down.png);}");
    btn_Promote->setFlat(true);
    //btn_Promote->setGeometry(200,20,150,40);
    connect(btn_Promote,SIGNAL(clicked()),this,SLOT(slot_updateInfo()));

 // btn_degrade   =  new QPushButton();
    btn_delete   =  new QPushButton(this);
    btn_delete->setFixedSize(150,40);
    btn_delete->setStyleSheet("QPushButton{border-image: url(:/picture/delusr-up.png);}"
                              "QPushButton:hover{border-image: url(:/picture/delusr-up.png);}"
                              "QPushButton:pressed{border-image: url(:/picture/delusr-down.png);}");
    btn_delete->setFlat(true);
 // btn_delete->setGeometry(200,20,150,40);
    connect(btn_delete,SIGNAL(clicked()),this,SLOT(slot_deleteUser()));

    layH_btn = new QHBoxLayout();
    layH_btn->addWidget(btn_AddUser);
    layH_btn->addWidget(btn_Promote);
//  layH_btn->addWidget(btn_degrade);
    layH_btn->addWidget(btn_delete);
   layH_btn ->setGeometry(QRect(30,300,600,80));

}
/*

    QLabel* lb_account; QLineEdit* le_account;      QHBoxLayout* layH_account;
    QLabel* lb_pwd;     QLineEdit* le_pwd;          QHBoxLayout* layH_pwd;
    QLabel* lb_name;    QLineEdit* le_name;         QHBoxLayout* layH_name;
    QLabel* lb_status;  QComboBox* cmbx_status;     QHBoxLayout* layH_status;
*/
void UserManagerDialog::init_lineEdit()
{
    QFont font("宋体",20,75);
    lb_account= new QLabel();lb_account->setText("账号：");lb_account->setFont(font);
    le_account = new QLineEdit();le_account->setFont(font);
    layH_account= new QHBoxLayout();
   layH_account->addSpacing(80);
   layH_account->addWidget(lb_account);
   layH_account->addWidget(le_account);
   layH_account->addSpacing(80);


    lb_pwd= new QLabel();lb_pwd->setText("密码：");lb_pwd->setFont(font);
    le_pwd = new QLineEdit();le_pwd->setFont(font);
    layH_pwd= new QHBoxLayout();
    layH_pwd->addSpacing(80);
    layH_pwd->addWidget(lb_pwd);
    layH_pwd->addWidget(le_pwd);
    layH_pwd->addSpacing(80);

    lb_name= new QLabel();lb_name->setText("姓名：");lb_name->setFont(font);
    le_name = new QLineEdit();le_name->setFont(font);
    layH_name= new QHBoxLayout();
    layH_name->addSpacing(80);
    layH_name->addWidget(lb_name);
    layH_name->addWidget(le_name);
    layH_name->addSpacing(80);

    lb_status= new QLabel();lb_status->setText("权限等级：");
    lb_status->setFont(font);
    cmbx_status = new QComboBox();cmbx_status->insertItem(0,"一级用户");cmbx_status->insertItem(1,"二级用户");cmbx_status->insertItem(2,"权限用户");cmbx_status->insertItem(3,"超级用户");
    cmbx_status->setFont(font);
    layH_status= new QHBoxLayout();
    layH_status->addSpacing(80);
    layH_status->addWidget(lb_status);
    layH_status->addWidget(cmbx_status);
    layH_status->addSpacing(80);

}

void UserManagerDialog::slot_addUser()
{
    qDebug()<<"新增用户";
    //--------------输入检测------------------
    if(le_account->text().isEmpty())
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("请输入用户账号！"));
        return;
    }
    if(le_account->text()=="admin")
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("不可新增，修改或者删除 超级管理员 账号！"));
        return;
    }
    if(le_pwd->text().isEmpty())
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("请输入用户密码！"));
        return;
    }
    if(le_name->text().isEmpty())
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("请输入真实姓名！"));
        return;
    }
    //-------------数据查重------------------
    QString account     =       le_account->text();
    QString password    =       le_pwd->text();
    QString name        =       le_name->text();
    QString status      =       cmbx_status->currentText();
    UserDaoImp op;
    if(op.isOneExist(account))
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("已存在该账号，请修改 “账号” 名称！"));
        return;
    }
    bool ret =op.insertUserInfo(account,password,name,status);
    if(!ret)
    {

        QMessageBox::critical(this,QObject::tr("错误"),QObject::tr("用户新增失败！"));
        return;
    }

    QMessageBox::information(this,QObject::tr("成功"),QObject::tr("成功新增用户！"));
    close();
}

void UserManagerDialog::slot_updateInfo()
{
    qDebug()<<"修改用户信息";
    //--------------输入检测------------------
    if(le_account->text().isEmpty())
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("请输入指定的用户账号！"));
        return;
    }
    if(le_account->text()=="admin")
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("不可新增，修改或者删除 超级管理员 账号！"));
        return;
    }
    if(le_pwd->text().isEmpty())
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("请输入修改后的用户密码！"));
        return;
    }
    if(le_name->text().isEmpty())
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("请输入修改后的真实姓名！"));
        return;
    }
    //-------------数据查重------------------
    QString account     =       le_account->text();
    QString password    =       le_pwd->text();
    QString name        =       le_name->text();
    QString status      =       cmbx_status->currentText();
    UserDaoImp op;
    if(!op.isOneExist(account))
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("不存在该账号，无法进行修改，请确认 “账号” 名称！"));
        return;
    }
    //已存在
    bool ret =op.updateUserInfo(account,password,name,status);
    if(!ret)
    {
        QMessageBox::critical(this,QObject::tr("错误"),QObject::tr("用户信息修改失败！"));
        return;
    }

    QMessageBox::information(this,QObject::tr("成功"),QObject::tr("成功修改用户信息！"));
    close();
}

void UserManagerDialog::slot_deleteUser()
{
    qDebug()<<"删除用户";
    //--------------输入检测------------------
    if(le_account->text().isEmpty())
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("请输入指定的用户账号！"));
        return;
    }
    if(le_account->text()=="admin")
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("不可新增，修改或者删除 超级管理员 账号！"));
        return;
    }
    UserDaoImp op;
    QString account     =       le_account->text();
    if(!op.isOneExist(account))
    {
        QMessageBox::critical(this,QObject::tr("提示！"),QObject::tr("不存在该账号，无法进行删除操作，请确认 “账号” 名称！"));
        return;
    }


    //消息框
    QMessageBox* msg =new QMessageBox(this);
    msg->setText(QString("确定要删除相关用户信息吗？\n    账号：%1").arg(account));
    msg->setWindowTitle("提示框：");
    msg->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msg->button(QMessageBox::Ok)->setText("确  定");
    msg->button(QMessageBox::Cancel)->setText("取  消");
    if(msg->exec() == QMessageBox::Ok)
    {
        op.deleteUserInfo(account);
        QMessageBox::information(this,QObject::tr("成功"),QObject::tr("成功删除用户信息！"));
        close();
    }
    else
    {
        qDebug()<<"已取消 删除命令！";
        close();
    }

}



