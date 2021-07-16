//
// Created by tereb on 15.07.2021.
//

#ifndef SUDOKU_MADNESS_SUDOKUUNIQUECHECKER_H
#define SUDOKU_MADNESS_SUDOKUUNIQUECHECKER_H

#include "../../domain/SudokuBoard.h"

/// Class which is used to check if the Sudoku board contains only unique elements (the main property besides having
/// number between 1 and size^2)

class SudokuUniqueChecker
{
public:
    static bool checkBoard(const SudokuBoard & sudokuBoard);
    // Checks if a given Sudoku board is valid (meaning, all its rows, columns, cells and diagonals contain
    // unique values)
    // returns: true if the board is valid, false otherwise

    static bool checkRow(const SudokuBoard & sudokuBoard, int row);
    // Checks if the given row is valid in the given sudoku board
    // returns: true if the row is valid, false otherwise

    static bool checkColumn(const SudokuBoard & sudokuBoard, int column);
    // Checks if the given column is valid in the given sudoku board
    // returns: true if the column is valid, false otherwise

    static bool checkGrid(const SudokuBoard & sudokuBoard, int grid);
    // Checks if the given grid (formation of size size*size) is valid in the given sudoku board
    // returns: true if the grid is valid, false otherwise
};


#endif //SUDOKU_MADNESS_SUDOKUUNIQUECHECKER_H
