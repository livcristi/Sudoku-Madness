//
// Created by tereb on 14.07.2021.
//

#include "SudokuRepository.h"

#include <utility>
#include <fstream>

SudokuRepository::SudokuRepository(std::string tFileName) : mFileName(std::move(tFileName))
{
    this->readFile();
}

SudokuBoard & SudokuRepository::getBoard()
{
    if(boards.empty())
        throw std::runtime_error("Cannot get a board");
    // todo: the get will also remove the returned board
    return boards[0];
}

int SudokuRepository::size() const
{
    return (int) boards.size();
}

void SudokuRepository::addBoard(const SudokuBoard &board)
{
    boards.push_back(board);
    this->writeToFile();
}

void SudokuRepository::readFile()
{
    std::ifstream inputFile(mFileName);
    if(!inputFile)
        throw std::runtime_error("Error during opening file for reading!");
    SudokuBoard board;
    while(inputFile >> board)
        boards.push_back(board);
    inputFile.close();
}

void SudokuRepository::writeToFile()
{
    std::ofstream outputFile(mFileName);
    if(!outputFile)
        throw std::runtime_error("Error during opening file for writing!");
    for(const auto & board : boards)
        outputFile << board << "\n";
    outputFile.close();
}