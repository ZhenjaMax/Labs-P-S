#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"

class Game
{
public:
	Game(sf::RenderWindow& window);
	~Game();
	int load();
	int save();
	void resizeView(const sf::RenderWindow& window, sf::View& view);
	void start();

private:
	sf::RenderWindow& window;
	bool fullScreen = false;
};

