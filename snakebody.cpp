#include "snakebody.h"
SnakeBody::SnakeBody(int plyr){
    QString extn = ".png";
    //defining pixmap locations
    body_left = ":/body_left_p";
    body_left.append( QString::number(plyr) );
    body_left.append(extn);
    body_right = ":/body_right_p";
    body_right.append( QString::number(plyr) );
    body_right.append(extn);
    body_up = ":/body_up_p";
    body_up.append( QString::number(plyr) );
    body_up.append(extn);
    body_down = ":/body_down_p";
    body_down.append( QString::number(plyr) );
    body_down.append(extn);
    pivot_up_left = ":/pivot_up_left_p";
    pivot_up_left.append( QString::number(plyr) );
    pivot_up_left.append(extn);
    pivot_up_right = ":/pivot_up_right_p";
    pivot_up_right.append( QString::number(plyr) );
    pivot_up_right.append(extn);
    pivot_down_left = ":/pivot_down_left_p";
    pivot_down_left.append( QString::number(plyr) );
    pivot_down_left.append(extn);
    pivot_down_right = ":/pivot_down_right_p";
    pivot_down_right.append( QString::number(plyr) );
    pivot_down_right.append(extn);

    //initialize brush
    brush.setTexture(QPixmap(body_up).scaledToWidth(20, Qt::SmoothTransformation));
}

SnakeBody::~SnakeBody(){

}

QRectF SnakeBody::boundingRect() const{
    return QRect(0, 0, 20, 20);
}

void SnakeBody::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QRectF rect = boundingRect();

    //dealing with pivots
    if(dir == LeftUp){brush.setTexture(QPixmap(pivot_up_left).scaledToWidth(20, Qt::SmoothTransformation));}
    else if(dir == RightUp){brush.setTexture(QPixmap(pivot_up_right).scaledToWidth(20, Qt::SmoothTransformation));}
    else if(dir == LeftDown){brush.setTexture(QPixmap(pivot_down_left).scaledToWidth(20, Qt::SmoothTransformation));}
    else if(dir == RightDown){brush.setTexture(QPixmap(pivot_down_right).scaledToWidth(20, Qt::SmoothTransformation));}
    //dealing with straights
    else if(dir == Left){brush.setTexture(QPixmap(body_left).scaledToWidth(20, Qt::SmoothTransformation));}
    else if(dir == Right){brush.setTexture(QPixmap(body_right).scaledToWidth(20, Qt::SmoothTransformation));}
    else if(dir == Up){brush.setTexture(QPixmap(body_up).scaledToWidth(20, Qt::SmoothTransformation));}
    else if(dir == Down){brush.setTexture(QPixmap(body_down).scaledToWidth(20, Qt::SmoothTransformation));}

    painter->fillRect(rect, brush);
}

void SnakeBody::advance(int phase){
    if(!phase) return;
}

int SnakeBody::get_x(){
    return this->x();
}

int SnakeBody::get_y(){
    return this->y();
}

Direction SnakeBody::get_dir(){
    return dir;
}

void SnakeBody::set_dir(Direction dr){
    prevdir = dir;
    dir = dr;
}
