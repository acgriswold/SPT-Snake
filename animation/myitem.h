#ifndef MYITEM_H
#define MYITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>


class MyItem : public QGraphicsItem
{
public:
    MyItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void rotateCW();
    void rotateCCW();

protected:
    void advance(int phase);

private:
    qreal angle;
    qreal speed;
    void DoCollision();
};

#endif // MYITEM_H
