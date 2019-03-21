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
                  "\nbefore things get out of hand!"
                  , font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, SCREENHEIGHT / 2.5f));
    
    //next button
    sf::Text nextButton("Next", font);
    nextButton.setCharacterSize(40);
    nextButton.setFillColor(sf::Color::Green);
    sf::FloatRect nextButtonRect = nextButton.getLocalBounds();
    nextButton.setOrigin(nextButtonRect.left + nextButtonRect.width / 2.0f, nextButtonRect.top + nextButtonRect.height / 2.0f);
    nextButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (9*SCREENHEIGHT / 10.0f)));
    
    sf::Event event;
    while (Running)
    {
        // Verifying events
        while (App.pollEvent(event))
        {
            // Window closed
            if (event.type == sf::Event::EventType::Closed)
                return (-1);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i position = sf::Mouse::getPosition(App);
                std::cout << position.x << " " << position.y << std::endl;
                if((position.x > (nextButton.getPosition().x-(nextButtonRect.width/2)) && position.x < (nextButton.getPosition().x+(nextButtonRect.width/2)) && (position.y > (nextButton.getPosition().y-(nextButtonRect.height/2)) && position.y < (nextButton.getPosition().y + (nextButtonRect.height/2)))))
                {
                    return (2);
                }
            }
        }
        
        App.clear();
        App.draw(text);
        App.draw(nextButton);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}
