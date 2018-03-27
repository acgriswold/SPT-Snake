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
        connect(timer, SIGNAL(timeout()), this, SLOT(step()));

        connect(game, SIGNAL(collision()), this, SLOT(endGame()));
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
