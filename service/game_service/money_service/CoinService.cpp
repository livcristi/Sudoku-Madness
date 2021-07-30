//
// Created by tereb on 23.07.2021.
//

#include "CoinService.h"
#include <fstream>
#include <utility>

CoinService::CoinService(std::string tFileName) : mFileName(std::move(tFileName)), mCoins(0)
{
    std::ifstream inputFile(mFileName);
    inputFile >> mCoins;
    inputFile.close();
}

CoinService::~CoinService()
{
    std::ofstream outputFile(mFileName);
    outputFile << mCoins;
    outputFile.close();
}

int CoinService::getCoins() const
{
    return mCoins;
}

void CoinService::addCoins(const std::string &difficulty, int time)
{
    if(difficulty == "Easy" || difficulty == "easy")
        mCoins += (60 - time <= 0 ? 10 : 60 - time);
    else if(difficulty == "Medium" || difficulty == "medium")
        mCoins += (80 - time <= 0 ? 30 : 80 - time);
    else if(difficulty == "Hard" || difficulty == "hard")
        mCoins += (100 - time <= 0 ? 50 : 100 - time);
    else
        mCoins += 10;
}

bool CoinService::subtractCoins(int amount)
{
    if(amount <= mCoins)
    {
        mCoins -= amount;
        return true;
    }
    else
        return false;
}

