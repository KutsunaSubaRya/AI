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

// in one choose, we need to choose one of the row or column point
// use first person get score minus second person get score as evaluation function
int AlphaBetaPruing(game gB, int alpha, int beta, bool isMax, int depth, bool currentPlayer) {
    // board clean then return
    if(gB.isBoardClean()){
        return gB.getPlayer1Score() - gB.getPlayer2Score();
    }
    int len = gB.getN() + gB.getM();
    if(isMax){ // player 1's turn
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
        for(int j=1; j<=len; j++){
            int i = arr[j-1].second;
            if (arr[j-1].first == 0){
                continue;
            }
            if(i<=gB.getN()){ // choosePoint::ROW
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::ROW, i);
                if(currentScore == 0){
                    continue;
                }
                game nextGB = gB;
                nextGB.nextOneStep(choosePoint::ROW, i); // player 1's turn
                nextGB.setplayer1Score(currentScore);
                int val = AlphaBetaPruing(nextGB, alpha, beta, false, depth-1, currentPlayer); // recursive and pass the updated the game board
                if(val > maxVal){
                    maxVal = val;
                    if(depth == 16){
                        selectPosI = i;
                    }
                }
                alpha = std::max(alpha, maxVal);
                if(beta <= alpha){ // if aplha >= beta, then prune
                    break;
                }
            }
            else{ // choosePoint::COLUMN
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::COLUMN, i-gB.getN());
                if(currentScore == 0){
                    continue;
                }
                game nextGB = gB;
                nextGB.nextOneStep(choosePoint::COLUMN, i-gB.getN()); // player 1's turn
                
                nextGB.setplayer1Score(currentScore);
                int val = AlphaBetaPruing(nextGB, alpha, beta, false, depth-1, currentPlayer); // recursive and pass the updated the game board
                if(val > maxVal){
                    maxVal = val;
                    if(depth == 16){
                        selectPosI = i;
                    }
                }
                alpha = std::max(alpha, maxVal);
                if(beta <= alpha){
                    break;
                }
            }
        }
        return maxVal;
    }
    else{ // player 2's turn
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
        for(int j=1; j<=len; j++){
            int i = arr[j-1].second;
            if (arr[j-1].first == 0){
                continue;
            }
            if(i<=gB.getN()){ // choosePoint::ROW
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::COLUMN, i-gB.getN());
                if(currentScore == 0){
                    continue;
                }
                game nextGB = gB;
                nextGB.nextOneStep(choosePoint::ROW, i); // player 2's turn
                
                nextGB.setplayer2Score(currentScore);
                int val = AlphaBetaPruing(nextGB, alpha, beta, true, depth-1, currentPlayer); // recursive and pass the updated the game board
                minVal = std::min(minVal, val);
                beta = std::min(beta, minVal);
                if(beta <= alpha){
                    break;
                }
            }
            else { //choosePoint::COLUMN
                int currentScore = gB.getCurrentRowOrColumnSum(choosePoint::COLUMN, i-gB.getN());
                if(currentScore == 0){
                    continue;
                }
                game nextGB = gB;
                nextGB.nextOneStep(choosePoint::COLUMN, i-gB.getN()); // player 2's turn
                
                nextGB.setplayer2Score(currentScore);
                int val = AlphaBetaPruing(nextGB, alpha, beta, true, depth-1, currentPlayer); // recursive and pass the updated the game board
                minVal = std::min(minVal, val);
                beta = std::min(beta, minVal);
                if(beta <= alpha){ // if aplha >= beta, then prune
                    break;
                }
            }
        }
        return minVal;
    }
}

int main(void){
    std::vector<std::vector<int>> v;
    v = initBoard(); // take the initial testcase of the game board
    int x=v.size(), y=v[0].size();
    // start to write code logic here ...
    auto started = std::chrono::high_resolution_clock::now();
    game gB(x, y, 0, 0); // construct new game board
    gB.initBoard(v, x, y); // initialize the game board
    bool player = true; // player 1 first
    bool isFirstChoose = true;
    int ansSelectPos = 1;
    while(!gB.isBoardClean()){ // play game until the board is clean
        int val = AlphaBetaPruing(gB, -1000000, 1000000, true, 16, player);
        if(isFirstChoose){
            ansSelectPos = selectPosI;
            isFirstChoose = false;
        }
        if(selectPosI <= gB.getN()){ // choosePoint::ROW
            gB.updatePlayerScore(gB.getRowOrColumnScore(choosePoint::ROW, selectPosI), player);
            gB.cleanRowOrColumnBoard(choosePoint::ROW, selectPosI);
        }
        else{ // choosePoint::COLUMN
            gB.updatePlayerScore(gB.getRowOrColumnScore(choosePoint::COLUMN, selectPosI), player);
            gB.cleanRowOrColumnBoard(choosePoint::COLUMN, selectPosI-gB.getN());
        }
        player = !player;
        selectPosI = 1;
    }
    // Calculating total time taken by the core algorithm.
    auto done = std::chrono::high_resolution_clock::now();
    if(ansSelectPos <= gB.getN()){ // choosePoint::ROW
        printf("Row # : %d\n", ansSelectPos);
    }
    else{ // choosePoint::COLUMN
        printf("Column # : %d\n", ansSelectPos-gB.getN());
    }
    gB.printPlayerScore();
    gB.printFinalScore();
    // print total time taken by the core algorithm.
    std::cout << "Total run time = " << std::fixed << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count()/1000.0 << std::setprecision(5);
    std::cout << " seconds." << "\n";
    return 0;
}