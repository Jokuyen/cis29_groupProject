//
//  screen_3.h
//  jscreens
//
//  Created by Mihika Marathe on 2/24/19 and Felicia Dewanaga on 3/7/19.
//  Copyright © 2019 Mihika Marathe and Felicia Dewanaga on 3/7/19. All rights reserved.
//

#ifndef screen_3_h
#define screen_3_h

#include "Monster.h"
#include "Collision.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

const std::string monsterImageFilename = "monster.png";

class screen_3 : public cScreen
{
public:
    screen_3(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int screen_3::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    bool Running = true;
    
    // Setup font
    sf::Font font;
    if (!font.loadFromFile("fake receipt.ttf"))
    {
        std::cout << "can't load font in screen_0" << std::endl;
        return (-1);
    }
    
    //bool pause = false;
    
    //Will need to link player object here.
    /*sf::Text txt("Name"
     "\t\t\t\t\t\t\t\t\tScore:  "
     "\tLives:  "
     "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nInstructions(Backspace)"
     "\t\t\t\t\t\t\t\tQuit(Q)", font);
     */
    
    const int BG_HEIGHT = SCREENHEIGHT - 100;
    sf::RectangleShape background(sf::Vector2f(SCREENWIDTH, BG_HEIGHT));
    background.setPosition(sf::Vector2f(0, 50));
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("grass.png");
    background.setTexture(&backgroundTexture);
    
    // Monster Vector Array
    std::vector<Monster>::const_iterator monsterIterator;
    std::vector<Monster> monsterArray;
    
    // Monsters
    sf::Texture monsterTexture;
    Collision::CreateTextureAndBitmask(monsterTexture, monsterImageFilename);
    
    sf::Texture playerTextureOne;
    playerTextureOne.loadFromFile("playertempone.png");
    sf::Texture playerTextureTwo;
    playerTextureTwo.loadFromFile("playertemptwo.png");
    sf::Texture shieldTexture;
    shieldTexture.loadFromFile("shield.png");
    Player p(playerTextureOne, playerTextureTwo, shieldTexture, SCREENWIDTH, BG_HEIGHT);
    
    string name = "Name";
    sf::Text txt(name + "                   " + "Score: " + to_string(p.getScore()) + "                 " + "Lives: " + to_string(p.getLives()), font);
    txt.setCharacterSize(40);
    txt.setFillColor(sf::Color::White);
    
    // Time management variables
    sf::Clock monsterSpeedClock;
    sf::Clock collisionDelayClock;
    
    sf::Event event;
    while (Running)
    {
        // Time management
        sf::Time monsterSpeedTimer = monsterSpeedClock.getElapsedTime();
        sf::Time collisionDelayTimer = collisionDelayClock.getElapsedTime();
        
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
                    case sf::Keyboard::Backspace: // Back to screen 2
                        return (2);
                        break;
                    case sf::Keyboard::Q: // Back to screen 0
                        return (0);
                        break;
                    case sf::Keyboard::Return: // Return to screen_1
                        return (4);
                        break;
                    default:
                        break;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) // Create new enemies
            {
                Monster monster(monsterTexture, SCREENWIDTH, BG_HEIGHT);
                monsterArray.push_back(monster);
            }
        }
        
        // Player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            p.move(Player::Left);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            p.move(Player::Right);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            p.move(Player::Up);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            p.move(Player::Down);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            p.applyShield();
        }
        
        
        App.clear();
        //App.draw(txt);
        App.draw(background);
        p.draw(App);
        
        // Drawing enemies
        int counter = 0;
        for (monsterIterator = monsterArray.begin(); monsterIterator != monsterArray.end(); monsterIterator++)
        {
            monsterArray[counter].updateMovement(SCREENWIDTH, BG_HEIGHT);
            
            // If timer passes 2.5 seconds, increase monsters' speed and restart clock to 0
            if (monsterSpeedTimer.asSeconds() > 2.5)
            {
                monsterArray[counter].increaseSpeed();
                monsterSpeedClock.restart();
            }
            
            monsterArray[counter].draw(App);
            
            if (Collision::PixelPerfectTest(monsterArray[counter].getSprite(), p.getSprite()))
            {
                /* If collisionDelayClock is more than selected seconds, allow to collision to occur and reset the clock
                 This allows player some time to recover and prevents multiple collisions after the first one */
                if (collisionDelayTimer.asSeconds() > 3)
                {
                    std::cout << "Player hit by monster" << std::endl;
                    p.loseLife();
                    txt.setString(name + "                      " + "Score: " + to_string(p.getScore()) + "                     " + "Lives: " + to_string(p.getLives()));
                    collisionDelayClock.restart();
                }
            }
            
            counter++;
        }
        
        App.draw(txt);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* screen_3_h */
