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

        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(step()));
}

Dialog::~Dialog(){
    delete ui;
}

void Dialog::keyPressEvent(QKeyEvent* e){
    if(e->key() == Qt::Key_A){
        game->proposeDir(Left, 1);
    }
    else if(e->key() == Qt::Key_D){
        game->proposeDir(Right, 1);
    }
    else if(e->key() == Qt::Key_W){
        game->proposeDir(Up, 1);
    }
    else if(e->key() == Qt::Key_S){
        game->proposeDir(Down, 1);
    }
    else if(e->key() == Qt::Key_J){
        game->proposeDir(Left, 2);
    }
    else if(e->key() == Qt::Key_L){
        game->proposeDir(Right, 2);
    }
    else if(e->key() == Qt::Key_I){
        game->proposeDir(Up, 2);
    }
    else if(e->key() == Qt::Key_K){
        game->proposeDir(Down, 2);
    }
    else if(e->key() == Qt::Key_P){
        game->add_part();
    }

    qDebug() << e->text();
}

void Dialog::step(){
    game->logic();
}

/*button handling*/
void Dialog::on_button_slug_clicked(){
    Mode md;
    if(ui->check_multiplayer->isChecked()){md = Multi;}
    else if(!ui->check_multiplayer->isChecked()){md = Single;}
    else {endGame();}

    game = new GamePlay(scene, md);
    game->renderGame();

    connect(game, SIGNAL(collision()), this, SLOT(endGame()));

    ui->stackedWidget->setCurrentIndex(1);
    timer->start(250);
}

void Dialog::on_button_worm_clicked(){
    Mode md;
    if(ui->check_multiplayer->isChecked()){md = Multi;}
    else if(!ui->check_multiplayer->isChecked()){md = Single;}
    else {endGame();}

    game = new GamePlay(scene, md);
    game->renderGame();

    connect(game, SIGNAL(collision()), this, SLOT(endGame()));

    ui->stackedWidget->setCurrentIndex(1);
    timer->start(100);
}

void Dialog::on_button_python_clicked(){
    Mode md;
    if(ui->check_multiplayer->isChecked()){md = Multi;}
    else if(!ui->check_multiplayer->isChecked()){md = Single;}
    else {endGame();}

    game = new GamePlay(scene, md);
    game->renderGame();

    connect(game, SIGNAL(collision()), this, SLOT(endGame()));

    ui->stackedWidget->setCurrentIndex(1);
    timer->start(50);
}

void Dialog::endGame(){
    ui->stackedWidget->setCurrentIndex(0);
    timer->stop();

    bool close = false;
    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Thank you for playing. Do you want to play again?", QMessageBox::Yes | QMessageBox::No)) {
         qApp->quit();
         QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
    else {
        close = true;
    }
    if(close) this->close();
}
