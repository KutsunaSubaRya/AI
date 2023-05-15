#include "board.h"

// unit in board

void boardUnit::setClean(){
    state_ = state::CLEAN;
}

void boardUnit::setBlack(){
    state_ = state::BLACK;
}

state boardUnit::getState() const{
    return state_;
}

// gameboard

void gameBoardUnit::initBoard(std::vector<std::vector<int>> board, int n, int m){  
    for(int i=0;i<n;++i){
        units_.emplace_back(std::vector<boardUnit>());
        for(int j=0;j<m;++j){
            if(board[i][j] == 0){
                units_[i].emplace_back(state::CLEAN);
            }
            else{
                units_[i].emplace_back(state::BLACK);
            }
        }
    }
}

bool gameBoardUnit::isBoardClean() const{
    for(auto i : units_){
        for(auto j:i){
            if(j.getState() == state::BLACK){
                return false;
            }
        }
    }
    return true;
}

void gameBoardUnit::printBoard() const{
    for(auto i : units_){
        for(auto j:i){
            if(j.getState() == state::CLEAN){
                printf("0 ");
            }
            else{
                printf("1 ");
            }
        }
        printf("\n");
    }
    printf("\n");
}