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
    QFont f( "Arial", 15, QFont::Bold);

    score = new QLabel(this);
    score->setFrameStyle(QFrame::Sunken);
    score->setGeometry(QRect(10,30,200,20));
    score->setStyleSheet("QLabel {color : white; }");
    score->setFont( f);
    lifes = new QLabel(this);
    lifes->setFrameStyle(QFrame::Sunken);
    lifes->setGeometry(QRect(10,10,200,20));
    lifes->setStyleSheet("QLabel {color : white; }");
    lifes->setFont( f);

    QFont f1( "Arial", 30, QFont::Bold);
    over = new QLabel(this);
    over->setFrameStyle(QFrame::Sunken);
    over->setGeometry(QRect(game.width()*0.36,game.height()/2,220,30));
    over->setStyleSheet("QLabel {color : white; }");
    over->setFont( f1);

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
