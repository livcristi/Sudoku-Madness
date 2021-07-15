//
// Created by tereb on 15.07.2021.
//

#include <set>
#include <cmath>
#include "SudokuUniqueChecker.h"

bool SudokuUniqueChecker::checkBoard(const SudokuBoard &sudokuBoard)
{
    int size = sudokuBoard.getSize();

    // Check all the lines
    for(int i = 0; i < size; ++i)
        if(!checkRow(sudokuBoard, i))
            return false;
    // Check all the columns
    for(int i = 0; i < size; ++i)
        if(!checkColumn(sudokuBoard, i))
            return false;
    // Check the grids
    for(int i = 0; i < size; ++i)
        if(!checkGrid(sudokuBoard, i))
            return false;
    return true;
}

// todo: validate the rows, columns and grid numbers

bool SudokuUniqueChecker::checkRow(const SudokuBoard &sudokuBoard, int row)
{
    int size = sudokuBoard.getSize();
    std::set<int> values;
    for(int i = 0; i < size; ++i)
    {
        int value = sudokuBoard.getCellValue(row, i);
        if (value > 0)
        {
            if(values.count(value))
                return false;
            else
                values.insert(value);
        }
    }
    return true;
}

bool SudokuUniqueChecker::checkColumn(const SudokuBoard &sudokuBoard, int column)
{
    int size = sudokuBoard.getSize();
    std::set<int> values;
    for(int i = 0; i < size; ++i)
    {
        int value = sudokuBoard.getCellValue(i, column);
        if (value > 0)
        {
            if(values.count(value))
                return false;
            else
                values.insert(value);
        }
    }
    return true;
}

bool SudokuUniqueChecker::checkGrid(const SudokuBoard &sudokuBoard, int grid)
{
    int size = (int)sqrt(sudokuBoard.getSize());
    int startX = grid / size * size;
    int startY = grid % size * size;
    std::set<int> values;
    for(int i = startX; i < startX + size; ++i)
    {
        for(int j = startY; j < startY + size; ++j)
        {
            int value = sudokuBoard.getCellValue(i, j);
            if (value > 0)
            {
                if(values.count(value))
                    return false;
                else
                    values.insert(value);
            }
        }
    }
    return true;
}


