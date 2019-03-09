#include <QCoreApplication>
#include <iostream>
#include <QSettings>
#include <QVariant>
#include <QString>
#include <QDialog>
#include <QPushButton>
#include "Game.h"
#include "mainwindow.h"
#include <QApplication>
#include "Initialization.h"
#include <ctime>

class QPaintEvent;
using namespace std;
void newGame(){

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand((unsigned int)time(NULL));//helps to generate random coords of objects
    QDialog *dialog = new QDialog;
    dialog->setWindowTitle("Set game");
    QPushButton *button = new QPushButton("New game", dialog);
    dialog->connect(button, SIGNAL(clicked()), this, SLOT(show()));
    dialog->show();

    Initialization& ini = Initialization::Instance();
    ini.Init("settings.ini");
    Game& game = Game::Instance();
    MainWindow w;
    w.show();
    return a.exec();
}
