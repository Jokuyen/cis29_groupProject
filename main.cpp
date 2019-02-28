// Johnny Nguyen
// CIS 29

/*
 DOCUMENTATION
 ----------------------------------------------------------------------------
 Screen 0: Introduction Screen (This is where the name of the game should be)
 Screen 1: Gameplay Screen
 Screen 2: Help/Controls Screen
 */

#include <SFML/Graphics.hpp>

#include "screens.h"

#include <iostream>

int main(int argc, char** argv)
{
	/*
	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Demo Game");

	sf::Event event;

	sf::Texture texture;
	if (!texture.loadFromFile("monster.png"))
	{
		std::cerr << "Could not load monster.png\n";
	}

	sf::Sprite sprite(texture);

	while (renderWindow.isOpen()) {
		while (renderWindow.pollEvent(event)) 
		{
			if (event.type == sf::Event::EventType::Closed)
				renderWindow.close();
			// Key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up: // Move up
					sprite.move(sf::Vector2f(0.f, -10.f));;
					break;
				case sf::Keyboard::Down: // Move down
					sprite.move(sf::Vector2f(0.f, 10.f));;
					break;
				case sf::Keyboard::Left: // Move left
					sprite.move(sf::Vector2f(-10.f, 0.f));;
					break;
				case sf::Keyboard::Right: // Move right
					sprite.move(sf::Vector2f(10.f, 0.f));;
					break;
				default:
					break;
				}
			}
		}

		renderWindow.clear();
		renderWindow.draw(sprite);
		renderWindow.display();
	}
	*/

    const int SCREENWIDTH = 1680;
    const int SCREENHEIGHT = 1050;
    
    // Applications variables
    std::vector<cScreen*> Screens;
    int screen = 0;
    
    // Window creation
    sf::RenderWindow App(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "Gold Rush");
    
    // Screens preparation
    screen_0 s0;
    Screens.push_back(&s0);
    screen_1 s1;
    Screens.push_back(&s1);
    screen_2 s2;
    Screens.push_back(&s2);
    screen_3 s3;
    Screens.push_back(&s3);
    
    // Main loop
    while (screen >= 0)
    {
        screen = Screens[screen]->Run(App, SCREENWIDTH, SCREENHEIGHT);
    }
}

/*
 jscreens mihika$ g++ -Wall -std=c++11 *.cpp -Iinclude -I/usr/local/include -L/usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -o main
*/
