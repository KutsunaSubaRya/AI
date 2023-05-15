#include "basic.h"
std::vector<std::vector<int>> initBoard(){
    // read file to string
    std::ifstream inFile("./testcase/input1.txt");

    // Read the first line with n and m
    int n, m;
    inFile >> n >> m;

    // Read the n x m board into a vector
    std::vector<std::vector<int>> board(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            inFile >> board[i][j];
        }
    }
    // Close the input file
    inFile.close();
    return board;
}

void printBoard(std::vector<std::vector<int>> v, int n, int m){
    printf("Board: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << v[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void updatePlayerScore(game gB, int score, bool isMax){
    gB.updatePlayerScore(score, isMax);
}