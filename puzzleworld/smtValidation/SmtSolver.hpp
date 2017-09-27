#ifndef SMTSOLVER_HPP
#define SMTSOLVER_HPP

#include <QObject>
#include <QProcess>

class SmtSolver : public QObject
{
    Q_OBJECT
public:
    explicit SmtSolver(QObject *parent = nullptr);

    /// Sends 'msg' to the child process (writes it to stdin).
    void sendCommandToSolver(std::string msg);

    void killChildProcess();

signals:
    void done(bool sat);

public slots:
    /// Handles the event of child processed finishing with work.
    void childProcessFinished(int status);

    /// Handles the event of child process having something written to stdout.
    void childProcessMessageReadyStdout();

    /// Handles the event of child process having something written to stderr.
    void childProcessMessageReadyStderr();

    /// Handles the errors that can occur.
    void childProcessError(QProcess::ProcessError e);

private:
    QProcess* m_process;
};

#endif // SMTSOLVER_HPP
