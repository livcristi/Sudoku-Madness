//
// Created by tereb on 14.07.2021.
//

#include "SudokuBoardFactory.h"
#include "../generators/BacktrackingSudokuGenerator.h"

SudokuBoardFactory::SudokuBoardFactory(SudokuRepository &tRepo): mRepo(tRepo)
{
    this->mGenerator = std::make_unique<BacktrackingSudokuGenerator>();
}

SudokuBoard SudokuBoardFactory::createSudokuBoard(int size)
{
    // todo: call a thread that will generate more boards and add them to the repo
    if(mRepo.size() < 5)
    {
        auto newBoard = this->mGenerator->generateBoard(size);
        return newBoard;
    }
    else
        return mRepo.getBoard();
}


