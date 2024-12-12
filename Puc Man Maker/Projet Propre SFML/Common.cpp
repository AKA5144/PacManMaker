#include "Common.hpp"

sf::Sprite LoadSprite(std::string _path, bool _centered)
{
	sf::Sprite sprite;
	sf::Texture* texture = new sf::Texture();

	texture->loadFromFile(_path);
	sprite.setTexture(*texture);

	if (_centered)
	{
		sprite.setOrigin({ (float)texture->getSize().x / 2, (float)texture->getSize().y / 2 });
	}

	return sprite;
}

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, sf::RenderWindow& _window, sf::Vector2f _scale, float _rotation, sf::Color _color)
{
	_sprite.setPosition(_pos);
	_sprite.setScale(_scale);
	_sprite.setRotation(_rotation);
	_sprite.setColor(_color);
	_window.draw(_sprite);
}

void DrawPixel(sf::Image& _image, int _posX, int _posY, sf::Color _color)
{
	if (_posX > 0 && _posY > 0 && _posX < SCREEN_WIDTH && _posY < SCREEN_HEIGHT)
	{
		_image.setPixel(_posX, _posY, _color);
	}
}
