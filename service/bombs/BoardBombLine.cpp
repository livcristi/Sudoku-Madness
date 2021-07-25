//
// Created by tereb on 20.07.2021.
//

#include "BoardBombLine.h"

void BoardBombLine::bombBoard(SudokuBoard &board, int row, int column)
{
    // Type 2 -> destroy line or column
    int attack = rand() % 2;
    if(attack == 0)
    {
        for(int i = 0; i < board.getSize(); ++i)
            board.setCellValue(row, i, BombedCell);
    }
    else
    {
        for(int i = 0; i < board.getSize(); ++i)
            board.setCellValue(i, column, BombedCell);
    }
}
