#include <iostream>
#include "cScreen.h"

#include <SFML/Graphics.hpp>

class screen_4 : public cScreen
{
public:
    screen_4(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int screen_4::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    bool Running = true;
    
    // Setup font
    sf::Font font;
    try { // throws error if file not opened
        if(!font.loadFromFile(fontImage))
        {
            throw FileOpenException(fontImage);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Text text("Game Over", font);
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
                    case sf::Keyboard::Return: // Progress to screen_2
                        return (5);
                        break;
                    case sf::Keyboard::Backspace: // Return to screen_0
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
