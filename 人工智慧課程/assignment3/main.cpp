#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include "./gameLib/basic.h"
#include "./gameLib/game.h"
#include "./gameLib/board.h"
int solution[10005]={0};

int main(void){
    auto started = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> v;
    v = initBoard(); // take the initial testcase of the game board
    int x=v.size(), y=v[0].size();
    printBoard(v, x, y); // print the initial testcase of the game board
    // start to write code here ...

    game gB(x,y); // construct new game board
    gB.initBoard(v, x, y); // initialize the game board
    gB.printBoard();
    return 0;
}