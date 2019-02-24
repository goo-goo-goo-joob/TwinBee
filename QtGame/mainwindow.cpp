#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Game.h"
#include "observer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Game& game = Game::Instance();
    this->setFixedSize(game.width(),game.height());
    Notifer::Instance().Subscribe(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Game& game = Game::Instance();
    game.Draw(this);
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    Game& game = Game::Instance();
    switch(event->key()){

        case Qt::Key_Up:
            game.bee->up = true;
            break;

        case Qt::Key_Right:
            game.bee->right=true;
            break;

        case Qt::Key_Left:
            game.bee->left=true;
            break;

        case Qt::Key_Down:
            game.bee->down = true;
            break;

        case Qt::Key_Space:
            GameItem* item = static_cast<GameItem*>(new FlyingObj());
            game.items.push_back(item);
            break;
        }

        game.bee->Move();
        update();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){

    Game& game = Game::Instance();
    switch(event->key()){

        case Qt::Key_Up:
            game.bee->up = false;
            break;

        case Qt::Key_Right:
            game.bee->right=false;
            break;

        case Qt::Key_Left:
            game.bee->left=false;
            break;

        case Qt::Key_Down:
            game.bee->down = false;
            break;
        }
    game.bee->Move();

}
