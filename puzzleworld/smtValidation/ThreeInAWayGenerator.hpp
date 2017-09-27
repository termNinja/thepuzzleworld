#ifndef THREE_IN_A_WAY_GENERATOR
#define THREE_IN_A_WAY_GENERATOR

#include <vector>
#include <string>

class ThreeInAWayGenerator
{
public:
    ThreeInAWayGenerator(int n);

    /// Returns the dimension of the game
    int n() const;

    /// Gives n*(n-2) conditions if there are n rows
    std::vector<std::string> generateYicesConditionsRows() const;

    /// Gives n*(n-2) conditions if there are n columns
    std::vector<std::string> generateYicesConditionsCols() const;

    /// Gives n condititions asserting that every row has the
    /// same number of blue and white squares (or xs and os)
    std::vector<std::string> generateYicesEqualRows() const;

    /// Gives n condititions asserting that every column has the
    /// same number of blue and white squares (or xs and os)
    std::vector<std::string> generateYicesEqualCols() const;

    /// Set initial state
    /// 1 marks the blue square, -1 the white square
    std::vector<std::string> generateInitialState(const std::vector<std::vector<short>>& state) const;

    /// Declare all variables that will be required for solution.
    std::vector<std::string> generateYicesVariableDeclaration() const;

    /// Returns all required conditions for the game.
    std::vector<std::string> generateAllConditions() const;

    /// Creates the header
    std::vector<std::string> generateYicesHeader() const;

    /// Creates the yices code for fetching all the variable values
    std::vector<std::string> generateYicesGetAllValues() const;

    /// Creates the full yices smt program;
    std::vector<std::string> generateYicesFullSolution(const std::vector<std::vector<short>>& tmp) const;

private:
    int m_n;
};

#endif /* ifndef THREE_IN_A_WAY_GENERATOR */
