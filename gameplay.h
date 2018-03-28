#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "fruit.h"
#include "snake.h"
#include <QGraphicsScene>
#include <QObject>
#include <QWidget>

class GamePlay:public QObject
{
    Q_OBJECT
public:
    GamePlay(QGraphicsScene *scene);
    ~GamePlay();

    void renderGame();
    void renderBorder();
    void renderSnake();
    void renderFruit();

    void proposeDir(Direction dir);
    void logic();

signals:
    void collision();

private:
    QGraphicsScene *scene;
    Snake *snake;
    QGraphicsEllipseItem *_fruit;
    void DoCollision();
};

#endif // GAMEPLAY_H
