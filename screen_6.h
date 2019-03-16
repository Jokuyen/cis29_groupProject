/********************
 *  Created by Manxin Zhang
 *  CIS29 / Group #4
 ********************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "cScreen.h"
#include <SFML/Graphics.hpp>

class screen_6 : public cScreen
{
public:
	screen_6(void) { }
	virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int screen_6::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
	multimap<int, string> highScores;
	const char* filename = "ScoreFile.txt";
	readFromScoreFile(filename, highScores);

	bool Running = true;


	sf::Font font;
	if (!font.loadFromFile("fake receipt.ttf"))
	{
		std::cout << "Unable to load font" << std::endl;
		return (-1);
	}


	sf::Text text("", font);
	ostringstream sout;
	sout << "Score Board" << endl;

	int count = 0;
	for (auto it = highScores.rbegin(); it != highScores.rend(); ++it) {
		sout << setw(2) << (++count) << setw(5) << it->first << "\t" << it->second << endl;
	}
	text.setString(sout.str());
	text.setCharacterSize(70);
	text.setFillColor(sf::Color::White);

	sf::Event event;
	while (Running)
	{
		// Verifying events
		while (App.pollEvent(event))
		{
			// Window closed
			if (event.type == sf::Event::EventType::Closed)
				return (-1);
			// Key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Return: // Progress to screen_0
					return (0);
					break;
				case sf::Keyboard::Backspace: // Return to screen_4
					return (5);
					break;
				default:
					break;
				}
			}
		}

		App.clear();
		App.draw(text);
		App.display();
	}

	return (-1);
}
