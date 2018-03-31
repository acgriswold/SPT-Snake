#include "snake.h"
#include <QDebug>

Snake::Snake(QGraphicsScene *scene, int plyr){
    //random start rotation
    dir = Up;
    prevdir = dir;

    //set speed
    speed = 20;

    player = plyr;


    QString extn = ".png";

    //defining pixmap locations
    head_up = ":/head_up_p";
    head_up.append( QString::number(plyr) );
    head_up.append(extn);
    head_right = ":/head_right_p";
    head_right.append( QString::number(plyr) );
    head_right.append(extn);
    head_left = ":/head_left_p";
    head_left.append( QString::number(plyr) );
    head_left.append(extn);
    head_down = ":/head_down_p";
    head_down.append( QString::number(plyr) );
    head_down.append(extn);

    int startX = 0;
    int startY = 0;

    if(player == 1){
        startX = -300;
        startY = 0;
    }
    else if(player == 2){
        startX = 300;
        startY = 0;
    }

        //initialize brush
        brush.setTexture(QPixmap(head_up).scaledToWidth(20, Qt::SmoothTransformation));
    setPos(startX, startY);


    body_parts = 0;

    for(int i = 0; i < 2; i++){
        body[i] = new SnakeBody(player);
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
    int currentx = this->x();
    int currenty = this->y();

    if(dir == Up && prevdir != Down){

        setPos(mapToParent(0,-speed));
        brush.setTexture(QPixmap(head_up).scaledToWidth(20, Qt::SmoothTransformation));
    }
    else if(dir == Right && prevdir != Left){

        setPos(mapToParent(speed, 0));
        brush.setTexture(QPixmap(head_right).scaledToWidth(20, Qt::SmoothTransformation));
    }
    else if(dir == Down && prevdir != Up){

        setPos(mapToParent(0,speed));
        brush.setTexture(QPixmap(head_down).scaledToWidth(20, Qt::SmoothTransformation));
    }
    else if(dir == Left && prevdir != Right){

        setPos(mapToParent(-speed, 0));
        brush.setTexture(QPixmap(head_left).scaledToWidth(20, Qt::SmoothTransformation));
    }
    else {
        dir = prevdir;
        this->movement();
    }

    prevdir = dir;

    //dealing with body movement
    for(int i=0; i<body_parts; i++){
        int prevx = body[i]->get_x();
        int prevy = body[i]->get_y();


        if(prevx < currentx){body[i]->set_dir(Right);}
        else if(prevx > currentx){body[i]->set_dir(Left);}
        else if(prevy < currenty){body[i]->set_dir(Down);}
        else if(prevy > currenty){body[i]->set_dir(Up);}

        //pivot logic
        if((i < body_parts-1)){
            if(i == 0){
                //first section
                if(body[i]->get_dir() == Left){
                    if(this->dir == Up){body[i]->set_dir(RightUp);}
                    else if(this->dir == Down){body[i]->set_dir(RightDown);}
                }
                else if(body[i]->get_dir() == Right){
                    if(this->dir == Up){body[i]->set_dir(LeftUp);}
                    else if(this->dir == Down){body[i]->set_dir(LeftDown);}
                }
                else if(body[i]->get_dir() == Up){
                    if(this->dir == Left){body[i]->set_dir(LeftDown);}
                    else if(this->dir == Right){body[i]->set_dir(RightDown);}

                }
                else if(body[i]->get_dir() == Down){
                    if(this->dir == Left){body[i]->set_dir(LeftUp);}
                    else if(this->dir == Right){body[i]->set_dir(RightUp);}
                }
            }
            //rest of body
            else if(body[i]->get_dir() == Left){
                if(body[i-1]->get_dir() == Up){body[i]->set_dir(RightUp);}
                else if(body[i-1]->get_dir() == Down){body[i]->set_dir(RightDown);}
            }
            else if(body[i]->get_dir() == Right){
                if(body[i-1]->get_dir() == Up){body[i]->set_dir(LeftUp);}
                else if(body[i-1]->get_dir() == Down){body[i]->set_dir(LeftDown);}
            }
            else if(body[i]->get_dir() == Up){
                if(body[i-1]->get_dir() == Left){body[i]->set_dir(LeftDown);}
                else if(body[i-1]->get_dir() == Right){body[i]->set_dir(RightDown);}

            }
            else if(body[i]->get_dir() == Down){
                if(this->dir == Left){body[i]->set_dir(LeftUp);}
                else if(this->dir == Right){body[i]->set_dir(RightUp);}
            }
        }

        body[i]->setPos(currentx, currenty);

        currentx = prevx;
        currenty = prevy;
    }
}

void Snake::add_body(int cnt, QGraphicsScene *scene){
    for(int i = 0; i < cnt; i++){
        body[body_parts] = new SnakeBody(player);

        //position correction based on place of last two body parts
        if(body[body_parts-1]->get_x() < body[body_parts-2]->get_x()){
            body[body_parts]->setPos(body[body_parts-1]->get_x()+20, body[body_parts-1]->get_y());
        }
        else if(body[body_parts-1]->get_x() > body[body_parts-2]->get_x()){
            body[body_parts]->setPos(body[body_parts-1]->get_x()-20, body[body_parts-1]->get_y());
        }
        else if(body[body_parts-1]->get_y() < body[body_parts-2]->get_y()){
            body[body_parts]->setPos(body[body_parts-1]->get_x(), body[body_parts-1]->get_y()-20);
        }
        else if(body[body_parts-1]->get_y() > body[body_parts-2]->get_y()){
            body[body_parts]->setPos(body[body_parts-1]->get_x(), body[body_parts-1]->get_y()+20);
        }

        scene->addItem(body[body_parts]);
        body_parts++;
    }
}

void Snake::setDir(Direction dir){
    this->dir = dir;
}

