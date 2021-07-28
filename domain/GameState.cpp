//
// Created by tereb on 28.07.2021.
//

#include "GameState.h"

#include <utility>

GameState::GameState()
{
    normalBoard = SudokuBoard();
    maskBoard = SudokuBoard();
    seconds = 0;
}

GameState::GameState(SudokuBoard &tNormalBoard, SudokuBoard &tMaskBoard, std::string  tDifficulty, int tSeconds) :
        normalBoard(tNormalBoard), maskBoard(tMaskBoard), difficulty(std::move(tDifficulty)), seconds(tSeconds)
{}

std::istream &operator>>(std::istream &in, GameState & state)
{
    in >> state.normalBoard >> state.maskBoard >> state.difficulty >> state.seconds;
    return in;
}

std::ostream &operator<<(std::ostream &out, const GameState & state)
{
    out << state.normalBoard << "\n";
    out << state.maskBoard << "\n";
    out << state.difficulty << "\n";
    out << state.seconds << "\n";
    return out;
}

const SudokuBoard &GameState::getNormalBoard() const {
    return normalBoard;
}

const SudokuBoard &GameState::getMaskBoard() const {
    return maskBoard;
}

int GameState::getSeconds() const {
    return seconds;
}

const std::string &GameState::getDifficulty() const {
    return difficulty;
}

