#ifndef SMTSOLVER_HPP
#define SMTSOLVER_HPP

#include <QObject>
#include <QProcess>
#include "ThreeInAWayGenerator.hpp"

class SmtSolver : public QObject
{
    Q_OBJECT
public:
    explicit SmtSolver(int n, QObject *parent = nullptr);
    ~SmtSolver();

    /// Sends 'msg' to the child process (writes it to stdin).
    void sendCommandToSolver(std::string msg);

    /// Perform the solving process.
    void solve();

    /// Kill the child process and terminate work.
    void killChildProcess();

signals:
    // True if puzzle can be solved, false otherwise.
    void done(bool sat);

    // Variable 'sat' is True if puzzle can be solved a 'solution'
    // is filled for values of variables x_i_j (use i and j to index).
    // 1 means the square is blue, -1 means that it's white.
    void done(bool sat, std::vector<std::vector<int>> solution);

    // True if solution for the puzzle is unique, false otherwise.
    void solutionUnique(bool status);

public slots:
    /// Handles the event of child processed finishing with work.
    void childProcessFinished(int status);

    /// Handles the event of child process having something written to stdout.
    void childProcessMessageReadyStdout();

    /// Handles the event of child process having something written to stderr.
    void childProcessMessageReadyStderr();

    /// Handles the errors that can occur.
    void childProcessError(QProcess::ProcessError e);

    /// Handles the logic when the child process starts.
    void started();

    /// Handles the logic on when the child process status changes.
    void stateChanged(QProcess::ProcessState);

private:
    QProcess* m_process;
    ThreeInAWayGenerator m_generator;
};

#endif // SMTSOLVER_HPP
