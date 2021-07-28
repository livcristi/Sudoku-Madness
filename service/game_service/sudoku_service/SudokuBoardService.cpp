//
// Created by tereb on 16.07.2021.
//

#include <utility>
#include <vector>
#include <array>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "SudokuBoardService.h"
#include "../../generators/SudokuUniqueChecker.h"
#include "../../bombs/BoardBombGrenade.h"
#include "../../bombs/BoardBombLine.h"
#include "../../bombs/BoardBombMissile.h"
#include "../../../domain/GameState.h"

SudokuBoardService::SudokuBoardService(SudokuBoardFactory &tSudokuFactory, std::string  tSaveFile) :
mSudokuFactory(tSudokuFactory), saveFile(std::move(tSaveFile))
{
    this->bombs.push_back(std::unique_ptr<BoardBomb>(new BoardBombGrenade));
    this->bombs.push_back(std::unique_ptr<BoardBomb>(new BoardBombLine));
    this->bombs.push_back(std::unique_ptr<BoardBomb>(new BoardBombMissile));
    currentDifficulty = "easy";
    this->createNewBoard(currentDifficulty);
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
    if(mMaskBoard.getCellValue(row, column) & OccupiedCell)
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

    markClashingCells();

    return flag;
}

bool SudokuBoardService::checkWinner() const
{
    // First, check if the player entered all the values
    for(int i = 0; i < mCurrentBoard.getSize(); ++i)
        for(int j = 0; j < mCurrentBoard.getSize(); ++j)
            if(mCurrentBoard.getCellValue(i, j) == UnassignedCell)
                return false;
    // Then, check if the board is valid (the unique cells property)
    return this->checkValidBoard();
}

void SudokuBoardService::createNewBoard(const std::string &difficulty)
{
    currentDifficulty = difficulty;
    mCurrentBoard = this->mSudokuFactory.createSudokuBoard(difficulty);
    mMaskBoard = SudokuBoard();
    for(int i = 0; i < mMaskBoard.getSize(); ++i)
        for(int j = 0; j < mMaskBoard.getSize(); ++j)
        {
            if(mCurrentBoard.cellContainsValue(i, j))
                mMaskBoard.setCellValue(i, j, OccupiedCell);
            else
                mMaskBoard.setCellValue(i, j, FreeCell);
        }
}

bool SudokuBoardService::checkOccupiedCell(int row, int column)
{
    return mMaskBoard.getCellValue(row, column) & OccupiedCell;
}

void SudokuBoardService::bombBoard(int row, int column, int bombType)
{
    // todo: throw custom exception
    if(bombType < 1 || bombType > (int)bombs.size())
        throw std::runtime_error("Cannot use a bomb");
    this->bombs[bombType - 1]->bombBoard(mCurrentBoard, row, column);
    markClashingCells();
}

bool SudokuBoardService::checkClashingCell(int row, int column)
{
    return (mMaskBoard.getCellValue(row, column) & (InvalidRow | InvalidColumn | InvalidGrid));
}

void SudokuBoardService::markClashingCells()
{
    // Mark the clashing values on the rows, columns and grids
    for(int index = 0; index < mCurrentBoard.getSize(); ++index)
    {
        SudokuUniqueChecker::markRow(mCurrentBoard, mMaskBoard, index);
        SudokuUniqueChecker::markColumn(mCurrentBoard, mMaskBoard, index);
        SudokuUniqueChecker::markGird(mCurrentBoard, mMaskBoard, index);
    }
}

int SudokuBoardService::loadGameFromFile()
{
    std::ifstream savedFile(saveFile);
    if(!savedFile || savedFile.peek() == std::ifstream::traits_type::eof())
        return -1;
    GameState oldState;
    savedFile >> oldState;
    savedFile.close();
    mCurrentBoard = oldState.getNormalBoard();
    mMaskBoard = oldState.getMaskBoard();
    currentDifficulty = oldState.getDifficulty();
    return oldState.getSeconds();
}

void SudokuBoardService::saveGameToFile(int seconds)
{
    std::ofstream savedFile(saveFile);
    if(!savedFile)
        throw std::runtime_error("Cannot save the game");
    GameState currentState(mCurrentBoard, mMaskBoard, currentDifficulty, seconds);
    savedFile << currentState;
    savedFile.close();
}

const std::string &SudokuBoardService::getCurrentDifficulty() const {
    return currentDifficulty;
}
