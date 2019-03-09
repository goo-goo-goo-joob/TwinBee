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
#include <QMessageBox>

class QPaintEvent;
using namespace std;
void newGame(){

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand((unsigned int)time(NULL));//helps to generate random coords of objects

    Initialization& ini = Initialization::Instance();

    QString saved = "settings_saved.ini";
    if (QFile::exists(saved)){

        QMessageBox msgBox;
        msgBox.setText("Load saved game?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        if (msgBox.exec() == QMessageBox::Ok){
            ini.Init("settings_saved.ini");;
        }else{
            ini.Init("settings.ini");
        }
    }
    else {
        ini.Init("settings.ini");
    }

    Game& game = Game::Instance();
    MainWindow w;
    w.show();
    return a.exec();
}
