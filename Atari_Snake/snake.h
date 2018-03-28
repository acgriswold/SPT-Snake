#ifndef SNAKE_H
#define SNAKE_H

#include "snakebody.h"

class Snake : public QGraphicsItem
{
public:
    Snake(QGraphicsScene *scene);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setDir(Direction dir);

    void movement();

    void add_body(int cnt, QGraphicsScene *scene);
protected:
    void advance(int phase);

private:
    qreal speed;
    Direction dir;
    Direction prevdir;
    QBrush brush;

    SnakeBody *(body[1950]);
    int body_parts;
};

#endif // SNAKE_H
