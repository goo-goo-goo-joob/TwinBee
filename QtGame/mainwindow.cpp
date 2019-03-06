#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Game.h"
#include "observer.h"
#include "bulletgen.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Game& game = Game::Instance();
    this->setFixedSize(game.width(),game.height());
    Notifer::Instance().Subscribe(this);
    QPixmap bkgnd("images/back.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
//    this->centralWidget()->setStyleSheet(
//             "background-image:url(\"images/Bee.png\"); background-position: center;" );
//    this->setStyleSheet("background-image: url(images/Bee.png); "
//                                    "background-position: top left; "
//                                    "background-repeat: repeat-xy;");
      shootID = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
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
        game.bee->right = true;
        break;

    case Qt::Key_Left:
        game.bee->left = true;
        break;

    case Qt::Key_Down:
        game.bee->down = true;
        break;

    case Qt::Key_Space:
       //if(!event->isAutoRepeat()){
            BulletGen& gen = BulletGen::Instance();
            gen.prev = gen.on;
            gen.on = true;
            gen.Update(Notifer::Instance());
        //}
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
        game.bee->right = false;
        break;

    case Qt::Key_Left:
        game.bee->left = false;
        break;

    case Qt::Key_Down:
        game.bee->down = false;
        break;

    case Qt::Key_Space:
        BulletGen& gen = BulletGen::Instance();
        //if(!event->isAutoRepeat()){
            gen.on = false;
        //}
        break;
    }
    game.bee->Move();
}
