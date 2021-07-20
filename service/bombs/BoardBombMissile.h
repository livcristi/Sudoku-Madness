//
// Created by tereb on 20.07.2021.
//

#ifndef SUDOKU_MADNESS_BOARDBOMBMISSILE_H
#define SUDOKU_MADNESS_BOARDBOMBMISSILE_H


#include "BoardBomb.h"

class BoardBombMissile : public BoardBomb
{
public:
    void bombBoard(SudokuBoard &board, int row, int column) override;
};


#endif //SUDOKU_MADNESS_BOARDBOMBMISSILE_H
