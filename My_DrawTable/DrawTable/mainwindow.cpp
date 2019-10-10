#include "mainwindow.h"
#include <QDebug>
#include <QMovie>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>
#include "Common/funcation.h"
#include <QPixmap>
#include <QPalette>
#include <QBitmap>
#define MW_WEIGHT 1000
#define MW_HEIGHT 500

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowIcon(QIcon(":/picture/ico.ico"));
    //获取数据
    getUserInfo_ini_File();

    //主窗口设置
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
   // move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    //      setWindowFlags(Qt::FramelessWindowHint);//不可调节大小
    screenWidth= desktop->width();
    screenHeight=desktop->height()-60;
    setFixedSize(1000,500);
    //resize(1000,500);
    //------------------
    Page_flag =0;//初始页面
    //-----------------创建背景--------------------
    DockWindow = new QDockWidget(this); //工具条窗口
    DockWindow->setAutoFillBackground(true);//自动填满背景
    DockWindow->setWindowFlags(Qt::FramelessWindowHint);//不可调节大小
    DockWindow->setFeatures(QDockWidget::NoDockWidgetFeatures);//不可移动
    DockWindow->setFixedWidth(200);

    //用于去除dock的标题栏
    QWidget* lTitleBar = DockWindow->titleBarWidget();
    QWidget* lEmptyWidget = new QWidget();
    DockWindow->setTitleBarWidget(lEmptyWidget);
    delete lTitleBar;

    //停靠窗口dock的背景图片
    QPixmap pix_tool;
    pix_tool.load(":/picture/toolbar.png");
    QPalette bgPalette;
    bgPalette.setBrush(QPalette::Background,pix_tool);
    DockWindow->setPalette(bgPalette);



    UserWindow = new QWidget(this);
    UserWindow->setAutoFillBackground(true);
    UserWindow->setWindowFlags(Qt::FramelessWindowHint);

    //添加一个停靠窗口
    DockWindow->setWidget(UserWindow);
    this->addDockWidget(Qt::LeftDockWidgetArea,DockWindow);

    QMovie *mov =new QMovie(":/picture/backgroundgif.gif");
    background_Label_pic = new QLabel(this);
    background_Label_pic->setGeometry(MW_WEIGHT/4-50,0,MW_WEIGHT/5*4,MW_HEIGHT);
    background_Label_pic->setMovie(mov);
    mov->setScaledSize(background_Label_pic->size());
    mov->start();

    Logo_Label_pic =new QLabel(UserWindow);
    Logo_Label_pic->setFixedSize(32,10);
    QPixmap pix_logo;
    pix_logo.load(":/picture/Kshine.png");
    pix_logo.scaled(Logo_Label_pic->size(), Qt::IgnoreAspectRatio);
    Logo_Label_pic->setScaledContents(true);
    Logo_Label_pic->setPixmap(pix_logo);
    Logo_Label_pic->setGeometry(MW_WEIGHT-40,MW_HEIGHT-15,32,10);

    //工具栏按钮----------------------
    Init_button();
    //绑定信号和槽--------------------
    Init_connect();
    //------------------------------
    Init_Info();
}

MainWindow::~MainWindow()
{

    qDebug()<<"关机，已释放主窗口对象！";
}

/*绑定信号和槽*/
void MainWindow::Init_connect()
{





}

/*按钮*/
void MainWindow::Init_button()
{
    btn_layout =new QVBoxLayout(); //不用继承 否则会爆提示
    //0   一级用户
    //10  二级用户
    //50  权限用户
    //80  超级用户
    //100 管理用户
    QString status1 ="一级用户";
    QString status2 ="二级用户";
    QString status3 ="权限用户";
    QString status4 ="超级用户";
    QString status5 ="管理用户";

//主页是所有人都可以
  if(user_status == status1 ||user_status ==status2 ||user_status ==status3 ||user_status == status4 ||user_status == status5)
    {
    homePage_Button     = new QPushButton(DockWindow);
    connect(homePage_Button,SIGNAL(clicked()),this,SLOT(create_HomePageWindow()));
    homePage_Button->setFlat(true);
    homePage_Button->setFocusPolicy(Qt::TabFocus);
    homePage_Button->setFixedSize(160,30);//图片的固定大小85 32
    homePage_Button->setStyleSheet("QPushButton{border-image: url(:/picture/homepagebtn-up.png);}"
                                   "QPushButton:hover{border-image: url(:/picture/homepagebtn-up.png);}"
                                   "QPushButton:pressed{border-image: url(:/picture/homepagebtn-down.png);}");
    btn_layout->addWidget(homePage_Button);
    }
 // 除了一级用户
  if(user_status ==status2 ||user_status ==status3 ||user_status == status4 ||user_status == status5)
    {
        analzePage_Button   = new QPushButton(DockWindow);
        connect(analzePage_Button,SIGNAL(clicked()),this,SLOT(create_AnalzyPageWindow_V2()));
        analzePage_Button->setFlat(true);
        analzePage_Button->setFocusPolicy(Qt::TabFocus);
        analzePage_Button->setFixedSize(160,30);//图片的固定大小85 32
        analzePage_Button->setStyleSheet("QPushButton{border-image: url(:/picture/analzebtn-up.png);}"
                                         "QPushButton:hover{border-image: url(:/picture/analzebtn-up.png);}"
                                         "QPushButton:pressed{border-image: url(:/picture/analzebtn-down.png);}");
        btn_layout->addWidget(analzePage_Button);
    }
  //权限可以看见三个菜单，超级和和管理原  可以所有
  if(user_status ==status3 ||user_status == status4 ||user_status == status5)
    {
        addDataPage_Button  = new QPushButton(DockWindow);
        connect(addDataPage_Button,SIGNAL(clicked()),this,SLOT(create_AddPageWindow()));
        addDataPage_Button->setFlat(true);
        addDataPage_Button->setFocusPolicy(Qt::TabFocus);
        addDataPage_Button->setFixedSize(160,30);//图片的固定大小85 32
        addDataPage_Button->setStyleSheet("QPushButton{border-image: url(:/picture/addbtn-up.png);}"
                                          "QPushButton:hover{border-image: url(:/picture/addbtn-up.png);}"
                                          "QPushButton:pressed{border-image: url(:/picture/addbtn-down.png);}");
        btn_layout->addWidget(addDataPage_Button);
    }

  //退出按钮 所有人可见
  if(user_status == status1 ||user_status ==status2 ||user_status ==status3 ||user_status == status4 ||user_status == status5)
    {
        quitPage_Button     = new QPushButton(DockWindow);
        connect(quitPage_Button,SIGNAL(clicked()),this,SLOT(slot_quitButton()));
        quitPage_Button->setFlat(true);
        quitPage_Button->setFocusPolicy(Qt::TabFocus);
        quitPage_Button->setFixedSize(160,30);//图片的固定大小85 32
        quitPage_Button->setStyleSheet("QPushButton{border-image: url(:/picture/quitbtn-up.png);}"
                                       "QPushButton:hover{border-image: url(:/picture/quitbtn-up.png);}"
                                       "QPushButton:pressed{border-image: url(:/picture/quitbtn-down.png);}");
        btn_layout->addWidget(quitPage_Button);
    }

  //仅超级和管理员
 if(user_status == status5)
     {
        userpage_Button     = new QPushButton(DockWindow);
        connect(userpage_Button,SIGNAL(clicked()),this,SLOT(create_UserPageWindow()));
        userpage_Button->setFlat(true);
        userpage_Button->setFocusPolicy(Qt::TabFocus);
        userpage_Button->setFixedSize(160,30);//图片的固定大小85 32
        userpage_Button->setStyleSheet("QPushButton{border-image: url(:/picture/userwindow-up.png);}"
                                       "QPushButton:hover{border-image: url(:/picture/userwindow-up.png);}"
                                       "QPushButton:pressed{border-image: url(:/picture/userwindow-down.png);}");
        btn_layout->addWidget(userpage_Button);
    }
#if 0
         //暂定所有
        if(user_status == status5)
            {
               quality_Button     = new QPushButton(DockWindow);
               connect(quality_Button,SIGNAL(clicked()),this,SLOT(create_QualityPageWindow()));
               quality_Button->setFlat(true);
               quality_Button->setFocusPolicy(Qt::TabFocus);
               quality_Button->setFixedSize(160,30);//图片的固定大小85 32
               quality_Button->setStyleSheet("QPushButton{border-image: url(:/picture/Kshine.png);}"
                                              "QPushButton:hover{border-image: url(:/picture/Kshine.png);}"
                                              "QPushButton:pressed{border-image: url(:/picture/Kshine.png);}");
               btn_layout->addWidget(quality_Button);
           }
#endif
    btn_layout->setGeometry(QRect(20,100,185,250));
}

void MainWindow::Init_Info()
{

    lb_account = new QLabel(DockWindow);
    lb_name = new QLabel(DockWindow);
    lb_status = new QLabel(DockWindow);
    //-------------------------
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    lb_account->setPalette(pa);
    lb_name->setPalette(pa);
    lb_status->setPalette(pa);
    //--------------------------
    lb_account->setText("账号："+account);
    lb_name->setText("姓名："+username);
    lb_status->setText("身份："+user_status);
//    if(user_status==0)lb_status->setText("身份：普通用户");
//    else if(user_status==100)lb_status->setText("身份：管理员");
    //------------------------
    layoutV_label = new QVBoxLayout();
    layoutV_label->addWidget(lb_status);
    layoutV_label->addWidget(lb_account);
    layoutV_label->addWidget(lb_name);

    layoutV_label->setGeometry(QRect(30,10,100,40));


}

void MainWindow::slot_quitButton()
{
    Page_flag=100;//可以不写
    this->setCentralWidget(NULL);
    //Delay_MSec_Suspend(1000);//阻塞式延时
    Delay_MSec(1000);//非阻塞式延时
    this->close();
}

void MainWindow::create_HomePageWindow()
{
    //    QMessageBox* msg =new QMessageBox(this);
    //    msg->setText("  欢迎来到首页    ");
    //    msg->setWindowTitle("提示框：");
    //    msg->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);


    //    msg->setStyleSheet(
    //                    "QMessageBox {  "
    //                    "font-family:宋体;font-size:18px;"
    //                    "border-image:url(:/picture/information.jpg);"
    //                    "}"
    //                        );
    //    if(msg->exec() == QMessageBox::Ok)
    //    {
    //---------------------
    if(Page_flag!=1)//如果在别的页面，则创建页面1
    {
        Page_flag=1; //避免重复创建

        HomeWindow =new HomePageWindow(this);
        HomeWindow->setWindowFlags(Qt::FramelessWindowHint);
        this->setCentralWidget(HomeWindow);
    }

    //    }

}

void MainWindow::create_AddPageWindow()
{
    //    QMessageBox* msg =new QMessageBox(this);
    //    msg->setText("  进入增加页面    ");
    //    msg->setWindowTitle("提示框：");
    //   //msg->setStandardButtons(QMessageBox::Ok);
    //    msg->setButtonText(1,"知道了！");
    //    msg->setStyleSheet(
    //                    "QMessageBox {  "
    //                    "font-family:宋体;font-size:18px;"
    //                    "border-image:url(:/picture/information.jpg);"
    //                    "}"
    //                        );
    //    msg->exec();
    if(Page_flag!=3)
    {
        Page_flag=3;
        Addwindow = new AddPageWindow(this);
        Addwindow->setWindowFlags(Qt::FramelessWindowHint);
        this->setCentralWidget(Addwindow);
    }
}

void MainWindow::create_UserPageWindow()
{
    if(Page_flag!=4)
    {
        Page_flag=4;
        Usermanagerwindow = new UserPage(this);
        Usermanagerwindow->setWindowFlags(Qt::FramelessWindowHint);
        this->setCentralWidget(Usermanagerwindow);
    }
}

void MainWindow::create_QualityPageWindow()
{
    if(Page_flag!=5)
    {
        Page_flag=5;
//        QualityWindow = new QualityPage(this);
//        QualityWindow->setWindowFlags(Qt::FramelessWindowHint);
//        this->setCentralWidget(QualityWindow);
    }
}

void MainWindow::create_AnalzyPageWindow_V2()
{
    if(Page_flag!=6)
    {
        Page_flag=6;
        AnalzyWindow =new ANALZYPAGE(this);
        AnalzyWindow->setWindowFlags(Qt::FramelessWindowHint);
        this->setCentralWidget(AnalzyWindow);
    }
}
void MainWindow::getUserInfo_ini_File()
{

    getCurrent_UserInfo(account,password,username,user_status);

}
