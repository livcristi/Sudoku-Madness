//
// Created by tereb on 14.07.2021.
//

#ifndef SUDOKU_MADNESS_SUDOKUREPOSITORY_H
#define SUDOKU_MADNESS_SUDOKUREPOSITORY_H

#include <string>
#include <vector>
#include "../domain/SudokuBoard.h"

/// Class definition for a file based sudoku repository

class SudokuRepository
{
private:
    std::string mFileName;
    std::vector<SudokuBoard> boards;
public:
    explicit SudokuRepository(std::string  tFileName);
    // Constructor for the file based repository
    // param tFileName: The file name from which the boards are read

    virtual SudokuBoard & getBoard();
    // Gets a board from the repository
    // throws: if the repository is empty

    virtual int size() const;
    // Gets the number of boards in the repository

    void addBoard(const SudokuBoard & board);
    // Adds a new board to the repository
    // param board: Sudoku Board which will be added to the repository

private:
    void readFile();
    // Reads the data from the file and stores the boards into the boards vector

    void writeToFile();
    // Writes the data from the repository to the file
};


#endif //SUDOKU_MADNESS_SUDOKUREPOSITORY_H
