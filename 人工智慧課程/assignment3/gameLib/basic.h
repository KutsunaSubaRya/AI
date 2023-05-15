#ifndef BASIC_H
#define BASIC_H
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>
#include <iostream>
#include "game.h"

std::vector<std::vector<int>> initBoard();
void printBoard(std::vector<std::vector<int>> v, int x, int y);
void updatePlayerScore(game gB, int score, bool isMax);
#endif