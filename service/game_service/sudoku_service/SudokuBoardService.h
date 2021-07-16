//
// Created by tereb on 16.07.2021.
//

#ifndef SUDOKU_MADNESS_SUDOKUBOARDSERVICE_H
#define SUDOKU_MADNESS_SUDOKUBOARDSERVICE_H

#include "../../factory/SudokuBoardFactory.h"

/// Class for the game board service, which handles main events on the playable board

class SudokuBoardService
{
private:
    SudokuBoardFactory & mSudokuFactory;
    SudokuBoard mCurrentBoard;
public:
    explicit SudokuBoardService(SudokuBoardFactory & tSudokuFactory);
    // Constructor for the Board Service
    // param tSudokuFactory: Sudoku Factory which is used to get new boards

    const SudokuBoard & getCurrentBoard();
    // Gets the current board which is played

    bool checkValidBoard() const;
    // Checks if the board is valid (contains only unique values)
    // returns: true if the board is valid, false otherwise

    int setBoardCell(int row, int column, int value);
    // Sets the value for a new cell and returns a flag using BoardCellVariants
    // param row: Row of the cell which is modified
    // param column: Column of the cell which is modified
    // param value: Value of the cell which will be modified
    // returns: Binary flag with values from the enum BoardCellVariants

    bool checkWinner() const;
};

enum BoardCellVariants
{
    ValidValue = 0,
    InvalidValue = 1,
    InvalidRow = 2,
    InvalidColumn = 4,
    InvalidGrid = 8
};

#endif //SUDOKU_MADNESS_SUDOKUBOARDSERVICE_H
