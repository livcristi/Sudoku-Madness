//
// Created by tereb on 14.07.2021.
//

#ifndef SUDOKU_MADNESS_SUDOKUBOARDFACTORY_H
#define SUDOKU_MADNESS_SUDOKUBOARDFACTORY_H

#include "../../repository/SudokuRepository.h"
#include "../generators/SudokuGenerator.h"
#include <memory>

/// Class for creating Sudoku boards ready to be played

class SudokuBoardFactory
{
private:
    SudokuRepository & mRepo;
    std::unique_ptr<SudokuGenerator> mGenerator;
public:
    explicit SudokuBoardFactory(SudokuRepository & tRepo);
    // Constructor for the factory
    // param tRepo: Reference to a SudokuRepository (from which the boards are retrieved or added by the factory)

    SudokuBoard createSudokuBoard(const std::string & difficulty, int size = 3);
    // Creates a new sudoku board with the given difficulty and size
    // param difficulty: Difficulty for the sudoku game (easy, medium, hard)
    // param size: Size of a grid on the sudoku board (default is 3)
    // returns: New sudoku board which has some missing cells (ready for begin played)
};


#endif //SUDOKU_MADNESS_SUDOKUBOARDFACTORY_H
