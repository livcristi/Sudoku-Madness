//
// Created by tereb on 14.07.2021.
//

#include "SudokuBoard.h"
#include "GameState.h"


SudokuBoard::SudokuBoard(int size)
{
    for(int i = 0; i < size * size; ++i)
        mBoard.emplace_back(size * size, UnassignedCell);
}

SudokuBoard::SudokuBoard(const SudokuBoard &sudokuBoard)
{
    mBoard = sudokuBoard.mBoard;
}

const std::vector<std::vector<int>> &SudokuBoard::getBoard() const
{
    return mBoard;
}

int SudokuBoard::getSize() const
{
    return (int) mBoard.size();
}

int SudokuBoard::getCellValue(int row, int column) const
{
    // Todo: Check if the row and column are valid
    return mBoard[row][column];
}

void SudokuBoard::setCellValue(int row, int column, int newValue)
{
    // Todo: Check if the row, column and newValue are valid
    mBoard[row][column] = newValue;
}

std::ostream &operator<<(std::ostream &os, const SudokuBoard &board)
{
    for(const auto & row : board.mBoard)
    {
        for(int cell : row)
        {
            os << cell << ' ';
        }
    }
    return os;
}

std::istream &operator>>(std::istream &in, SudokuBoard &board)
{
    for(auto & row : board.mBoard)
    {
        for(int & cell : row)
        {
            in >> cell;
        }
    }
    return in;
}

bool SudokuBoard::operator==(const SudokuBoard &rhs) const
{
    return mBoard == rhs.mBoard;
}

bool SudokuBoard::operator!=(const SudokuBoard &rhs) const
{
    return !(rhs == *this);
}

bool SudokuBoard::cellContainsValue(int row, int column) const
{
    return (mBoard[row][column] != BombedCell && mBoard[row][column] != UnassignedCell);
}

