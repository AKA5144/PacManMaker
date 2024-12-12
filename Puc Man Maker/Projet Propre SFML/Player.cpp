#include "Player.h"
#include "Ghost.h"
#include "Common.hpp"





void playerLoad(GameData& _gameData)
{
	_gameData.counter = 0;
	_gameData.player.Hp = 5;
	_gameData.player.sprite[0] = LoadSprite("Assets/creaman1.png", true);
	_gameData.player.sprite[1] = LoadSprite("Assets/creaman2.png", true);
	_gameData.player.sprite[2] = LoadSprite("Assets/creaman3.png", true);
	_gameData.player.sprite[3] = LoadSprite("Assets/creaman4.png", true);
	_gameData.player.pos = { 1, 1 };
	////////////
	_gameData.player.imageCourante = 0;
	_gameData.player.color = sf::Color::White;
	_gameData.player.Invincible = false;
	_gameData.player.score = 0;
}
void MovePlayer(GameData& _gameData)
{
	// Vertical move
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z)))
	{

		_gameData.player.dir = UP;



	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
	{

		_gameData.player.dir = DOWN;

	}

	// Horizontal move
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q)))
	{


		_gameData.player.dir = LEFT;


	}
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
	{


		_gameData.player.dir = RIGHT;



	}

	switch (_gameData.player.dir)
	{
	case UP:
		if (_gameData.player.pos.y != 0)
		{
			if (_gameData.map[_gameData.player.pos.y - 1][_gameData.player.pos.x] != WALL)
			{

				_gameData.player.pos.y--;

			}
		}
		else if ((_gameData.player.pos.y == 0) && (_gameData.map[NB_ROWS - 1][_gameData.player.pos.x] != WALL))
		{
			_gameData.player.pos.y--;
		}
		if (_gameData.player.pos.y < 0)
		{
			_gameData.player.pos.y = NB_ROWS - 1;
		}
		break;
	case DOWN:
		if (_gameData.player.pos.y != NB_ROWS - 1)
		{
			if (_gameData.map[_gameData.player.pos.y + 1][_gameData.player.pos.x] != WALL)
			{

				_gameData.player.pos.y++;

			}
		}
		else if ((_gameData.player.pos.y == NB_ROWS - 1) && (_gameData.map[0][_gameData.player.pos.x] != WALL))
		{
			_gameData.player.pos.y++;
		}

		if (_gameData.player.pos.y >= NB_ROWS)
		{
			_gameData.player.pos.y = 0;
		}
		break;
	case RIGHT:
		if (_gameData.player.pos.x != NB_COLS - 1)
		{
			if (_gameData.map[_gameData.player.pos.y][_gameData.player.pos.x + 1] != WALL)
			{

				_gameData.player.pos.x++;
			}
		}
		else if ((_gameData.player.pos.x == NB_COLS - 1) && (_gameData.map[_gameData.player.pos.y][0] != WALL))
		{
			_gameData.player.pos.x++;
		}

		if (_gameData.player.pos.x >= NB_COLS)
		{
			_gameData.player.pos.x = 0;
		}
		break;
	case LEFT:
		if (_gameData.player.pos.x != 0)
		{
			if (_gameData.map[_gameData.player.pos.y][_gameData.player.pos.x - 1] != WALL)
			{

				_gameData.player.pos.x--;

			}
		}
		else if ((_gameData.player.pos.x == 0) && (_gameData.map[_gameData.player.pos.y][NB_COLS - 1] != WALL))
		{
			_gameData.player.pos.x--;
		}

		if (_gameData.player.pos.x < 0)
		{
			_gameData.player.pos.x = NB_COLS - 1;
		}
		break;

	}


}



void PlayerAnimation(GameData& _gameData)
{
	_gameData.player.tempsCourant = _gameData.player.animationClock.getElapsedTime().asSeconds();

	_gameData.player.imageCourante = (4 * _gameData.player.tempsCourant) / _gameData.player.animationSpeed;
	if (_gameData.player.imageCourante >= 4)
	{
		_gameData.player.imageCourante = 0;
		_gameData.player.animationClock.restart().asSeconds();
	}
}

void TurnPlayer(GameData& _gameData)
{
	switch (_gameData.player.dir)
	{
	case 0: _gameData.player.rotate = -90;
		break;
	case 1: _gameData.player.rotate = 90;
		break;
	case 2: _gameData.player.rotate = 180;
		break;
	case 3: _gameData.player.rotate = 0;
		break;
	}
}

void UpdateInvincibility(GameData& _gameData)
{

	if (_gameData.player.Invincible == true)
	{
		_gameData.player.color = sf::Color(255, 255, 255, 175);
		_gameData.player.InvGetTimer = _gameData.player.InvTimer.getElapsedTime().asSeconds();
		if (_gameData.player.InvGetTimer > 3)
		{
			_gameData.player.Invincible = false;
		}

	}
	else
	{
		_gameData.player.color = sf::Color::White;
	}

}

void IsColliding(GhostsData& _gohstsData, int _ghost_nb, GameData& _gameData)
{
	if (_gameData.debugInvicibility == false)
	{
		if (_gameData.player.Invincible == false)
		{
			if ((_gameData.player.pos.x + 1 == _gohstsData.ghosts[_ghost_nb].pos.x) && (_gameData.player.pos.y + 1 == _gohstsData.ghosts[_ghost_nb].pos.y))
			{
				_gameData.player.Hp--;
				_gameData.player.Invincible = true;
				_gameData.player.InvTimer.restart().asSeconds();

			}
			else if ((_gameData.player.pos.x + 1 == _gohstsData.ghosts[_ghost_nb].pos.x + 1) && (_gameData.player.pos.y + 1 == _gohstsData.ghosts[_ghost_nb].pos.y) && (_gohstsData.ghosts[_ghost_nb].dir == LEFT))
			{
				_gameData.player.Hp--;
				_gameData.player.Invincible = true;
				_gameData.player.InvTimer.restart().asSeconds();
			}
			else if ((_gameData.player.pos.x + 1 == _gohstsData.ghosts[_ghost_nb].pos.x - 1) && (_gameData.player.pos.y + 1 == _gohstsData.ghosts[_ghost_nb].pos.y) && (_gohstsData.ghosts[_ghost_nb].dir == RIGHT))
			{
				_gameData.player.Hp--;
				_gameData.player.Invincible = true;
				_gameData.player.InvTimer.restart().asSeconds();
			}
			else if ((_gameData.player.pos.y + 1 == _gohstsData.ghosts[_ghost_nb].pos.y + 1) && (_gameData.player.pos.x + 1 == _gohstsData.ghosts[_ghost_nb].pos.x) && (_gohstsData.ghosts[_ghost_nb].dir == UP))
			{
				_gameData.player.Hp--;
				_gameData.player.Invincible = true;
				_gameData.player.InvTimer.restart().asSeconds();
			}
			else if ((_gameData.player.pos.y + 1 == _gohstsData.ghosts[_ghost_nb].pos.y - 1) && (_gameData.player.pos.x + 1 == _gohstsData.ghosts[_ghost_nb].pos.x) && (_gohstsData.ghosts[_ghost_nb].dir == DOWN))
			{
				_gameData.player.Hp--;
				_gameData.player.Invincible = true;
				_gameData.player.InvTimer.restart().asSeconds();
			}
		}
	}
}

void UpdatePlayer(GameData& _gameData)
{
	PlayerAnimation(_gameData);
	TurnPlayer(_gameData);
	UpdateInvincibility(_gameData);

}

void drawPlayer(GameData& _gameData)
{
	BlitSprite(_gameData.player.sprite[_gameData.player.imageCourante], { _gameData.player.pos.x * 32 + _gameData.player.sprite[_gameData.player.imageCourante].getGlobalBounds().width / 2, _gameData.player.pos.y * 32 + _gameData.player.sprite[_gameData.player.imageCourante].getGlobalBounds().height / 2 }, _gameData.window, { 1.0, 1.0 }, _gameData.player.rotate, _gameData.player.color);
}
