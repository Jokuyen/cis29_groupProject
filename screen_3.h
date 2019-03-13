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
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

const char* backgroundImage = "grass.png";
// Monster
const char* monsterImage = "monster.png";
const char* monsterCollisionImage = "monsterCollision.png";
// Player
const char* playerImageOne = "playertempone.png";
const char* playerImageTwo = "playertemptwo.png";
const char* shieldImage = "shield.png";

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
    try { // throws error if file not opened
        if(!font.loadFromFile(fontImage))
        {
            throw FileOpenException(fontImage);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
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
    try { // throws error if file not opened
        if(!backgroundTexture.loadFromFile(backgroundImage))
        {
            throw FileOpenException(backgroundImage);
        }
    }
    catch(exception& e)
    {
        //cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    background.setTexture(&backgroundTexture);
    
    // Monster Vector Array
    std::vector<Monster>::const_iterator monsterIterator;
    std::vector<Monster> monsterArray;
    
    // Monsters
    sf::Texture monsterTexture;
	sf::Texture monsterCollisionTexture;
	monsterTexture.loadFromFile(monsterImage);
	monsterCollisionTexture.loadFromFile(monsterCollisionImage);
    
    sf::Texture playerTextureOne;
    try { // throws error if file not opened
        if(!playerTextureOne.loadFromFile(playerImageOne))
        {
            throw FileOpenException(playerImageOne);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Texture playerTextureTwo;
    try { // throws error if file not opened
        if(!playerTextureTwo.loadFromFile(playerImageTwo))
        {
            throw FileOpenException(playerImageTwo);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Texture shieldTexture;
    try { // throws error if file not opened
        if(!shieldTexture.loadFromFile(shieldImage))
        {
            throw FileOpenException(shieldImage);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    Player p(playerTextureOne, playerTextureTwo, shieldTexture, SCREENWIDTH, BG_HEIGHT);
    
    string name = "Name";
    sf::Text txt(name + "                   " + "Score: " + to_string(p.getScore()) + "                 " + "Lives: " + to_string(p.getLives()), font);
    txt.setCharacterSize(40);
    txt.setFillColor(sf::Color::White);
    
    // Time management variables
	sf::Clock monsterSpawnClock;
    sf::Clock monsterSpeedClock;
	sf::Clock shieldDelayClock;
	sf::Clock shieldPopClock;
   
    sf::Event event;
    while (Running)
    {
        // Time management
		sf::Time monsterSpawnTimer = monsterSpawnClock.getElapsedTime();
        sf::Time monsterSpeedTimer = monsterSpeedClock.getElapsedTime();
		sf::Time shieldDelayTimer = shieldDelayClock.getElapsedTime();
		sf::Time shieldPopTimer = shieldPopClock.getElapsedTime();
        
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
		if (shieldDelayTimer.asSeconds() > 5)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				p.applyShield();
				shieldDelayClock.restart();
				shieldPopClock.restart();
			}
		}
		if (shieldPopTimer.asSeconds() > 2.2 && shieldPopTimer.asSeconds() < 2.5) 
		{
			p.loseShield();
		}

        
        App.clear();
        //App.draw(txt);
        App.draw(background);
        p.draw(App);
        
        // Drawing monsters

		if (monsterSpawnTimer.asSeconds() > 3.2) // Create new monster
		{
			int randomNumber;
			randomNumber = rand() % 2;

			if (randomNumber == 0) // Spawn from left side
			{
				Monster monster(monsterTexture, monsterCollisionTexture, -65, static_cast<float>(rand() % (BG_HEIGHT * 2)));
				monsterArray.push_back(monster);
			}
			else if (randomNumber == 1) // Spawn from right side
			{
				Monster monster(monsterTexture, monsterCollisionTexture, static_cast<float>(SCREENWIDTH * 2.1), static_cast<float>(rand() % (BG_HEIGHT * 2)));
				monsterArray.push_back(monster);
			}

			monsterSpawnClock.restart();
		}

        int counter = 0;
        for (monsterIterator = monsterArray.begin(); monsterIterator != monsterArray.end(); monsterIterator++)
        {
            if (p.getPosition() == monsterArray[counter].getPosition())
            {
                //std::cout << p.getPosition() << "     " << monsterArray[counter].getPosition() << std::endl;
                p.loseLife();
            }
            monsterArray[counter].updateMovement(SCREENWIDTH, BG_HEIGHT);
            
            // If timer passes 2.5 seconds, increase monsters' speed and restart clock to 0
			if (monsterSpeedTimer.asSeconds() > 2.5)
			{
				monsterArray[counter].increaseSpeed();
				monsterSpeedClock.restart();
			}
            
            if (p.hitByMonster(monsterArray[counter].getPosition().x, monsterArray[counter].getPosition().y, monsterArray[counter].size()))
            {
                if (p.getHit() == -1) {
                    std::cout << "Player hit by Monster" << std::endl;
                    p.setHit(counter);
                    p.loseLife();
                    txt.setString(name + "                      " + "Score: " + to_string(p.getScore()) + "                     " + "Lives: " + to_string(p.getLives()));
					monsterArray[counter].collisionAnimation();
				}
            }
            else
            {
                if (p.getHit() == counter)
                    p.setHit(-1);
				monsterArray[counter].movementAnimation();
                //std::cout << "No Collision" << std::endl;
            }
            
			monsterArray[counter].draw(App);
            counter++;
        }
        
        
        
        App.draw(txt);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* screen_3_h */
