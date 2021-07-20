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

void SudokuUniqueChecker::markRow(const SudokuBoard &sudokuBoard, SudokuBoard &markBoard, int row)
{
    // Count the frequencies for the given row
    std::vector<int> freq(sudokuBoard.getSize() + 1, 0);
    for(int col = 0; col < sudokuBoard.getSize(); ++col)
        if(sudokuBoard.getCellValue(row, col) > 0)
            freq[sudokuBoard.getCellValue(row, col)]++;

    // Mark the cells based on frequency (> 1 -> InvalidRow, <= 1 -> ValidRow)
    for(int col = 0; col < sudokuBoard.getSize(); ++col)
    {
        if(freq[sudokuBoard.getCellValue(row, col)] > 1)
        {
            int maskValue = markBoard.getCellValue(row, col);
            markBoard.setCellValue(row, col, maskValue | InvalidRow);
        }
        else
        {
            int maskValue = markBoard.getCellValue(row, col);
            if(maskValue & InvalidRow)
                markBoard.setCellValue(row, col, maskValue ^ InvalidRow);
        }
    }
}

void SudokuUniqueChecker::markColumn(const SudokuBoard &sudokuBoard, SudokuBoard &markBoard, int column)
{
    // Count the frequencies
    std::vector<int> freq(sudokuBoard.getSize() + 1, 0);
    for(int row = 0; row < sudokuBoard.getSize(); ++row)
        if(sudokuBoard.getCellValue(row, column) > 0)
            freq[sudokuBoard.getCellValue(row, column)]++;

    // Mark the cells based on frequency
    for(int row = 0; row < sudokuBoard.getSize(); ++row)
    {
        if(freq[sudokuBoard.getCellValue(row, column)] > 1)
        {
            int maskValue = markBoard.getCellValue(row, column);
            markBoard.setCellValue(row, column, maskValue | InvalidColumn);
        }
        else
        {
            int maskValue = markBoard.getCellValue(row, column);
            if(maskValue & InvalidColumn)
                markBoard.setCellValue(row, column, maskValue ^ InvalidColumn);
        }
    }
}

void SudokuUniqueChecker::markGird(const SudokuBoard &sudokuBoard, SudokuBoard &markBoard, int grid)
{
    int size = (int)sqrt(sudokuBoard.getSize());
    int startX = grid / size * size;
    int startY = grid % size * size;

    // Count the frequencies
    std::vector<int> freq(sudokuBoard.getSize() + 1, 0);

    for(int row = startX; row < startX + size; ++row)
    {
        for(int column = startY; column < startY + size; ++column)
        {
            if(sudokuBoard.getCellValue(row, column) > 0)
                freq[sudokuBoard.getCellValue(row, column)]++;
        }
    }

    // Mark the cells based on frequency
    for(int row = startX; row < startX + size; ++row)
    {
        for(int column = startY; column < startY + size; ++column)
        {
            if(freq[sudokuBoard.getCellValue(row, column)] > 1)
            {
                int maskValue = markBoard.getCellValue(row, column);
                markBoard.setCellValue(row, column, maskValue | InvalidGrid);
            }
            else
            {
                int maskValue = markBoard.getCellValue(row, column);
                if(maskValue & InvalidGrid)
                    markBoard.setCellValue(row, column, maskValue ^ InvalidGrid);
            }
        }
    }
}


