#include <iostream>
#include "cScreen.h"
#include <string>

#include <SFML/Graphics.hpp>


/*
 This screen contains a message saying the game is over and controls to move forward.
 */
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
    //sf::Text text("Game Over", font);
    string t = "Game Over";
    sf::Text title(t + "\n", font);
    string score = "\n\n\nScore: ";
    sf::Text text(score + to_string(Score::score) +  "\n  Next", font);
    title.setCharacterSize(70);
    text.setCharacterSize(60);
    
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    title.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f));
    title.setFillColor(sf::Color::Red);
    
    // Center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f));
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
        App.draw(title);
        App.draw(text);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}
