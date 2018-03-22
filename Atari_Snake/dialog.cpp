#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);

        ui->graphicsView->setRenderHint(QPainter::Antialiasing);
        //scene->setSceneRect(-150, -150, 300, 300);
        scene->setSceneRect(-650, -290, 1300, 600);
        QPen mypen = QPen(Qt::gray);

        QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
        QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
        QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
        QLineF BottomLine(scene->sceneRect().bottomRight(), scene->sceneRect().bottomLeft());

        scene->addLine(TopLine,mypen);
        scene->addLine(LeftLine,mypen);
        scene->addLine(RightLine,mypen);
        scene->addLine(BottomLine,mypen);

        game = new GamePlay(scene);
        game->renderSnake();
        game->renderFruit();


        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    }

    Dialog::~Dialog(){
        delete ui;
    }

    void Dialog::keyPressEvent(QKeyEvent* e){
        if(e->key() == Qt::Key_A){
            game->proposeDir(Left);
        }
        else if(e->key() == Qt::Key_D){
            game->proposeDir(Right);
        }
        else if(e->key() == Qt::Key_W){
            game->proposeDir(Up);
        }
        else if(e->key() == Qt::Key_S){
            game->proposeDir(Down);
        }
        /*switch(currentDir){

            case(Up):
                if(e->key() == Qt::Key_D){snake->rotateCW(); currentDir = Right;}
                else if(e->key() == Qt::Key_A){snake->rotateCCW(); currentDir = Left;}
            break;
            case(Right):
                if(e->key() == Qt::Key_W){snake->rotateCCW(); currentDir = Up;}
                else if(e->key() == Qt::Key_S){snake->rotateCW(); currentDir = Down;}
            break;
            case(Down):
                if(e->key() == Qt::Key_D){snake->rotateCCW(); currentDir = Right;}
                else if(e->key() == Qt::Key_A){snake->rotateCW(); currentDir = Left;}
            break;
            case(Left):
                if(e->key() == Qt::Key_W){snake->rotateCW(); currentDir = Up;}
                else if(e->key() == Qt::Key_S){snake->rotateCCW(); currentDir = Down;}
            break;

        }*/

        qDebug() << e->text();
    }

/*button handling*/
    void Dialog::on_button_slug_clicked(){
        ui->stackedWidget->setCurrentIndex(1);
        timer->start(250);
    }

    void Dialog::on_button_worm_clicked(){
        ui->stackedWidget->setCurrentIndex(1);
        timer->start(200);
    }

    void Dialog::on_button_python_clicked(){
        ui->stackedWidget->setCurrentIndex(1);
        timer->start(50);
    }
