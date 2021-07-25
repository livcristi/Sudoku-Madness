//
// Created by tereb on 14.07.2021.
//

#include <QDir>

#include <fstream>
#include <cassert>
#include <iostream>
#include <memory>
#include "Tester.h"
#include "../domain/SudokuBoard.h"
#include "../repository/SudokuRepository.h"
#include "../service/generators/SudokuGenerator.h"
#include "../service/generators/BacktrackingSudokuGenerator.h"
#include "../service/factory/SudokuBoardFactory.h"
#include "../service/game_service/sudoku_service/SudokuBoardService.h"
#include "../service/game_service/money_service/CoinService.h"

void Tester::testAll()
{
    testSudokuBoard();
    testSudokuRepo();
    testSudokuChecker();
    testBktSudokuGenerator();
    testSudokuFactory();
    testBoardService();
    testBombing();
    testMarking();
    testCoinsService();
}

std::string getTestDataFile(int type = 1)
{
    if(type == 1)
        return R"(C:\Users\tereb\OneDrive\Desktop\Github-SM\Sudoku-Madness\testing\data\testing_data.txt)";
    else
        return R"(C:\Users\tereb\OneDrive\Desktop\Github-SM\Sudoku-Madness\testing\data\testing_coins.txt)";
    std::string dirPath = QDir::currentPath().toStdString();
    while(dirPath[dirPath.size() - 1] != '/')
        dirPath.pop_back();
    dirPath += "Sudoku-Madness/testing/data/testing_data.txt";
    return dirPath;
}

void Tester::testSudokuBoard()
{
    // Read a board from the data file and check it it was read correctly
    std::ifstream input(getTestDataFile());
    if(!input)
    {
        throw std::runtime_error("Error opening file!");
    }

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
    SudokuRepository testRepo(getTestDataFile());

    // Read the data from the file and check that it is equal and the repo read it well
    std::ifstream input(getTestDataFile());
    SudokuBoard testBoard1, testBoard2;
    input >> testBoard1 >> testBoard2;
    input.close();

    assert(testBoard1 == testRepo.getBoard());
    assert(testRepo.size() == 2);

    testRepo.addBoard(testBoard1);
    assert(testRepo.size() == 3);

    // Rewrite the data in the file
    std::ofstream output(getTestDataFile());
    output << testBoard1 << "\n" << testBoard2;
    output.close();
}

void Tester::testBktSudokuGenerator()
{
    std::unique_ptr<SudokuGenerator> testGenerator = std::make_unique<BacktrackingSudokuGenerator>();

    // Generate a few 4*4 boards and check that they are correct
    for(int i = 0; i < 5; ++i)
    {
        auto newBoard = testGenerator->generateBoard(2);
        assert(newBoard.getSize() == 4);
        assert(SudokuUniqueChecker::checkBoard(newBoard));

        for(int j = 0; j < 4; ++j)
            for(int k = 0; k < 4; ++k)
                assert(newBoard.getCellValue(j, k) > 0);
    }

    // Generate a few 9*9 boards and check that they are correct
    for(int i = 0; i < 5; ++i)
    {
        auto newBoard = testGenerator->generateBoard(3);
        assert(newBoard.getSize() == 9);
        assert(SudokuUniqueChecker::checkBoard(newBoard));
        for(int j = 0; j < 9; ++j)
            for(int k = 0; k < 9; ++k)
                assert(newBoard.getCellValue(j, k) > 0);
    }
}

void Tester::testSudokuChecker()
{
    // Get some valid boards
    std::ifstream input(getTestDataFile());
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

// Mocks for testing

// Create a mock repo (mostly for fun)
class MockRepo : public SudokuRepository
{
private:
    std::vector<SudokuBoard> boards;
public:
    int mSize;
public:
    MockRepo(const SudokuBoard & testBoard1, const SudokuBoard & testBoard2) :
            SudokuRepository(getTestDataFile())
    {
        boards.push_back(testBoard1);
        boards.push_back(testBoard2);
        mSize = 10;
    };

    SudokuBoard &getBoard() override
    {
        return boards[0];
    }

    int size() const override
    {
        return mSize;
    }
};

void Tester::testSudokuFactory()
{
    // Read the data from the file, it may get updated
    std::ifstream input(getTestDataFile());
    SudokuBoard testBoard1, testBoard2;
    input >> testBoard1 >> testBoard2;
    input.close();

    MockRepo testRepo(testBoard1, testBoard2);

    // Check that it retrieves from the repo
    SudokuBoardFactory testFactory(testRepo);
    auto newBoard = testFactory.createSudokuBoard("easy");
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j)
            assert(newBoard.getCellValue(i, j) == UnassignedCell || newBoard.getCellValue(i, j) == testBoard1.getCellValue(i, j));

    // Modify the repository
    testRepo.mSize = 2;

    // Check that the factory creates a new board
    newBoard = testFactory.createSudokuBoard("medium");
    assert(newBoard != testBoard1 && newBoard != testBoard2);
}

// Create a mock factory
class MockFactory : public SudokuBoardFactory
{
private:
    SudokuBoard & board;
public:
    MockFactory(SudokuRepository & repo, SudokuBoard & testBoard) : SudokuBoardFactory(repo), board(testBoard) {}

    SudokuBoard createSudokuBoard(const std::string &difficulty, int size) override
    {
        return board;
    }
};

void Tester::testBoardService()
{
    // Read the data from the file, it may get updated
    std::ifstream input(getTestDataFile());
    SudokuBoard testBoard1, testBoard2;
    input >> testBoard1 >> testBoard2;
    input.close();

    MockRepo mockRepo(testBoard1, testBoard2);
    MockFactory mockFactory(mockRepo, testBoard1);

    // Create the service and test it
    SudokuBoardService testService(mockFactory);

    // Change the first cell of the board which will be used in the service
    testBoard1.setCellValue(0, 0, 1);

    testService.createNewBoard("easy");

    assert(testService.getCurrentBoard() == testBoard1);
    assert(testService.checkWinner() == false);
    assert(testService.checkValidBoard() == false);
    assert(testService.setBoardCell(0, 0, 5) == InvalidCell);

    // Change the board to make it editable
    testBoard1.setCellValue(0, 0, UnassignedCell);
    testService.createNewBoard("easy");

    assert(testService.getCurrentBoard() == testBoard1);
    assert(testService.checkValidBoard() == true);
    assert(testService.checkWinner() == false);

    // Make a few changes to test the enum
    assert(testService.setBoardCell(0, 0, 14) == InvalidValue);
    assert(testService.setBoardCell(0, 0, 1) == (InvalidRow | InvalidColumn | InvalidGrid));
    assert(testService.setBoardCell(0, 0, 5) == ValidValue);
    assert(testService.checkWinner() == true);
}

void Tester::testBombing()
{
    // Read the data from the file, it may get updated
    std::ifstream input(getTestDataFile());
    SudokuBoard testBoard1, testBoard2;
    input >> testBoard1 >> testBoard2;
    input.close();

    MockRepo mockRepo(testBoard1, testBoard2);
    MockFactory mockFactory(mockRepo, testBoard1);

    // Create the service to have access to bombs
    SudokuBoardService testService(mockFactory);

    // Test bomb type 1 on corner
    testService.bombBoard(0, 0, 1);
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)
            assert(testService.getCurrentBoard().getCellValue(i, j) == BombedCell);

    // Test bomb type 1 on center cells
    testService.createNewBoard("easy");
    testService.bombBoard(1, 1, 1);
    int bombedCnt = 0;
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
        {
            if(testService.getCurrentBoard().getCellValue(i, j) == BombedCell)
                bombedCnt++;
        }
    assert(bombedCnt >= 5);

    // Test bomb type 2
    testService.createNewBoard("easy");
    testService.bombBoard(1, 1, 2);
    bombedCnt = 0;
    for(int i = 0; i < 9; ++i)
    {
        if(testService.getCurrentBoard().getCellValue(i, 1) == BombedCell ||
           testService.getCurrentBoard().getCellValue(1, i) == BombedCell)
            bombedCnt++;
    }
    assert(bombedCnt == 9);

    // Test bomb type 3
    testService.createNewBoard("easy");
    testService.bombBoard(3, 3, 3);
    bombedCnt = 0;
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(testService.getCurrentBoard().getCellValue(i, j) == BombedCell)
                bombedCnt++;
        }
    }
    assert(bombedCnt == 25);
}

void Tester::testMarking()
{
    // Read the data from the file, it may get updated
    std::ifstream input(getTestDataFile());
    SudokuBoard testBoard1, testBoard2;
    input >> testBoard1 >> testBoard2;
    input.close();

    MockRepo mockRepo(testBoard1, testBoard2);
    MockFactory mockFactory(mockRepo, testBoard1);

    // Create the service to have access to bombs
    SudokuBoardService testService(mockFactory);

    // Set an invalid value and check that the other cells were marked
    testBoard1.setCellValue(0, 0, UnassignedCell);
    testService.createNewBoard("easy");
    testService.setBoardCell(0, 0, 1);
    assert(testService.checkClashingCell(0, 0));
    assert(testService.checkClashingCell(0, 3));
    assert(testService.checkClashingCell(8, 0));
    assert(testService.checkClashingCell(1, 2));
    int count = 0;
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j)
            count += testService.checkClashingCell(i, j);
    assert(count == 4);

    // Make a correct mode and check again
    testService.setBoardCell(0, 0, 5);
    assert(!testService.checkClashingCell(0, 0));
    assert(!testService.checkClashingCell(0, 3));
    assert(!testService.checkClashingCell(8, 0));
    assert(!testService.checkClashingCell(1, 2));
    count = 0;
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j)
            count += testService.checkClashingCell(i, j);
    assert(count == 0);

    assert(testService.checkWinner());
}

void Tester::testCoinsService()
{
    // Save the value to add it at the end
    std::ifstream testFile(getTestDataFile(2));
    int testValue;
    testFile >> testValue;
    testFile.close();

    // Test the coin service with a few operations
    {
        CoinService testService(getTestDataFile(2));
        assert(testService.getCoins() == 100);

        testService.addCoins("Easy", 15);
        assert(testService.getCoins() > 130 && testService.getCoins() < 200);

        assert(testService.subtractCoins(100));
        assert(testService.getCoins() < 100);

        testService.addCoins("Medium", 30);
        assert(testService.getCoins() > 50);
    }


    std::ofstream testFileOut(getTestDataFile(2));
    testFileOut << testValue;
    testFileOut.close();
}
