#ifndef FRUIT_H
#define FRUIT_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>

class fruit : public QGraphicsItem
{
public:
    fruit();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    void advance(int phase);
private:

    QBrush Fruitbrush;
};

#endif // FRUIT_H

