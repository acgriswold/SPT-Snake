#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "snake.h"
#include <QGraphicsScene>
#include <QObject>
#include <QMediaPlayer>

enum Mode{Single, Multi};

class GamePlay : public QObject
{
    Q_OBJECT
public:
    GamePlay(QGraphicsScene *scene, Mode md);
    ~GamePlay();

    void renderGame();
    void renderBorder();
    void renderSnake(int ItemCount);
    void renderFruit();

    void proposeDir(Direction dir, int plyr);
    void logic();
    void add_part();

signals:
    void collision();

private:
    QGraphicsScene *scene;
    Snake *snake;
    Snake *snake_p2;
    QGraphicsEllipseItem *fruit;
    void DoCollision();
    Mode mode;
    QMediaPlayer *bite;
};

#endif // GAMEPLAY_H
