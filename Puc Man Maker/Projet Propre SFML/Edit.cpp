#include "Edit.hpp"
#include "Common.hpp"

void InitMapManager(GameData& _gameData)
{
	std::ifstream inFile;
	inFile.open(_gameData.FileToOpen);
	std::string line = "";
	std::string temp = "";
	int k = 0;
	int j = 0;



	if (inFile.is_open())
	{

		while (getline(inFile, line))
		{
			if (line != "")
			{
				j = 0;
				line = line + ',';
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] != ',')
					{
						temp += line[i];
					}
					else
					{
						_gameData.map[k][j] = stoi(temp);
						temp = "";
						j++;
					}
				}
			}
			k++;
		}
	}



}


void saveMap(GameData& _gameData, std::string _FileToSave)
{
	std::ofstream fw(_FileToSave, std::ofstream::out);
	if (fw.is_open())
	{

		for (int row = 0; row < NB_ROWS; row++)
		{
			for (int col = 0; col < NB_COLS; col++)
			{
				fw << _gameData.map[row][col];
				if (col < NB_COLS - 1)
				{
					fw << ',';
				}

			}
			fw << "\n";
		}
		fw.close();
	}
}

void EraseMap(GameData& _gameData, std::string _FileToErase)
{
	std::ofstream fw(_FileToErase, std::ofstream::out);
	if (fw.is_open())
	{

		for (int row = 0; row < NB_ROWS; row++)
		{
			for (int col = 0; col < NB_COLS; col++)
			{
				fw << "0";
				if (col < NB_COLS - 1)
				{
					fw << ',';
				}

			}
			fw << "\n";
		}
		fw.close();
	}
}
void UpdateEdit(GameData& _gameData)
{
	_gameData.rectangle.setSize(sf::Vector2f(32, 32));
	for (int row = 0; row < NB_ROWS; row++)
	{
		for (int col = 0; col < NB_COLS; col++)
		{
			if ((sf::Mouse::getPosition(_gameData.window).x > _gameData.SfmlMap[row][col].pos.x) && (sf::Mouse::getPosition(_gameData.window).x < _gameData.SfmlMap[row][col].pos.x + _gameData.SfmlMap[row][col].sprite.getGlobalBounds().width)
				&& (sf::Mouse::getPosition(_gameData.window).y > _gameData.SfmlMap[row][col].pos.y) && (sf::Mouse::getPosition(_gameData.window).y < _gameData.SfmlMap[row][col].pos.y + _gameData.SfmlMap[row][col].sprite.getGlobalBounds().height))
			{
				_gameData.RectPos = _gameData.SfmlMap[row][col].pos;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					_gameData.map[row][col] = _gameData.TileToSet;

				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{

				if (_gameData.TileToSet == 0)
				{
					_gameData.TileToSet = 1;
				}
				else if (_gameData.TileToSet == 1)
				{
					_gameData.TileToSet = 2;
				}
				else if (_gameData.TileToSet == 2)
				{
					_gameData.TileToSet = 0;
				}
				Sleep(200);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				if (_gameData.TileToSet == 0)
				{
					_gameData.TileToSet = 2;
				}
				else if (_gameData.TileToSet == 1)
				{
					_gameData.TileToSet = 0;
				}
				else if (_gameData.TileToSet == 2)
				{
					_gameData.TileToSet = 1;
				}
				Sleep(100);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				_gameData.map[row][col] = 0;
			}


		}
	}
}






void DrawEdit(GameData& _gameData)
{
	//	rectangle.setPosition({ (float)sf::Mouse::getPosition(_gameData.window).x, (float)sf::Mouse::getPosition(_gameData.window).y });
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
				_gameData.SfmlMap[i][j].sprite = _gameData.TilesSprite[2];
				break;
			}
			_gameData.SfmlMap[i][j].pos = { _gameData.SfmlMap[i][j].sprite.getGlobalBounds().width * j ,  _gameData.SfmlMap[i][j].sprite.getGlobalBounds().height * i };

		}
	}
	_gameData.rectangle.setPosition(_gameData.RectPos);
	_gameData.rectangle.setFillColor(sf::Color::Transparent);
	_gameData.rectangle.setOutlineColor(sf::Color::White);
	_gameData.rectangle.setOutlineThickness(2);
	_gameData.window.draw(_gameData.rectangle);

	switch (_gameData.TileToSet)
	{
	case 0:
		BlitSprite(_gameData.SquareTurn, { SCREEN_WIDTH / 2 - _gameData.SquareTurn.getGlobalBounds().width, (SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4) + _gameData.SquareTurn.getGlobalBounds().height }, _gameData.window, { 1.5 , 1.5 }, 0, sf::Color(255, 255, 255, 100));

		BlitSprite(_gameData.SquareGround, { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4 }, _gameData.window, { 2 , 2 }, 0, sf::Color::White);

		BlitSprite(_gameData.SquareWall, { SCREEN_WIDTH / 2 + _gameData.SquareWall.getGlobalBounds().width, (SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4) + _gameData.SquareWall.getGlobalBounds().height }, _gameData.window, { 1.5 , 1.5 }, 0, sf::Color(255, 255, 255, 100));
		break;

	case 1:
		BlitSprite(_gameData.SquareGround, { SCREEN_WIDTH / 2 - _gameData.SquareTurn.getGlobalBounds().width, (SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4) + _gameData.SquareTurn.getGlobalBounds().height }, _gameData.window, { 1.5 , 1.5 }, 0, sf::Color(255, 255, 255, 100));

		BlitSprite(_gameData.SquareWall, { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4 }, _gameData.window, { 2 , 2 }, 0, sf::Color::White);

		BlitSprite(_gameData.SquareTurn, { SCREEN_WIDTH / 2 + _gameData.SquareTurn.getGlobalBounds().width, (SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4) + _gameData.SquareTurn.getGlobalBounds().height }, _gameData.window, { 1.5 , 1.5 }, 0, sf::Color(255, 255, 255, 100));
		break;

	case 2:
		BlitSprite(_gameData.SquareWall, { SCREEN_WIDTH / 2 - _gameData.SquareTurn.getGlobalBounds().width, (SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4) + _gameData.SquareTurn.getGlobalBounds().height }, _gameData.window, { 1.5 , 1.5 }, 0, sf::Color(255, 255, 255, 100));

		BlitSprite(_gameData.SquareTurn, { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4 }, _gameData.window, { 2 , 2 }, 0, sf::Color::White);

		BlitSprite(_gameData.SquareGround, { SCREEN_WIDTH / 2 + _gameData.SquareWall.getGlobalBounds().width, (SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4) + _gameData.SquareWall.getGlobalBounds().height }, _gameData.window, { 1.5 , 1.5 }, 0, sf::Color(255, 255, 255, 100));
		break;


	}




}