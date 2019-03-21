

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
        sout << "Congratulations!" << endl;
        sout << "You made it into the top 10!" << endl;
        sout << endl;
        sout << "Enter your name: ";
        sout << endl;
    }
    else {
        sout << "Nice job!" << endl;
        sout << "Play again to be on the" << endl;
        sout << "list of Top 10 players!" << endl;
        sout << endl;
        sout << endl;
    }
    text.setString(sout.str());
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f));
    
    sf::Text nextButton("Next", font);
    nextButton.setCharacterSize(40);
    nextButton.setFillColor(sf::Color::Green);
    sf::FloatRect nextButtonRect = nextButton.getLocalBounds();
    nextButton.setOrigin(nextButtonRect.left + nextButtonRect.width / 2.0f, nextButtonRect.top + nextButtonRect.height / 2.0f);
    nextButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (9*SCREENHEIGHT / 10.0f)));
    
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
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i position = sf::Mouse::getPosition(App);
                std::cout << position.x << " " << position.y << std::endl;
                if((position.x > (nextButton.getPosition().x-(nextButtonRect.width/2)) && position.x < (nextButton.getPosition().x+(nextButtonRect.width/2)) && (position.y > (nextButton.getPosition().y-(nextButtonRect.height/2)) && position.y < (nextButton.getPosition().y + (nextButtonRect.height/2)))))
                {
					if (!name.empty()) {
						highScores.insert({ score, name });
						if (highScores.size() > 10)
							highScores.erase((highScores.begin())->first);
						writeToScoreFile(filename, highScores);
					}
                    return (6);
                }
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128) {
                    name += static_cast<char>(event.text.unicode);
                    sout << static_cast<char>(event.text.unicode);
                    text.setString(sout.str());
                }
                //sout << "Next";
                
            }
            App.draw(text);
        }
        
        App.clear();
        App.draw(text);
        App.draw(nextButton);
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
