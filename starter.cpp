//
// Created by tereb on 14.07.2021.
//

#include <iostream>
#include <ctime>
#include "testing/Tester.h"

int main()
{
    srand(time(nullptr));
    Tester::testAll();
    std::cout << "Everything alright so far!";
    return 0;
}