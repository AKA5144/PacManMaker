#include "Ghost.h"
#include "Common.hpp"
#include "Player.h"


void InitGhost(GhostsData& _gohstsData)
{
	for (int i = 0; i < NB_GHOSTS; i++)
	{
		_gohstsData.ghosts[i].animation[0] = LoadSprite("Assets/fantomebas.png", true);
		_gohstsData.ghosts[i].animation[1] = LoadSprite("Assets/fantomehaut.png", true);
		_gohstsData.ghosts[i].animation[2] = LoadSprite("Assets/fantomedroite.png", true);
		_gohstsData.ghosts[i].animation[3] = LoadSprite("Assets/fantomegauche.png", true);
	}



}

void Move(struct Ghost _ghosts[], int _ghost_nb, int _map[NB_ROWS][NB_COLS])
{
	Pos dirXY = { 0 };
	int nextX;
	int nextY;
	int RandFirstGhosts;
	if (_ghosts[_ghost_nb].dir == LEFT)
	{
		_ghosts[_ghost_nb].sprite = _ghosts[_ghost_nb].animation[3];
		dirXY.x--;
		if (_ghosts[_ghost_nb].pos.x == 2)
		{
			_ghosts[_ghost_nb].dir = RIGHT;
		}
	}
	else if (_ghosts[_ghost_nb].dir == RIGHT)
	{
		dirXY.x++;
		_ghosts[_ghost_nb].sprite = _ghosts[_ghost_nb].animation[2];
		if (_ghosts[_ghost_nb].pos.x == NB_COLS - 1)
		{
			_ghosts[_ghost_nb].dir = LEFT;
		}
	}
	else if (_ghosts[_ghost_nb].dir == DOWN)
	{
		dirXY.y++;
		_ghosts[_ghost_nb].sprite = _ghosts[_ghost_nb].animation[0];
		if (_ghosts[_ghost_nb].pos.y == NB_ROWS - 1)
		{
			_ghosts[_ghost_nb].dir = UP;
		}
	}
	else if (_ghosts[_ghost_nb].dir == UP)
	{
		dirXY.y--;
		_ghosts[_ghost_nb].sprite = _ghosts[_ghost_nb].animation[1];
		if (_ghosts[_ghost_nb].pos.y == 2)
		{
			_ghosts[_ghost_nb].dir = DOWN;
		}
	}


	nextX = _ghosts[_ghost_nb].pos.x + dirXY.x;
	nextY = _ghosts[_ghost_nb].pos.y + dirXY.y;

	switch (_map[nextY - 1][nextX - 1])
	{

		//turning point
	case TURNING_POINT:
		_ghosts[_ghost_nb].pos.x += dirXY.x;
		_ghosts[_ghost_nb].pos.y += dirXY.y;
		_ghosts[_ghost_nb].dir = (Dir)(rand() % 4);
		break;
		// impossible move
	case WALL:
		if (_ghost_nb != 0)
		{
			_ghosts[_ghost_nb].dir = (Dir)(rand() % 4);
		}
		if (_ghost_nb == 0)
		{
			RandFirstGhosts = rand() % 4;
			if (RandFirstGhosts < 3)
			{
				_ghosts[_ghost_nb].dir = (Dir)(rand() % 4);
			}
			if (RandFirstGhosts == 3)
			{
				switch (_ghosts[_ghost_nb].dir)
				{
				case UP:
					_ghosts[_ghost_nb].dir = DOWN;
					break;
				case DOWN:
					_ghosts[_ghost_nb].dir = UP;
					break;
				case LEFT:
					_ghosts[_ghost_nb].dir = RIGHT;
					break;
				case RIGHT:
					_ghosts[_ghost_nb].dir = LEFT;
					break;
				}
			}
		}

		break;
		// free cell
	case FREE_CELL:
		_ghosts[_ghost_nb].pos.x += dirXY.x;
		_ghosts[_ghost_nb].pos.y += dirXY.y;
		break;
	}

}



void InitGhostsMoves(GhostsData& _gohstsData, GameData& _gameData, std::vector<Pos>& _freeCells)
{
	Dir dir;

	for (size_t i = 0; i < NB_GHOSTS; i++)
	{
		int randPos = rand() % _freeCells.size();
		if (randPos == (1, 1))
		{
			randPos = rand() % _freeCells.size();
		}
		// location
		_gohstsData.ghosts[i].pos = { _freeCells[randPos] };
		// direction
		_freeCells.erase(_freeCells.begin() + randPos, _freeCells.begin() + randPos + 1);
		_gohstsData.ghosts[i].dir = (Dir)(rand() % 4);
	}
}

void DrawGhosts(GhostsData& _gohstsData, GameData& _gameData)
{
	for (size_t i = 0; i < NB_GHOSTS; i++)
	{
		BlitSprite(_gohstsData.ghosts[i].sprite, { (_gohstsData.ghosts[i].pos.x - 1) * 32 + _gohstsData.ghosts[i].sprite.getGlobalBounds().width / 2, (_gohstsData.ghosts[i].pos.y - 1) * 32 + _gohstsData.ghosts[i].sprite.getGlobalBounds().height / 2 }, _gameData.window, { 1.0, 1.0 }, 0, sf::Color::White);
	}
}
void DebugGhosts(GhostsData& _gohstsData, GameData& _gameData, std::vector<Pos>& _freeCells)
{
	for (size_t i = 0; i < NB_GHOSTS; i++)
	{
		if ((_gohstsData.ghosts[i].pos.y < 1) || (_gohstsData.ghosts[i].pos.y > NB_ROWS) || (_gohstsData.ghosts[i].pos.x > NB_COLS) || (_gohstsData.ghosts[i].pos.x < 1))
		{
			int randPos = rand() % _freeCells.size();
			_gohstsData.ghosts[i].pos = { _freeCells[randPos] };
		}


	}
}

void UpdateGhosts(GhostsData& _gohstsData, GameData& _gameData)
{
	for (size_t i = 0; i < NB_GHOSTS; i++)
	{
		Move(_gohstsData.ghosts, i, _gameData.map);
		DebugGhosts(_gohstsData, _gameData, _gameData.freeCells);
		IsColliding(_gohstsData, i, _gameData);


	}
}