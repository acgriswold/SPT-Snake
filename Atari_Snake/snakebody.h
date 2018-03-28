#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <vector>

enum Direction{Left, Right, Up, Down};

class SnakeBody : public QGraphicsItem
{
public:
    SnakeBody();
    ~SnakeBody();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void set_tail();
    int get_x();
    int get_y();
protected:
    void advance(int phase);

private:
    QBrush brush;

    bool tail;
    int pivot;
};

#endif // SNAKEBODY_H
