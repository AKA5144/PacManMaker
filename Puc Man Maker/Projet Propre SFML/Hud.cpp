#include "Hud.hpp"
#include <iostream>   
#include <string>  
//PublicPixel.ttf


void InitFont(GameData& _gameData)
{
	_gameData.font.loadFromFile("Assets/fonts/PublicPixel.ttf");
	_gameData.Score.setFont(_gameData.font);
	_gameData.Score.setCharacterSize(20);

	_gameData.Life.setFont(_gameData.font);
	_gameData.Life.setCharacterSize(20);

}

void UpdateHud(GameData& _gameData)
{
	_gameData.Score.setString("Score :" + std::to_string(_gameData.player.score));
	_gameData.Life.setString("Life :" + std::to_string(_gameData.player.Hp));
}
void DisplayText(GameData& _gameData)
{
	if (_gameData.state == GAME)
	{
		_gameData.Score.setPosition(SCREEN_WIDTH / 2 - _gameData.Score.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 + _gameData.Score.getGlobalBounds().height * 2);
		_gameData.window.draw(_gameData.Score);

		_gameData.Life.setPosition(SCREEN_WIDTH / 2 - _gameData.Life.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 + _gameData.Life.getGlobalBounds().height * 4);
		_gameData.window.draw(_gameData.Life);
	}
	if (_gameData.DisplayError == true)
	{
		_gameData.window.draw(_gameData.AlertText);
	}
}