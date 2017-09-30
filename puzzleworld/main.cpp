//#include "game_2.hpp"
#include "game_1.hpp"
#include <QApplication>

#include <sstream>
#include <QDebug>
#include <QProcess>
#include <QStringList>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game_1 w;
    w.show();

    return a.exec();
}
