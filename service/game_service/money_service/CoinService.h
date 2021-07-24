//
// Created by tereb on 23.07.2021.
//

#ifndef SUDOKU_MADNESS_COINSERVICE_H
#define SUDOKU_MADNESS_COINSERVICE_H

#include <string>

/// Class for managing the coins

class CoinService
{
private:
    std::string mFileName;
    int mCoins;
public:
    explicit CoinService(std::string tFileName);
    // Constructor for the service
    // param tFileName: Name of the file in which the coin value is saved (persistent storage)

    int getCoins() const;
    // Get the amount of coins

    void addCoins(const std::string & difficulty, int time);
    // Add coins based on the previous game performance
    // param difficulty: The difficulty of the game
    // param time: The time (int minutes) taken to complete the board

    bool subtractCoins(int amount);
    // Tries to subtract an amount of coins
    // param amount: A positive amount of coins
    // returns: True if the amount was subtracted, False otherwise

    ~CoinService();
    // Destructor (saves the amount of coins in a file)
};


#endif //SUDOKU_MADNESS_COINSERVICE_H
