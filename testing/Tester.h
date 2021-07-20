//
// Created by tereb on 14.07.2021.
//

#ifndef SUDOKU_MADNESS_TESTER_H
#define SUDOKU_MADNESS_TESTER_H


class Tester
{
public:
    static void testAll();

private:
    static void testSudokuBoard();
    static void testSudokuRepo();
    static void testSudokuChecker();
    static void testBktSudokuGenerator();
    static void testSudokuFactory();
    static void testBoardService();
    static void testBombing();
    static void testMarking();
};


#endif //SUDOKU_MADNESS_TESTER_H
