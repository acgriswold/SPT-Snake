#include "snakebody.h"

SnakeBody::SnakeBody(){
    //initialize brush
    brush.setTexture(QPixmap(":/body_up.png").scaledToWidth(20, Qt::SmoothTransformation));
}

SnakeBody::~SnakeBody(){

}

QRectF SnakeBody::boundingRect() const{
    return QRect(0, 0, 20, 20);
}

void SnakeBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QRectF rect = boundingRect();

    painter->fillRect(rect, brush);
}

void SnakeBody::advance(int phase){
    if(!phase) return;
}

void SnakeBody::set_tail(){
    tail = true;
}

int SnakeBody::get_x(){
    return this->x();
}

int SnakeBody::get_y(){
    return this->y();
}
