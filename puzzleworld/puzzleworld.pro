#-------------------------------------------------
#
# Project created by QtCreator 2017-09-26T14:52:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++11

TARGET = puzzleworld
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        smtValidation/ThreeInAWayGenerator.cpp \
    smtValidation/SmtSolver.cpp \
<<<<<<< HEAD
    game_2.cpp \
    ThreeInARow.cpp\
    Hitori.cpp\
    game_1.cpp\
    mainwindow.cpp
=======
    smtValidation/SmtTester.cpp
>>>>>>> cd7302716f8304d5b8b3b16132f108a9c39221f6

HEADERS += \
        smtValidation/ThreeInAWayGenerator.hpp \
    smtValidation/SmtSolver.hpp \
<<<<<<< HEAD
    game_2.hpp \
    ThreeInARow.hpp\
    Hitori.hpp\
    game_1.hpp\
    mainwindow.h

FORMS += \
    game_2.ui \
    game_1.ui\
    mainwindow.ui
=======
    smtValidation/SmtTester.hpp

FORMS += \
        MainWindow.ui \
    ThreeInARow.ui
>>>>>>> cd7302716f8304d5b8b3b16132f108a9c39221f6
