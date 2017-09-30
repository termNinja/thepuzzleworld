/*
 * ThreeInAWayGenerator.cpp
 * Copyright (C) 2017 Nemanja Micovic <nmicovic@outlook.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "ThreeInAWayGenerator.hpp"

#include <sstream>
#include <iostream>
#include <QRegExp>
#include <QDebug>

std::vector<std::string> ThreeInAWayGenerator::generateInitialState(const std::vector<std::vector<int>>& state) const
{
    std::vector<std::string> result;
    for (unsigned i = 0; i < state.size(); i++)
    {
        for (unsigned j = 0; j < state[i].size(); ++j) {
            if (state[i][j] != 0)
            {
                std::string val = state[i][j] == -1 ? "(- 1)" : std::to_string(state[i][j]);
                std::string s = "(= x" + std::to_string(i) + "_" + std::to_string(j) + " " + val + ")";
                result.push_back(s);
            }
            else
            {
                std::stringstream ss;
                // (and
                ss << "(and ";
                //  (<= (- 1) xij)
                    ss << "(<= ";
                    ss << "(- 1) ";
                    ss << "x" << i << "_" << j;
                    ss << ")";
                //  (>= 1 xij)
                    ss << "(>= ";
                    ss << "1 ";
                    ss << "x" << i << "_" << j;
                    ss << ")";
                //  (distinct 0 xij)
                    ss << "(distinct 0 ";
                    ss << "x" << i << "_" << j;
                    ss << ")";
                // )
                ss << ")";
                result.push_back(ss.str());
            }
        }
    }
    return result;
}

std::vector<std::string> ThreeInAWayGenerator::generateYicesConditionsRows() const
{
    // TODO: precalculate how much spaces are required and reserve it
    std::vector<std::string> result;
    result.push_back(";; No three of the same in a row that are near each other");
    for (int i = 0; i < m_n; i++)
    {
        for (int j = 0; j < m_n -2; j++)
        {
            std::stringstream ss;

            // (and
            ss << "(and ";
            //   (>
            ss << "(> ";
            //      (+ xij xij+1 xij+2) (-3))
                ss << "(+ x" << i << "_" << j << " x" << i << "_" << j+1 << " x" << i << "_" << j+2 << ") (- 3)";
            ss << ")";
            //   (< (+ xij sij+1 xij+2) 3)
            ss << "(< ";
            //      (+ xij xij+1 xij+2) (-3))
                ss << "(+ x" << i << "_" << j << " x" << i << "_" << j+1 << " x" << i << "_" << j+2 << ") 3";
            ss << ")";
            // )
            ss << ")";
            result.push_back(ss.str());

            //old code with distinct
            //std::stringstream ss;
            //ss << "(distinct ";
            //ss << "x" << i << "_" << j << " ";
            //ss << "x" << i << "_" << j+1 << " ";
            //ss << "x" << i << "_" << j+2;
            //ss << ")";
            result.push_back(ss.str());
        }
    }
    return result;
}

std::vector<std::string> ThreeInAWayGenerator::generateYicesConditionsCols() const
{
    // TODO: precalculate how much spaces are required and reserve it
    std::vector<std::string> result;
    result.push_back(";; No three of the same in a column that are near each other");
    for (int j = 0; j < m_n; j++)
    {
        for (int i = 0; i < m_n -2; i++)
        {
            std::stringstream ss;
            // (and
            ss << "(and ";
            //   (>
            ss << "(> ";
            //      (+ xij xi+1j xi+1j) (-3))
                ss << "(+ x" << i << "_" << j << " x" << i+1 << "_" << j << " x" << i+2 << "_" << j << ") (- 3)";
            ss << ")";
            //   (< (+ xij sij+1 xij+2) 3)
            ss << "(< ";
            //      (+ xij xij+1 xij+2) (-3))
                ss << "(+ x" << i << "_" << j << " x" << i+1 << "_" << j << " x" << i+2 << "_" << j << ") 3";
            ss << ")";
            // )
            ss << ")";
            //result.push_back(ss.str());
            //std::stringstream ss;
            //ss << "(distinct ";
            //ss << "x" << i << "_" << j << " ";
            //ss << "x" << i+1 << "_" << j << " ";
            //ss << "x" << i+2 << "_" << j;
            //ss << ")";
            result.push_back(ss.str());
        }
    }
    return result;
}

std::vector<std::string> ThreeInAWayGenerator::generateYicesEqualRows() const
{
    // TODO: precalculate how much spaces are required and reserve it
    std::vector<std::string> result;
    result.push_back(";; In every row, there is an same number of blue and white squares.");

    for (int i = 0; i < m_n; i++)
    {
        std::stringstream ss;
        ss << "(= 0 ";
        ss << "(+";
        for (int j = 0; j < m_n; j++)
        {
           ss << " x" << i << "_" << j; 
        }
        ss << "))";
        result.push_back(ss.str());
    }

    return result;
}

std::vector<std::string> ThreeInAWayGenerator::generateYicesEqualCols() const
{
    // TODO: precalculate how much spaces are required and reserve it
    std::vector<std::string> result;
    result.push_back(";; In every column, there is an same number of blue and white squares.");

    for (int i = 0; i < m_n; i++)
    {
        std::stringstream ss;
        ss << "(= 0 ";
        ss << "(+";
        for (int j = 0; j < m_n; j++)
        {
           ss << " x" << j << "_" << i; 
        }
        ss << "))";
        result.push_back(ss.str());
    }

    return result;
}

std::vector<std::string> ThreeInAWayGenerator::generateAllConditions() const
{
    auto c1 = generateYicesConditionsRows();
    auto c2 = generateYicesConditionsCols();
    auto c3 = generateYicesEqualRows();
    auto c4 = generateYicesEqualCols();

    c1.reserve(c1.size() + c2.size() + c3.size() + c4.size());
    c1.insert(c1.end(), c2.begin(), c2.end());
    c1.insert(c1.end(), c3.begin(), c3.end());
    c1.insert(c1.end(), c4.begin(), c4.end());

    return c1;
}

std::vector<std::string> ThreeInAWayGenerator::generateYicesHeader() const
{
    return { "(set-logic QF_LIA)" };
}

int ThreeInAWayGenerator::n() const
{
    return m_n;
}

ThreeInAWayGenerator::ThreeInAWayGenerator(int n)
    : m_n(n)
{}

std::vector<std::string> ThreeInAWayGenerator::generateYicesVariableDeclaration() const
{
    std::vector<std::string> result;
    for (int i = 0; i < m_n; ++i)
    {
        for (int j = 0; j < m_n; ++j)
        {
            result.push_back(
                "(declare-fun x" +
                std::to_string(i) + "_" + std::to_string(j) +
                " () Int)"
            );
        }
    }
    return result;
}

std::vector<std::string> ThreeInAWayGenerator::generateYicesGetAllValues() const
{
    std::string t = "(get-value (";
    for (int i = 0; i < m_n; ++i)
    {
        for (int j = 0; j < m_n; ++j)
        {
            t += " x" + std::to_string(i) + "_" + std::to_string(j); 
        }
    }
    t += "))";
    return {t};
}

std::vector<std::string> ThreeInAWayGenerator::generateYicesFullSolution(const std::vector<std::vector<int>>& tmp) const
{
    // (set-logic QF_LIA)
    auto header = this->generateYicesHeader();

    // (declare-fun x_i_j () Int)
    auto vars = this->generateYicesVariableDeclaration();

    // (assert
    //  (and
    vars.push_back("(assert (and ");
    auto init = this->generateInitialState(tmp);
    auto conds = this->generateAllConditions();
    conds.push_back("))");
    conds.push_back("(check-sat)");
    // ))
    auto getvals = this->generateYicesGetAllValues();
    getvals.push_back("(exit)");

    header.reserve(header.size() + vars.size() + init.size() + conds.size() + getvals.size());
    header.insert(header.end(), vars.begin(), vars.end());
    header.insert(header.end(), init.begin(), init.end());
    header.insert(header.end(), conds.begin(), conds.end());
    header.insert(header.end(), getvals.begin(), getvals.end());

    return header;
}

int ThreeInAWayGenerator::makeIntFromYicesGetValue(QString s)
{
    return s == "(- 1)" ? -1 : s.toInt();
}


std::vector<std::vector<int> > ThreeInAWayGenerator::parseSolution(QString solution) const
{
    return ThreeInAWayGenerator::parseSolutionStatic(solution, m_n);
}

std::vector<std::vector<int>> ThreeInAWayGenerator::parseSolutionStatic(QString solution, int n)
{

    std::vector<std::vector<int>> result;
    result.resize(n);
    for (int i = 0; i < n; i++)
        result[i].resize(n);

    qDebug() << "Data: " << solution;
    QRegExp rx("x(\\d)+_(\\d+) (1|([(]- 1[)]))");

    int pos = 0;
    while ((pos = rx.indexIn(solution, pos)) != -1)
    {
        qDebug() << "x" << rx.cap(1).toInt() << "_" << rx.cap(2).toInt() << "=" << makeIntFromYicesGetValue(rx.cap(3));

        int i = rx.cap(1).toInt();
        int j = rx.cap(2).toInt();
        int val = makeIntFromYicesGetValue(rx.cap(3));

        // Insert into matrix
        result[i][j] = val;

        // Move to next occurence
        pos += rx.matchedLength();
    }

    qDebug() << "Created matrix with values:";
    for (unsigned i = 0; i < result.size(); i++)
    {
        for (unsigned j = 0; j < result[i].size(); j++)
        {
//            qDebug() << "result[" << i << ", " << j << "] = " << result[i][j];
            std::cout << result[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return result;
}
