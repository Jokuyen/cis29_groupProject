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
    if (!font.loadFromFile("fake receipt.ttf"))
    {
        std::cout << "can't load font in screen_1" << std::endl;
        return (-1);
    }
    sf::Text text("Gameplay:"
                  "\nMonsters roam around the level."
                  "\nAttack monsters to damage them."
                  "\nDefend yourself from damage by shielding."
                  "\nNote that you cannot attack"
                  "\nand defend at the same time."
                  
                  "\n\nDefeat all monsters to advance."
                  "\nHowever, monsters become harder"
                  "\nto defeat as you advance!"
                  
                  "\n\nMeanwhile, coins are randomly"
                  "\nplaced throughout the level."
                  
                  "\n\nYour goal is to collect as many coins"
                  "\nas possible before being defeated!"
                  "\nGood luck!", font);
    text.setCharacterSize(50);
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
