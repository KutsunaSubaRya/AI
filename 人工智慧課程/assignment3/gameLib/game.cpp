#include "game.h"

void game::initBoard(std::vector<std::vector<int>> v, int n , int m){
    gB_.initBoard(v, n, m);
    lastStepUnit_.initBoard(v, n, m);
}

void game::printBoard(){
    printf("current board: \n");
    gB_.printBoard();
    // printf("\nlast board: \n");
    // lastStepUnit_.printBoard();
    printf("----------------------\n\n");
}

bool game::isBoardClean(){
    return gB_.isBoardClean();
}

void game::cleanRowOrColumnBoard(choosePoint cp, int pos){
    --pos;
    if(cp == choosePoint::ROW){
        for(int i=0; i<m_; i++){
            gB_.units_[pos][i].setClean();
        }
    }
    else{
        for(int i=0; i<n_; i++){
            gB_.units_[i][pos].setClean();
        }
    }
}

int game::getCurrentRowOrColumnSum(choosePoint cp, int pos){
    --pos;
    int totalVal=0;
    if(cp == choosePoint::ROW){
        for(int i=0; i<m_; i++){
            if(gB_.units_[pos][i].getState() == state::BLACK){
                ++ totalVal;
            }
        }
    }
    else{
        for(int i=0; i<n_; i++){
            if(gB_.units_[i][pos].getState() == state::BLACK){
                ++ totalVal;
            }
        }
    }
    return totalVal;
}

int game::getOneStepVal(choosePoint cp, int pos){
    // be aware that pos must be original value - 1
    int val = getCurrentRowOrColumnSum(cp, pos);
    // store board to lastStepUnit
    // printf("val= %d\n", val);
    lastStepUnit_.units_ = gB_.units_;
    cleanRowOrColumnBoard(cp, pos);
    return val;
}

void game::revertLastStepBoard(){
    gB_.units_ = lastStepUnit_.units_;
}

int game::getN() const{
    return n_;
}

int game::getM() const{
    return m_;
}

int game::getRowOrColumnScore(choosePoint cp, int pos){
    int score = 0;
    if(cp == choosePoint::ROW){
        for(int i=0; i<m_; i++){
            if(gB_.units_[pos-1][i].getState() == state::BLACK){
                ++ score;
            }
        }
    }
    else{
        pos = pos - n_;
        for(int i=0; i<n_; i++){
            if(gB_.units_[i][pos-1].getState() == state::BLACK){
                ++ score;
            }
        }
    }
    return score;
}

void game::updatePlayerScore(int score, bool isPlayer1){
    if(isPlayer1){
        player1Score += score;
    }
    else{
        player2Score += score;
    }
}

void game::printPlayerScore(){
    printf("player1 score: %d\n", player1Score);
    printf("player2 score: %d\n", player2Score);
}

void game::printFinalScore(){
    printf("%d points\n", player1Score - player2Score);
}

void game::setplayer1Score(int score){
    player1Score = score;
}

void game::setplayer2Score(int score){
    player2Score = score;
}

int game::getPlayer1Score() const{
    return player1Score;
}

int game::getPlayer2Score() const{
    return player2Score;
}