#include <iostream>
#include "Game.h"
#include "Field.h"

#include <fstream>

static const float VIEW_HEIGHT = 512.0f;

Game::Game(sf::RenderWindow& window):
    window(window)
{

}

Game::~Game()
{

}

int Game::load()
{
	return 0;
}

int Game::save()
{
	return 0;
}

void Game::resizeView(const sf::RenderWindow& window, sf::View& view)
{
    float windowRatio = (float)window.getSize().x / window.getSize().y;
    view.setSize(VIEW_HEIGHT * windowRatio, VIEW_HEIGHT);
}

void Game::start()
{
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));            // getSize окна

    sf::Texture wallTexture, floorTexture;
    wallTexture.loadFromFile("textures/wall.png");
    floorTexture.loadFromFile("textures/floor.png");
    sf::Texture* textures[2] = {&floorTexture, &wallTexture};

    Field field(textures);

    float switchTime = 0.3f;                                                                                                // Скорость смены спрайтов в секунду
    float speed = 100.0f;                                                                                                   // скорость измеряется в ... ?
    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/frisk.png");

    Player& player = Player::getInstance();                                                                                 // Размер изображения в спрайтах - 2*4, х*у
    player.create(&playerTexture, sf::Vector2u(4, 3), switchTime, speed);                                                   // Это SINGLETON !!!

    sf::Texture wallUATexture;
    wallUATexture.loadFromFile("textures/test5.png");
    Platform wallUA(&wallUATexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(150.0f, 300.0f));

    sf::Texture wallRUTexture;
    wallRUTexture.loadFromFile("textures/test6.png");
    Platform wallRU(&wallRUTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(300.0f, 150.0f));

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())                                                                                 // Сделать смену тиков == 50
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "\nNew size is:\t" << event.size.width << "\t" << event.size.height << std::endl;
                resizeView(window, view);
                break;
            case sf::Event::TextEntered:
                std::cout << (char)event.text.unicode;
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            fullScreen = !fullScreen;
            if (fullScreen)
            {
                window.create(sf::VideoMode::getDesktopMode(), "OOP Game", sf::Style::Fullscreen);
                resizeView(window, view);
            }
            else
            {
                window.create(sf::VideoMode(512, 512), "OOP Game", sf::Style::Close | sf::Style::Resize);
                resizeView(window, view);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            return;                                                         // ВЫХОД В МЕНЮ
        }

        wallRU.getCollider().checkCollision(player.getCollider(), 0.6f);
        wallUA.getCollider().checkCollision(player.getCollider(), 0.6f);
        wallRU.getCollider().checkCollision(wallUA.getCollider(), 0.6f);
        wallUA.getCollider().checkCollision(wallRU.getCollider(), 0.6f);

        player.update(deltaTime);
        view.setCenter(player.getPosition());
        window.clear(sf::Color(190, 242, 138));
        window.setView(view);

        field.draw(window);

        player.draw(window);
        wallUA.draw(window);
        wallRU.draw(window);

        window.display();

    }
}