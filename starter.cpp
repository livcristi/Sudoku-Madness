//
// Created by tereb on 14.07.2021.
//

#include "testing/Tester.h"
#include "repository/SudokuRepository.h"
#include "service/game_service/sudoku_service/SudokuBoardService.h"
#include "gui/model/GUIModel.h"
#include "gui/window/mainwindow.h"
#include "gui/delegate/SudokuBoardDelegate.h"

#include <QApplication>
#include <QDir>
#include <iostream>

// Get the path to the data file
std::string getDataFile(int type = 1)
{
//    if(type == 1)
//        return R"(C:\Users\tereb\OneDrive\Desktop\Github-SM\Sudoku-Madness\data\boards.txt)";
//    else if(type == 2)
//        return R"(C:\Users\tereb\OneDrive\Desktop\Github-SM\Sudoku-Madness\data\coins.txt)";
//    else
//        return R"(C:\Users\tereb\OneDrive\Desktop\Github-SM\Sudoku-Madness\data\savefile.txt)";
//    std::string dirPath = QDir::currentPath().toStdString();
//    while(dirPath[dirPath.size() - 1] != '/')
//        dirPath.pop_back();
//    switch (type) {
//        case 1:
//            dirPath += "Sudoku-Madness/data/boards.txt";
//            break;
//        case 2:
//            dirPath += "Sudoku-Madness/data/coins.txt";
//            break;
//        default:
//            dirPath += "Sudoku-Madness/data/savefile.txt";
//    }
    std::string dirPath = QCoreApplication::applicationDirPath().toStdString();
    switch (type) {
        case 1:
            dirPath += "/data/boards.txt";
            break;
        case 2:
            dirPath += "/data/coins.txt";
            break;
        default:
            dirPath += "/data/savefile.txt";
    }

    return dirPath;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    // Tester::testAll();
    QApplication app(argc, argv);

    SudokuRepository repository(getDataFile());
    SudokuBoardFactory factory(repository);
    SudokuBoardService boardService(factory, getDataFile(3));

    CoinService coinService(getDataFile(2));

    GUIModel model(boardService);
    SudokuBoardDelegate delegate(boardService);
    MainWindow mainWindow(model,  delegate,boardService, coinService);
    mainWindow.show();

    mainWindow.show();
    return app.exec();
}
