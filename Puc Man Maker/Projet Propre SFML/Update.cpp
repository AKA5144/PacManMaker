#include "Update.hpp"
#include "common.hpp"
#include "Init.hpp"
#include"Edit.hpp"
void Conditions(GameData& _gameData)
{
	if (_gameData.state == GAME)
	{
		if (_gameData.player.Hp <= 0)
		{
			_gameData.Bg = LoadSprite("Assets/bg/Loose.png", false);
			_gameData.MenuButtonSprite = _gameData.MenuButton[1];
			_gameData.music.openFromFile("Assets/Sounds/Lose.ogg");
			_gameData.music.play();
			_gameData.nextState = MENU;
			_gameData.state = OVER;
		}
		if ((_gameData.player.score >= _gameData.ScoreMax) && (_gameData.MapIsLoad == true))
		{
			_gameData.Bg = LoadSprite("Assets/bg/Win.png", false);
			_gameData.MenuButtonSprite = _gameData.MenuButton[1];
			_gameData.music.openFromFile("Assets/Sounds/Win.ogg");
			_gameData.music.play();
			_gameData.nextState = MENU;
			_gameData.state = WIN;
		}

	}

}


void Update(GameData& _gameData, GhostsData& _gohstsData)
{

	_gameData.window.setFramerateLimit(_gameData.FrameLimit);

	switch (_gameData.state)
	{
	case MENU:

		_gameData.FrameLimit = 240;
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			switch (_gameData.nextState)
			{
			case GAME:
				_gameData.ClicSound.play();
				_gameData.nextState = CUSTOM_MAP_MENU;
				_gameData.PlayButtonSprite = _gameData.PlayButton[0];
				_gameData.CreateButtonSprite = _gameData.CreateButton[1];
				break;
			case CUSTOM_MAP_MENU:
				_gameData.ClicSound.play();
				_gameData.nextState = GAME;
				_gameData.PlayButtonSprite = _gameData.PlayButton[1];
				_gameData.CreateButtonSprite = _gameData.CreateButton[0];

				break;
			}
			Sleep(200);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (_gameData.nextState == GAME)
			{
				_gameData.ClicSound.play();
				_gameData.FileToOpen = "maps/Default.txt";
				_gameData.FrameLimit = 5;
				_gameData.state = GAME;
				ResetGame(_gameData, _gohstsData);

			}
			else if (_gameData.nextState == CUSTOM_MAP_MENU)
			{
				_gameData.ClicSound.play();
				_gameData.FileToOpen = "maps/Save1.txt";
				_gameData.Bg = LoadSprite("Assets/bg/EditMenu.png", false);
				_gameData.state = CUSTOM_MAP_MENU;
				ResetGame(_gameData, _gohstsData);
				_gameData.SaveButtonSprite[0] = _gameData.SaveButton[0][1];
				_gameData.SaveSelect = 1;
				_gameData.music.openFromFile("Assets/Sounds/Edit.ogg");
				_gameData.music.play();
				Sleep(200);

			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			_gameData.ClicSound.play();
			_gameData.state = HELP;
			_gameData.Bg = LoadSprite("Assets/bg/Help.png", false);
			Sleep(200);
		}
		break;
	case EDIT:

		UpdateEdit(_gameData);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			_gameData.ClicSound.play();
			saveMap(_gameData, _gameData.FileToOpen);
			resetSaveSprite(_gameData);
			_gameData.Bg = LoadSprite("Assets/bg/Menu.png", false);
			_gameData.state = MENU;
			_gameData.nextState = GAME;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (_gameData.DisplayError == false)
			{
				_gameData.ClicSound.play();
				_gameData.freeCells.clear();
				FindFreeCells(_gameData, _gameData.freeCells, NB_ROWS, NB_COLS, _gameData.map);
				if (_gameData.freeCells.size() <= 10)
				{
					_gameData.AlertText = _gameData.IssueBox[0];
					if (_gameData.map[1][1] == WALL)
					{
						_gameData.AlertText = _gameData.IssueBox[2];
					}
					_gameData.DisplayError = true;
				}
				else if (_gameData.map[1][1] == WALL)
				{
					_gameData.AlertText = _gameData.IssueBox[1];
					if (_gameData.freeCells.size() <= 10)
					{
						_gameData.AlertText = _gameData.IssueBox[2];
					}
					_gameData.DisplayError = true;

				}
				else
				{
					_gameData.ClicSound.play();
					saveMap(_gameData, _gameData.FileToOpen);
					ResetGame(_gameData, _gohstsData);
					_gameData.music.openFromFile("Assets/Sounds/MenuGame.ogg");
					_gameData.music.play();
					_gameData.state = GAME;


				}

			}
			else if (_gameData.DisplayError == true)
			{
				_gameData.ClicSound.play();
				_gameData.DisplayError = false;
			}
			Sleep(150);

		}
		break;
	case CUSTOM_MAP_MENU:

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			_gameData.ClicSound.play();
			_gameData.FrameLimit = 240;
			switch (_gameData.SaveSelect)
			{
			case 1:
				_gameData.SaveSelect = 2;
				_gameData.FileToOpen = "maps/Save2.txt";
				resetSaveSprite(_gameData);
				_gameData.SaveButtonSprite[1] = _gameData.SaveButton[1][1];
				break;

			case 2:
				_gameData.SaveSelect = 1;
				_gameData.FileToOpen = "maps/Save1.txt";
				resetSaveSprite(_gameData);
				_gameData.SaveButtonSprite[0] = _gameData.SaveButton[0][1];
				break;
			case 3:
				_gameData.SaveSelect = 4;
				_gameData.FileToOpen = "maps/Save4.txt";
				resetSaveSprite(_gameData);
				_gameData.SaveButtonSprite[3] = _gameData.SaveButton[3][1];
				break;
			case 4:
				_gameData.SaveSelect = 3;
				_gameData.FileToOpen = "maps/Save3.txt";
				resetSaveSprite(_gameData);
				_gameData.SaveButtonSprite[2] = _gameData.SaveButton[2][1];
				break;
			}

			Sleep(200);
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
		{
			_gameData.ClicSound.play();
			switch (_gameData.SaveSelect)
			{
			case 1:
				_gameData.SaveSelect = 3;
				_gameData.FileToOpen = "maps/Save3.txt";
				resetSaveSprite(_gameData);
				_gameData.SaveButtonSprite[2] = _gameData.SaveButton[2][1];
				break;

			case 2:
				_gameData.SaveSelect = 4;
				_gameData.FileToOpen = "maps/Save4.txt";
				resetSaveSprite(_gameData);
				_gameData.SaveButtonSprite[3] = _gameData.SaveButton[3][1];
				break;
			case 3:
				_gameData.SaveSelect = 1;
				_gameData.FileToOpen = "maps/Save1.txt";
				resetSaveSprite(_gameData);
				_gameData.SaveButtonSprite[0] = _gameData.SaveButton[0][1];
				break;
			case 4:
				_gameData.SaveSelect = 2;
				_gameData.FileToOpen = "maps/Save2.txt";
				resetSaveSprite(_gameData);
				_gameData.SaveButtonSprite[1] = _gameData.SaveButton[1][1];
				break;
			}
			Sleep(200);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			_gameData.ClicSound.play();
			EraseMap(_gameData, _gameData.FileToOpen);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			_gameData.ClicSound.play();
			ResetGame(_gameData, _gohstsData);
			_gameData.PlayButtonSprite = _gameData.PlayButton[1];
			_gameData.state = LOAD_OR_MODIFY;
			_gameData.DisplayError = false;
			_gameData.ToModify = false;
			_gameData.PlayButtonSprite = _gameData.PlayButton[1];
			_gameData.EditButtonSprite = _gameData.EditButton[0];
			Sleep(200);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			_gameData.ClicSound.play();
			resetSaveSprite(_gameData);
			_gameData.Bg = LoadSprite("Assets/bg/Menu.png", false);
			_gameData.state = MENU;
			_gameData.nextState = GAME;
			_gameData.music.openFromFile("Assets/Sounds/MenuGame.ogg");
			_gameData.music.play();
		}
		break;
	case LOAD_OR_MODIFY:

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			switch (_gameData.ToModify)
			{
			case true:
				_gameData.ClicSound.play();
				_gameData.ToModify = false;
				_gameData.PlayButtonSprite = _gameData.PlayButton[1];
				_gameData.EditButtonSprite = _gameData.EditButton[0];

				break;
			case false:
				_gameData.ClicSound.play();
				_gameData.ToModify = true;
				_gameData.PlayButtonSprite = _gameData.PlayButton[0];
				_gameData.EditButtonSprite = _gameData.EditButton[1];
				break;
			}
			Sleep(200);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{

			if (_gameData.ToModify == true)
			{
				_gameData.ClicSound.play();
				_gameData.state = EDIT;
				_gameData.Bg = LoadSprite("Assets/bg/Edit.png", false);
			}
			else
			{
				if (_gameData.DisplayError == false)
				{
					_gameData.ClicSound.play();
					_gameData.freeCells.clear();
					FindFreeCells(_gameData, _gameData.freeCells, NB_ROWS, NB_COLS, _gameData.map);
					if (_gameData.freeCells.size() <= 10)
					{
						_gameData.AlertText = _gameData.IssueBox[0];
						if (_gameData.map[1][1] == WALL)
						{
							_gameData.AlertText = _gameData.IssueBox[2];
						}
						_gameData.DisplayError = true;
					}
					else if (_gameData.map[1][1] == WALL)
					{
						_gameData.AlertText = _gameData.IssueBox[1];
						if (_gameData.freeCells.size() <= 10)
						{
							_gameData.AlertText = _gameData.IssueBox[2];
						}
						_gameData.DisplayError = true;

					}
					else
					{
						saveMap(_gameData, _gameData.FileToOpen);
						ResetGame(_gameData, _gohstsData);
						_gameData.FrameLimit = 5;
						_gameData.state = GAME;
						_gameData.music.openFromFile("Assets/Sounds/MenuGame.ogg");
						_gameData.music.play();

					}

				}
				else if (_gameData.DisplayError == true)
				{
					_gameData.ClicSound.play();
					_gameData.DisplayError = false;
				}

			}


			Sleep(150);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			_gameData.state = CUSTOM_MAP_MENU;
			_gameData.SaveButtonSprite[0] = _gameData.SaveButton[0][1];
			_gameData.SaveSelect = 1;
			_gameData.ClicSound.play();
			Sleep(200);
		}

		break;
	case GAME:
		_gameData.FrameLimit = 5;
#pragma region debug 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			_gameData.player.score = _gameData.ScoreMax;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			_gameData.player.Hp = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			switch (_gameData.debugInvicibility)
			{
			case true:_gameData.debugInvicibility = false;
				break;
			case false:_gameData.debugInvicibility = true;
				break;
			}
			Sleep(200);
		}


#pragma endregion
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			_gameData.FrameLimit = 240;
			_gameData.Bg = LoadSprite("Assets/bg/Pause.png", false);
			_gameData.state = PAUSE;
			_gameData.music.setVolume(50);
			Sleep(200);
		}
		MovePlayer(_gameData);
		UpdateGhosts(_gohstsData, _gameData);
		EatDot(_gameData);
		UpdatePlayer(_gameData);
		UpdateHud(_gameData);
		Conditions(_gameData);
		_gameData.ClicSound.play();
		break;
	case PAUSE:

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			resetSaveSprite(_gameData);
			ResetGame(_gameData, _gohstsData);
			_gameData.state = MENU;
			_gameData.Bg = LoadSprite("Assets/bg/Menu.png", false);
			_gameData.nextState = GAME;
			_gameData.ClicSound.play();
			_gameData.music.setVolume(100);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			_gameData.FrameLimit = 5;
			_gameData.state = GAME;
			_gameData.ClicSound.play();
			_gameData.music.setVolume(100);
			Sleep(200);
		}

		break;
	case WIN:

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			switch (_gameData.nextState)
			{
			case MENU:
				_gameData.nextState = EXIT;
				_gameData.ExitButtonSprite = _gameData.ExitButton[1];
				_gameData.MenuButtonSprite = _gameData.MenuButton[0];
				_gameData.ClicSound.play();
				break;
			case EXIT:
				_gameData.nextState = MENU;
				_gameData.ExitButtonSprite = _gameData.ExitButton[0];
				_gameData.MenuButtonSprite = _gameData.MenuButton[1];
				_gameData.ClicSound.play();
				break;
			}
			Sleep(200);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			resetSaveSprite(_gameData);
			_gameData.state = _gameData.nextState;
			_gameData.Bg = LoadSprite("Assets/bg/Menu.png", false);
			_gameData.nextState = GAME;
			_gameData.ClicSound.play();
			_gameData.music.openFromFile("Assets/Sounds/MenuGame.ogg");
			_gameData.music.play();
			Sleep(200);
		}
		break;
	case OVER:

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			switch (_gameData.nextState)
			{
			case MENU:
				_gameData.nextState = EXIT;
				_gameData.ExitButtonSprite = _gameData.ExitButton[1];
				_gameData.MenuButtonSprite = _gameData.MenuButton[0];
				_gameData.ClicSound.play();
				break;
			case EXIT:
				_gameData.nextState = MENU;
				_gameData.ExitButtonSprite = _gameData.ExitButton[0];
				_gameData.MenuButtonSprite = _gameData.MenuButton[1];
				_gameData.ClicSound.play();
				break;
			}
			Sleep(200);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			resetSaveSprite(_gameData);
			_gameData.state = _gameData.nextState;
			_gameData.Bg = LoadSprite("Assets/bg/Menu.png", false);
			_gameData.nextState = GAME;
			_gameData.ClicSound.play();
			_gameData.music.openFromFile("Assets/Sounds/MenuGame.ogg");
			_gameData.music.play();
			Sleep(200);
		}
		break;
	case HELP:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
		{
			_gameData.state = MENU;
			_gameData.Bg = LoadSprite("Assets/bg/Menu.png", false);
			_gameData.ClicSound.play();
			Sleep(200);
		}
		break;
	case EXIT:
		_gameData.window.close();
		break;
	}
}
