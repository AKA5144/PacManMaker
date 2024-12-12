#ifndef COMMON_HPP
#define COMMON_HPP

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

#include "GameData.hpp"





sf::Sprite LoadSprite(std::string _path, bool _centered);
void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, sf::RenderWindow& _window, sf::Vector2f _scale = { 1.0,1.0 }, float _rotation = 0, sf::Color _color = sf::Color::White);
void DrawPixel(sf::Image& _image, int _posX, int _posY, sf::Color _color);


#endif

