#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "HomePage/homepagewindow.h"
#include "AnalzyPage/ANALZYPAGE.h"
#include "AddPage/addpagewindow.h"
#include "UserPage/userpage.h"
//#include "Quality_inspection_reportPage/qualitypage.h"
#include <QDockWidget>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Init_connect();
    void Init_button();
    void Init_Info();
public slots:
    void slot_quitButton();
    //创建哥功能界面
    void create_HomePageWindow();
    void create_AnalzyPageWindow_V2();
    void create_AddPageWindow();
    void create_UserPageWindow();
    void create_QualityPageWindow();
private:
   QLabel* toolbar_Label_pic;
   QLabel* background_Label_pic;
   QLabel* Logo_Label_pic;
   QVBoxLayout* ly_V_tool;

   QVBoxLayout* btn_layout;
   QPushButton* homePage_Button;
   QPushButton* analzePage_Button;
   QPushButton* addDataPage_Button;
   QPushButton* quitPage_Button;

   QPushButton* userpage_Button;
   QPushButton* quality_Button;

   HomePageWindow* HomeWindow;
   //AnalzyPageWindow* AnalzyWindow;
   AddPageWindow* Addwindow;
   UserPage*      Usermanagerwindow;
   //QualityPage* QualityWindow;
   ANALZYPAGE* AnalzyWindow;

   //主界面构成
   QDockWidget* DockWindow;//左侧工具条
   QWidget* UserWindow; //右侧
   QHBoxLayout* ly_H_main;
   //标志
    unsigned char Page_flag;
    QString account;
    QString password;
    QString username;
    QString user_status;
    void getUserInfo_ini_File();
    //显示用户信息
    QLabel* lb_account;//展示账号
    QLabel* lb_name;//身份
    QLabel* lb_status;//身份
    QVBoxLayout* layoutV_label;

    int screenWidth;//屏幕宽度
    int screenHeight;//屏幕高度

};

#endif // MAINWINDOW_H
