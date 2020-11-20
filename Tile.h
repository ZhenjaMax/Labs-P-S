#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Player.h"

class Tile
{
public:
	Tile(sf::Texture* texture, sf::Vector2f position, int tileType);
	~Tile() {};
	void draw(sf::RenderWindow& window);
	int getTileType()						{return tileType;}
	sf::Vector2f getSize()					{return body.getSize();};
	sf::Vector2f getPosition()				{return body.getPosition();}
	void setTileType(int newTileType)		{tileType = newTileType;}
	void setSize(sf::Vector2f dimensions)	{body.setSize(dimensions);}
	void setPosition(sf::Vector2f position) {body.setPosition(position);}

private:
	int tileType = 0;
	bool isPassable = false;
	sf::Texture* texture = nullptr;
	sf::RectangleShape body;
	Collider tileCollider;
	Collider playerCollider = Player::getInstance().getCollider();
};
