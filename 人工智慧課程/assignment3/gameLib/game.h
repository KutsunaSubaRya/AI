#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <string>
#include <sstream>
#include "board.h"

enum class choosePoint{
    ROW,
    COLUMN
};
class game{
    private:
        gameBoardUnit gB_;
        const int n_, m_;
    public:
        game(int n, int m) : n_(n), m_(m) {};
        void initBoard(std::vector<std::vector<int>> v, int n , int m);
        void printBoard();
        void cleanRowOrColumnBoard(choosePoint cp, int pos);
        int getCurrentRowOrColumnSum(choosePoint cp, int pos);
        int getOneStepVal(choosePoint cp, int pos);
};
    
#endif