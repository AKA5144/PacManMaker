#ifndef PLAYER_H
#define PLAYER_H

#include "GameData.hpp"
#include "CreaMan.h"
#include"Ghost.h"

void playerLoad(GameData& _gameData);
void MovePlayer(GameData& _gameData);
void drawPlayer(GameData& _gameData);
void UpdatePlayer(GameData& _gameData);
void IsColliding(GhostsData& _gohstsData, int _ghost_nb, GameData& _gameData);
#endif

