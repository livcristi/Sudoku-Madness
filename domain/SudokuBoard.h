//
// Created by tereb on 14.07.2021.
//

#ifndef SUDOKU_MADNESS_SUDOKUBOARD_H
#define SUDOKU_MADNESS_SUDOKUBOARD_H

#include <vector>
#include <istream>
#include <ostream>

/// Class definition for the Sudoku Board used in the game

class SudokuBoard
{
private:
    std::vector<std::vector<int>> mBoard;
public:
    explicit SudokuBoard(int size = 3);
    // Constructor for a board of size size^2 * size^2 (normally it is 9*9)

    SudokuBoard(const SudokuBoard & sudokuBoard);
    // Copy constructor

    int getSize() const;
    // Get the size of the board

    int getCellValue(int row, int column) const;
    // Get the value of a cell in the given row and column
    // Param row: The number of the row (starting from 0)
    // Param column: The number of the column (starting from 0)

    void setCellValue(int row, int column, int newValue);
    // Sets the value of a cell in the given row and column
    // Param row: The number of the row (starting from 0)
    // Param column: The number of the column (starting from 0)
    // Param newValue: The value which will be added to the cell

    const std::vector<std::vector<int>> &getBoard() const;
    // Gets the board as a std::vector matrix

    friend std::istream & operator >> (std::istream & in, SudokuBoard & board);
    friend std::ostream & operator << (std::ostream & out, const SudokuBoard &board);
};


#endif //SUDOKU_MADNESS_SUDOKUBOARD_H
