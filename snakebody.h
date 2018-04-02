#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <vector>
#include <QString>

enum Direction{Left, Right, Up, Down, LeftUp, LeftDown, RightUp, RightDown};

class SnakeBody : public QGraphicsItem
{
public:
    SnakeBody(int plyr);
    ~SnakeBody();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void set_dir(Direction dr);
    Direction get_dir();

    int get_x();
    int get_y();
protected:
    void advance(int phase);

private:
    QBrush brush;

    QString body_left;
    QString body_right;
    QString body_up;
    QString body_down;
    QString pivot_up_left;
    QString pivot_up_right;
    QString pivot_down_left;
    QString pivot_down_right;

    Direction prevdir;
    Direction dir;
};

#endif // SNAKEBODY_H
