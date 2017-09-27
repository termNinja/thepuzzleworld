#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->cb_dimension, SIGNAL(currentIndexChanged(int)), this, SLOT(changeFieldDimensions(int)));
    connect(ui->pb_check, SIGNAL(clicked(bool)), this, SLOT(checkSolution()));
    connect(ui->pb_restart, SIGNAL(clicked(bool)), this, SLOT(restartGame()));
    connect(ui->pb_answer, SIGNAL(clicked(bool)), this, SLOT(showAnswer()));
    connect(ui->pb_new_game, SIGNAL(clicked(bool)), this, SLOT(newGame()));

    initialiseRects(m_game->getDimension());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_game;
    delete []rects;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter * painter = new QPainter(this);
    painter->setPen(Qt::black);
    int dimension = m_game->getDimension();
    painter->drawRects(rects, dimension*dimension);
    auto field = m_game->getField();
    int k = 0;
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
            if (abs(field[i][j]) == 1)
            {
                QBrush brush(Qt::white);
                painter->fillRect(rects[k++], brush);
            }
            else if (abs(field[i][j]) == 2)
            {
                QBrush brush(Qt::blue);
                painter->fillRect(rects[k++], brush);
            }
            else if (field[i][j] == 0)
            {
                QBrush brush(Qt::gray);
                painter->fillRect(rects[k++], brush);
            }
}

void MainWindow::mousePressEvent(QMouseEvent * coord)
{
    ui->lb_info->setText("");
    int dimension = m_game->getDimension();
    if (coord->x() >= 50 && coord->x() <= 50 * (dimension + 1) &&
        coord->y() >= 50 && coord->y() <= 50 * (dimension + 1))
    {
        std::cout << coord->x() << " " << coord->y() << std::endl;
        int x = floor(coord->x() / 50) - 1;
        int y = floor(coord->y() / 50) - 1;
        std::cout << x << " " << y << std::endl;
        auto field = m_game->getField();
        if (field[x][y] >= 0)
            field[x][y] = (++field[x][y]) % 3;
        m_game->setField(field);
        repaint();
    }
}

void MainWindow::changeFieldDimensions(int index)
{
    renderAgain();
}


void MainWindow::checkSolution()
{
    std::cout << "Check" << std::endl;
    bool result = m_game->checkSolution();
    if (result == true)
        ui->lb_info->setText("Correct!");
    else
        ui->lb_info->setText("Bad!");
}

void MainWindow::restartGame()
{
    ui->lb_info->setText("");
    m_game->restartGame();
    repaint();
}

void MainWindow::showAnswer()
{
    ui->lb_info->setText("Correct answer :)");
    m_game->showSolution();
    repaint();
}

void MainWindow::initialiseRects(int n)
{
    int k=0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            rects[k++] = QRect((j+1)*50 ,(i+1)*50, 48 ,48);
}

void MainWindow::newGame()
{
    renderAgain();
}

void MainWindow::renderAgain()
{
    delete [] rects;
    delete m_game;

    int index = ui->cb_dimension->currentIndex();
    switch (index)
    {
    case 1:
        rects = new QRect[64];
        m_game = new ThreeInARow(8);
        initialiseRects(8);
        break;
    case 2:
        rects = new QRect[100];
        m_game = new ThreeInARow(10);
        initialiseRects(10);
        break;
    default:
        rects = new QRect[36];
        m_game = new ThreeInARow(6);
        initialiseRects(6);
        break;
    }
    repaint();
    qApp->processEvents();
}
