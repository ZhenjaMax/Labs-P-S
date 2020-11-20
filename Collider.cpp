#include "Collider.h"
#include <SFML/Graphics.hpp>

bool Collider::checkCollision(Collider other, float pushSpeed) 
{
	sf::Vector2f otherPosition = other.getPosition();
	sf::Vector2f otherHalfSize = other.getHalfSize();
	sf::Vector2f thisPosition = getPosition();
	sf::Vector2f thisHalfSize = getHalfSize();

	float dx = otherPosition.x - thisPosition.x;
	float dy = otherPosition.y - thisPosition.y;
	float intersectX = abs(dx) - (thisHalfSize.x + otherHalfSize.x);
	float intersectY = abs(dy) - (thisHalfSize.y + otherHalfSize.y);

	bool isCollision = ((intersectX < 0.0f) && (intersectY < 0.0f));

	if (isCollision)
	{
		pushSpeed = std::min(std::max(pushSpeed, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (dx > 0.0f)
			{
				move(intersectX * (1.0f - pushSpeed), 0.0f);
				other.move(-intersectX * pushSpeed, 0.0f);
			}
			else
			{
				move(-intersectX * (1.0f - pushSpeed), 0.0f);
				other.move(intersectX * pushSpeed, 0.0f);
			}
		}
		else
		{
			if (dy > 0.0f)
			{
				move(0.0f, intersectY * (1.0f - pushSpeed));
				other.move(0.0f, -intersectY * pushSpeed);
			}
			else
			{
				move(0.0f, -intersectY * (1.0f - pushSpeed));
				other.move(0.0f, intersectY * pushSpeed);
			}
		}
		return true;
	}
	return false;
}

