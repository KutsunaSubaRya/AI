#include "board.h"

// unit in board

void boardUnit::setClean(){
    state_ = state::CLEAN;
}

void boardUnit::setVirus(){
    state_ = state::VIRUS;
}

state boardUnit::getState() const{
    return state_;
}

// gameboard

void gameBoardUnit::initBoard(std::vector<int> board){
    const int boardSize = board.size();
    for(int idx=0;idx<boardSize;++idx){
        if(board[idx] == 0){
            units_.emplace_back(state::CLEAN);
        }
        else{
            units_.emplace_back(state::VIRUS);
        }
    }
}

void gameBoardUnit::printBoard() const{
    printf("current board: ");
    for(auto i : units_){
        if(i.getState() == state::CLEAN){
            printf("0 ");
        }
        else{
            printf("1 ");
        }
    }
    printf("\n");
}