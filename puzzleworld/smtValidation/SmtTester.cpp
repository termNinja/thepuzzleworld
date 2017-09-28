#include "SmtTester.hpp"
#include "SmtSolver.hpp"
#include "ThreeInAWayGenerator.hpp"

SmtTester::SmtTester(QObject* parent)
    : m_parent(parent)
{

}

void SmtTester::performWriteTesting()
{
    SmtSolver* solver = new SmtSolver(6, m_parent);
    ThreeInAWayGenerator generator(6);

    std::vector<std::vector<int>> initVals = {
           { 0,  0, 1, 0,  0,  0},
           { 0,  1, 0, 0, -1,  0},
           { 0, -1, 0, 0,  0,  0},
           {-1,  0, 1, 0, -1,  0},
           { 0,  0, 0, 0,  0, -1},
           { 0,  1, 1, 0,  1,  0},
       };

    std::vector<std::string> cmds = generator.generateYicesFullSolution(initVals);
    std::string cmd = "";
    for (auto line: cmds)
        cmd += line + "\n";

    solver->sendCommandToSolver(cmd);
}
