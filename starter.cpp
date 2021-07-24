//
// Created by tereb on 14.07.2021.
//

#include "testing/Tester.h"
#include "repository/SudokuRepository.h"
#include "service/game_service/sudoku_service/SudokuBoardService.h"
#include "gui/model/GUIModel.h"
#include "gui/window/mainwindow.h"

#include <QApplication>
#include <QDir>

// Get the path to the data file
std::string getDataFile(int type = 1)
{
    if(type == 1)
        return R"(C:\Users\tereb\OneDrive\Desktop\Github-SM\Sudoku-Madness\data\boards.txt)";
    else
        return R"(C:\Users\tereb\OneDrive\Desktop\Github-SM\Sudoku-Madness\data\coins.txt)";
    std::string dirPath = QDir::currentPath().toStdString();
    while(dirPath[dirPath.size() - 1] != '/')
        dirPath.pop_back();
    dirPath += "Sudoku-Madness/data/boards.txt";
    return dirPath;
}


int main(int argc, char *argv[])
{
    srand(time(0));
    Tester::testAll();
    QApplication a(argc, argv);

    SudokuRepository repository(getDataFile());
    SudokuBoardFactory factory(repository);
    SudokuBoardService boardService(factory);

    CoinService coinService(getDataFile(2));

    GUIModel model(boardService);
    MainWindow mainWindow(model, boardService, coinService);
    mainWindow.show();

    mainWindow.show();
    return a.exec();
}
