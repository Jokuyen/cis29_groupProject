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
    sf::Text text("Controls: \n\nMovement (Arrow keys) \nAttack (A) \nShield (S) \n\nShield lasts for 2 seconds \nand recharges after 4 seconds. \nClick (Left) to drop a bomb."
                  , font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    
    //menu button
    sf::Text mButton("Menu", font);
    mButton.setCharacterSize(50);
    mButton.setFillColor(sf::Color::Green);
    sf::FloatRect mButtonRect = mButton.getLocalBounds();
    mButton.setOrigin(mButtonRect.left + mButtonRect.width / 2.0f, mButtonRect.top + mButtonRect.height / 2.0f);
    mButton.setPosition(sf::Vector2f(SCREENWIDTH / 14.0f, (8*SCREENHEIGHT / 9.0f)));
    
    //play button
    sf::Text pButton("Play", font);
    pButton.setCharacterSize(50);
    pButton.setFillColor(sf::Color::Green);
    sf::FloatRect pButtonRect = pButton.getLocalBounds();
    pButton.setOrigin(pButtonRect.left + pButtonRect.width / 2.0f, pButtonRect.top + pButtonRect.height / 2.0f);
    pButton.setPosition(sf::Vector2f(13*SCREENWIDTH / 14.0f, (8*SCREENHEIGHT / 9.0f)));
    
    sf::Event event;
    while (Running)
    {
        // Verifying events
        while (App.pollEvent(event))
        {
            // Window closed
            if (event.type == sf::Event::EventType::Closed)
                return (-1);
            // mouse pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i position = sf::Mouse::getPosition(App);
                std::cout << position.x << " " << position.y << std::endl;
                if((position.x > (mButton.getPosition().x-(mButtonRect.width/2)) && position.x < (mButton.getPosition().x+(mButtonRect.width/2)) && (position.y > (mButton.getPosition().y-(mButtonRect.height/2)) && position.y < (mButton.getPosition().y + (mButtonRect.height/2)))))
                {
                    return (7);
                }
                if((position.x > (pButton.getPosition().x-(pButtonRect.width/2)) && position.x < (pButton.getPosition().x+(pButtonRect.width/2)) && (position.y > (pButton.getPosition().y-(pButtonRect.height/2)) && position.y < (pButton.getPosition().y + (pButtonRect.height/2)))))
                {
                    return (8);
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Return: // Progress to screen_2
                        return (8);
                        break;
                    case sf::Keyboard::Backspace: // Progress to screen_2
                        return (2);
                        break;
                    default:
                        break;
                }
            }
            
            //key pressed
        }
        
        App.clear();
        App.draw(text);
        App.draw(mButton);
        App.draw(pButton);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}
