#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
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
    score->setGeometry(QRect(10,45,200,20));
    score->setStyleSheet("QLabel {color : white; }");
    score->setFont( f);
    lifes = new QLabel(this);
    lifes->setFrameStyle(QFrame::Sunken);
    lifes->setGeometry(QRect(10,25,200,20));
    lifes->setStyleSheet("QLabel {color : white; }");
    lifes->setFont( f);

    QFont f1( "Arial", 30, QFont::Bold);
    over = new QLabel(this);
    over->setFrameStyle(QFrame::Sunken);
    over->setGeometry(QRect(game.width()*0.36,game.height()/2,220,30));
    over->setStyleSheet("QLabel {color : white; }");
    over->setFont( f1);

    AboutAct = new QAction(tr("&About"), this);
    connect(AboutAct, SIGNAL(triggered()), this, SLOT(About()));

    SaveAct = new QAction(tr("&Save"), this);
    SaveAct->setShortcuts(QKeySequence::Save);
    SaveAct->setStatusTip(tr("Save a game"));
    connect(SaveAct, SIGNAL(triggered()), this, SLOT(Save()));

    NewAct = new QAction(tr("&New game"), this);
    NewAct->setShortcuts(QKeySequence::New);
    NewAct->setStatusTip(tr("Set a new game"));
    connect(NewAct, SIGNAL(triggered()), this, SLOT(newGame()));

    HelpMenu = new QMenu();
    HelpMenu = menuBar()->addMenu(tr("&Help"));
    HelpMenu->addAction(AboutAct);
    HelpMenu = menuBar()->addMenu(tr("&Game"));
    HelpMenu->addAction(SaveAct);
    HelpMenu->addAction(NewAct);
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
    if(game.play() && game.bee->Lifes())
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

void MainWindow::About(){
    QMessageBox::about(this, tr("About"),
                       tr("The Game rules:\nSpace - shoot\nLeft arrow - move left\n"
                          "Right arrow - move right\nUp arrow - move up\nDown arrow - move down\n"));
}

void MainWindow::Save(){
    Game& game = Game::Instance();
    game.Save();
}

void MainWindow::newGame(){
    Game& game = Game::Instance();
    game.box.clear();
    game.setLevel1();
    game.score(0);
    game.bee->Lifes(3);
    game.play(true);
    over -> setText(QString("Level 1"));
}
