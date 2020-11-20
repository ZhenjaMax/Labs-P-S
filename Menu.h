#pragma once
#include "SFML/Graphics.hpp"

static const int MAX_NUMBER_OF_ITEMS = 3;
static const float VIEW_HEIGHT = 512.0f;

class Menu
{
public:
	Menu();
	~Menu();
	void exec();


private:
	void draw();
	void MoveUp();
	void MoveDown();
	int GetPressedItem();
	int selectedItemIndex;

	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::RenderWindow window;
};