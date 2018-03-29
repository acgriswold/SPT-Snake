#include "gameplay.h"
#include <QDebug>

GamePlay::GamePlay(QGraphicsScene *scene, Mode md){
    this->scene = scene;
    mode = md;
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

void GamePlay::renderFruit(){
    int ItemCount = 1;
    for(int i = 0; i< ItemCount; i++){
        QBrush fruitbrush;
        fruitbrush.setTexture(QPixmap(":/fruit.png").scaledToWidth(10, Qt::SmoothTransformation));

        QGraphicsEllipseItem *apple=new QGraphicsEllipseItem(QRect(qrand()%((640+1)+650)-650,qrand()%((300+1)+290)-290,10,10));

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

void GamePlay::DoCollision(){
    if(mode == Single){
        //basic collision detection
        if(!scene->collidingItems(snake).isEmpty()){
            qDebug() << "collision!!" << scene->collidingItems(snake)[0]->type();

            /*Player 1*/
            //collding border
            if(scene->collidingItems(snake)[0]->type() == 6){
                qDebug() << "_wall!";
                emit collision();
            }
            //colliding self
            else if(scene->collidingItems(snake)[0]->type() == 65536){
                qDebug() << "_self!";
                emit collision();
            }
            //colliding fruit
            else if(scene->collidingItems(snake)[0]->type() == 4){qDebug() << "fruit!";
                qDebug() << "fruit!";
                scene->removeItem(fruit);
                renderFruit();
                snake->add_body(1,scene);
            }
        }
    }

    else if(mode == Multi){
        //basic collision detection
        if(!scene->collidingItems(snake).isEmpty()){
            qDebug() << "collision!!" << scene->collidingItems(snake)[0]->type();

            /*Player 1*/
            //collding border
            if(scene->collidingItems(snake)[0]->type() == 6){
                qDebug() << "_wall!";
                emit collision();
            }
            //colliding self
            else if(scene->collidingItems(snake)[0]->type() == 65536){
                qDebug() << "_self!";
                emit collision();
            }
            //colliding fruit
            else if(scene->collidingItems(snake)[0]->type() == 4){qDebug() << "fruit!";
                qDebug() << "fruit!";
                scene->removeItem(fruit);
                renderFruit();
                snake->add_body(1,scene);
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
                scene->removeItem(fruit);
                renderFruit();
                snake_p2->add_body(1,scene);
            }
        }
    }

}
