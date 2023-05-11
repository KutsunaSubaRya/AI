#include "game.h"

void game::initBoard(std::vector<std::vector<int>> v, int n , int m){
    gB_.initBoard(v, n, m);
}

void game::printBoard(){
    gB_.printBoard();
}
