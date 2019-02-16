#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Game.h"
class QPaintEvent;

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

void MainWindow::on_pushButton_clicked()
{
    Game& game = Game::Instance();
    game.bee->Move(5);
    update();
}
