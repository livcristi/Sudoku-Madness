//
// Created by tereb on 14.07.2021.
//

#ifndef SUDOKU_MADNESS_SUDOKUGENERATOR_H
#define SUDOKU_MADNESS_SUDOKUGENERATOR_H

#include "../domain/SudokuBoard.h"

/// Base class for the SudokuGenerator
/// This will be used as an approach to the Strategy Design pattern to have multiple ways of generating boards

class SudokuGenerator
{
public:
    virtual SudokuBoard generateBoard(int size) = 0;
};


#endif //SUDOKU_MADNESS_SUDOKUGENERATOR_H
