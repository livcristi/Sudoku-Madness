//
// Created by tereb on 14.07.2021.
//

#include "BacktrackingSudokuGenerator.h"
#include <algorithm>
#include <random>
#include <iostream>

SudokuBoard BacktrackingSudokuGenerator::generateBoard(int size) {
    SudokuBoard newBoard(size);

    // Strategy: Fill the diagonal grids with permutations of (1, ... size^2)
    for(int k = 0; k < size; ++k)
    {
        std::vector<int> perm(size * size, 0);
        for(int i = 1; i <= size * size; ++i)
            perm[i - 1] = i;
        std::random_shuffle(perm.begin(), perm.end());

        int startX = k * size;
        int startY = k * size;
        int cnt = 0;
        for(int i = 0; i < size; ++i)
        {
            for(int j = 0; j < size; ++j)
            {
                newBoard.setCellValue(startX + i, startY + j, perm[cnt++]);
            }
        }
    }

    // All that's left is to call a backtracking procedure on the remaining cells and return the board
    backtracking(newBoard, size, size);

    return newBoard;
}

bool BacktrackingSudokuGenerator::backtracking(SudokuBoard &board, int row, int column) {
    if (row == board.getSize())
        return true;
    int size = (int) sqrt(board.getSize());
    int newRow = (column + 1 == board.getSize()) ? row + 1 : row;
    int newColumn = (column + 1 == board.getSize()) ? 1 : column + 1;
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
            !SudokuUniqueChecker::checkGrid(board, grid)) {
            board.setCellValue(row, column, UNASSIGNED);
            continue;
        }

        if (backtracking(board, newRow, newColumn))
            return true;

        board.setCellValue(row, column, UNASSIGNED);
    }
    return false;
}

