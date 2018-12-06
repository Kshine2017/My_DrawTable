#include "mainwindow.h"
#include <QApplication>
#include "loginwidget.h"
#if 0
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    LoginWidgett login;//(&w);
    if(login.exec() == QDialog::Accepted)
    {

    w.show();
    return a.exec();
    }
    return 0;
}
#elif 1
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setWindowIcon(QIcon("exe.ico"));

    LoginWidgett login;//(&w);
    if(login.exec() == QDialog::Accepted)
    {
    MainWindow w;
    w.show();
    return a.exec();
    }
    return 0;
}
#endif
