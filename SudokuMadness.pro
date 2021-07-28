QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += mChronometer++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    domain/GameState.cpp \
    gui/delegate/SudokuBoardDelegate.cpp \
    gui/helper_widgets/chronometer/chronoui.cpp \
    gui/helper_widgets/dialog/difficultydialog.cpp \
    gui/window/mainwindow.cpp \
    gui/model/GUIModel.cpp \
    service/game_service/money_service/CoinService.cpp \
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
    domain/GameState.h \
    gui/delegate/SudokuBoardDelegate.h \
    gui/helper_widgets/chronometer/chronoui.h \
    gui/helper_widgets/dialog/difficultydialog.h \
    gui/window/mainwindow.h \
    gui/model/GUIModel.h \
    domain/SudokuBoard.h \
    repository/SudokuRepository.h \
    service/bombs/BoardBomb.h \
    service/bombs/BoardBombGrenade.h \
    service/bombs/BoardBombLine.h \
    service/bombs/BoardBombMissile.h \
    service/factory/SudokuBoardFactory.h \
    service/game_service/money_service/CoinService.h \
    service/game_service/sudoku_service/SudokuBoardService.h \
    service/generators/BacktrackingSudokuGenerator.h \
    service/generators/SudokuGenerator.h \
    service/generators/SudokuUniqueChecker.h \
    testing/Tester.h

FORMS += \
    gui/helper_widgets/dialog/difficultydialog.ui \
    gui/window/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    data/background.jpg \
    data/boards.txt \
    data/coins.txt \
    data/savefile.txt \
    testing/data/testing_coins.txt \
    testing/data/testing_data.txt

RESOURCES += \
    resource.qrc

