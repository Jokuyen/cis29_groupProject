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
    
    //how to play button
    sf::Text htpButton("How to Play", font);
    htpButton.setCharacterSize(60);
    htpButton.setFillColor(sf::Color::White);
    sf::FloatRect htpButtonRect = htpButton.getLocalBounds();
    htpButton.setOrigin(htpButtonRect.left + htpButtonRect.width / 2.0f, htpButtonRect.top + htpButtonRect.height / 2.0f);
    htpButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (SCREENHEIGHT / 8.0f)));
    
    //play button
    sf::Text pButton("Play", font);
    pButton.setCharacterSize(60);
    pButton.setFillColor(sf::Color::White);
    sf::FloatRect pButtonRect = pButton.getLocalBounds();
    pButton.setOrigin(pButtonRect.left + pButtonRect.width / 2.0f, pButtonRect.top + pButtonRect.height / 2.0f);
    pButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (3*SCREENHEIGHT / 8.0f)));
    
    //high score screen button
    sf::Text hsButton("High Score List", font);
    hsButton.setCharacterSize(60);
    hsButton.setFillColor(sf::Color::White);
    sf::FloatRect hsButtonRect = hsButton.getLocalBounds();
    hsButton.setOrigin(hsButtonRect.left + hsButtonRect.width / 2.0f, hsButtonRect.top + hsButtonRect.height / 2.0f);
    hsButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (5*SCREENHEIGHT / 8.0f)));
    
    //quit button
    sf::Text qButton("Quit", font);
    qButton.setCharacterSize(60);
    qButton.setFillColor(sf::Color::White);
    sf::FloatRect qButtonRect = qButton.getLocalBounds();
    qButton.setOrigin(qButtonRect.left + qButtonRect.width / 2.0f, qButtonRect.top + qButtonRect.height / 2.0f);
    qButton.setPosition(sf::Vector2f(SCREENWIDTH / 2.0f, (7*SCREENHEIGHT / 8.0f)));
    
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
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Backspace: // Return to title screen
					return (0);
					break;
				default:
					break;
				}
			}
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "in";
                    sf::Vector2i position = sf::Mouse::getPosition(App);
                    std::cout << position.x << " " << position.y << std::endl;
                    //how to play button
                    if((position.x > (htpButton.getPosition().x-(htpButtonRect.width/2)) && position.x < (htpButton.getPosition().x+(htpButtonRect.width/2)) && (position.y > (htpButton.getPosition().y-(htpButtonRect.height/2)) && position.y < (htpButton.getPosition().y + (htpButtonRect.height/2)))))
                    {
                        return (1);
                    }
                    //play button
                    if((position.x > (pButton.getPosition().x-(pButtonRect.width/2)) && position.x < (pButton.getPosition().x+(pButtonRect.width/2)) && (position.y > (pButton.getPosition().y-(pButtonRect.height/2)) && position.y < (pButton.getPosition().y + (pButtonRect.height/2)))))
                    {
                        return (8);
                    }
                    //high score list button
                    if((position.x > (hsButton.getPosition().x-(hsButtonRect.width/2)) && position.x < (hsButton.getPosition().x+(hsButtonRect.width/2)) && (position.y > (hsButton.getPosition().y-(hsButtonRect.height/2)) && position.y < (hsButton.getPosition().y + (hsButtonRect.height/2)))))
                    {
                        return (6);
                    }
                    //quit button
                    if((position.x > (qButton.getPosition().x-(qButtonRect.width/2)) && position.x < (qButton.getPosition().x+(qButtonRect.width/2)) && (position.y > (qButton.getPosition().y-(qButtonRect.height/2)) && position.y < (qButton.getPosition().y + (qButtonRect.height/2)))))
                    {
                        return (-1);
                    }
                }
            }
        }
        
        App.clear();
        App.draw(htpButton);
        App.draw(pButton);
        App.draw(hsButton);
        App.draw(qButton);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* Menu_h */
