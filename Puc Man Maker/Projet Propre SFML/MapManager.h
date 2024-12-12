#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H
#include "GameData.hpp"
#include "CreaMan.h"


void InitDots(GameData& _gameData);
void initSfmlMap(GameData& _gameData);
void FindFreeCells(GameData& _gameData, std::vector<Pos>& _freeCells, int _nbRows, int _nbCols, int _map[NB_ROWS][NB_COLS]);
bool IsDotOnMap(const std::vector<Pos>& _dots, Pos _here, int& _index);
void EatDot(GameData& _gameData);
void DisplayMap(GameData& _gameData, struct Pos _textPos, int _map[NB_ROWS][NB_COLS], WindowSize _winSize);
void DrawDots(GameData& _gameData);
#endif //MAP_MANAGER_H