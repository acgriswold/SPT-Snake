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

        background_music = new QMediaPlayer();

        background_music->setMedia(QUrl("qrc:/sound/gameMusic.mp3"));

        playlist = new QMediaPlaylist();
        playlist->addMedia(QUrl("qrc:/sound/gameMusic.mp3"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        background_music->setPlaylist(playlist);
        background_music->setVolume(20);
        background_music->play();

        ui->score_label_2->hide();
        ui->Score_board_p2->hide();

        cnt = 0;
}

Dialog::~Dialog(){
    delete ui;
}

void Dialog::keyPressEvent(QKeyEvent* e){
    if(ui->stackedWidget->currentIndex()==1){
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
            if(cnt==0){
                timer->stop();
                cnt=1;
            }
            else if(cnt==1){
                timer->start();
                cnt=0;
            }
        }
        else if(e->key() == Qt::Key_Escape){
            this->close();
        }
    }

    qDebug() << e->text();
}

void Dialog::step(){
    game->logic();
    ui->Score_board->display(game->current_score());
    ui->Score_board_p2->display(game->current_score_p2());

}

/*button handling*/
void Dialog::on_button_slug_clicked(){
    Mode md;
    if(ui->check_multiplayer->isChecked()){
        md = Multi;
        ui->score_label_2->show();
        ui->Score_board_p2->show();
    }
    else if(!ui->check_multiplayer->isChecked()){md = Single;}
    else {endGame();}

    game = new GamePlay(scene, md);
    game->renderGame();

    connect(game, SIGNAL(collision()), this, SLOT(endGame()));
    connect(game, SIGNAL(collision_p2()), this, SLOT(endGame_p2()));
    connect(game, SIGNAL(collision_ssssstale()), this, SLOT(endGame_ssssstale()));

    ui->stackedWidget->setCurrentIndex(1);
    timer->start(250);

}

void Dialog::on_button_worm_clicked(){
    Mode md;
    if(ui->check_multiplayer->isChecked()){
        md = Multi;
        ui->score_label_2->show();
        ui->Score_board_p2->show();
    }
    else if(!ui->check_multiplayer->isChecked()){md = Single;}
    else {endGame();}

    game = new GamePlay(scene, md);
    game->renderGame();

    connect(game, SIGNAL(collision()), this, SLOT(endGame()));
    connect(game, SIGNAL(collision_p2()), this, SLOT(endGame_p2()));
    connect(game, SIGNAL(collision_ssssstale()), this, SLOT(endGame_ssssstale()));

    ui->stackedWidget->setCurrentIndex(1);
    timer->start(100);
}

void Dialog::on_button_python_clicked(){
    Mode md;
    if(ui->check_multiplayer->isChecked()){
        md = Multi;
        ui->score_label_2->show();
        ui->Score_board_p2->show();
    }
    else if(!ui->check_multiplayer->isChecked()){md = Single;}
    else {endGame();}

    game = new GamePlay(scene, md);
    game->renderGame();

    connect(game, SIGNAL(collision()), this, SLOT(endGame()));
    connect(game, SIGNAL(collision_p2()), this, SLOT(endGame_p2()));
    connect(game, SIGNAL(collision_ssssstale()), this, SLOT(endGame_ssssstale()));


    ui->stackedWidget->setCurrentIndex(1);
    timer->start(50);
}

void Dialog::endGame(){
    ui->stackedWidget->setCurrentIndex(0);
    timer->stop();
    QString endMess="Player 1 WON!! Thank you for playing. Do you want to play again?";

    bool close = false;
    if(game->get_md() == Single){endMess="Thank you for playing. Do you want to play again?";}
    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", endMess , QMessageBox::Yes | QMessageBox::No)) {
         qApp->quit();
         QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
    else {
        close = true;
    }
    if(close) this->close();
}


void Dialog::endGame_p2(){
    ui->stackedWidget->setCurrentIndex(0);
    timer->stop();

    bool close = false;
    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Player 2 WON!!! Thank you for playing. Do you want to play again?", QMessageBox::Yes | QMessageBox::No)) {
         qApp->quit();
         QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
    else {
        close = true;
    }
    if(close) this->close();
}

void Dialog::endGame_ssssstale(){
    ui->stackedWidget->setCurrentIndex(0);
    timer->stop();

    bool close = false;
    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "You are all loserssssss.", QMessageBox::Yes | QMessageBox::No)) {
         qApp->quit();
         QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    }
    else {
        close = true;
    }
    if(close) this->close();
}

void Dialog::on_button_slug_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void Dialog::on_button_slug_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
