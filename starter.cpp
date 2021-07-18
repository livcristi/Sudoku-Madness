//
// Created by tereb on 14.07.2021.
//

#include "testing/Tester.h"
#include "repository/SudokuRepository.h"
#include "service/game_service/sudoku_service/SudokuBoardService.h"
#include "gui/model/GUIModel.h"
#include "gui/window/mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    srand(time(0));
    Tester::testAll();
    QApplication a(argc, argv);

    SudokuRepository repository(R"(C:\Users\tereb\OneDrive\Desktop\Sudoku-Madness\data\boards.txt)");
    SudokuBoardFactory factory(repository);
    SudokuBoardService boardService(factory);

    GUIModel model(boardService);
    MainWindow mainWindow(model, boardService);
    mainWindow.show();

    mainWindow.show();
    return a.exec();
}