#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Game.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Game& game = Game::Instance();
    this->setFixedSize(game.width(),game.height());
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

void MainWindow::keyReleaseEvent(QKeyEvent * event)
{
    if( event->key() == Qt::Key_Left )
    {
        Game& game = Game::Instance();
        //MoveGameItems visitor;
        //game.bee->access(visitor);
        game.bee->Move(-5);
        update();
    }
    if( event->key() == Qt::Key_Right )
    {
        Game& game = Game::Instance();
        game.bee->Move(5);
        update();
    }
}
