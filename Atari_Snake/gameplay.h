#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "fruit.h"
#include "snake.h"
#include <QGraphicsScene>

class GamePlay
{
public:
    GamePlay(QGraphicsScene *scene);

    void renderSnake();
    void renderFruit();

    void proposeDir(Direction dir);
    void logic();


private:
    QGraphicsScene *scene;
    Snake *snake;
    fruit *Fruit;
    void DoCollision();
};

#endif // GAMEPLAY_H
