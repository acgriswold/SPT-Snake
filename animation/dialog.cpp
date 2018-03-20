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
    scene->setSceneRect(-650, -280, 1300, 600);
    QPen mypen = QPen(Qt::red);

    QLineF TopLine(scene->sceneRect().topLeft(), scene->sceneRect().topRight());
    QLineF LeftLine(scene->sceneRect().topLeft(), scene->sceneRect().bottomLeft());
    QLineF RightLine(scene->sceneRect().topRight(), scene->sceneRect().bottomRight());
    QLineF BottomLine(scene->sceneRect().bottomRight(), scene->sceneRect().bottomLeft());

    scene->addLine(TopLine,mypen);
    scene->addLine(LeftLine,mypen);
    scene->addLine(RightLine,mypen);
    scene->addLine(BottomLine,mypen);

    int ItemCount = 1;
    for(int i = 0; i< ItemCount; i++){
        MyItem *item = new MyItem();
        myitem = item;
        scene->addItem(item);
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));
    qDebug() << "Debugged!";
}

Dialog::~Dialog(){
    delete ui;
}

void Dialog::keyPressEvent(QKeyEvent* e){
    if(e->key() == Qt::Key_A){
        myitem->rotateCCW();
    }
    else if(e->key() == Qt::Key_D){
        myitem->rotateCW();
    }
    /*switch(currentDir){

        case(Up):
            if(e->key() == Qt::Key_D){myitem->rotateCW(); currentDir = Right;}
            else if(e->key() == Qt::Key_A){myitem->rotateCCW(); currentDir = Left;}
        break;
        case(Right):
            if(e->key() == Qt::Key_W){myitem->rotateCCW(); currentDir = Up;}
            else if(e->key() == Qt::Key_S){myitem->rotateCW(); currentDir = Down;}
        break;
        case(Down):
            if(e->key() == Qt::Key_D){myitem->rotateCCW(); currentDir = Right;}
            else if(e->key() == Qt::Key_A){myitem->rotateCW(); currentDir = Left;}
        break;
        case(Left):
            if(e->key() == Qt::Key_W){myitem->rotateCW(); currentDir = Up;}
            else if(e->key() == Qt::Key_S){myitem->rotateCCW(); currentDir = Down;}
        break;

    }*/

    qDebug() << e->text();
    /*QMessageBox* box = new QMessageBox();
    box->setWindowTitle(QString("Hello"));
    box->setText(QString("You Pressed: ")+ e->text());
    box->show();*/
}

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
