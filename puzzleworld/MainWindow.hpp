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

#include "ThreeInARow.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    Ui::MainWindow *ui;
    QRect *rects = new QRect[36];
    ThreeInARow *m_game = new ThreeInARow(6);
};

#endif // MAINWINDOW_HPP
