#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	currentImage.y = 0;

	uvRect.width = texture->getSize().x / imageCount.x;
	uvRect.height = texture->getSize().y / imageCount.y;
}

void Animation::update(int rowY, float deltaTime, bool isfaceRight, bool isStanding) 
{
	currentImage.y = rowY;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		if (!isStanding) {
			currentImage.x++;
			if (currentImage.x >= imageCount.x)
			{
				currentImage.x = 0;
			}
		}
		else
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * uvRect.height;

	if (isfaceRight)
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
	else
	{
		uvRect.left = currentImage.x * abs(uvRect.width);
		uvRect.width = abs(uvRect.width);
	}
}
