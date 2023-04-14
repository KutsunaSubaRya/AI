#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "basic.h"
#include "game.h"
#include "board.h"
int solution[10005]={0};
int clusterOfOne(std::vector<int> v){
    std::vector<int> clusters;
    int currentClusterSize = 0;

    for (int i = 0; i < v.size(); i++) {
        if (v[i] == 1) {
            currentClusterSize++;
        } else if (currentClusterSize > 0) {
            clusters.push_back(currentClusterSize);
            currentClusterSize = 0;
        }
    }

    if (currentClusterSize > 0) {
        clusters.push_back(currentClusterSize);
    }

    return clusters.size();
}
int IDAstar(game gB, std::vector<int> v, int& gx, int& bound, bool& ans){
    // printf("This is round %d, and the board is like this: \n", gx);
    // gB.printBoard();
    // g(x) = round
    // h(x) = number of the virus on game board
	// int hx = gB.getVirusNumber();
    int hx =  clusterOfOne(v);
    const int sz = gB.getBoardSize();
	if (gx + hx > bound) {
        return gx + hx;	// 超過深度，回傳下次的bound
    }
    if (hx == 0 || !gB.isGameContinue()) {
        ans = true;
        return gx;
    }	// 找到最佳解

	int nextBound = 1e9;
	for (int idx=0; idx<sz; ++idx){				// find 1
		if(v[idx] == 1){
            solution[gx] = idx;					// record the eliminate pos

            game tmpgB(v.size());
            tmpgB.initBoard(v);
            std::vector<int> tmpv;
            tmpv = tmpgB.getOneStepResult(idx);

            ++gx;
            int ret = IDAstar(tmpgB, tmpv, gx, bound, ans);
            if (ans) return ret;
            --gx;
            nextBound = std::min(nextBound, ret);

        }
            
	}
	return nextBound;
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
	int bound = 0, gx = 0;
	while (!ans && bound <= 100)
		bound = IDAstar(gB, v, gx, bound, ans);
    
    printf("Ans: ");
    for(int idx=0;idx<gx;++idx){
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

// heuristic cluster of 1's number 
// testcase length 20
// result below:
// Board: 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
// Ans: 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19
// Time taken by program is : 103 sec