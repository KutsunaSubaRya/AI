#include "game.h"

void game::initBoard(std::vector<int> v){
    gB_.initBoard(v);
}

void game::printBoard(){
    gB_.printBoard();
}

const int game::getBoardSize() const {
    return boardSize_;
}

const int game::getVirusNumber() const{
    const int boardSize = gB_.units_.size();
    int virusNumber = 0;
    for(int idx=0;idx<boardSize;++idx){
        if(gB_.units_[idx].getState() == state::VIRUS){
            ++ virusNumber;
        }
    }
    return virusNumber;
}

const bool game::isBoardClean() const {
    if(getVirusNumber() == 0){
        return true;
    }
    return false;
}

const bool game::isGameContinue() const {
    if(isBoardClean()==true){
        return false;
    }
    return true;
}

std::vector<int> game::getOneStepResult(const int pos){
    std::vector<int> ret;
    const int sz = getBoardSize();
    cleanPosVirus(pos);
    virusSplit();
    for(int idx=0;idx<sz;++idx){
        if(gB_.units_[idx].getState() == state::CLEAN){
            ret.emplace_back(0);
        }
        else{
            ret.emplace_back(1);
        }
    }
    return ret;
}

void game::virusSplit(void){
    const int sz = getBoardSize();
    int tmp_v[sz+1]={0};
    for(int idx=0;idx<sz;++idx){
        if(gB_.units_[idx].getState() == state::VIRUS){
            if(idx == 0){ // left boundary
                tmp_v[idx+1] = 1;
            }
            else if(idx == sz-1){ // right boundary
                tmp_v[idx-1] = 1;
            }
            else {
                tmp_v[idx+1] = 1;
                tmp_v[idx-1] = 1;
            }
        }
    }
    for(int idx=0;idx<sz;++idx){
        if(tmp_v[idx] == 0){
            gB_.units_[idx].setClean();
        }
        else{
            gB_.units_[idx].setVirus();
        }
    }
}

void game::cleanPosVirus(const int pos) {
    gB_.units_[pos].setClean();
}