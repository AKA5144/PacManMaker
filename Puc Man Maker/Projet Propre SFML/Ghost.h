#ifndef GHOST_H
#define GHOST_H
#include "CreaMan.h"
#include "GameData.hpp"
struct Ghost
{
	Pos pos;
	Dir dir;
	sf::Sprite animation[4];
	sf::Sprite sprite;
};

struct GhostsData
{
	Ghost ghosts[NB_GHOSTS];

};

void InitGhost(GhostsData& _gohstsData);
void Move(struct Ghost _ghosts[], struct GameData& gameData, int _ghost_nb, int _map[NB_ROWS][NB_COLS]);
void InitGhostsMoves(GhostsData& _gohstsData, GameData& _gameData, std::vector<Pos>& _freeCells);
void DrawGhosts(GhostsData& _gohstsData, GameData& _gameData);
void UpdateGhosts(GhostsData& _gohstsData, GameData& _gameData);

#endif //GHOST_H