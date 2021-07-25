//
// Created by tereb on 14.07.2021.
//

#include "SudokuBoardFactory.h"
#include "../generators/BacktrackingSudokuGenerator.h"
#include <algorithm>
#include <cctype>
#include <string>

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

    // Convert string to lowercase
    std::string lowercaseDifficulty(difficulty);
    std::transform(lowercaseDifficulty.begin(), lowercaseDifficulty.end(), lowercaseDifficulty.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    // Empty random cells to for the difficulty
    int side = size * size;
    int removedCells = side;
    if(lowercaseDifficulty == "easy")
        removedCells = rand() % side + side * 2;
    else if(lowercaseDifficulty == "medium")
        removedCells = rand() % side + side * 3;
    else if(lowercaseDifficulty == "hard")
        removedCells = rand() % side + side * 4;

    while(removedCells > 0)
    {
        int row = rand() % newBoard.getSize();
        int col = rand() % newBoard.getSize();
        if(newBoard.getCellValue(row, col) != UnassignedCell)
        {
            newBoard.setCellValue(row, col, UnassignedCell);
            removedCells--;
        }
    }

    return newBoard;
}


