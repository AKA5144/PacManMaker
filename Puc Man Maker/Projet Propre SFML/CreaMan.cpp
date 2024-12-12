#include <iostream>
#include <time.h>

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>
#include "SFML/OpenGL.hpp"

#include "Common.hpp"

#include "CreaMan.h"
#include "Player.h"
#include "MapManager.h"
#include "Ghost.h"
#include "GameData.hpp"
#include "Init.hpp"
#include "Display.hpp"
#include "UPdate.hpp"




int main()
{
	struct GameData gameData;
	struct GhostsData ghostsData;
	gameData.window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "CreaMan");
	gameData.window.setFramerateLimit(gameData.FrameLimit);
	gameData.winSize = InitDisplay();
	// Initialization
	srand((unsigned int)time(NULL));

	load(gameData, ghostsData);

	DisplayMap(gameData, gameData.textPos, gameData.map, gameData.winSize);
	// GameLoop


	while (gameData.window.isOpen())
	{

		sf::Event event;
		while (gameData.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				gameData.window.close();
			}
		}

		Update(gameData, ghostsData);

		Display(gameData, ghostsData);

	}
	
}