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
                 "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nInstructions(Backspace)"
                 "\t\t\t\t\t\t\t\tQuit(Q)", font);
    txt.setCharacterSize(40);
    txt.setFillColor(sf::Color::White);
    
    sf::RectangleShape background(sf::Vector2f(1650.0f, 900.0f));
    background.setPosition(sf::Vector2f(15, 50));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("grass.jpg");
    background.setTexture(&backgroundTexture);

	// Monsters
	Monster monster(monsterImageFilename);

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
        
        App.clear();
        App.draw(txt);
        App.draw(background);
		monster.draw(App);
		monster.move();
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* screen_3_h */
