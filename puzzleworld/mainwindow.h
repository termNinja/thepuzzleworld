#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "game_1.hpp"
#include "game_2.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openGame1();
    void openGame2();

private:
//    Game_1 *g1;
    Game_2 *g2;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
