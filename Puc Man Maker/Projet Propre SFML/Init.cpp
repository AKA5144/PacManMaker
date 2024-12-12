#include "Init.hpp"
#include "Common.hpp"


void ResetGame(GameData& _gameData, GhostsData& _gohstsData)
{
	system("cls");
	_gameData.freeCells.clear();
	_gameData.MapIsLoad = false;
	playerLoad(_gameData);
	_gameData.ScoreMax = 0;
	_gameData.textPos.x = 35;
	_gameData.DotsAreLoaded = false;
	_gameData.textPos.y = 1;
	initSfmlMap(_gameData);
	// Init character locations & player HP
	FindFreeCells(_gameData, _gameData.freeCells, NB_ROWS, NB_COLS, _gameData.map);
	InitGhostsMoves(_gohstsData, _gameData, _gameData.freeCells);
	InitDots(_gameData);
	InitGhost(_gohstsData);
	InitFont(_gameData);
	_gameData.debugInvicibility = false;
}

void LoadButtonSprite(GameData& _gameData)
{
	_gameData.PlayButton[0] = LoadSprite("Assets/Buttons/Play1.png", true);
	_gameData.PlayButton[1] = LoadSprite("Assets/Buttons/Play2.png", true);
	_gameData.PlayButtonSprite = _gameData.PlayButton[1];

	_gameData.CreateButton[0] = LoadSprite("Assets/Buttons/Create1.png", true);
	_gameData.CreateButton[1] = LoadSprite("Assets/Buttons/Create2.png", true);
	_gameData.CreateButtonSprite = _gameData.CreateButton[0];


	_gameData.SaveButton[0][0] = LoadSprite("Assets/Buttons/Save1_1.png", true);
	_gameData.SaveButton[0][1] = LoadSprite("Assets/Buttons/Save1_2.png", true);
	_gameData.SaveButtonSprite[0] = _gameData.SaveButton[0][1];

	_gameData.SaveButton[1][0] = LoadSprite("Assets/Buttons/Save2_1.png", true);
	_gameData.SaveButton[1][1] = LoadSprite("Assets/Buttons/Save2_2.png", true);
	_gameData.SaveButtonSprite[1] = _gameData.SaveButton[1][0];

	_gameData.SaveButton[2][0] = LoadSprite("Assets/Buttons/Save3_1.png", true);
	_gameData.SaveButton[2][1] = LoadSprite("Assets/Buttons/Save3_2.png", true);
	_gameData.SaveButtonSprite[2] = _gameData.SaveButton[2][0];

	_gameData.SaveButton[3][0] = LoadSprite("Assets/Buttons/Save4_1.png", true);
	_gameData.SaveButton[3][1] = LoadSprite("Assets/Buttons/Save4_2.png", true);
	_gameData.SaveButtonSprite[3] = _gameData.SaveButton[3][0];

	_gameData.MenuButton[0] = LoadSprite("Assets/Buttons/Menu1.png", true);
	_gameData.MenuButton[1] = LoadSprite("Assets/Buttons/Menu2.png", true);
	_gameData.MenuButtonSprite = _gameData.MenuButton[0];

	_gameData.EditButton[0] = LoadSprite("Assets/Buttons/Edit1.png", true);
	_gameData.EditButton[1] = LoadSprite("Assets/Buttons/Edit2.png", true);;
	_gameData.EditButtonSprite = _gameData.EditButton[0];

	_gameData.ExitButton[0] = LoadSprite("Assets/Buttons/Exit1.png", true);
	_gameData.ExitButton[1] = LoadSprite("Assets/Buttons/Exit2.png", true);;
	_gameData.ExitButtonSprite = _gameData.ExitButton[0];


	_gameData.SquareWall = LoadSprite("Assets/mur.png", true);
	_gameData.SquareGround = LoadSprite("Assets/pelouse.png", true);
	_gameData.SquareTurn = LoadSprite("Assets/TurnPoint.png", true);
	_gameData.PlayerIcon = LoadSprite("Assets/creaman1.png", true);

	_gameData.TilesSprite[0] = LoadSprite("Assets/pelouse.png", false);
	_gameData.TilesSprite[1] = LoadSprite("Assets/mur.png", false);
	_gameData.TilesSprite[2] = LoadSprite("Assets/TurnPoint.png", false);

	_gameData.IssueBox[0] = LoadSprite("Assets/bg/Warning1.png", false);
	_gameData.IssueBox[1] = LoadSprite("Assets/bg/Warning2.png", false);
	_gameData.IssueBox[2] = LoadSprite("Assets/bg/Warning3.png", false);

}

void resetSaveSprite(GameData& _gameData)
{
	_gameData.PlayButtonSprite = _gameData.PlayButton[1];

	_gameData.SaveButtonSprite[0] = _gameData.SaveButton[0][0];

	_gameData.SaveButtonSprite[1] = _gameData.SaveButton[1][0];

	_gameData.SaveButtonSprite[2] = _gameData.SaveButton[2][0];

	_gameData.SaveButtonSprite[3] = _gameData.SaveButton[3][0];

	_gameData.ExitButtonSprite = _gameData.ExitButton[0];

	_gameData.EditButtonSprite = _gameData.EditButton[0];

	_gameData.MenuButtonSprite = _gameData.MenuButton[0];

	_gameData.CreateButtonSprite = _gameData.CreateButton[0];
}

void LoadSound(GameData& _gameData)
{
	_gameData.music.openFromFile("Assets/Sounds/MenuGame.ogg");
	_gameData.music.play();
	_gameData.buffer.loadFromFile("Assets/Sounds/clic.wav");
	_gameData.ClicSound.setBuffer(_gameData.buffer);
}
void load(GameData& _gameData, GhostsData& _gohstsData)
{

	_gameData.state = MENU;
	switch (_gameData.state)
	{
	case MENU:

		_gameData.Bg = LoadSprite("Assets/bg/Menu.png", false);
		_gameData.nextState = GAME;
		LoadSound(_gameData);
		LoadButtonSprite(_gameData);
		break;
	case GAME:

		break;
	}

}