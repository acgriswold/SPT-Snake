#include "fruit.h"

fruit::fruit(){
    int startX = 0;
    int startY = 0;

    setPos(startX, startY);

    Fruitbrush.setTexture(QPixmap(":/fruit.png").scaledToWidth(10, Qt::SmoothTransformation));
}

QRectF fruit::boundingRect() const{
    return QRect(0, 0, 10, 10);

}

void fruit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QRectF rect = boundingRect();

    painter->fillRect(rect, Fruitbrush);
}

void fruit::advance(int phase){
    if(!phase) return;

}
