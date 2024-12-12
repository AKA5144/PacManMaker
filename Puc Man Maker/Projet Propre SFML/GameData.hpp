#ifndef GAMEDATA_HPP
#define GAMEDATA_HPP


#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>
#include "SFML/OpenGL.hpp"
#include"GameLib_CPP.h"

#define NB_GHOSTS 4
#define NB_ROWS 11
#define NB_COLS 31
#define SCREEN_WIDTH 992
#define SCREEN_HEIGHT 652

enum InputKeys
{
	Z = 122,
	S = 115,
	Q = 113,
	D = 100,
	R = 114,
	L = 108,
	ENTER = 13
};

enum Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct Player
{
	Pos pos;
	Dir dir;
	sf::Sprite sprite[4];
	int rotate = 0;
	sf::Clock animationClock;
	float animationSpeed = 1.0f;
	float tempsCourant;
	int imageCourante = 0;
	int score = 0;
	int Hp;
	bool Invincible;
	sf::Clock InvTimer;
	float InvGetTimer;
	sf::Color color;
	sf::Vector2i SpawnLocation;
};



enum TilesType
{
	FREE_CELL,
	WALL,
	TURNING_POINT,
};

struct Tile
{
	sf::Vector2f pos;
	sf::Sprite sprite;
	TilesType type;
	bool IsFree;
};

struct Dots
{
	bool isEaten;
	sf::Sprite sprite;
	sf::Vector2f pos;

};

enum State
{
	MENU,
	GAME,
	PAUSE,
	OVER,
	WIN,
	EDIT,
	CUSTOM_MAP_MENU,
	LOAD_OR_MODIFY,
	EXIT,
	HELP,
};
struct GameData
{

	sf::RenderWindow window;
	WindowSize winSize;
	int map[NB_ROWS][NB_COLS];
	Tile SfmlMap[NB_ROWS][NB_COLS];
	Dots dots[NB_ROWS][NB_COLS];

	Pos textPos = { 0 };

	InputKeys keyPressed;
	Player player;
	int ScoreMax;
	State state;

	bool DotsAreLoaded;
	bool gameSaved = false;
	std::vector<Pos> freeCells;

	bool debugInvicibility = false;
	bool isThereADot = false;
	char numScore[4] = { 0 };
	char chInput = 0;
	int idxDot = 0;

	bool MapIsLoad;
	sf::Font font;
	sf::Text Score;

	sf::Text Life;
	sf::Sprite AlertText;
	sf::Sprite IssueBox[3];

	sf::Sprite Bg;

	State nextState;
	sf::Sprite PlayButton[2];
	sf::Sprite PlayButtonSprite;

	sf::Sprite CreateButton[2];
	sf::Sprite CreateButtonSprite;

	sf::Sprite MenuButton[2];
	sf::Sprite MenuButtonSprite;

	sf::Sprite EditButton[2];
	sf::Sprite EditButtonSprite;

	sf::Sprite ExitButton[2];
	sf::Sprite ExitButtonSprite;


	sf::Sprite SaveButton[4][2];
	sf::Sprite SaveButtonSprite[4];

	sf::Sprite TilesSprite[3];

	int FrameLimit = 240;
	sf::Music music;
	sf::Sound ClicSound;
	sf::SoundBuffer buffer;
	/// ///////////// EDIT SECTION

	int SaveSelect = 1;

	sf::Vector2i SpawnPlayer;
	bool IsGhostRandomSpawn;
	int counter = 0;
	int DataStore[3];
	std::string FileToOpen;

	sf::RectangleShape rectangle;
	sf::Vector2f RectPos;

	int TileToSet = 0;
	bool ToModify = false;
	std::string FileDataToOpen;

	sf::Sprite SquareWall;
	sf::Sprite SquareGround;
	sf::Sprite SquareTurn;
	sf::Sprite PlayerIcon;
	bool SetPlayer = false;
	bool DisplayError = false;
};



#endif

