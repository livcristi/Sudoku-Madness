//
// Created by tereb on 20.07.2021.
//

#ifndef SUDOKU_MADNESS_BOARDBOMB_H
#define SUDOKU_MADNESS_BOARDBOMB_H

#include "../../domain/SudokuBoard.h"

/// Base class for the bombs

class BoardBomb
{
public:
    virtual void bombBoard(SudokuBoard & board, int row, int column) = 0;
};


#endif //SUDOKU_MADNESS_BOARDBOMB_H
