#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "snake.h"
#include <QGraphicsScene>

class GamePlay
{
public:
    GamePlay(QGraphicsScene *scene);

    void renderSnake();

    void proposeDir(Direction dir);
    void logic();


private:
    QGraphicsScene *scene;
    Snake *snake;
    void DoCollision();
};

#endif // GAMEPLAY_H
