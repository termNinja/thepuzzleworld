#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <iostream>

#include "Hitori.hpp"

namespace Ui {
class Game_2;
}

class Game_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game_2(QWidget *parent = 0);
    ~Game_2();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent * coord);
    void initialiseRects(int n);
    void renderAgain();

public slots:
    void changeFieldDimensions(int index);
    void checkSolution();
    void restartGame();
    void showAnswer();
    void newGame();

private:
    Ui::Game_2 *ui;
    QRect *rects = new QRect[36];
    Hitori *m_game = new Hitori(6);
};

#endif // MAINWINDOW_HPP
