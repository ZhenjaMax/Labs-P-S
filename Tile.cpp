#include "Tile.h"
#include "Collider.h"
#include <SFML/Graphics.hpp>

Tile::Tile(sf::Texture* texture, sf::Vector2f position, int tileType) :
	tileType(tileType), tileCollider(body)
{
	body.setSize(sf::Vector2f((float)texture->getSize().x, (float)texture->getSize().y));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position * body.getSize().x);
	body.setTexture(texture);
}

void Tile::draw(sf::RenderWindow& window)
{
	window.draw(body);
	if (tileType == 1)
		tileCollider.checkCollision(playerCollider, 1.0f);
}