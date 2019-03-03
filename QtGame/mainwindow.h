#pragma once
#include <QMainWindow>
#include <QKeyEvent>
#include "GameItem.h"
#include "observer.h"

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
        update();
    }
private:
    Ui::MainWindow *ui;
    int shootID = 0;
public slots:
    void keyReleaseEvent(QKeyEvent*);
    void keyPressEvent(QKeyEvent*);
};
