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
        if(game.play()){
            game.bee->up = keysPressed.contains(Qt::Key_Up);
            game.bee->right = keysPressed.contains(Qt::Key_Right);
            game.bee->left = keysPressed.contains(Qt::Key_Left);
            game.bee->down = keysPressed.contains(Qt::Key_Down);

            BulletGen& gen = BulletGen::Instance();
            gen.on = keysPressed.contains(Qt::Key_Space);
            gen.Update(Notifer::Instance());

            game.bee->Move();
        }
        else{
            over -> setText(QString("Game over"));
        }
        score -> setText(QString("Score: %1").arg(game.score()));
        lifes -> setText(QString("Lifes: %1").arg(game.bee->Lifes() ));
        update();
    }
private:
    Ui::MainWindow *ui;
    QLabel *score;
    QLabel *lifes;
    QLabel *over;
    int shootID = 0;
    QSet<int> keysPressed;
public slots:
    void keyReleaseEvent(QKeyEvent*);
    void keyPressEvent(QKeyEvent*);
};
