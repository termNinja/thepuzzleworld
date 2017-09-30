#include "ThreeInARow.hpp"

// Interface for genereting first state
void ThreeInARow::generateInitState()
{
    m_init_field.resize(m_dimension, std::vector<int>(m_dimension));
    for(int i = 0; i < m_dimension; i++)
    {
        std::vector<int> tmp_vector;
        for(int j = 0; j < m_dimension; j++)
            tmp_vector.push_back(0);
        m_init_field.push_back(tmp_vector);
    }

    m_init_field = {
        { 0,  0, -2, 0,  0,  0},
        { 0,  -2, 0, 0, -1,  0},
        { 0, -1, 0, 0,  0,  0},
        {-1,  0, -2, 0, -1,  0},
        { 0,  0, 0, 0,  0, -1},
        { 0,  -2, -2, 0,  -2,  0},
    };

    m_field = m_init_field;
    findSolution();
}

// Interface for solution
void ThreeInARow::findSolution()
{
//    1  -1  1 -1 -1  1
//    -1  1 -1  1 -1  1
//    1  -1 -1  1  1 -1
//    -1  1  1 -1 -1  1
//    1  -1 -1  1  1 -1
//    -1  1  1 -1  1 -1

//    m_solution = {
//        { 2,  1,    -2,     1,  1,  2},
//        { 1,  -2,   1,      2,  -1,  2},
//        { 2, -1,    1,      2,   2,  1},
//        {-1,  2,    -2,     1, -1,  2},
//        { 2,  1,    1,      2,  2, -1},
//        { 1,  -2,   -2,     1,  -2,  1},
//    };
//    m_solution = m_field;
//    for (int i = 0; i < m_dimension; i++)
//        for (int j = 0; j < m_dimension; j++)
//            m_solution[i][j] = m_solution[i][j] < 0 ? m_solution[i][j] : -1 * m_solution[i][j];
}

bool ThreeInARow::checkSolution()
{
    for(int i = 0; i < m_dimension; i++)
        for(int j = 0; j < m_dimension; j++)
            if (abs(m_field[i][j]) != abs(m_solution[i][j]))
                return false;
    return true;
}

int ThreeInARow::getDimension()
{
    return m_dimension;
}

std::vector<std::vector<int>> ThreeInARow::getField()
{
    return m_field;
}

void ThreeInARow::restartGame()
{
    m_field = m_init_field;
}

void ThreeInARow::setField(std::vector<std::vector<int>> field)
{
    m_field = field;
}

void ThreeInARow::showSolution()
{
    m_field = m_solution;
}

void ThreeInARow::setSolution(std::vector<std::vector<int> > solution)
{
   m_solution = solution;
}

std::vector<std::vector<int> > &ThreeInARow::getSolution()
{
   return m_solution;
}
