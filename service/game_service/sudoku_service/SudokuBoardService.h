//
// Created by tereb on 16.07.2021.
//

#ifndef SUDOKU_MADNESS_SUDOKUBOARDSERVICE_H
#define SUDOKU_MADNESS_SUDOKUBOARDSERVICE_H

#include "../../factory/SudokuBoardFactory.h"
#include "../../bombs/BoardBomb.h"
#include <memory>

/// Class for the game board service, which handles main events on the playable board

class SudokuBoardService
{
private:
    SudokuBoardFactory &mSudokuFactory;
    SudokuBoard mCurrentBoard;
    SudokuBoard mMaskBoard;
    std::vector<std::unique_ptr<BoardBomb>> bombs;
    std::string saveFile;
    std::string currentDifficulty;
public:
    const std::string &getCurrentDifficulty() const;

public:
    explicit SudokuBoardService(SudokuBoardFactory &tSudokuFactory, std::string tSaveFile = "");
    // Constructor for the Board Service
    // param tSudokuFactory: Sudoku Factory which is used to get new boards

    const SudokuBoard &getCurrentBoard();
    // Gets the current board which is played

    bool checkValidBoard() const;
    // Checks if the board is valid (contains only unique values)
    // returns: true if the board is valid, false otherwise

    int setBoardCell(int row, int column, int value);
    // Sets the value for a new cell and returns a flag using BoardCellVariants
    // param row: Row of the cell which is modified
    // param column: Column of the cell which is modified
    // param value: Value of the cell which will be modified
    // returns: Binary flag with values from the enum BoardCellVariants

    bool checkWinner() const;
    // Check if the player won (the board is completed and correct)

    void createNewBoard(const std::string &difficulty);
    // Creates a new Sudoku board

    bool checkOccupiedCell(int row, int column);
    // Checks if a cell at the given row and column is pre-made (not to be edited by the player)
    // param row: Row of the cell
    // param column: Column of the cell
    // returns: True if the cell is occupied, false otherwise

    bool checkClashingCell(int row, int column);
    // Checks if a cell is clashing with another cell

    void bombBoard(int row, int column, int bombType);
    // Bombs a cell at the given row and column with a bomb of the specified type

    int loadGameFromFile();

    void saveGameToFile(int seconds);
private:
    void markClashingCells();
};

#endif //SUDOKU_MADNESS_SUDOKUBOARDSERVICE_H
