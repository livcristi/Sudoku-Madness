//
// Created by tereb on 20.07.2021.
//

#include <queue>
#include <cmath>
#include "BoardBombMissile.h"

void BoardBombMissile::bombBoard(SudokuBoard &board, int row, int column)
{
    // Type 3 -> destroy more cells (in a BFS manner)
    // Set up a direction vector and a visited matrix
    std::vector<std::vector<int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    std::vector<std::vector<int>> visitedMap (board.getBoard());
    for(int i = 0; i < board.getSize(); ++i)
        for(int j = 0; j < board.getSize(); ++j)
            visitedMap[i][j] = 0;
    std::queue<std::pair<int, int>> moveQueue;
    std::queue<std::pair<int, int>> tempQueue;
    moveQueue.push({row, column});
    board.setCellValue(row, column, BombedCell);
    visitedMap[row][column] = 1;
    int noSteps = (int)sqrt(board.getSize());
    for(int steps = 0; steps < noSteps; ++steps)
    {
        while(!moveQueue.empty())
        {
            auto point = moveQueue.front();
            moveQueue.pop();
            for(int k = 0; k < 4; ++k)
            {
                int newX = point.first + dir[k][0];
                int newY = point.second + dir[k][1];
                if(newX < 0 || newX >= board.getSize() || newY < 0 || newY >= board.getSize() || visitedMap[newX][newY])
                    continue;
                board.setCellValue(newX, newY, BombedCell);
                tempQueue.push({newX, newY});
                visitedMap[newX][newY] = 1;
            }
        }
        while(!tempQueue.empty())
        {
            moveQueue.push(tempQueue.front());
            tempQueue.pop();
        }
    }
}
