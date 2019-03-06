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
#include "Collision.h"

#include "screens.h"

#include <iostream>

int main(int argc, char** argv)
{
	const int SCREENWIDTH = 2048;
	const int SCREENHEIGHT = 1536;

	// Applications variables
	std::vector<cScreen*> Screens;
	int screen = 0;

	// Window creation & set frame rate
	sf::RenderWindow App(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "Gold Rush");
	App.setFramerateLimit(60);

	// Screens preparation
	screen_0 s0;
	Screens.push_back(&s0);
	screen_1 s1;
	Screens.push_back(&s1);
	screen_2 s2;
	Screens.push_back(&s2);
	screen_3 s3;
	Screens.push_back(&s3);
	screen_4 s4;
	Screens.push_back(&s4);

	// Main loop
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App, SCREENWIDTH, SCREENHEIGHT);
	}
}

/*
 jscreens mihika$ g++ -Wall -std=c++11 *.cpp -Iinclude -I/usr/local/include -L/usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -o main
*/