#ifndef SNAKE_H
#define SNAKE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "snakebody.h"

enum Direction{Left, Right, Up, Down};

class Snake : public QGraphicsItem
{
public:
    Snake();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void rotateCW();
    void rotateCCW();

    void setDir(Direction dir);

protected:
    void advance(int phase);

private:
    qreal speed;
    Direction dir;
    QBrush brush;
    SnakeBody body[];
};

#endif // SNAKE_H
