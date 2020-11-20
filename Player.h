#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Singleton.h"

class Player : public Singleton<Player>
{
public:
	friend class Singleton<Player>;
	void create(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position) {body.setPosition(position);}
	Collider getCollider();

private:
	Player();
	~Player();
	sf::RectangleShape body;
	Animation* animation = nullptr;
	unsigned int row = 0;
	float speed = 0;
	bool isFaceRight = false;
	bool isStanding = false;
};

