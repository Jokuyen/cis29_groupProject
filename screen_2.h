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
    if (!font.loadFromFile("fake receipt.ttf"))
    {
        std::cout << "can't load font in screen_1" << std::endl;
        return (-1);
    }
    sf::Text text("Controls \nW: Move up \nS: Move down \nA: Move left \nD: Move right \n\nO: Attack \nP: Defend", font);
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
					case sf::Keyboard::Return: // Progress to screen_3
						return (3);
						break;
                    case sf::Keyboard::Backspace: // Return to screen_1
                        return (1);
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
