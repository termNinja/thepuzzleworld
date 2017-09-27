#include "MainWindow.hpp"
#include <QApplication>

#include <sstream>
#include <QDebug>
#include <QProcess>
#include <QStringList>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
