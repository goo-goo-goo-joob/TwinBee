#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "observer.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Game& game = Game::Instance();
    this->setFixedSize(game.width(),game.height());
    Notifer::Instance().Subscribe(this);
    QPixmap bkgnd("images/back.png");
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
    keysPressed.insert(event->key());
    return;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event){

    keysPressed.remove(event->key());
    return;
}
