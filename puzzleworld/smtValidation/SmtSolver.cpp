#include "SmtSolver.hpp"
#include <QStringList>
#include <QDebug>
#include <QProcess>

#include "ThreeInAWayGenerator.hpp"

SmtSolver::SmtSolver(int n, QObject *parent)
    : QObject(parent), m_generator(ThreeInAWayGenerator(n))
{
    m_process = new QProcess(parent);
    QStringList args;

    QObject::connect(m_process, SIGNAL(finished(int)), this, SLOT(childProcessFinished(int)));
    QObject::connect(m_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(childProcessError(QProcess::ProcessError)));

    // Disabled and going to be remove probably because it's much easier to parse child process output if we wait for child
    // process to finish and we read everything in one go.
//    QObject::connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(childProcessMessageReadyStdout()));
    QObject::connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(childProcessMessageReadyStderr()));
    QObject::connect(m_process, SIGNAL(started()), this, SLOT(started()));
    QObject::connect(m_process, SIGNAL(stateChanged(QProcess::ProcessState)), this, SLOT(stateChanged(QProcess::ProcessState)));

    qDebug() << "Starting yices smt solver.";
    m_process->start("yices-smt2", args);
}

void SmtSolver::sendCommandToSolver(std::string msg)
{
    qDebug() << "Sending msg to solver";
    qDebug() << "Msg: " << QString::fromStdString(msg);
    m_process->write(msg.c_str());
}

void SmtSolver::killChildProcess()
{
    qDebug() << "Killing child process.";
    m_process->kill();
}

void SmtSolver::childProcessFinished(int status)
{
    qDebug() << "Child process finished with code " + QString::number(status);
    childProcessMessageReadyStdout();
}

void SmtSolver::childProcessMessageReadyStdout()
{
    qDebug() << "Child process stdout is ready to be read";
    QString msg = m_process->readAllStandardOutput();
    qDebug() << "msg: " + msg;
    if (msg == "sat\n")
    {
        qDebug() << "Emmiting signal done(true)";
        emit done(true, {});
    }
    else if (msg == "unsat\n")
    {
        qDebug() << "Emmiting signal done(false)";
        emit done(false, {});
    }
    else if (msg.contains("sat"))
    {
        // We have received both 'sat' and values for variables
        auto result = m_generator.parseSolution(msg);
        emit done(true, result);
    }
    else if (msg[0] == '(')
    {
        // This should not happen, though this condition was added just in case.
        qDebug() << "Problem detected. Child process hasnt reported SAT/UNSAT and variable values in one msg but instead variables are sent in a separate msg!";
        qDebug() << "Received values for variables.";
        auto result = m_generator.parseSolution(msg);
        exit(1);
    }
}

void SmtSolver::childProcessMessageReadyStderr()
{
    qDebug() << "Child process stderr is ready to be read";
    qDebug() << "msg: " + m_process->readAllStandardError();
}

void SmtSolver::childProcessError(QProcess::ProcessError e)
{
    switch (e)
    {
        case QProcess::ProcessError::FailedToStart:
            qDebug() << "Failed to start!";
            break;
        case QProcess::ProcessError::Crashed:
            qDebug() << "Crashed!";
            break;
        case QProcess::ProcessError::Timedout:
            qDebug() << "Timed out!";
            break;
        case QProcess::ProcessError::WriteError:
            qDebug() << "Write error!";
            break;
        case QProcess::ProcessError::ReadError:
            qDebug() << "Read error!";
            break;
        case QProcess::ProcessError::UnknownError:
            qDebug() << "Unknown error!";
            break;
    }
}

void SmtSolver::started()
{
    qDebug() << "Child process confirms it has started";
}

void SmtSolver::stateChanged(QProcess::ProcessState newState)
{
    qDebug() << "Process status has changed.";
    if (newState == QProcess::ProcessState::NotRunning)
        qDebug() << "Process state: Not Running";
    else if (newState == QProcess::ProcessState::Running)
        qDebug() << "Process state: Running";
    else if (newState == QProcess::ProcessState::Starting)
        qDebug() << "Process state: Starting";
}
