cmake_minimum_required(VERSION 3.19)
project(Sudoku_Madness)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "D:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake")
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Charts)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Charts)

add_executable(Sudoku_Madness
        starter.cpp
        domain/SudokuBoard.cpp
        domain/SudokuBoard.h
        service/factory/SudokuBoardFactory.cpp
        service/factory/SudokuBoardFactory.h
        repository/SudokuRepository.cpp
        repository/SudokuRepository.h
        service/generators/SudokuGenerator.h
        service/generators/BacktrackingSudokuGenerator.cpp
        service/generators/BacktrackingSudokuGenerator.h
        testing/Tester.cpp
        testing/Tester.h
        service/generators/SudokuUniqueChecker.cpp
        service/generators/SudokuUniqueChecker.h
        service/game_service/sudoku_service/SudokuBoardService.cpp
        service/game_service/sudoku_service/SudokuBoardService.h
        gui/model/GUIModel.cpp
        gui/model/GUIModel.h
        gui/window/mainwindow.h
        gui/window/mainwindow.cpp
        service/bombs/BoardBomb.h
        service/bombs/BoardBombGrenade.cpp
        service/bombs/BoardBombGrenade.h
        service/bombs/BoardBombLine.cpp
        service/bombs/BoardBombLine.h
        service/bombs/BoardBombMissile.cpp
        service/bombs/BoardBombMissile.h
        service/game_service/money_service/CoinService.cpp
        service/game_service/money_service/CoinService.h
        gui/helper_widgets/chronometer/chronoui.cpp
        gui/helper_widgets/chronometer/chronoui.h
        gui/helper_widgets/dialog/difficultydialog.cpp
        gui/helper_widgets/dialog/difficultydialog.h)

file(COPY testing/data/testing_data.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})