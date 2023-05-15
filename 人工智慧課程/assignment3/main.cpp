#include <stdio.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include "./gameLib/basic.h"
#include "./gameLib/game.h"
#include "./gameLib/board.h"

int selectPosI = 1;
bool sortByFir(const std::pair<int,int> &a,const std::pair<int,int> &b){
    return (a.first > b.first);
}

// choosePoint::ROW and choosePoint::COLUMN are son of the node
// in one choose, we need to choose one of the row or column point
// use first person get score minus second person get score as evaluation function
int AlphaBetaPruing(game gB, std::vector<std::vector<int>> v, int alpha, int beta, bool isMax, int depth, bool currentPlayer) {
    // board clean then return
    if(gB.isBoardClean()){
        return gB.getPlayer1Score() - gB.getPlayer2Score();
    }
    int len = gB.getN() + gB.getM();
    // printf("isMax = %d\n", isMax);
    // printf("len = %d\n", len);
    if(isMax){
        int maxVal = -1000000;
        std::pair<int,int> arr[len]; // first val, second index
        for(int i=1; i<=len; i++){
            if(i<=gB.getN()){ // choosePoint::ROW
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::ROW, i);
                arr[i-1] = std::make_pair(currentScore, i);
                if(currentScore == 0){
                    continue;
                }
            }
            else{ // choosePoint::COLUMN
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::COLUMN, i-gB.getN());
                arr[i-1] = std::make_pair(currentScore, i);
                if(currentScore == 0){
                    continue;
                }
            }
        }
        std::sort(arr, arr+len, sortByFir);
        // for(int i=1; i<=len; i++){
        for(int j=1; j<=len; j++){
            int i = arr[j-1].second;
            if (i == 0){
                continue;
            }
            // printf("HI\n");
            if(i<=gB.getN()){ // choosePoint::ROW
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::ROW, i);
                if(currentScore == 0){
                    continue;
                }
                game tmpGB = gB;
                tmpGB.getOneStepVal(choosePoint::ROW, i);
                
                tmpGB.setplayer1Score(currentScore);
                // printf("i = %d currentEVal = %d depth = %d\n", i, currentEVal, depth);
                int val = AlphaBetaPruing(tmpGB, v, alpha, beta, false, depth-1, currentPlayer);
                if(depth == 16 && val >= maxVal){
                    maxVal = val;
                    selectPosI = i;
                }
                else{
                    maxVal = std::max(maxVal, val);
                }
                alpha = std::max(alpha, maxVal);
                if(beta <= alpha){
                    // printf("max Prune\n");
                    break;
                }
                // printf("i = %d currentEVal = %d\n", i, currentEVal);
            }
            else{ // choosePoint::COLUMN
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::COLUMN, i-gB.getN());
                if(currentScore == 0){
                    continue;
                }
                game tmpGB = gB;
                tmpGB.getOneStepVal(choosePoint::COLUMN, i-gB.getN());
                
                tmpGB.setplayer1Score(currentScore);
                // printf("i = %d currentEVal = %d depth = %d\n", i, currentEVal, depth);
                int val = AlphaBetaPruing(tmpGB, v, alpha, beta, false, depth-1, currentPlayer);
                if(depth == 16 && val >= maxVal){
                    maxVal = val;
                    selectPosI = i;
                }
                else{
                    maxVal = std::max(maxVal, val);
                }
                alpha = std::max(alpha, maxVal);
                if(beta <= alpha){
                    // printf("max Prune\n");
                    break;
                }
                // printf("i = %d currentEVal = %d\n", i, currentEVal);
            }
            // printf("i = %d maxVal = %d\n", i, maxVal);
        }
        return maxVal;
    }
    else{
        int minVal = 1000000;
        std::pair<int,int> arr[len]; // first val, second index
        for(int i=1; i<=len; i++){
            if(i<=gB.getN()){ // choosePoint::ROW
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::ROW, i);
                arr[i-1] = std::make_pair(currentScore, i);
                if(currentScore == 0){
                    continue;
                }
            }
            else{ // choosePoint::COLUMN
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::COLUMN, i-gB.getN());
                arr[i-1] = std::make_pair(currentScore, i);
                if(currentScore == 0){
                    continue;
                }
            }
        }
        std::sort(arr, arr+len, sortByFir);
        // for(int i=1; i<=len; i++){
        for(int j=1; j<=len; j++){
            int i = arr[j-1].second;
            if (i == 0){
                continue;
            }
            if(i<=gB.getN()){ // choosePoint::ROW
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::COLUMN, i-gB.getN());
                if(currentScore == 0){
                    continue;
                }
                game tmpGB = gB;
                tmpGB.getOneStepVal(choosePoint::ROW, i);
                
                tmpGB.setplayer2Score(currentScore);
                // printf("i = %d currentEVal = %d depth = %d\n", i, currentEVal, depth);
                int val = AlphaBetaPruing(tmpGB, v, alpha, beta, true, depth-1, currentPlayer);
                minVal = std::min(minVal, val);
                beta = std::min(beta, minVal);
                if(beta <= alpha){
                    // printf("min Prune\n");
                    break;
                }
            }
            else { //choosePoint::COLUMN
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::COLUMN, i-gB.getN());
                if(currentScore == 0){
                    continue;
                }
                game tmpGB = gB;
                tmpGB.getOneStepVal(choosePoint::COLUMN, i-gB.getN());
                
                tmpGB.setplayer2Score(currentScore);
                // printf("i = %d currentEVal = %d depth = %d\n", i, currentEVal, depth);
                int val = AlphaBetaPruing(tmpGB, v, alpha, beta, true, depth-1, currentPlayer);
                minVal = std::min(minVal, val);
                beta = std::min(beta, minVal);
                if(beta <= alpha){
                    // printf("min Prune\n");
                    break;
                }
            }
        }
        return minVal;
    }
}

int main(void){
    auto started = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> v;
    v = initBoard(); // take the initial testcase of the game board
    int x=v.size(), y=v[0].size();
    // start to write code logic here ...
    game gB(x, y, 0, 0); // construct new game board
    gB.initBoard(v, x, y); // initialize the game board
    bool player = true; // player 1 first
    bool isFirstChoose = true;
    int ansSelectPos = 1;
    while(!gB.isBoardClean()){ // play game until the board is clean
        selectPosI = 1;
        int val = AlphaBetaPruing(gB, v, -1000000, 1000000, true, 16, player);
        // printf("ab prune ret val = %d\n", val);
        // printf("selectPosI = %d\n", selectPosI);
        // give the player score he/she choose
        // gB.printBoard();
        if(isFirstChoose){
            ansSelectPos = selectPosI;
            isFirstChoose = false;
        }
        if(selectPosI <= gB.getN()){ // choosePoint::ROW
            // printf("player = %d, score = %d\n", player, gB.getRowOrColumnScore(choosePoint::ROW, selectPosI));
            gB.updatePlayerScore(gB.getRowOrColumnScore(choosePoint::ROW, selectPosI), player);
            gB.cleanRowOrColumnBoard(choosePoint::ROW, selectPosI);
        }
        else{ // choosePoint::COLUMN
            // printf("player = %d, score = %d\n", player, gB.getRowOrColumnScore(choosePoint::COLUMN, selectPosI));
            gB.updatePlayerScore(gB.getRowOrColumnScore(choosePoint::COLUMN, selectPosI), player);
            gB.cleanRowOrColumnBoard(choosePoint::COLUMN, selectPosI-gB.getN());
        }
        // gB.printBoard();
        player = !player;
    }
    if(ansSelectPos <= gB.getN()){ // choosePoint::ROW
        printf("Row # : %d\n", ansSelectPos);
    }
    else{ // choosePoint::COLUMN
        printf("Column # : %d\n", ansSelectPos-gB.getN());
    }
    gB.printPlayerScore();
    gB.printFinalScore();
    // Calculating total time taken by the program.
    auto done = std::chrono::high_resolution_clock::now();
    std::cout << "Total run time = " << std::fixed << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count()/1000.0 << std::setprecision(5);
    std::cout << " seconds." << "\n";
    return 0;
}