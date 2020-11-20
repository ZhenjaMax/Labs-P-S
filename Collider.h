#pragma once
#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body) : body(body) {}
	~Collider() {}
	bool checkCollision(Collider other, float pushSpeed);
	sf::Vector2f getPosition() {return body.getPosition();}
	sf::Vector2f getHalfSize() {return body.getSize() / 2.0f;}
	void move(float dx, float dy) {body.move(dx, dy);}

private:
	sf::RectangleShape& body;
};

