#include "snakewindow.h"
#include <QIcon>
#include <qmessagebox.h>
#include "constants.h"
#include <qaction.h>
#include <qmenubar.h>
#include <qapplication.h>
#include <QTimer>
#include <QDebug>
SnakeWindow::SnakeWindow(QWidget *parent) : QMainWindow(parent),
    scene(new QGraphicsScene(this)),
    view(new QGraphicsView(scene, this)),
    game(new GameController(*scene, this))
{
    setAttribute(Qt::WA_DeleteOnClose); //在关闭该窗口时，自主调用析构函数
    setWindowModality(Qt::ApplicationModal);//模态显示
    setCentralWidget(view);
//    resize(600, 600);
    setFixedSize(600, 600);
    setWindowIcon(QIcon(":/picture/snake.ico"));

    createActions();
    createMenus();

    initScene();
    initSceneBackground();

    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
    show();

}

SnakeWindow::~SnakeWindow()
{
    qDebug()<<"释放贪吃蛇";
}


void SnakeWindow::adjustViewSize()
{
    QRect rrr(-105,-105,210,210);
    view->fitInView(rrr, Qt::KeepAspectRatioByExpanding);
}

void SnakeWindow::createActions()
{
    newGameAction = new QAction(tr("&重新开始"), this);
    newGameAction->setShortcuts(QKeySequence::New);
    newGameAction->setStatusTip(tr("开始一个新游戏"));
    connect(newGameAction, &QAction::triggered, this, &SnakeWindow::newGame);

    exitAction = new QAction(tr("&退出"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出游戏"));
    connect(exitAction, &QAction::triggered, this, &SnakeWindow::close);

    pauseAction = new QAction(tr("&暂停"), this);
    pauseAction->setStatusTip(tr("暂停..."));
    connect(pauseAction, &QAction::triggered, game, &GameController::pause);

    resumeAction = new QAction(tr("&恢复"), this);
    resumeAction->setStatusTip(tr("恢复..."));
    connect(resumeAction, &QAction::triggered, game, &GameController::resume);

    gameHelpAction = new QAction(tr("游戏 &帮助"), this);
    gameHelpAction->setShortcut(tr("Ctrl+H"));
    gameHelpAction->setStatusTip(tr("该游戏的帮助"));
    connect(gameHelpAction, &QAction::triggered, this, &SnakeWindow::gameHelp);

    aboutAction = new QAction(tr("&关于"), this);
    aboutAction->setStatusTip(tr("显示该游戏的开发环境"));
    connect(aboutAction, &QAction::triggered, this, &SnakeWindow::about);

    aboutQtAction = new QAction(tr("关于 &Qt"), this);
    aboutQtAction->setStatusTip(tr("显示关于Qt的库"));
    connect(aboutQtAction, &QAction::triggered, qApp, QApplication::aboutQt);
}

void SnakeWindow::createMenus()
{
    QMenu *options = menuBar()->addMenu(tr("&设置"));
    options->addAction(newGameAction);
    options->addSeparator();
    options->addAction(pauseAction);
    options->addAction(resumeAction);
    options->addSeparator();
    options->addAction(exitAction);

    QMenu *help = menuBar()->addMenu(tr("&帮助"));
    help->addAction(gameHelpAction);
    help->addAction(aboutAction);
    help->addAction(aboutQtAction);
}

void SnakeWindow::initScene()
{
    scene->setSceneRect(-100,-100, 200, 200);
}

void SnakeWindow::initSceneBackground()
{
    QPixmap bg(400, 400);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    //p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);
    p.drawImage(QRect(0,0,105,105),QImage(":/picture/snake.ico"));

    view->setBackgroundBrush(QBrush(bg));
}

void SnakeWindow::newGame()
{
    QTimer::singleShot(0, game, SLOT(gameOver()));
}

void SnakeWindow::about()
{
    QMessageBox::about(this, tr("关于这个游戏"), tr("<h2>贪吃蛇</h2>"
        "<p>Copyright &copy China;"
        "<p>该游戏基于 Qt5.13 开发环境. "));
}

void SnakeWindow::gameHelp()
{
    QMessageBox::about(this, tr("帮助"), tr("使用键盘的上下左右控制小🐍吃食物"
        "<p>空格键 - 暂停 & 恢复"));
}
