#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "gamecontroller.h"

class SnakeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SnakeWindow(QWidget *parent = nullptr);
    ~SnakeWindow();
private slots:
    void adjustViewSize();
    void newGame();
    void gameHelp();
    void about();

private:
    void createActions();
    void createMenus();

    void initScene();
    void initSceneBackground();


    QGraphicsScene *scene;
    QGraphicsView *view;

    GameController *game;

    QAction *newGameAction;
    QAction *pauseAction;
    QAction *resumeAction;
    QAction *exitAction;
    QAction *gameHelpAction;
    QAction *aboutAction;
    QAction *aboutQtAction;





signals:

public slots:
};

#endif // SNAKEWINDOW_H
