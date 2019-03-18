/*
 This is the welcome screen, it includes the name of the game and controls to move forward.
 */

#include <iostream>
#include "cScreen.h"
#include "FileOpenException.h"

#include <SFML/Graphics.hpp>

class screen_0 : public cScreen
{
public:
    screen_0(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int screen_0::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
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
    sf::Text text("Gold Rush"
                  "\n\nEnter: Next screen"
                  "\nBackspace: Previous screen", font);
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::White);

    // Center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f));

    sf::Event event;

    //View a.k.a camera
    sf::View view;
    view.reset(sf::FloatRect(0, 0, SCREENWIDTH, SCREENHEIGHT));
    view.setViewport(sf::FloatRect(0, 0, 0.7f, 0.7f));
    sf::Vector2f viewPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);

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
                    case sf::Keyboard::Return: // Progress to screen_1
                        return (1);
                        break;
                    default:
                        break;
                }
            }
        }

        App.setView(view);
        App.clear();
        App.draw(text);
        App.display();
    }

    // Never reach this point normally, but just in case, exit the application
    return (-1);
}
