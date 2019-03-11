#pragma once
#include <QMainWindow>
#include <QKeyEvent>
#include "GameItem.h"
#include "observer.h"
#include "Game.h"
#include "bulletgen.h"
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void Update(const Notifer& n) {
        Game& game = Game::Instance();
        if(game.play() && game.bee->Lifes()){
            game.bee->up = keysPressed.contains(Qt::Key_Up);
            game.bee->right = keysPressed.contains(Qt::Key_Right);
            game.bee->left = keysPressed.contains(Qt::Key_Left);
            game.bee->down = keysPressed.contains(Qt::Key_Down);

            BulletGen& gen = BulletGen::Instance();
            gen.on = keysPressed.contains(Qt::Key_Space);
            gen.Update(Notifer::Instance());

            game.bee->Move();
            if (lastLevel != game.level()){
                lastLevel = game.level();
                lastLevelStartTime = n.getStage();
                isShown = true;
                over -> setText(QString("Level %1").arg(lastLevel));
            }
            else if(isShown && (n.getStage() - lastLevelStartTime) > (n.getPeriod() * 3)){
                isShown = false;
                over -> setText(QString(""));
            }
        }
        else{
            //if (lastLevel != game.level()){
                lastLevel = game.level();
                lastLevelStartTime = n.getStage();
                isShown = true;
                over -> setText(QString("Game over"));
                game.score(0);
                game.level(1);
                game.Save();
            //}
            //else if(isShown && (n.getStage() - lastLevelStartTime) > (n.getPeriod() * 3)){
            //    isShown = false;
            //    over -> setText(QString(""));
            //}
        }
        score -> setText(QString("Score: %1").arg(game.score()));
        lifes -> setText(QString("Lifes: %1").arg(game.bee->Lifes() ));
        update();
    }
private:
    int lastLevel = -1;
    int lastLevelStartTime = -1;
    bool isShown = false;
    Ui::MainWindow *ui;
    QLabel *score;
    QLabel *lifes;
    QLabel *over;
    int shootID = 0;
    QSet<int> keysPressed;
    QMenu *HelpMenu;
    QAction *AboutAct;
    QAction *SaveAct;
    QAction *NewAct;
    //void createActions();
    //void createMenus();
public slots:
    void About();
    void Save();
    void newGame();
    void keyReleaseEvent(QKeyEvent*);
    void keyPressEvent(QKeyEvent*);
};
