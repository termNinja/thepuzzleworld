#ifndef THREEINAROW_H
#define THREEINAROW_H

#include <vector>
#include <utility>
#include <iostream>
#include <random>

class Hitori
{

public:
    Hitori(int dimension)
        :m_dimension(dimension)
    {
        generateInitState();
    }

    void generateInitState();
    void findSolution();
    bool checkSolution();

    int getDimension();
    void restartGame();
    void showSolution();
    std::vector<std::vector<std::pair<int, int>>> getField();
    void setField(std::vector<std::vector<std::pair<int, int>>> field);


private:
    int m_dimension;
    std::vector<std::vector<std::pair<int, int>>> m_solution;
    std::vector<std::vector<std::pair<int, int>>> m_init_field;
    std::vector<std::vector<std::pair<int, int>>> m_field;
};

#endif // THREEINAROW_H
