//
// Created by tereb on 14.07.2021.
//

#ifndef SUDOKU_MADNESS_BACKTRACKINGSUDOKUGENERATOR_H
#define SUDOKU_MADNESS_BACKTRACKINGSUDOKUGENERATOR_H

#include "SudokuGenerator.h"
#include "SudokuUniqueChecker.h"

/// Class for generating a sudoku board using backtracking

class BacktrackingSudokuGenerator : public SudokuGenerator
{
public:
    SudokuBoard generateBoard(int size) override;
    // Generates a new Sudoku board of given size
private:
    bool backtracking(SudokuBoard & board, int row, int column);
    // The backtracking method to generate the board
};


#endif //SUDOKU_MADNESS_BACKTRACKINGSUDOKUGENERATOR_H
