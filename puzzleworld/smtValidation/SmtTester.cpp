#include "SmtTester.hpp"
#include "SmtSolver.hpp"
#include "ThreeInAWayGenerator.hpp"

SmtTester::SmtTester(QObject* parent)
    : m_parent(parent)
{

}

void SmtTester::performWriteTesting()
{
    // Construct the solver object
    SmtSolver* solver = new SmtSolver(6, m_parent);
    //                                ^ specify board dimension

    // invoke the solve procedure
    solver->solve();
}
