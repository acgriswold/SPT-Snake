#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "snake.h"
#include <QGraphicsScene>
#include <QObject>
#include <QMediaPlayer>
#include <QLCDNumber>

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

    int current_score();


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
    QLCDNumber *score_board;
};

#endif // GAMEPLAY_H
