//
// Created by tereb on 14.07.2021.
//

#include "BacktrackingSudokuGenerator.h"
#include <algorithm>
#include <random>

SudokuBoard BacktrackingSudokuGenerator::generateBoard(int size) {
    SudokuBoard newBoard(size);

    // First, create a random permutation and use it as the first row and to build the first column
    std::vector<int> permutation(size * size);
    for (int i = 0; i < size * size; ++i)
        permutation[i] = i + 1;
    std::random_shuffle(permutation.begin(), permutation.end());

    // First row
    std::vector<int> firstRow(permutation);

    // Create the first column
    std::vector<int> firstColumn(size * size);
    // Method: Copy the first number and the last two numbers from the permutation as the first number on the column
    // Then, remove them, shuffle the permutation and add the remaining number to the column
    firstColumn[0] = permutation[0];
    permutation.erase(permutation.begin());
    for (int i = 1; i < size; ++i) {
        firstColumn[i] = permutation[permutation.size() - 1];
        permutation.pop_back();
    }
    std::random_shuffle(permutation.begin(), permutation.end());
    for (int i = size; i < size * size; ++i) {
        firstColumn[i] = permutation[i - size];
    }

    // Set the first row and column
    for (int i = 0; i < size * size; ++i)
        newBoard.setCellValue(0, i, firstRow[i]);
    for (int i = 0; i < size * size; ++i)
        newBoard.setCellValue(i, 0, firstColumn[i]);

    // All that's left is to call a backtracking procedure on the remaining cells and return the board
    backtracking(newBoard, 1, 1);

    return newBoard;
}

bool BacktrackingSudokuGenerator::backtracking(SudokuBoard &board, int row, int column)
{
    if (row == board.getSize())
        return true;
    int size = (int) sqrt(board.getSize());
    int newRow = (column + 1 == board.getSize()) ? row + 1 : row;
    int newColumn = (column + 1 == board.getSize()) ? 0 : column + 1;
    int grid = row / size * size + column / size;

    // Skip assigned cells
    if(board.getCellValue(row, column) > 0)
        return backtracking(board, newRow, newColumn);

    for (int i = 1; i <= board.getSize(); ++i) {
        // Assign new value to a cell
        board.setCellValue(row, column, i);
        // Check if the new value is correct
        if (!SudokuUniqueChecker::checkRow(board, row) ||
            !SudokuUniqueChecker::checkColumn(board, column) ||
            !SudokuUniqueChecker::checkGrid(board, grid))
        {
            board.setCellValue(row, column, UNASSIGNED);
            continue;
        }

        if (backtracking(board, newRow, newColumn))
            return true;

        board.setCellValue(row, column, UNASSIGNED);
    }
    return false;
}

