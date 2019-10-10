#include "printdialog.h"
#include <QDebug>
#include "DataBaseOpration/recorddaoimp.h"
#include <QMessageBox>
#include "printticket.h"
#include <QDateTime>
#include "funcation.h"
PrintDialog::PrintDialog(const QStringList &str , QWidget *parent)
    :QDialog(parent)
{
    setWindowModality(Qt::WindowModal);
    setAttribute(Qt::WA_DeleteOnClose); //在关闭该窗口时，自主调用析构函数
    setFixedSize(400,400);
    //setWindowIconText("哈哈");
    init_lb_le();
    init_data(str);
    show();
}

PrintDialog::~PrintDialog()
{
    qDebug()<<"释放打印对话框";
}

void PrintDialog::init_lb_le()
{
    //lb_number = new QLabel(this);lb_number->setText("流 水 号：");
//------------------------------------------------------------------
    lb_thingstype = new QLabel(this);lb_thingstype->setText("品    类：");
    lb_placename = new QLabel(this);lb_placename->setText("场地名称：");

    lb_receiver = new QLabel(this);lb_receiver->setText("收 货 人：");
    lb_carnumber = new QLabel(this);lb_carnumber->setText("车 牌 号：");

    lb_dirver = new QLabel(this);lb_dirver->setText("驾 驶 员：");
    lb_totalWeight = new QLabel(this);lb_totalWeight->setText("毛    重：");

    lb_carweight = new QLabel(this);lb_carweight->setText("皮    重：");
    lb_thingsweight = new QLabel(this);lb_thingsweight->setText("净    重：");

    lb_price = new QLabel(this);lb_price->setText("单    价：");
    lb_time = new QLabel(this);lb_time->setText("出单日期：");

    lb_watcher = new QLabel(this);lb_watcher->setText("过 磅 员：");
    lb_type = new QLabel(this);lb_type->setText("单据类型：");

    le_number = new QLineEdit(this);le_number->setEnabled(false);
    //---------------------------------------------------------
    le_thingstype   = new QLineEdit(this);
    le_placename = new QLineEdit(this);
    le_receiver = new QLineEdit(this);
    le_carnumber = new QLineEdit(this);
    le_dirver = new QLineEdit(this);
    le_totalWeight = new QLineEdit(this);connect(le_totalWeight,SIGNAL(editingFinished()),this,SLOT(slot_calculate_weight()));
    le_carweight = new QLineEdit(this);connect(le_carweight,SIGNAL(editingFinished()),this,SLOT(slot_calculate_weight()));
    le_thingsweight = new QLineEdit(this);le_thingsweight->setEnabled(false);
    le_price = new QLineEdit(this);
    le_time = new QLineEdit(this);le_time->setEnabled(false);
    le_watcher = new QLineEdit(this);
    le_type = new QLineEdit(this);le_type->setEnabled(false);


    lh_1 = new QHBoxLayout();lh_1->addWidget(lb_thingstype);lh_1->addWidget(le_thingstype);lh_1->addWidget(lb_placename);lh_1->addWidget(le_placename);
    lh_2 = new QHBoxLayout();lh_2->addWidget(lb_receiver);lh_2->addWidget(le_receiver);lh_2->addWidget(lb_carnumber);lh_2->addWidget(le_carnumber);
    lh_3 = new QHBoxLayout();lh_3->addWidget(lb_dirver);lh_3->addWidget(le_dirver);lh_3->addWidget(lb_totalWeight);lh_3->addWidget(le_totalWeight);
    lh_4 = new QHBoxLayout();lh_4->addWidget(lb_carweight);lh_4->addWidget(le_carweight);lh_4->addWidget(lb_thingsweight);lh_4->addWidget(le_thingsweight);
    lh_5 = new QHBoxLayout();lh_5->addWidget(lb_price);lh_5->addWidget(le_price);lh_5->addWidget(lb_time);lh_5->addWidget(le_time);
    lh_6 = new QHBoxLayout();lh_6->addWidget(lb_watcher);lh_6->addWidget(le_watcher);lh_6->addWidget(lb_type);lh_6->addWidget(le_type);

    //备注
    lb_otherinformation = new QLabel(this);
    lb_otherinformation->setText("备注信息:");
    te_otherinformation = new QTextEdit(this);
    te_otherinformation->setPlaceholderText("建议:(英文,数字,符号算半个汉字)\n每行5个汉字\n最多4行。");


    //按钮
    btn_print = new QPushButton(this);
    btn_print->setFixedSize(150,40);
    btn_print->setStyleSheet(  "QPushButton{border-image: url(:/picture/printBtn-up.png);}"
                                "QPushButton:hover{border-image: url(:/picture/printBtn-up.png);}"
                                "QPushButton:pressed{border-image: url(:/picture/printBtn-down.png);}");
    btn_print->setFlat(true);

    btn_update = new QPushButton(this);
    btn_update->setFixedSize(150,40);
    btn_update->setStyleSheet(  "QPushButton{border-image: url(:/picture/updateBtn-up.png);}"
                                "QPushButton:hover{border-image: url(:/picture/updateBtn-up.png);}"
                                "QPushButton:pressed{border-image: url(:/picture/updateBtn-down.png);}");
    btn_update->setFlat(true);

    btn_delete = new QPushButton(this);
    btn_delete->setFixedSize(150,40);
    btn_delete->setStyleSheet(  "QPushButton{border-image: url(:/picture/deleteBtn-up.png);}"
                                "QPushButton:hover{border-image: url(:/picture/deleteBtn-up.png);}"
                                "QPushButton:pressed{border-image: url(:/picture/deleteBtn-down.png);}");
    btn_delete->setFlat(true);


    connect(btn_delete,SIGNAL(clicked()),this,SLOT(slot_delete()));
    connect(btn_update,SIGNAL(clicked()),this,SLOT(slot_update()));
    connect(btn_print,SIGNAL(clicked()),this,SLOT(slot_print()));

    lv_all=new QVBoxLayout();
    lv_all->addWidget(le_number);
    lv_all->addLayout(lh_1);
    lv_all->addLayout(lh_2);
    lv_all->addLayout(lh_3);
    lv_all->addLayout(lh_4);
    lv_all->addLayout(lh_5);
    lv_all->addLayout(lh_6);
    lv_all->addSpacing(10);
    lv_all->addWidget(lb_otherinformation);
    lv_all->addWidget(te_otherinformation);
    lv_all->addSpacing(30);
    lv_all->addWidget(btn_print);
    lv_all->setAlignment(btn_print,Qt::AlignCenter);
    lv_all->addWidget(btn_update);
    lv_all->setAlignment(btn_update,Qt::AlignCenter);
    lv_all->addWidget(btn_delete);
    lv_all->setAlignment(btn_delete,Qt::AlignCenter);
    lv_all->setGeometry(QRect(20,20,360,360));


        ckb_dirver = new QCheckBox(this);
        ckb_receiver=new QCheckBox(this);
        ckb_watcher=new QCheckBox(this);
        ckb_watcher->setCheckState(Qt::Checked);
        //ckb_dirver->setText("12321321");
        ckb_dirver->setStyleSheet(
                    "QCheckBox {spacing: 0px;}"
                    "QCheckBox::indicator {width: 20px;height: 20px;}"
                    "QCheckBox::indicator:unchecked {image: url(:/picture/unchecked.png);} "
                    "QCheckBox::indicator:checked   {image: url(:/picture/checked.png); }"
                    );

        ckb_receiver->setStyleSheet(
                    "QCheckBox {spacing: 0px;}"
                    "QCheckBox::indicator {width: 20px;height: 20px;}"
                    "QCheckBox::indicator:unchecked {image: url(:/picture/unchecked.png);} "
                    "QCheckBox::indicator:checked   {image: url(:/picture/checked.png); }"
                    );

        ckb_watcher->setStyleSheet(
                    "QCheckBox {spacing: 0px;}"
                    "QCheckBox::indicator {width: 20px;height: 20px;}"
                    "QCheckBox::indicator:unchecked {image: url(:/picture/unchecked.png);} "
                    "QCheckBox::indicator:checked   {image: url(:/picture/checked.png); }"
                    );

        ckb_receiver->setGeometry(lb_receiver->x()-20,lb_receiver->y()-5,30,30);
        ckb_dirver->setGeometry(lb_dirver->x()-20,lb_dirver->y()-5,30,30);
        ckb_watcher->setGeometry(lb_watcher->x()-20,lb_watcher->y()-5,30,30);

}

void PrintDialog::init_data(QStringList str)
{
    le_number->setText(str.at(0));
    le_thingstype->setText(str.at(1));
    le_placename->setText(str.at(2));
    le_receiver->setText(str.at(3));
    le_carnumber->setText(str.at(4));
    le_dirver->setText(str.at(5));
    le_totalWeight->setText(str.at(6));
    le_carweight->setText(str.at(7));
    le_thingsweight->setText(str.at(8));
    le_price->setText(str.at(9));
    le_time->setText(str.at(10));

    le_watcher->setText(str.at(12));
    le_type->setText(str.at(15));
    te_otherinformation->setPlainText(str.at(16));
}

void PrintDialog::slot_delete()
{
    QString number =le_number->text();
    QMessageBox* msg =new QMessageBox(this);
    msg->setText(QString("确定要删除相关的所有信息吗？\n    流水号：%1").arg(number));
    msg->setWindowTitle("提示框：");
    msg->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msg->button(QMessageBox::Ok)->setText("确  定");
    msg->button(QMessageBox::Cancel)->setText("取  消");
    if(msg->exec() == QMessageBox::Ok)
    {

        RecordDaoImp rdi;
        bool ret = rdi.deleteRecordInfo(number);
        if(ret)
        {
            qDebug()<<"提示：删除成功";
            QMessageBox::information(this,tr("提示"),tr("删除成功!"));
            close();
        }
        else
        {
            qDebug()<<"提示：删除失败";
            QMessageBox::critical(this,tr("提示"),tr("删除失败!"));
        }
    }
    else
    {
        return;
    }
}

void PrintDialog::slot_update()
{
    //数据准备
    QString number =le_number->text();
    QString thingstype = le_thingstype->text();
    QString placename =le_placename->text();

    QString receiver = le_receiver->text();
    QString carnumber = le_carnumber->text();
    QString dirver = le_dirver->text();
    double totalWeight = le_totalWeight->text().toDouble();
    double carweight = le_carweight->text().toDouble();
    double thingsweight = le_thingsweight->text().toDouble();
    double price = le_price->text().toDouble();

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");//le_time->text();//创建时间
    QString account;
    QString name;
    QString password;
    QString status;
    getCurrent_UserInfo(account,password,name,status);
   // QString watcher = le_watcher->text();
    QString type ="已被修改";// le_type->text();
    QString otherinformation=te_otherinformation->toPlainText();

    //更新
    RecordDaoImp rdi;
    bool ret = rdi.updateRecordInfo(number,thingstype,placename,receiver,carnumber,dirver,time,name,totalWeight,carweight,thingsweight,price,otherinformation,type);
    if(ret)
    {
        qDebug()<<"提示：修改成功";
        QMessageBox::information(this,tr("提示"),tr("修改成功!"));
        close();
    }
    else
    {
        qDebug()<<"提示：修改失败";
        QMessageBox::critical(this,tr("提示"),tr("修改失败!"));
    }

}
void PrintDialog::slot_print()
{
    PrintTicket pt(this);
    //数据准备
    pt.number   =le_number->text();
    pt.type     =le_thingstype->text();
    pt.placename =le_placename->text();
    pt.receiver = le_receiver->text();
    pt.carnumber = le_carnumber->text();
    pt.dirver = le_dirver->text();
    pt.totalweight = le_totalWeight->text().toDouble();
    pt.carweight = le_carweight->text().toDouble();
    pt.thingsweight = le_thingsweight->text().toDouble();
    pt.price = le_price->text().toDouble();
    pt.ticketTime = le_time->text();//创建时间

    pt.watcher = le_watcher->text();
    pt.recordflag="丢失补印";
    pt.otherinformation=te_otherinformation->toPlainText();
    if(ckb_dirver->checkState()==Qt::Checked)
        pt.flag_dirver=true;
    else
        pt.flag_dirver=false;
    if(ckb_receiver->checkState()==Qt::Checked)
        pt.flag_receiver=true;
    else
        pt.flag_receiver=false;
    if(ckb_watcher->checkState()==Qt::Checked)
        pt.flag_watcher=true;
    else
        pt.flag_watcher=false;
    pt.print();
}

void PrintDialog::slot_calculate_weight()
{
    if(le_totalWeight->text().isEmpty())le_totalWeight->setText("0");
    if(le_carweight->text().isEmpty())le_carweight->setText("0");

    double TW =le_totalWeight->text().toDouble();
    double CW =le_carweight->text().toDouble();
    le_thingsweight->setText(QString::number(TW-CW));
}


