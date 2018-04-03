#include "gameplay.h"
#include <QDebug>

int score=0;
int score_p2=0;

GamePlay::GamePlay(QGraphicsScene *scene, Mode md){
    this->scene = scene;
    mode = md;

    bite = new QMediaPlayer();
    bite->setMedia(QUrl("qrc:/sound/bite.mp3"));

    explosion = new QMediaPlayer();
    explosion->setMedia(QUrl("qrc:/sound/explosion.mp3"));
    explosion->setVolume(5);
}

GamePlay::~GamePlay(){
    delete snake;
}

void GamePlay::logic(){
    snake->movement();
    if(mode == Multi){snake_p2->movement();}
    DoCollision();
}

void GamePlay::renderGame(){
    if(mode == Single){
        this->renderSnake(1);
    }
    else if(mode == Multi){
        this->renderSnake(2);
    }
    this->renderBorder();
    this->renderFruit();
    this->current_score();
}

void GamePlay::renderBorder(){
    QPen mypen = QPen(Qt::gray);

    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomRight(), scene->sceneRect().bottomLeft());

    scene->addLine(TopLine,mypen);
    scene->addLine(LeftLine,mypen);
    scene->addLine(RightLine,mypen);
    scene->addLine(BottomLine,mypen);
}

void GamePlay::renderSnake(int ItemCount){
    for(int i = 0; i < ItemCount; i++){
        if(i == 0){
            Snake *item = new Snake(scene, 1);
            snake = item;
            scene->addItem(snake);
        }
        else if (i == 1){
            Snake *item = new Snake(scene, 2);
            snake_p2 = item;
            scene->addItem(snake_p2);
        }
    }
}

int GamePlay::current_score(){
    return score;
}

int GamePlay::current_score_p2(){
    return score_p2;
}

void GamePlay::renderFruit(){
    int ItemCount = 1;
    int highx=620/20;
    int lowx=-620/20;
    int highy=280/20;
    int lowy=-280/20;

    int randx=qrand()%((highx+1)-lowx)+lowx;
    int randy=qrand()%((highy+1)-lowy)+lowy;

    for(int i = 0; i< ItemCount; i++){
        QBrush fruitbrush;
        fruitbrush.setTexture(QPixmap(":/new_apple.png").scaledToWidth(20, Qt::SmoothTransformation));

        QGraphicsEllipseItem *apple=new QGraphicsEllipseItem(QRect(randx*20,randy*20,20,20));

        apple->setPen(QPen(Qt::transparent));
        apple->setBrush(fruitbrush);
        fruit = apple;
        scene->addItem(apple);
    }
}

void GamePlay::proposeDir(Direction dir, int plyr){
    if(plyr == 1){
        snake->setDir(dir);
    }
    else if(plyr == 2){
        if(mode == Multi){
            snake_p2->setDir(dir);
        }
    }
}

void GamePlay::add_part(){
    snake->add_body(1, scene);
    if(mode == Multi){snake_p2->add_body(1, scene);}
}

Mode GamePlay::get_md()
{
    return mode;
}


void GamePlay::DoCollision(){
    if(mode == Single){
        //basic collision detection
        if(!scene->collidingItems(snake).isEmpty()){
            qDebug() << "collision!!" << scene->collidingItems(snake)[0]->type();

            /*Player 1*/
            //collding border
            if(scene->collidingItems(snake)[0]->type() == 6){
                explosion->play();
                qDebug() << "_wall!";
                emit collision();
            }
            //colliding self
            else if(scene->collidingItems(snake)[0]->type() == 65536){
                explosion->play();
                qDebug() << "_self!";
                emit collision();
            }
            //colliding fruit
            else if(scene->collidingItems(snake)[0]->type() == 4){qDebug() << "fruit!";
                qDebug() << "fruit!";
                bite->play();
                scene->removeItem(fruit);
                renderFruit();
                snake->add_body(1,scene);
                score++;
                qDebug()<<score;
            }
        }
    }

    else if(mode == Multi){
        //basic collision detection
        if(!scene->collidingItems(snake).isEmpty() && !scene->collidingItems(snake_p2).isEmpty()){
            if((scene->collidingItems(snake)[0]->type() == snake_p2->type() && scene->collidingItems(snake_p2)[0]->type() == snake->type()) || (scene->collidingItems(snake)[0]->type() == 6 && scene->collidingItems(snake_p2)[0]->type() == 6)){
                if(score > score_p2){
                    emit collision();
                }
                else if(score < score_p2){
                    emit collision_p2();
                }
                else{
                    emit collision_ssssstale();
                }
            }
        }
        else if(!scene->collidingItems(snake).isEmpty()){
            qDebug() << "collision!!" << scene->collidingItems(snake)[0]->type();

            /*Player 1*/
            //collding border
            if(scene->collidingItems(snake)[0]->type() == 6){
                qDebug() << "_wall!";
                emit collision_p2();
            }
            //colliding self
            else if(scene->collidingItems(snake)[0]->type() == 65536){
                qDebug() << "_self!";
                emit collision_p2();
            }
            //colliding fruit
            else if(scene->collidingItems(snake)[0]->type() == 4){qDebug() << "fruit!";
                qDebug() << "fruit!";
                bite->play();
                scene->removeItem(fruit);
                renderFruit();
                snake->add_body(1,scene);
                score++;
            }
        }
        else if(!scene->collidingItems(snake_p2).isEmpty()){
            /*Player 2*/
            //collding border
            if(scene->collidingItems(snake_p2)[0]->type() == 6){
                qDebug() << "_wall!";
                emit collision();
            }
            //colliding self
            else if(scene->collidingItems(snake_p2)[0]->type() == 65536){
                qDebug() << "_self!";
                emit collision();
            }
            //colliding fruit
            else if(scene->collidingItems(snake_p2)[0]->type() == 4){qDebug() << "fruit!";
                qDebug() << "fruit!";
                bite->play();
                scene->removeItem(fruit);
                renderFruit();
                snake_p2->add_body(1,scene);
                score_p2++;
            }
        }
    }

}
