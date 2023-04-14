#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <cstdio>

enum class state{
    CLEAN,
    VIRUS
};

class boardUnit{
    private:
        state state_;
    public:
        boardUnit(): state_(state::CLEAN) {};
        boardUnit(state s): state_(s) {};
        void setClean();
        void setVirus();
        state getState() const;
};

class gameBoardUnit{
    private: 
        std::vector<boardUnit> units_;
    public:
        friend class game;
        void initBoard(std::vector<int> board);
        void printBoard() const;
        
};

#endif