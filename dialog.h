#ifndef DIALOG_H
#define DIALOG_H

#include "gameplay.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>

#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void keyPressEvent(QKeyEvent* e);

private slots:
    void on_button_slug_clicked();
    void on_button_worm_clicked();
    void on_button_python_clicked();
    void step();
    void endGame();

    void on_Score_board_overflow();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    GamePlay *game;
    QMediaPlayer *background_music;
    QMediaPlaylist *playlist;
};

#endif // DIALOG_H
