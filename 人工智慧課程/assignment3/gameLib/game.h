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
        gameBoardUnit lastStepUnit_;
        int player1Score, player2Score;
    public:
        game(int n, int m) : n_(n), m_(m), player1Score(0), player2Score(0) {};
        game(int n, int m, int score1, int score2) : n_(n), m_(m), player1Score(score1), player2Score(score2) {};
        void initBoard(std::vector<std::vector<int>> v, int n , int m);
        void printBoard();
        bool isBoardClean();
        void cleanRowOrColumnBoard(choosePoint cp, int pos);
        int getCurrentRowOrColumnSum(choosePoint cp, int pos);
        int getOneStepVal(choosePoint cp, int pos);
        void revertLastStepBoard();
        int getN() const;
        int getM() const;
        int getRowOrColumnScore(choosePoint cp, int pos);
        void updatePlayerScore(int score, bool isPlayer1);
        void printPlayerScore();
        void printFinalScore();
        void setplayer1Score(int score);
        void setplayer2Score(int score);
        int getPlayer1Score() const;
        int getPlayer2Score() const;
};
    
#endif