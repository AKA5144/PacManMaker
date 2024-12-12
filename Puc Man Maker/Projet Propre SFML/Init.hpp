#ifndef INIT_HPP
#define INIT_HPP
#include "CreaMan.h"
#include "GameData.hpp"
#include "Player.h"
#include "Ghost.h"
#include "MapManager.h"
#include "Hud.hpp"

void resetSaveSprite(GameData& _gameData);
void load(GameData& _gameData, GhostsData& _gohstsData);
void ResetGame(GameData& _gameData, GhostsData& _gohstsData);

#endif 