#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <cstdio>

enum class state{
    CLEAN,
    BLACK
};

class boardUnit{
    private:
        state state_;
    public:
        boardUnit(): state_(state::CLEAN) {};
        boardUnit(state s): state_(s) {};
        void setClean();
        void setBlack();
        state getState() const;
};

class gameBoardUnit{
    private: 
        std::vector<std::vector<boardUnit>> units_;
    public:
        friend class game;
        void initBoard(std::vector<std::vector<int>> board, int n, int m);
        void printBoard() const;
        
};

#endif