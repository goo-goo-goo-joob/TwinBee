#pragma once
#include <QMainWindow>
#include <QKeyEvent>
#include "GameItem.h"
#include "observer.h"
#include "Game.h"
#include "bulletgen.h"

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
        game.bee->up = keysPressed.contains(Qt::Key_Up);
        game.bee->right = keysPressed.contains(Qt::Key_Right);
        game.bee->left = keysPressed.contains(Qt::Key_Left);
        game.bee->down = keysPressed.contains(Qt::Key_Down);

         BulletGen& gen = BulletGen::Instance();
         gen.on = keysPressed.contains(Qt::Key_Space);
         gen.Update(Notifer::Instance());

        game.bee->Move();

        update();
    }
private:
    Ui::MainWindow *ui;
    int shootID = 0;
    QSet<int> keysPressed;
public slots:
    void keyReleaseEvent(QKeyEvent*);
    void keyPressEvent(QKeyEvent*);
};
