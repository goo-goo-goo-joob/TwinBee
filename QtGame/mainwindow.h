#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
public slots:
    void on_pushButton_clicked();
    //void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
};

#endif // MAINWINDOW_H
