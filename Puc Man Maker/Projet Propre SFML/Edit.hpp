#ifndef EDIT_HPP
#define EDIT_HPP
#include "CreaMan.h"
#include "GameData.hpp"
#include "Player.h"
#include "Ghost.h"
#include "MapManager.h"
#include "Hud.hpp"

void InitMapManager(GameData& _gameData);
void UpdateEdit(GameData& _gameData);
void DrawEdit(GameData& _gameData);
void saveMap(GameData& _gameData, std::string _FileToSave);
void EraseMap(GameData& _gameData, std::string _FileToErase);
#endif 