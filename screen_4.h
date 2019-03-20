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
    
    sf::Text text("Game Over"
                  , font);
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::Red);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, 4*SCREENHEIGHT / 10.0f));
    
    
    //sf::Text text("Game Over", font);
    string score = "Score: ";
    sf::Text sPrint(score + to_string(Score::score), font);
    sPrint.setCharacterSize(60);
    sPrint.setFillColor(sf::Color::White);
    sf::FloatRect sRect = sPrint.getLocalBounds();
    sPrint.setOrigin(sRect.left + sRect.width / 2.0f, sRect.top + sRect.height / 2.0f);
    sPrint.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.0f));
    
    sf::Text nextButton("Next", font);
    nextButton.setCharacterSize(50);
    nextButton.setFillColor(sf::Color::White);
    sf::FloatRect nextButtonRect = nextButton.getLocalBounds();
    nextButton.setOrigin(nextButtonRect.left + nextButtonRect.width / 2.0f, nextButtonRect.top + nextButtonRect.height / 2.0f);
    nextButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (3*SCREENHEIGHT / 5.0f)));
    
    
    
    
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
                sf::Vector2i position = sf::Mouse::getPosition(App);
                std::cout << position.x << " " << position.y << std::endl;
                if((position.x > (nextButton.getPosition().x-(nextButtonRect.width/2)) && position.x < (nextButton.getPosition().x+(nextButtonRect.width/2)) && (position.y > (nextButton.getPosition().y-(nextButtonRect.height/2)) && position.y < (nextButton.getPosition().y + (nextButtonRect.height/2)))))
                {
                    return (5);
                }
            }
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
        App.draw(sPrint);
        App.draw(nextButton);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}
