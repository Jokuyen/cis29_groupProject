//
//  screen_3.h
//  jscreens
//
//  Created by Mihika Marathe on 2/24/19.
//  Copyright © 2019 Mihika Marathe. All rights reserved.
//

#ifndef screen_3_h
#define screen_3_h

#include "monster.h"
const std::string monsterImageFilename = "monster.png";

class screen_3 : public cScreen
{
public:
    screen_3(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int screen_3::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    bool Running = true;
    
    // Setup font
    sf::Font font;
    if (!font.loadFromFile("fake receipt.ttf"))
    {
        std::cout << "can't load font in screen_0" << std::endl;
        return (-1);
    }
    
    //Will need to link player object here.
    sf::Text txt("Name"
                   "\t\t\t\t\t\t\t\t\tScore:  "
                   "\tLives:  "
                 "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nInstructions(Backspace)"
                 "\t\t\t\t\t\t\t\tQuit(Q)", font);
    txt.setCharacterSize(40);
    txt.setFillColor(sf::Color::White);
    
	const int BG_HEIGHT = SCREENHEIGHT - 100;
    sf::RectangleShape background(sf::Vector2f(SCREENWIDTH, BG_HEIGHT));
    background.setPosition(sf::Vector2f(0, 50));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("grass.jpg");
    background.setTexture(&backgroundTexture);

	// Monster Vector Array
	std::vector<Monster>::const_iterator monsterIterator;
	std::vector<Monster> monsterArray;

	// Monsters
	sf::Texture monsterTexture;
	Collision::CreateTextureAndBitmask(monsterTexture, monsterImageFilename);

	sf::Clock clock;

    sf::Event event;
    while (Running)
    {
		// Time management
		sf::Time timer = clock.getElapsedTime();
		//std::cout << timer.asSeconds() << std::endl;

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
                    //instructions
                    case sf::Keyboard::Backspace: // Back to screen 2
                        return (2);
                        break;
                    //quit
                    case sf::Keyboard::Q: // Back to screen 0
                        return (0);
                        break;
                    default:
                        break;
                }
            }
        }

		// Create new enemies
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			Monster monster(&monsterTexture, SCREENWIDTH, BG_HEIGHT);
			monsterArray.push_back(monster);
		}
        
        App.clear();
        App.draw(txt);
        App.draw(background);

		// Draw enemies
		int counter = 0;
		for (monsterIterator = monsterArray.begin(); monsterIterator != monsterArray.end(); monsterIterator++)
		{
			monsterArray[counter].updateMovement(SCREENWIDTH, BG_HEIGHT);

			// If timer passes 2.5 seconds, increase monsters' speed and restart clock to 0
			if (timer.asSeconds() > 2.5)
			{
				monsterArray[counter].increaseSpeed();
				clock.restart();
			}

			monsterArray[counter].draw(App);

			counter++;
		}

        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* screen_3_h */
