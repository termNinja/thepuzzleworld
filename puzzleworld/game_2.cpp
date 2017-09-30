#include "game_2.hpp"
#include "ui_game_2.h"

#include <cmath>
#include <QPixmap>

Game_2::Game_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_2)
{
    ui->setupUi(this);
    connect(ui->cb_dimension, SIGNAL(currentIndexChanged(int)), this, SLOT(changeFieldDimensions(int)));
    connect(ui->pb_check, SIGNAL(clicked(bool)), this, SLOT(checkSolution()));
    connect(ui->pb_restart, SIGNAL(clicked(bool)), this, SLOT(restartGame()));
    connect(ui->pb_answer, SIGNAL(clicked(bool)), this, SLOT(showAnswer()));
    connect(ui->pb_new_game, SIGNAL(clicked(bool)), this, SLOT(newGame()));

    initialiseRects(m_game->getDimension());
}

Game_2::~Game_2()
{
    delete ui;
    delete m_game;
    delete []rects;
}

void Game_2::paintEvent(QPaintEvent *event)
{
    QPainter * painter = new QPainter(this);
    painter->setPen(Qt::black);
    int dimension = m_game->getDimension();
    painter->drawRects(rects, dimension*dimension);
    auto field = m_game->getField();
    int k = 0;
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
        {
            auto pos = field[i][j];
            if (pos.second == 1)
            {
                QBrush brush(Qt::white);
                painter->fillRect(rects[k++], brush);
            }
            else if (pos.second == 2)
            {
                QBrush brush(Qt::blue);
                painter->fillRect(rects[k++], brush);
            }
            else if (pos.second == 0)
            {
                QBrush brush(Qt::gray);
                painter->fillRect(rects[k++], brush);
            }
        }

    k = 0;
    for (int i = 0; i < dimension; i++)
        for (int j = 0; j < dimension; j++)
        {
            auto pos = field[i][j];
            if (pos.first == 1)
                painter->drawTiledPixmap(rects[k++], QPixmap("C:/Users/lazar/Desktop/15/number_1.png"));
            else if (pos.first == 2)
                painter->drawTiledPixmap(rects[k++], QPixmap("C:/Users/lazar/Desktop/15/number_2.png"));
            else if (pos.first == 3)
                painter->drawTiledPixmap(rects[k++], QPixmap("C:/Users/lazar/Desktop/15/number_3.png"));
            else if (pos.first == 4)
                painter->drawTiledPixmap(rects[k++], QPixmap("C:/Users/lazar/Desktop/15/number_4.png"));
            else if (pos.first == 5)
                painter->drawTiledPixmap(rects[k++], QPixmap("C:/Users/lazar/Desktop/15/number_5.png"));
            else
                k++;
        }
}

void Game_2::mousePressEvent(QMouseEvent * coord)
{
    ui->lb_info->setText("");
    int dimension = m_game->getDimension();
    if (coord->x() >= 50 && coord->x() <= 50 * (dimension + 1) &&
        coord->y() >= 50 && coord->y() <= 50 * (dimension + 1))
    {
        std::cout << coord->x() << " " << coord->y() << std::endl;
        int y = floor(coord->x() / 50) - 1;
        int x = floor(coord->y() / 50) - 1;
        std::cout << x << " " << y << std::endl;
        auto field = m_game->getField();
        field[x][y].second = (++field[x][y].second) % 3;
        m_game->setField(field);
        repaint();
    }
}

void Game_2::changeFieldDimensions(int index)
{
    renderAgain();
}


void Game_2::checkSolution()
{
    std::cout << "Check" << std::endl;
    bool result = m_game->checkSolution();
    if (result == true)
        ui->lb_info->setText("Correct!");
    else
        ui->lb_info->setText("Bad!");
}

void Game_2::restartGame()
{
    ui->lb_info->setText("");
    m_game->restartGame();
    repaint();
}

void Game_2::showAnswer()
{
    ui->lb_info->setText("Correct answer :)");
    m_game->showSolution();
    repaint();
}

void Game_2::initialiseRects(int n)
{
    int k=0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            rects[k++] = QRect((j+1)*50 ,(i+1)*50, 48 ,48);
}

void Game_2::newGame()
{
    renderAgain();
}

void Game_2::renderAgain()
{
    delete [] rects;
    delete m_game;

    int index = ui->cb_dimension->currentIndex();
    switch (index)
    {
    case 1:
        rects = new QRect[64];
        m_game = new Hitori(8);
        initialiseRects(8);
        break;
    case 2:
        rects = new QRect[100];
        m_game = new Hitori(10);
        initialiseRects(10);
        break;
    default:
        rects = new QRect[36];
        m_game = new Hitori(6);
        initialiseRects(6);
        break;
    }
    repaint();
    qApp->processEvents();
}
