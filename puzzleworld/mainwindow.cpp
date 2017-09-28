#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pb_game_1, SIGNAL(clicked(bool)), this, SLOT(openGame1()));
    connect(ui->pb_game_2, SIGNAL(clicked(bool)), this, SLOT(openGame2()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openGame1()
{
//    g1 = new Game_1();
//    g1->show();
}

void MainWindow::openGame2()
{
    g2 = new Game_2();
    g2->show();
}
