//
// Created by tereb on 20.07.2021.
//

#include "BoardBombGrenade.h"

void BoardBombGrenade::bombBoard(SudokuBoard &board, int row, int column)
{
    // Type 1 -> destroy some neighbouring cells
    std::vector<std::vector<int>> dir = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {1, -1}, {1, 1}, {-1, 0}, {-1, 1}, {-1, -1}};
    std::vector<bool> used(9, false);

    int attackedCells = rand() % 3 + 5;
    // Special case: Corners
    if(row == 0 || column == 0 || row == board.getSize() - 1 || column == board.getSize() - 1)
    {
        attackedCells = 4;
    }
    while(attackedCells > 0)
    {
        int attackDir = rand() % 9;
        if(used[attackDir])
            continue;
        int attackedRow = row + dir[attackDir][0];
        int attackedColumn = column + dir[attackDir][1];

        // Check if the attacked cell is within boundaries
        if(attackedRow < 0 || attackedRow >= board.getSize() ||
           attackedColumn < 0 || attackedColumn >= board.getSize())
        {
            continue;
        }
        board.setCellValue(attackedRow, attackedColumn, BombedCell);
        used[attackDir] = true;
        attackedCells--;
    }
}
