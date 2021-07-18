//
// Created by tereb on 14.07.2021.
//

#include <iostream>
#include <ctime>
#include <QApplication>
#include "testing/Tester.h"
#include "repository/SudokuRepository.h"
#include "service/factory/SudokuBoardFactory.h"
#include "service/game_service/sudoku_service/SudokuBoardService.h"
#include "gui/model/GUIModel.h"
#include "gui/window/MainWindow.h"

int main(int argc, char ** argv)
{
    srand(time(nullptr));

//    Tester::testAll();
//    return 0;

    QApplication app{argc, argv};

    SudokuRepository repository(R"(C:\Users\tereb\OneDrive\Desktop\Sudoku-Madness\data\boards.txt)");
    SudokuBoardFactory factory(repository);
    SudokuBoardService boardService(factory);

    GUIModel model(boardService);
    MainWindow mainWindow(boardService, model);
    mainWindow.show();

    return app.exec();
}