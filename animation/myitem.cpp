#include "myitem.h"

MyItem::MyItem(){
    //random start rotation
    angle = 0;//(qrand()%3);
    setRotation(angle);

    //set speed
    speed = 20;

    //random start position
    int startX = 0;
    int startY = 0;

    /*if((qrand() % 1)){
        startX = (qrand() % 100);
        startY = (qrand() % 100);
    }
    else{
        startX = (qrand() % -100);
        startY = (qrand() % -100);
    }*/

    setPos(mapToParent(startX, startY));
}

QRectF MyItem::boundingRect() const{
    return QRect(0, 0, 20, 20);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QRectF rect = boundingRect();
    QBrush brush(Qt::gray);

    //basic collision detection

    if(scene()->collidingItems(this).isEmpty()){
        //no collision
        brush.setColor(Qt::green);
    }
    else{
        //collision
        brush.setColor(Qt::red);
        //Set the position
        DoCollision();
    }

    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}

void MyItem::advance(int phase){
    if(!phase) return;

    QPointF location = this->pos();

    setPos(mapToParent(0,-(speed)));
}

void MyItem::DoCollision(){
    //get a new position

    //change the angle with a little randomness
    /*if((qrand()%1)){
        setRotation(rotation()+(180+(qrand()%10)));
    }
    else{
        setRotation(rotation()+(180+(qrand()%-10)));
    }

    //see if the new position exceedes limits
    QPointF newpoint = mapToParent(-(boundingRect().width()), -(boundingRect().width() + 2));

    if(!scene()->sceneRect().contains(newpoint)){
        //move into the bounds
        newpoint = mapToParent(0,0);
    }
    else{
        //set position
        setPos(newpoint);
    }*/
}

void MyItem::rotateCW(){
    angle+=90;
    if(angle>=360) angle=0;

    setRotation(angle);
}
void MyItem::rotateCCW(){
    angle-=90;
    if(angle<=0) angle=360;

    setRotation(angle);
}
