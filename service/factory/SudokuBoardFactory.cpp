//
// Created by tereb on 14.07.2021.
//

#include "SudokuBoardFactory.h"
#include "../generators/BacktrackingSudokuGenerator.h"
#include <iostream>

SudokuBoardFactory::SudokuBoardFactory(SudokuRepository &tRepo): mRepo(tRepo)
{
    this->mGenerator = std::make_unique<BacktrackingSudokuGenerator>();
}

SudokuBoard SudokuBoardFactory::createSudokuBoard(const std::string & difficulty, int size)
{
    // todo: call a thread that will generate more boards and add them to the repo
    SudokuBoard newBoard;
    if(mRepo.size() < 5)
    {
        newBoard = this->mGenerator->generateBoard(size);
    }
    else
    {
        newBoard = mRepo.getBoard();
    }

    // Empty random cells to for the difficulty
    int side = size * size;
    int removedCells = side;
    if(difficulty == "easy")
        removedCells = rand() % side + side;
    else if(difficulty == "medium")
        removedCells = rand() % side + side * 2;
    else if(difficulty == "hard")
        removedCells = rand() % side + side * 3;

    while(removedCells > 0)
    {
        int row = rand() % newBoard.getSize();
        int col = rand() % newBoard.getSize();
        if(newBoard.getCellValue(row, col) != 0)
        {
            newBoard.setCellValue(row, col, UNASSIGNED);
            removedCells--;
        }
    }

    return newBoard;
}


