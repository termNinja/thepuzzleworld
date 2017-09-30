#ifndef SMTTESTER_HPP
#define SMTTESTER_HPP

#include <QObject>

class SmtTester
{
public:
    SmtTester(QObject* parent = nullptr);

    void performWriteTesting();

private:
    QObject* m_parent;
};

#endif // SMTTESTER_HPP
