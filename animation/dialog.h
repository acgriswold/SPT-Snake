#ifndef DIALOG_H
#define DIALOG_H

#include "myitem.h"
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>

#include <QKeyEvent>
#include <QDebug>
#include <QMessageBox>

enum Direction{Left, Right, Up, Down};

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

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    MyItem *myitem;
    int currentDir;

};

#endif // DIALOG_H
