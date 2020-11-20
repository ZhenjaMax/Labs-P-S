#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"

Menu::Menu()
{
    window.create(sf::VideoMode(512, 512), "OOP Game", sf::Style::Close | sf::Style::Resize);

    float width = (float)window.getSize().x;
    float height = (float)window.getSize().y;

    font.loadFromFile("arial.ttf");

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	selectedItemIndex = 0;
}


Menu::~Menu()
{

}

void Menu::draw()
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		window.draw(menu[i]);
}

void Menu::MoveUp()
{
	menu[selectedItemIndex].setFillColor(sf::Color::White);
	if (--selectedItemIndex < 0)
		selectedItemIndex += MAX_NUMBER_OF_ITEMS;
	menu[selectedItemIndex].setFillColor(sf::Color::Red);
}

void Menu::MoveDown()
{
	menu[selectedItemIndex].setFillColor(sf::Color::White);
	if (++selectedItemIndex >= MAX_NUMBER_OF_ITEMS)
		selectedItemIndex -= MAX_NUMBER_OF_ITEMS;
	menu[selectedItemIndex].setFillColor(sf::Color::Red);
}

int Menu::GetPressedItem()
{
	return selectedItemIndex;
}

void Menu::exec()
{
    Game game(window);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    MoveUp();
                    break;
                case sf::Keyboard::Down:
                    MoveDown();
                    break;
                case sf::Keyboard::Return:
                    switch (GetPressedItem())
                    {
                    case 0:
                        std::cout << "Play button has been pressed" << std::endl;
                        game.start();                                                           // ÒÎ×ÊÀ ÂÕÎÄÀ Â ÈÃÐÓ
                        break;
                    case 1:
                        std::cout << "Option button has been pressed" << std::endl;
                        break;
                    case 2:
                        window.close();
                        break;
                    }
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        window.clear(sf::Color(127, 127, 127));
        draw();
        window.display();
    }
}


/*if ( ((float)sf::Mouse::getPosition(window).x > 0) && ((float)sf::Mouse::getPosition(window).y > 0) &&
     ((float)sf::Mouse::getPosition(window).x < 512) && ((float)sf::Mouse::getPosition(window).y < 512) )
{
    player.setPosition((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);
}*/

/*
if (player.getPosition().x > 512)
{
    player.setPosition(512, player.getPosition().y);
}
if (player.getPosition().y > 512)
{
    player.setPosition(player.getPosition().x, 512);
}
if (player.getPosition().x < 0)
{
    player.setPosition(0, player.getPosition().y);
}
if (player.getPosition().y < 0)
{
    player.setPosition(player.getPosition().x, 0);
}
*/