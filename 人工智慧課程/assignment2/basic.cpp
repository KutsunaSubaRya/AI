#include "basic.h"

std::vector<int> initBoard(){
    // read file to string
    std::ifstream file ("./input.txt");
    std::string str;
    file.seekg(0, std::ios::end);   
    str.reserve(file.tellg());
    file.seekg(0, std::ios::beg);
    str.assign((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
    // strtok to vector
    std::vector<int> board;
    std::istringstream iss(str);
    std::string token;
    while(std::getline(iss, token, ' ')){
        if(token == "0"){
            board.emplace_back(0);
        }
        else{
            board.emplace_back(1);
        }
    }
    return board;
}

void printBoard(std::vector<int> v){
    printf("Board: ");
    for(auto i : v){
        printf("%d ", i);
    }
    printf("\n");
}