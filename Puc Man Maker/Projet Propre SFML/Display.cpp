#include "Display.hpp"
#include "Common.hpp"
#include "Edit.hpp"


void Display(GameData& _gameData, GhostsData& _gohstsData)
{
	_gameData.window.clear(sf::Color::Black);
	switch (_gameData.state)
	{
	case MENU:
		BlitSprite(_gameData.Bg, { 0, 0 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);
		BlitSprite(_gameData.PlayButtonSprite, { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);
		BlitSprite(_gameData.CreateButtonSprite, { SCREEN_WIDTH - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);
		break;
	case HELP:
		BlitSprite(_gameData.Bg, { 0, 0 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);
		break;
	case PAUSE:
		DisplayMap(_gameData, _gameData.textPos, _gameData.map, _gameData.winSize);
		DrawDots(_gameData);
		drawPlayer(_gameData);
		DrawGhosts(_gohstsData, _gameData);
		DisplayText(_gameData);
		BlitSprite(_gameData.Bg, { 0, 0 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);
		break;
	case GAME:
		DisplayMap(_gameData, _gameData.textPos, _gameData.map, _gameData.winSize);
		DrawDots(_gameData);
		drawPlayer(_gameData);
		DrawGhosts(_gohstsData, _gameData);
		DisplayText(_gameData);
		break;
	case EDIT:
		BlitSprite(_gameData.Bg, { 0, 0 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);
		DisplayMap(_gameData, _gameData.textPos, _gameData.map, _gameData.winSize);
		drawPlayer(_gameData);
		DrawEdit(_gameData);
		DisplayText(_gameData);

		break;
	case OVER:

		BlitSprite(_gameData.Bg, { 0, 0 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);
		BlitSprite(_gameData.MenuButtonSprite, { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);
		BlitSprite(_gameData.ExitButtonSprite, { SCREEN_WIDTH - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);

		break;
	case WIN:
		BlitSprite(_gameData.Bg, { 0, 0 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);
		BlitSprite(_gameData.MenuButtonSprite, { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);
		BlitSprite(_gameData.ExitButtonSprite, { SCREEN_WIDTH - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);


		break;
	case CUSTOM_MAP_MENU:
		BlitSprite(_gameData.Bg, { 0, 0 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);

		BlitSprite(_gameData.SaveButtonSprite[0], { (SCREEN_WIDTH / 4), 0 + SCREEN_HEIGHT / 4 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);

		BlitSprite(_gameData.SaveButtonSprite[1], { SCREEN_WIDTH - SCREEN_WIDTH / 4,  SCREEN_HEIGHT / 4 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);

		BlitSprite(_gameData.SaveButtonSprite[2], { SCREEN_WIDTH / 4, SCREEN_HEIGHT - SCREEN_HEIGHT / 4 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);

		BlitSprite(_gameData.SaveButtonSprite[3], { SCREEN_WIDTH - SCREEN_WIDTH / 4 , SCREEN_HEIGHT - SCREEN_HEIGHT / 4 }, _gameData.window, { 1, 1 }, 0, sf::Color::White);
		break;
	case LOAD_OR_MODIFY:

		DisplayMap(_gameData, _gameData.textPos, _gameData.map, _gameData.winSize);
		BlitSprite(_gameData.PlayButtonSprite, { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, _gameData.window, { 2, 2 }, 0, sf::Color(255, 255, 255, 200));
		BlitSprite(_gameData.EditButtonSprite, { SCREEN_WIDTH - SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 }, _gameData.window, { 2, 2 }, 0, sf::Color(255, 255, 255, 200));
		DisplayText(_gameData);
		break;
	}

	_gameData.window.display();
}