#include "SmtSolver.hpp"
#include <QStringList>
#include <QDebug>

SmtSolver::SmtSolver(QObject *parent) : QObject(parent)
{
    m_process = new QProcess(parent);
    QStringList args;

    QObject::connect(m_process, SIGNAL(finished(int)), this, SLOT(childProcessFinished(int)));
    QObject::connect(m_process, SIGNAL(error(QProcess::ProcessError)), this, SLOT(childProcessError(QProcess::ProcessError)));
    QObject::connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(childProcessMessageReadyStdout()));
    QObject::connect(m_process, SIGNAL(readyReadStandardError()), this, SLOT(childProcessMessageReadyStderr()));

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
}

void SmtSolver::childProcessMessageReadyStdout()
{
    qDebug() << "Child process stdout is ready to be read";
    QString msg = m_process->readAllStandardOutput();
    qDebug() << "msg: " + msg;
    if (msg == "sat\n")
    {
        qDebug() << "Emmiting signal done(true)";
        emit done(true);
    }
    else if (msg == "unsat\n")
    {
        qDebug() << "Emmiting signal done(false)";
        emit done(false);
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
        default:
            qDebug() << e;
    }
}
