#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Tile.h"
#include <fstream>

Field::Field(sf::Texture** texture)
{
	std::ifstream mapFile;
	mapFile.open("stringMap.txt");

	mapFile >> height >> width;

	height = 10;
	width = 10;
	int stringMap[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	tileMap = new Tile** [height];
	for (int y = 0; y < height; y++) {
		tileMap[y] = new Tile* [width];
		for (int x = 0; x < width; x++)
			tileMap[y][x] = new Tile(texture[stringMap[y][x]], sf::Vector2f((float)x, (float)y), stringMap[y][x]);
	}
}

Field::~Field()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			delete tileMap[y][x];
		delete tileMap[y];
	}
}

void Field::draw(sf::RenderWindow& window)
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			tileMap[y][x]->draw(window);
}
