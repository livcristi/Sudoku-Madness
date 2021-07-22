QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui/window/mainwindow.cpp \
    gui/model/GUIModel.cpp \
    starter.cpp \
    domain/SudokuBoard.cpp \
    repository/SudokuRepository.cpp \
    service/bombs/BoardBombGrenade.cpp \
    service/bombs/BoardBombLine.cpp \
    service/bombs/BoardBombMissile.cpp \
    service/factory/SudokuBoardFactory.cpp \
    service/game_service/sudoku_service/SudokuBoardService.cpp \
    service/generators/BacktrackingSudokuGenerator.cpp \
    service/generators/SudokuUniqueChecker.cpp \
    testing/Tester.cpp

HEADERS += \
    gui/window/mainwindow.h \
    gui/model/GUIModel.h \
    domain/SudokuBoard.h \
    repository/SudokuRepository.h \
    service/bombs/BoardBomb.h \
    service/bombs/BoardBombGrenade.h \
    service/bombs/BoardBombLine.h \
    service/bombs/BoardBombMissile.h \
    service/factory/SudokuBoardFactory.h \
    service/game_service/sudoku_service/SudokuBoardService.h \
    service/generators/BacktrackingSudokuGenerator.h \
    service/generators/SudokuGenerator.h \
    service/generators/SudokuUniqueChecker.h \
    testing/Tester.h

FORMS += \
    gui/window/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    data/boards.txt \
    testing/data/testing_data.txt

