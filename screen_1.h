/*
 This screen includes an explanation of the game along with controls to move forward.
 */


#include <iostream>
#include "cScreen.h"

#include <SFML/Graphics.hpp>

class screen_1 : public cScreen
{
public:
    screen_1(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int screen_1::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    bool Running = true;
    
    // Setup font
    sf::Font font;
    try { // throws error if file not opened
        if(!font.loadFromFile(FONTIMAGE))
        {
            throw FileOpenException(FONTIMAGE);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
	sf::Text text("Gameplay:"
		"\n\nCollect coins to increase \nyour score."
		"\n\nBe careful of wandering monsters!"
		"\nAttack monsters to defeat them."
		"\nDefend yourself by shielding."

		"\n\nMonsters gradually increase in"
		"\nspeed, so defeat them quickly"
		"\nbefore things get out of hand!", font);
    text.setCharacterSize(85);
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
                    case sf::Keyboard::Return: // Progress to screen_2
                        return (2);
                        break;
                    case sf::Keyboard::Backspace: // Return to screen_0
                        return (0);
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
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}
