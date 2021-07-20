//
// Created by tereb on 20.07.2021.
//

#ifndef SUDOKU_MADNESS_BOARDBOMBGRENADE_H
#define SUDOKU_MADNESS_BOARDBOMBGRENADE_H


#include "BoardBomb.h"

class BoardBombGrenade : public BoardBomb
{
public:
    void bombBoard(SudokuBoard & board, int row, int column) override;
};


#endif //SUDOKU_MADNESS_BOARDBOMBGRENADE_H
