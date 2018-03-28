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

    /*QBrush mybrush;
    mypen = QPen(Qt::transparent);
    mybrush.setTexture(QPixmap(":/_up.png").scaledToWidth(20, Qt::SmoothTransformation));
    scene->addEllipse(120, 220, 20, 20, mypen, mybrush);*/
}

void GamePlay::renderSnake(){
    int ItemCount = 1;
    for(int i = 0; i< ItemCount; i++){
        Snake *item = new Snake(scene);
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

        //collding border
        if(scene->collidingItems(snake)[0]->type() == 6){
            qDebug() << "_wall!";
            emit collision();
        }
        //colliding self
        else if(scene->collidingItems(snake)[0]->type() == 65536){qDebug() << "_self!";}
        //colliding fruit
        else if(scene->collidingItems(snake)[0]->type() == 4){qDebug() << "fruit!";}
    }
}

void GamePlay::add_part(){
    snake->add_body(1,scene);
}
