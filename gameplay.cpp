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
    this->renderFruit();
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

void GamePlay::renderSnake(){
    int ItemCount = 1;
    for(int i = 0; i< ItemCount; i++){
        Snake *item = new Snake();
        snake = item;
        scene->addItem(snake);

    }

}

void GamePlay::renderFruit(){
    QBrush fruitbrush;
    fruitbrush.setTexture(QPixmap(":/fruit.png").scaledToWidth(10, Qt::SmoothTransformation));
    QGraphicsEllipseItem *apple=new QGraphicsEllipseItem(
    QRect(qrand()%((640+1)+650)-650,qrand()%((300+1)+290)-290,10,10));
    apple->setPen(QPen(Qt::transparent));
    apple->setBrush(fruitbrush);
    _fruit = apple;
    scene->addItem(apple);



    /*fruit *apple=new fruit();
    _fruit=apple;
    scene->addItem(apple);*/


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
        //colliding fruit
        else if(scene->collidingItems(snake)[0]->type() == 4){
            qDebug() << "fruit!";
            scene->removeItem(_fruit);
            renderFruit();

        }
        //colliding self
        else if(scene->collidingItems(snake)[0]->type() == 65536){qDebug() << "_self!";}
    }

}
