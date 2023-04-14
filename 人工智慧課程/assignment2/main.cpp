#include <stdio.h>
#include <vector>
#include "basic.h"
#include "game.h"
#include "board.h"


int main(void){
    std::vector<int> v;
    v = initBoard();

    // start to write code here ...
    
    game gB(v.size());
    gB.initBoard(v);
    printBoard(v);
    
    return 0;
}