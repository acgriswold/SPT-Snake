#include "gameplay.h"
#include <QDebug>

GamePlay::GamePlay(QGraphicsScene *scene){
    this->scene = scene;
}

GamePlay::~GamePlay(){
    delete snake;
}

void GamePlay::logic(){
    snake->movement();
    DoCollision();
}

void GamePlay::renderGame(){
    this->renderSnake();
    this->renderBorder();
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

    scene->addEllipse(100, 200, 20, 20, mypen);
}

void GamePlay::renderSnake(){
    int ItemCount = 1;
    for(int i = 0; i< ItemCount; i++){
        Snake *item = new Snake();
        snake = item;
        scene->addItem(snake);
    }
}

void GamePlay::proposeDir(Direction dir){
    snake->setDir(dir);
}

void GamePlay::DoCollision(){
    //basic collision detection

    if(scene->collidingItems(snake).isEmpty()){
        //no collision
         qDebug() << "none";
    }
    else{
        qDebug() << "collision!!" << scene->collidingItems(snake)[0]->type();

        //colliding self
        if(scene->collidingItems(snake)[0]->type() == 65536){qDebug() << "_self!";}
        //collding border
        else if(scene->collidingItems(snake)[0]->type() == 6){
            qDebug() << "_wall!";
            emit collision();
        }
        //colliding fruit
        else if(scene->collidingItems(snake)[0]->type() == 4){qDebug() << "fruit!";}
    }

}
