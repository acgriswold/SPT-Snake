#include "gameplay.h"
#include <QDebug>

GamePlay::GamePlay(QGraphicsScene *scene){
    this->scene = scene;
}

void GamePlay::logic(){
    DoCollision();
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
    }
    else{

    }

}
