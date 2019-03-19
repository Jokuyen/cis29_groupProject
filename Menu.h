//
//  Menu.h
//  jscreens


#ifndef Menu_h
#define Menu_h

#include <iostream>
#include "cScreen.h"
#include "FileOpenException.h"

#include <SFML/Graphics.hpp>

class Menu : public cScreen
{
public:
    Menu(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int Menu::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
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
    sf::Text text("How to Play"
                  "\n\nPlay"
                  "\n\nHigh Score Board"
                  "\n\nQuit"
                  , font);
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);
    
    // Center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f));
    
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
                sf::Vector2i position = sf::Mouse::getPosition();
                std::cout << position.x << " " << position.y << std::endl;
                //how to play
                if((position.x > 890 && position.x < 1660) && (position.y > 2290 && position.y < 2380))
                {
                    return (1);
                }
                //game screen
                if((position.x > 890 && position.x < 1175) && (position.y > 2530 && position.y < 2630))
                {
                    return (3);
                }
                //highscore screen
                if((position.x > 890 && position.x < 2000) && (position.y > 2780 && position.y < 2875))
                {
                    cout << "6" << endl;
                    return (6);
                }
                //quit
                if((position.x > 890 && position.x < 1185) && (position.y > 3020 && position.y < 3105))
                {
                    return (-1);
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

#endif /* Menu_h */
