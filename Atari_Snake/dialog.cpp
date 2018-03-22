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

        game = new GamePlay(scene);
        game->renderGame();

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), scene, SLOT(advance()));

        QTimer *logic_timer = new QTimer(this);
        connect(logic_timer, SIGNAL(timeout()), this, SLOT(step()));
        logic_timer->start(500);
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

    qDebug() << e->text();
}

void Dialog::step(){
    game->logic();
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
