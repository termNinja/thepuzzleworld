#include "Hitori.hpp"

// Interface for genereting first state
void Hitori::generateInitState()
{
    m_init_field.resize(m_dimension, std::vector<std::pair<int, int>>(m_dimension));
    m_init_field[0][0] = std::make_pair(1, 0);
    m_init_field[0][1] = std::make_pair(1, 0);
    m_init_field[0][2] = std::make_pair(4, 0);
    m_init_field[0][3] = std::make_pair(5, 0);
    m_init_field[2][5] = std::make_pair(2, 1);
    m_init_field[2][3] = std::make_pair(5, 2);
    m_init_field[4][3] = std::make_pair(4, 1);
    m_init_field[5][5] = std::make_pair(4, 1);
    m_field = m_init_field;
    findSolution();
}

// Interface for solution
void Hitori::findSolution()
{
    m_solution = m_field;
    for (int i = 0; i < m_dimension; i++)
        for (int j = 0; j < m_dimension; j++)
            m_solution[i][j].second = m_solution[i][j].second < 0 ? m_solution[i][j].second : -1 * m_solution[i][j].second;
}

bool Hitori::checkSolution()
{
    for(int i = 0; i < m_dimension; i++)
        for(int j = 0; j < m_dimension; j++)
            if (m_field[i][j] != m_solution[i][j])
                return false;
    return true;
}

int Hitori::getDimension()
{
    return m_dimension;
}

std::vector<std::vector<std::pair<int, int>>> Hitori::getField()
{
    return m_field;
}

void Hitori::restartGame()
{
    m_field = m_init_field;
}

void Hitori::setField(std::vector<std::vector<std::pair<int, int>>> field)
{
    m_field = field;
}

void Hitori::showSolution()
{
    m_field = m_solution;
}
