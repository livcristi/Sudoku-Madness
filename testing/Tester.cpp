//
// Created by tereb on 14.07.2021.
//

#include <fstream>
#include <cassert>
#include <iostream>
#include <memory>
#include "Tester.h"
#include "../domain/SudokuBoard.h"
#include "../repository/SudokuRepository.h"
#include "../generators/SudokuGenerator.h"
#include "../generators/BacktrackingSudokuGenerator.h"

void Tester::testAll()
{
    testSudokuBoard();
    testSudokuRepo();
    testSudokuChecker();
    testBktSudokuGenerator();
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

void Tester::testSudokuRepo()
{
    // Create a test repository
    SudokuRepository testRepo(R"(C:\Users\tereb\OneDrive\Desktop\Sudoku-Madness\testing\data\testing_data.txt)");

    // Read the data from the file and check that it is equal and the repo read it well
    std::ifstream input(R"(C:\Users\tereb\OneDrive\Desktop\Sudoku-Madness\testing\data\testing_data.txt)");
    SudokuBoard testBoard1, testBoard2;
    input >> testBoard1 >> testBoard2;
    input.close();

    assert(testBoard1 == testRepo.getBoard());
    assert(testRepo.size() == 2);

    testRepo.addBoard(testBoard1);
    assert(testRepo.size() == 3);

    // Rewrite the data in the file
    std::ofstream output(R"(C:\Users\tereb\OneDrive\Desktop\Sudoku-Madness\testing\data\testing_data.txt)");
    output << testBoard1 << "\n" << testBoard2;
    output.close();
}

void Tester::testBktSudokuGenerator()
{
    std::unique_ptr<SudokuGenerator> testGenerator = std::make_unique<BacktrackingSudokuGenerator>();

    auto newBoard = testGenerator->generateBoard(3);

    assert(newBoard.getSize() == 9);
    assert(SudokuUniqueChecker::checkBoard(newBoard));

    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            std::cout << newBoard.getCellValue(i, j) << " ";
        }
        std::cout << "\n";
    }
}

void Tester::testSudokuChecker()
{
    // Get some valid boards
    std::ifstream input(R"(C:\Users\tereb\OneDrive\Desktop\Sudoku-Madness\testing\data\testing_data.txt)");
    SudokuBoard testBoard1, testBoard2;
    input >> testBoard1 >> testBoard2;
    input.close();

    // Change testBoard2 to become invalid
    testBoard2.setCellValue(0, 3, 5);

    SudokuUniqueChecker testChecker;
    // Test that it passes the valid board
    assert(testChecker.checkBoard(testBoard1));

    // Test that it does not pass the invalid board
    assert(!testChecker.checkBoard(testBoard2));
    assert(!testChecker.checkRow(testBoard2, 0));
    assert(!testChecker.checkColumn(testBoard2, 3));
    assert(!testChecker.checkGrid(testBoard2, 1));
}
