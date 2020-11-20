#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Field
{
public:
	Field(sf::Texture** texture);
	~Field();
	void draw(sf::RenderWindow& window);

private:
	Tile*** tileMap = nullptr;
	int height = 0;			// UP-DOWN
	int width = 0;			// LEFT-RIGHT
};

