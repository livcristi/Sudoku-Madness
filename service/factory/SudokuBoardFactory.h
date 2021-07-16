//
// Created by tereb on 14.07.2021.
//

#ifndef SUDOKU_MADNESS_SUDOKUBOARDFACTORY_H
#define SUDOKU_MADNESS_SUDOKUBOARDFACTORY_H

#include "../../repository/SudokuRepository.h"
#include "../generators/SudokuGenerator.h"
#include <memory>

class SudokuBoardFactory
{
private:
    SudokuRepository & mRepo;
    std::unique_ptr<SudokuGenerator> mGenerator;
public:
    explicit SudokuBoardFactory(SudokuRepository & tRepo);
    SudokuBoard createSudokuBoard(int size = 3);
};


#endif //SUDOKU_MADNESS_SUDOKUBOARDFACTORY_H
