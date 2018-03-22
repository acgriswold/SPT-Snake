#include "snake.h"
#include <QDebug>

Snake::Snake(){
    //random start rotation
    dir = Up;

    //set speed
    speed = 20;

    //random start position
    int startX = 0;
    int startY = 0;

    setPos(startX, startY);

    //initialize brush
    brush.setTexture(QPixmap(":/snake_head_up.png").scaledToWidth(40, Qt::SmoothTransformation));
}

QRectF Snake::boundingRect() const{
    return QRect(0, 0, 40, 40);
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QRectF rect = boundingRect();

    painter->fillRect(rect, brush);
}

void Snake::advance(int phase){
    if(!phase) return;

    if(dir == Up){
        brush.setTexture(QPixmap(":/snake_head_up.png").scaledToWidth(40, Qt::SmoothTransformation));
        setPos(mapToParent(0,-speed));
    }
    else if(dir == Right){
        setPos(mapToParent(speed, 0));
        brush.setTexture(QPixmap(":/snake_head_right.png").scaledToWidth(40, Qt::SmoothTransformation));
    }
    else if(dir == Down){
        setPos(mapToParent(0,speed));
        brush.setTexture(QPixmap(":/snake_head_down.png").scaledToWidth(40, Qt::SmoothTransformation));
    }
    else if(dir == Left){
        brush.setTexture(QPixmap(":/snake_head_left.png").scaledToWidth(40, Qt::SmoothTransformation));
        setPos(mapToParent(-speed, 0));
    }

}

void Snake::setDir(Direction dir){
    this->dir = dir;
}

