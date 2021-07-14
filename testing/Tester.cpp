//
// Created by tereb on 14.07.2021.
//

#include <fstream>
#include <cassert>
#include <iostream>
#include "Tester.h"
#include "../domain/SudokuBoard.h"

void Tester::testAll()
{
    testSudokuBoard();
}

void Tester::testSudokuBoard()
{
    // Read a board from the data file and check it it was read correctly
    std::ifstream input(R"(C:\Users\tereb\OneDrive\Desktop\Sudoku-Madness\testing\data\testing_data.txt)");
    if(!input)
        throw std::runtime_error("Error opening file!");

    SudokuBoard testBoard;
    input >> testBoard;

    assert(testBoard.getSize() == 9);
    assert(testBoard.getCellValue(0, 0) == 5);
    assert(testBoard.getCellValue(8, 8) == 2);

    // Read and test the next board
    SudokuBoard testBoard2;
    input >> testBoard2;

    assert(testBoard2.getSize() == 9);
    assert(testBoard2.getCellValue(0, 0) == 5);
    assert(testBoard2.getCellValue(8, 8) == 8);

    testBoard.setCellValue(1, 1, 4);
    assert(testBoard.getCellValue(1, 1) == 4);

    input.close();
}
