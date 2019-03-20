//
//  GameMode.h
//  jscreens


#ifndef GameMode_h
#define GameMode_h

#include <iostream>
#include "cScreen.h"
#include "FileOpenException.h"

#include <SFML/Graphics.hpp>

class GameMode : public cScreen
{
public:
    GameMode(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int GameMode::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
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
    
    //how to play button
    sf::Text regMode("Regular Mode", font);
    regMode.setCharacterSize(60);
    regMode.setFillColor(sf::Color::White);
    sf::FloatRect regButtonRect = regMode.getLocalBounds();
    regMode.setOrigin(regButtonRect.left + regButtonRect.width / 2.0f, regButtonRect.top + regButtonRect.height / 2.0f);
    regMode.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (2*SCREENHEIGHT / 7.0f)));
    
    //play button
    sf::Text pButton("Test Mode", font);
    pButton.setCharacterSize(60);
    pButton.setFillColor(sf::Color::White);
    sf::FloatRect pButtonRect = pButton.getLocalBounds();
    pButton.setOrigin(pButtonRect.left + pButtonRect.width / 2.0f, pButtonRect.top + pButtonRect.height / 2.0f);
    pButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (4*SCREENHEIGHT / 7.0f)));
    
    //high score screen button
    sf::Text mButton("Menu", font);
    mButton.setCharacterSize(50);
    mButton.setFillColor(sf::Color::White);
    sf::FloatRect mButtonRect = mButton.getLocalBounds();
    mButton.setOrigin(mButtonRect.left + mButtonRect.width / 2.0f, mButtonRect.top + mButtonRect.height / 2.0f);
    mButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (6*SCREENHEIGHT / 7.0f)));
    
    // Center text
    
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
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "in";
                    sf::Vector2i position = sf::Mouse::getPosition(App);
                    std::cout << position.x << " " << position.y << std::endl;
                    //how to play button
                    if((position.x > (regMode.getPosition().x-(regButtonRect.width/2)) && position.x < (regMode.getPosition().x+(regButtonRect.width/2)) && (position.y > (regMode.getPosition().y-(regButtonRect.height/2)) && position.y < (regMode.getPosition().y + (regButtonRect.height/2)))))
                    {
                        return (3);
                    }
                    //play button
                    if((position.x > (pButton.getPosition().x-(pButtonRect.width/2)) && position.x < (pButton.getPosition().x+(pButtonRect.width/2)) && (position.y > (pButton.getPosition().y-(pButtonRect.height/2)) && position.y < (pButton.getPosition().y + (pButtonRect.height/2)))))
                    {
                        testmode = true;
                        return (3);
                    }
                    //menu button
                    if((position.x > (mButton.getPosition().x-(mButtonRect.width/2)) && position.x < (mButton.getPosition().x+(mButtonRect.width/2)) && (position.y > (mButton.getPosition().y-(mButtonRect.height/2)) && position.y < (mButton.getPosition().y + (mButtonRect.height/2)))))
                    {
                        return (7);
                    }
                }
            }
        }
        
        App.clear();
        App.draw(mButton);
        App.draw(pButton);
        App.draw(regMode);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* Menu_h */
