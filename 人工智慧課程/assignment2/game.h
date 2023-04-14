#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <string>
#include <sstream>
#include "board.h"

class game{
    private:
        gameBoardUnit gB_;
        const int boardSize_;
    public:
        game(int boardSize) : boardSize_(boardSize) {};
        void initBoard(std::vector<int> v);
        void printBoard();
        const int getBoardSize() const ;
        const int getVirusNumber() const;
        const bool isBoardClean() const;
        const bool isGameContinue() const;
        std::vector<int> getOneStepResult(const int pos);
        void virusSplit(void);
        void cleanPosVirus(const int pos);
};
    
#endif