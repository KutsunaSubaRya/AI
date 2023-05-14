#include "game.h"

void game::initBoard(std::vector<std::vector<int>> v, int n , int m){
    gB_.initBoard(v, n, m);
}

void game::printBoard(){
    gB_.printBoard();
}

void game::cleanRowOrColumnBoard(choosePoint cp, int pos){
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
    cleanRowOrColumnBoard(cp, pos);
    return val;
}