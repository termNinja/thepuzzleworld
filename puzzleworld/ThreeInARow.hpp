#ifndef THREEINAROW_H
#define THREEINAROW_H

#include <vector>
#include <iostream>

class ThreeInARow
{

public:
    ThreeInARow(int dimension)
        : m_dimension(dimension)
    {
        generateInitState();
    }

    void generateInitState();
    void findSolution();
    bool checkSolution();
    void showSolution();

    int getDimension();
    void restartGame();

    void setCurrentStateAsSolved();

    void setSolution(std::vector<std::vector<int>> solution);

    std::vector<std::vector<int>>& getSolution();
    std::vector<std::vector<int>> getField();
    void setField(std::vector<std::vector<int>> field);


private:
    int m_dimension;
    std::vector<std::vector<int>> m_solution;
    std::vector<std::vector<int>> m_init_field;
    std::vector<std::vector<int>> m_field;
};

#endif // THREEINAROW_H
