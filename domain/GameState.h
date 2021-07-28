//
// Created by tereb on 28.07.2021.
//

#ifndef SUDOKU_MADNESS_GAMESTATE_H
#define SUDOKU_MADNESS_GAMESTATE_H


#include "SudokuBoard.h"

class GameState
{
private:
    SudokuBoard normalBoard;
    SudokuBoard maskBoard;
    std::string difficulty;
    int seconds;
public:
    GameState();

    GameState(SudokuBoard & tNormalBoard, SudokuBoard & tMaskBoard, std::string  tDifficulty, int tSeconds);

    const SudokuBoard &getNormalBoard() const;

    const SudokuBoard &getMaskBoard() const;

    const std::string &getDifficulty() const;

    int getSeconds() const;

    friend std::istream & operator >> (std::istream & in, GameState & state);
    // Istream operator overload

    friend std::ostream & operator << (std::ostream & out, const GameState & state);
    // Ostream operator overload
};


#endif //SUDOKU_MADNESS_GAMESTATE_H
