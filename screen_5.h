/********************
 *  Created by Manxin Zhang
 *  CIS29 / Group #4
 ********************/

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <map>
using namespace std;

#include "cScreen.h"
#include <SFML/Graphics.hpp>

const size_t MaxNumOfScores = 10;
void eraseScoreFile(const char* filename);
int writeToScoreFile(const char* filename, multimap<int, string>);
int readFromScoreFile(const char* filename, multimap<int, string>&);

class screen_5 : public cScreen
{
public:
	screen_5(void) { }
	virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int screen_5::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
	string name = "";
	int score = Score::score;

	multimap<int, string> highScores;
	const char* filename = "ScoreFile.txt";
	readFromScoreFile(filename, highScores);

	bool Running = true;


	sf::Font font;
	try { // throws error if file not opened
		if (!font.loadFromFile(FONTIMAGE))
		{
			throw FileOpenException(FONTIMAGE);
		}
	}
	catch (exception& e)
	{
		cout << "Cannot open: " << e.what() << endl;
		exit(-1);
	}


	sf::Text text("", font);
	ostringstream sout;

	if (highScores.size() < 10 || score > (highScores.begin())->first && score > 0) {
		sout << "Congratulations! You made it into top 10!" << endl;
		sout << "Enter your name: ";
	}
	else {
		sout << "Nice job!\nPlay again to be on the \nlist of Top 10 players!";
	}
	text.setString(sout.str());
	text.setCharacterSize(70);
	text.setFillColor(sf::Color::White);

	// Center text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f));
	App.draw(text);

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
			else if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128) {
					name += static_cast<char>(event.text.unicode);
					sout << static_cast<char>(event.text.unicode);
					text.setString(sout.str());
				}

			}
			else if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Return: // Progress to screen_0
					if (!name.empty()) {
						highScores.insert({ score, name });
						if (highScores.size() > 10)
							highScores.erase((highScores.begin())->first);
						writeToScoreFile(filename, highScores);
					}
					return (6);
					break;
				case sf::Keyboard::Backspace: // Return to screen_4
					return (4);
					break;
				default:
					break;
				}
			}
			App.draw(text);
		}

		App.clear();
		App.draw(text);
		App.display();
	}

	return (-1);
}

void eraseScoreFile(const char* filename) {
	ofstream fout(filename);
}

int writeToScoreFile(const char* filename, multimap<int, string> myMap) {
	ofstream fout(filename);
	try {
		if (!fout) {
			throw FileOpenException(filename);
		}
	}
	catch (FileOpenException& e) {
		cout << "File not found. Creating new file: " << e.what() << endl;
		ofstream fout(filename);
		fout.close();
		return 0;
	}

	if (myMap.size() == 0) {
		return 0;
	}
	for (auto it : myMap) {
		fout << it.first << "  " << it.second << endl;
	}

	fout.close();
}

int readFromScoreFile(const char* filename, multimap<int, string>& myMap) {
	int count = 0;
	ifstream fin(filename);
	try {
		if (!fin) {
			throw FileOpenException(filename);
		}
	}
	catch (FileOpenException& e) {
		cout << "File not found. Creating new file: " << e.what() << endl;
		ofstream fout(filename);
		fout.close();
		return count;
	}

	if (fin.peek() == std::ifstream::traits_type::eof()) {
		return count;
	}

	int score = 0;
	string name = "";

	while (fin >> score) {
		fin >> name;
		myMap.insert({ score, name });
		count++;
	}
	fin.close();
	return count;
}