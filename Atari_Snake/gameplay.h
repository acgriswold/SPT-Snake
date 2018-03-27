#ifndef GAMEPLAY_H
#define GAMEPLAY_H


#include "snake.h"
#include <QGraphicsScene>
#include <QObject>

class GamePlay : public QObject
{
    Q_OBJECT
public:
    GamePlay(QGraphicsScene *scene);
    ~GamePlay();

    void renderGame();
    void renderBorder();
    void renderSnake();

    void proposeDir(Direction dir);
    void logic();

signals:
    void collision();

private:
    QGraphicsScene *scene;
    Snake *snake;
    void DoCollision();
};

#endif // GAMEPLAY_H
