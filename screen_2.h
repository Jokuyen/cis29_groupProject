/*
 This screen has an explanation the control functions of the game specifically along with controls to move forward.
 */
#include <iostream>
#include "cScreen.h"

#include <SFML/Graphics.hpp>

class screen_2 : public cScreen
{
public:
    screen_2(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int screen_2::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
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
    sf::Text text("Controls: \n\nMovement (Arrow keys) \nAttack (A) \nShield (S) \n\nShield lasts for 2 seconds \nand recharges after 4 seconds.", font);
    text.setCharacterSize(100);
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
                    case sf::Keyboard::Backspace: // Return to screen_1
                        return (1);
                        break;
                    case sf::Keyboard::Return: // Return to screen_1
                        return (3);
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
