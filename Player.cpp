#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

Player::Player(){}

Player::~Player()
{
	if (animation != nullptr)
		delete animation;
}

void Player::create(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
{
	this->speed = speed;
	row = 0;

	body.setSize(sf::Vector2f(float(texture->getSize().x / imageCount.x), float(texture->getSize().y / imageCount.y)));
	body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
	body.setPosition(100.0f, 100.0f);
	body.setTexture(texture);
	animation = new Animation(texture, imageCount, switchTime);
}

void Player::update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= speed * deltaTime;

	if (movement.y > 0.0f)
	{
		row = 0;
	}
	if (movement.y < 0.0f)
	{
		row = 1;
	}
	if (movement.x != 0.0f)
	{
		row = 2;
		isFaceRight = (movement.x > 0.0f);
	}

	if ((movement.x != 0.0f) && (movement.y != 0.0f))
	{
		movement.x *= 0.75;												// ≈сли не учитывать, то окажетс€,
		movement.y *= 0.75;												// что по диагонали идти намного быстрее
	}																	// ѕусть sqrt(0.5) ~= 0.75

	isStanding = ((movement.x == 0.0f) && (movement.y == 0.0f));		// TODO: слева по€вл€етс€ пиксель

	animation->update(row, deltaTime, isFaceRight, isStanding);			// ≈сли персонаж стоит, то первый спрайт
	body.setTextureRect(animation->uvRect);
	body.move(movement);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

sf::Vector2f Player::getPosition() 
{
	return body.getPosition();
}

Collider Player::getCollider()
{
	return Collider(body);
}