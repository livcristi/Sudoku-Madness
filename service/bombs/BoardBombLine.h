//
// Created by tereb on 20.07.2021.
//

#ifndef SUDOKU_MADNESS_BOARDBOMBLINE_H
#define SUDOKU_MADNESS_BOARDBOMBLINE_H


#include "BoardBomb.h"

class BoardBombLine : public BoardBomb
{
public:
    void bombBoard(SudokuBoard &board, int row, int column) override;
};


#endif //SUDOKU_MADNESS_BOARDBOMBLINE_H
