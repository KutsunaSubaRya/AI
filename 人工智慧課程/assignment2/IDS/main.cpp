#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "../gameLib/basic.h"
#include "../gameLib/game.h"
#include "../gameLib/board.h"
int solution[10005]={0};
bool DLS(game gB, std::vector<int> v, int& step, int limit){
    // printf("This is round %d, and the board is like this: \n", step);
    // gB.printBoard();
    
    if (!gB.isGameContinue())
        return true;
    
    // If reached the maximum depth, stop recursing.
    if (limit <= 0)
        return false;

    const int sz = gB.getBoardSize();
    for (int idx=0; idx<sz; ++idx){				
		if(v[idx] == 1){
            solution[step] = idx;
            game tmpgB(v.size());
            tmpgB.initBoard(v);
            std::vector<int> tmpv;
            tmpv = tmpgB.getOneStepResult(idx);
            ++step;
            if (DLS(tmpgB, tmpv, step, limit-1) == true){
                return true;
            }
            --step;
        }
    }

    return false;
}
   
// IDDFS to search if target is reachable from v.
// It uses recursive DFSUtil().
bool IDDFS(game gB, std::vector<int> v, int& step, int maxDepth){
    // Repeatedly depth-limit search till the
    // maximum depth.
    for (int i = 0; i <= maxDepth; i++){
        int r = 0;
        if (DLS(gB, v, r, i) == true){
            step = r;
            return true;
        }
    }
    return false;
}

int main(void){
    time_t start, end;
    time(&start);

    std::vector<int> v;
    v = initBoard(); // take the initial testcase of the game board

    // start to write code here ...
    
    game gB(v.size()); // construct new game board
    gB.initBoard(v);
    printBoard(v);
    bool ans = false;
	int bound = 10000, round = 0;
	while (!ans){
		ans = IDDFS(gB, v, round, bound);
    }
    std::cout << "round = " << round << "\n";
    printf("Ans: ");
    for(int idx=0;idx<round;++idx){
        printf("%d ", solution[idx]+1);
    }
    printf("\n");

    time(&end);

    // Calculating total time taken by the program.
    double time_taken = double(end - start);
    std::cout << "Time taken by program is : " << std::fixed << time_taken << std::setprecision(5);
    std::cout << " sec " << "\n";
    return 0;
}

// IDS
// testcase length 14
// result below:
// Board: 0 1 0 1 0 1 0 1 0 1 0 1 0 1
// round = 12
// Ans: 2 3 4 5 6 7 8 9 10 11 12 13
// Time taken by program is : 573.000000 sec