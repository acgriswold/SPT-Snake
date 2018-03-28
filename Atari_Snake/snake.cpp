#include "snake.h"
#include <QDebug>

Snake::Snake(QGraphicsScene *scene){
    //random start rotation
    dir = Up;
    prevdir = dir;

    //set speed
    speed = 20;

    //random start position
    int startX = 0;
    int startY = 0;

    setPos(startX, startY);

    //initialize brush
    brush.setTexture(QPixmap(":/head_up.png").scaledToWidth(20, Qt::SmoothTransformation));

    body_parts = 0;

    for(int i = 0; i < 2; i++){
        body[i] = new SnakeBody();
        body[i]->setPos(startX, startY+(20*(i+1)));
        scene->addItem(body[i]);
        body_parts++;
    }
}

QRectF Snake::boundingRect() const{
    return QRect(0, 0, 20, 20);
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QRectF rect = boundingRect();

    painter->fillRect(rect, brush);
}

void Snake::advance(int phase){
    if(!phase) return;
}

void Snake::movement(){
    int prevx = this->x();
    int prevy = this->y();

    if(dir == Up && prevdir != Down){
        setPos(mapToParent(0,-speed));
        brush.setTexture(QPixmap(":/head_up.png").scaledToWidth(20, Qt::SmoothTransformation));
    }
    else if(dir == Right && prevdir != Left){
        setPos(mapToParent(speed, 0));
        brush.setTexture(QPixmap(":/head_right.png").scaledToWidth(20, Qt::SmoothTransformation));
    }
    else if(dir == Down && prevdir != Up){
        setPos(mapToParent(0,speed));
        brush.setTexture(QPixmap(":/head_down.png").scaledToWidth(20, Qt::SmoothTransformation));
    }
    else if(dir == Left && prevdir != Right){
        setPos(mapToParent(-speed, 0));
        brush.setTexture(QPixmap(":/head_left.png").scaledToWidth(20, Qt::SmoothTransformation));
    }
    else {
        dir = prevdir;
        this->movement();
    }
    prevdir = dir;

    //dealing with body movement
    for(int i=0; i<body_parts; i++){
        int currentx = body[i]->get_x();
        int currenty = body[i]->get_y();

        body[i]->setPos(prevx, prevy);

        prevx = currentx;
        prevy = currenty;
    }
}

void Snake::add_body(int cnt, QGraphicsScene *scene){
    for(int i = 0; i < cnt; i++){
            body[body_parts] = new SnakeBody();

            body[body_parts]->setPos(body[body_parts-2]->x()-20, body[body_parts-2]->y()-20);
            scene->addItem(body[body_parts]);
            body_parts++;
        }


}

void Snake::setDir(Direction dir){
    this->dir = dir;
}

