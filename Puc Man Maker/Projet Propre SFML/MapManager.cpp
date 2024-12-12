#include "MapManager.h"
#include "Common.hpp"
#include <fstream>
#include "Edit.hpp"


void InitDots(GameData& _gameData)
{
	for (int row = 0; row < NB_ROWS; row++)
	{
		for (int col = 0; col < NB_COLS; col++)
		{
			_gameData.dots[row][col].sprite = LoadSprite("Assets/pastille.png", true);
			if (_gameData.map[row][col] != 1)
			{
				_gameData.dots[row][col].pos = { _gameData.SfmlMap[row][col].pos.x + _gameData.dots[row][col].sprite.getGlobalBounds().width / 2, _gameData.SfmlMap[row][col].pos.y + _gameData.dots[row][col].sprite.getGlobalBounds().height / 2 };
				_gameData.dots[row][col].isEaten = false;
				_gameData.ScoreMax++;
			}
			else
			{
				_gameData.dots[row][col].isEaten = true;
			}
		}
	}
	_gameData.MapIsLoad = true;
}
void initSfmlMap(GameData& _gameData)
{
	InitMapManager(_gameData);
	for (unsigned int i = 0; i < NB_ROWS; i++)
	{
		for (unsigned int j = 0; j < NB_COLS; j++)
		{
			switch (_gameData.map[i][j])
			{
			case(0):
				_gameData.SfmlMap[i][j].type = FREE_CELL;
				_gameData.SfmlMap[i][j].sprite = _gameData.TilesSprite[0];
				break;
			case(1):
				_gameData.SfmlMap[i][j].type = WALL;
				_gameData.SfmlMap[i][j].sprite = _gameData.TilesSprite[1];
				break;
			case(2):
				_gameData.SfmlMap[i][j].type = TURNING_POINT;
				_gameData.SfmlMap[i][j].sprite = _gameData.TilesSprite[0];
				break;
			}
			_gameData.SfmlMap[i][j].IsFree = false;
			_gameData.SfmlMap[i][j].pos = { _gameData.SfmlMap[i][j].sprite.getGlobalBounds().width * j ,  _gameData.SfmlMap[i][j].sprite.getGlobalBounds().height * i };

		}
	}

}
// Position of cells are given in console coordinates
void FindFreeCells(GameData& _gameData, std::vector<Pos>& _freeCells, int _nbRows, int _nbCols, int _map[NB_ROWS][NB_COLS])
{
	for (int row = 0; row < _nbRows; row++)
	{
		for (int col = 0; col < _nbCols; col++)
		{

			if (_map[row][col] != 1)
			{
				Pos tempPos = { col + 1, row + 1 };
				_gameData.SfmlMap[row][col].IsFree = true;
				_freeCells.push_back(tempPos);

			}
		}
	}

}

void DisplayMap(GameData& _gameData, struct Pos _textPos, int _map[NB_ROWS][NB_COLS], WindowSize _winSize)
{
	for (int row = 0; row < NB_ROWS; row++)
	{
		for (int col = 0; col < NB_COLS; col++)
		{
			BlitSprite(_gameData.SfmlMap[row][col].sprite, _gameData.SfmlMap[row][col].pos, _gameData.window, { 1.0,1.0 }, 0, sf::Color::White);
			if (_gameData.state == EDIT)
			{
				if (_map[row][col] == 1)
				{
					DrawSquare(COLOR_BKG_GREEN, BRIGHT, col + 1, row + 1);
				}
				else
				{
					_textPos.x = col + 1;
					_textPos.y = row + 1;
					DrawLetter(_winSize, COLOR_TXT_BLUE, COLOR_BKG_BLUE, _textPos, ' ');
				}
			}

		}
	}
}
bool IsDotOnMap(const std::vector<Pos>& _dots, Pos _here, int& _index)
{
	bool dotOnMap = false;
	for (size_t i = 0; i < _dots.size(); i++)
	{
		if (_dots[i].x == _here.x && _dots[i].y == _here.y)
		{
			dotOnMap = true;
			_index = i;
			i = _dots.size();
		}
	}
	return dotOnMap;
}

void EatDot(GameData& _gameData)
{
	for (int row = 0; row < NB_ROWS; row++)
	{
		for (int col = 0; col < NB_COLS; col++)
		{
			if (_gameData.dots[row][col].pos == sf::Vector2f(_gameData.player.pos.x * 32 + _gameData.player.sprite[_gameData.player.imageCourante].getGlobalBounds().width / 2, _gameData.player.pos.y * 32 + _gameData.player.sprite[_gameData.player.imageCourante].getGlobalBounds().height / 2)
				&& (_gameData.dots[row][col].isEaten == false))
			{
				_gameData.dots[row][col].isEaten = true;
				_gameData.player.score++;
			}
		}
	}
}


void DrawDots(GameData& _gameData)
{
	for (int row = 0; row < NB_ROWS; row++)
	{
		for (int col = 0; col < NB_COLS; col++)
		{
			if (_gameData.dots[row][col].isEaten == false)
			{
				BlitSprite(_gameData.dots[row][col].sprite, _gameData.dots[row][col].pos, _gameData.window, { 1.0, 1.0 }, 0, sf::Color::White);

			}
		}
	}
}