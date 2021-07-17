//
// Created by tereb on 16.07.2021.
//

#include "SudokuBoardService.h"
#include "../../generators/SudokuUniqueChecker.h"

SudokuBoardService::SudokuBoardService(SudokuBoardFactory &tSudokuFactory) : mSudokuFactory(tSudokuFactory)
{
    mCurrentBoard = tSudokuFactory.createSudokuBoard("easy");
    mMaskBoard = SudokuBoard(mCurrentBoard);
}

const SudokuBoard & SudokuBoardService::getCurrentBoard()
{
    return mCurrentBoard;
}

bool SudokuBoardService::checkValidBoard() const
{
    return SudokuUniqueChecker::checkBoard(mCurrentBoard);
}

int SudokuBoardService::setBoardCell(int row, int column, int value)
{
    if(value <= 0 || value > mCurrentBoard.getSize())
        return InvalidValue;
    if(mMaskBoard.getCellValue(row, column))
        return InvalidCell;

    mCurrentBoard.setCellValue(row, column, value);

    int flag = ValidValue;
    int minSize = (mCurrentBoard.getSize() == 9) ? 3 : 2;
    int grid = row / minSize * minSize + column / minSize;

    if(!SudokuUniqueChecker::checkRow(mCurrentBoard, row))
        flag |= InvalidRow;
    if(!SudokuUniqueChecker::checkColumn(mCurrentBoard, column))
        flag |= InvalidColumn;
    if(!SudokuUniqueChecker::checkGrid(mCurrentBoard, grid))
        flag |= InvalidGrid;

    return flag;
}

bool SudokuBoardService::checkWinner() const
{
    // First, check if the player entered all the values
    for(int i = 0; i < mCurrentBoard.getSize(); ++i)
        for(int j = 0; j < mCurrentBoard.getSize(); ++j)
            if(mCurrentBoard.getCellValue(i, j) < 1)
                return false;
    // Then, check if the board is valid (the unique cells property)
    return this->checkValidBoard();
}

void SudokuBoardService::createNewBoard(const std::string &difficulty)
{
    mCurrentBoard = this->mSudokuFactory.createSudokuBoard(difficulty);
    mMaskBoard = SudokuBoard();
    for(int i = 0; i < mMaskBoard.getSize(); ++i)
        for(int j = 0; j < mMaskBoard.getSize(); ++j)
            if(mCurrentBoard.getCellValue(i, j) > 0)
                mMaskBoard.setCellValue(i, j, 1);
}
