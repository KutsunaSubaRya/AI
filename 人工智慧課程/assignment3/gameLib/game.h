#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <string>
#include <sstream>
#include "board.h"

enum class choosePoint
{
    ROW,
    COLUMN
};
class game
{
private:
    gameBoardUnit gB_;
    const int n_, m_;
    gameBoardUnit lastStepUnit_;
    int player1Score, player2Score;

public:
    game(int n, int m) : n_(n), m_(m), player1Score(0), player2Score(0){}; // constructor init game board
    game(int n, int m, int score1, int score2) : n_(n), m_(m), player1Score(score1), player2Score(score2){}; // constructor init game board
    void initBoard(std::vector<std::vector<int>> v, int n, int m); // init game board
    void printBoard(); // 得到 game board 的大小 api
    bool isBoardClean(); // board 是否清空的 api
    void cleanRowOrColumnBoard(choosePoint cp, int pos); // 指定其中的 row 或 column 並將其清空
    int getCurrentRowOrColumnSum(choosePoint cp, int pos); // 得到其中的 row 或 column 的 1 (棋子) 的數量的 api
    void nextOneStep(choosePoint cp, int pos); // 下一回輪的操作的 api
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