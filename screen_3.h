//
//  screen_3.h
//  jscreens
//
//  Created by Mihika Marathe, Felicia Dewanaga, Johnny Nguyen, Manxin Zhang, Alan Rodriguez.
//  Copyright © 2019 Mihika Marathe, Felicia Dewanaga, Johnny Nguyen, Manxin Zhang, Alan Rodriguez.
//  All rights reserved.
//

#ifndef screen_3_h
#define screen_3_h

#include "Monster.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

const char* BACKGROUNDIMAGE = "grass.png";

// Monster assets
const char* MONSTERIMAGE = "monster.png";
const char* MONSTERTWOIMAGE = "monsterTwo.png";
const char* MONSTERCOLLISIONIMAGE = "monsterCollision.png";

// Player assets
const char* PLAYERIMAGEONE = "playertempone.png";
const char* PLAYERIMAGETWO = "playertemptwo.png";
const char* SHIELDIMAGE = "shield.png";

namespace Score {
	int score = 0;
}

class screen_3 : public cScreen
{
public:
    screen_3(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int screen_3::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    bool Running = true;
    
    // Font
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
    
    bool pause = false;
    
	// Background
    const int BG_HEIGHT = SCREENHEIGHT - 100;
    sf::RectangleShape background(sf::Vector2f(SCREENWIDTH, BG_HEIGHT));
    background.setPosition(sf::Vector2f(0, 50));
    sf::Texture backgroundTexture;
    try { // throws error if file not opened
        if(!backgroundTexture.loadFromFile(BACKGROUNDIMAGE))
        {
            throw FileOpenException(BACKGROUNDIMAGE);
        }
    }
    catch(exception& e)
    {
        //cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    background.setTexture(&backgroundTexture);
    
	// Player
    sf::Texture playerTextureOne;
    try { // throws error if file not opened
        if(!playerTextureOne.loadFromFile(PLAYERIMAGEONE))
        {
            throw FileOpenException(PLAYERIMAGEONE);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Texture playerTextureTwo;
    try { // throws error if file not opened
        if(!playerTextureTwo.loadFromFile(PLAYERIMAGETWO))
        {
            throw FileOpenException(PLAYERIMAGETWO);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Texture shieldTexture;
    try { // throws error if file not opened
        if(!shieldTexture.loadFromFile(SHIELDIMAGE))
        {
            throw FileOpenException(SHIELDIMAGE);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    Player p(playerTextureOne, playerTextureTwo, shieldTexture, SCREENWIDTH, BG_HEIGHT);

	// Header line
	string name = "Name";
	sf::Text txt(name + "                   " + "Score: " + to_string(p.getScore()) + "                 " + "Lives: " + to_string(p.getLives()), font);
	txt.setCharacterSize(40);
	txt.setFillColor(sf::Color::White);

	// Monster
	sf::Texture monsterTexture;
	sf::Texture monsterTwoTexture;
	sf::Texture monsterCollisionTexture;
	monsterTexture.loadFromFile(MONSTERIMAGE);
	monsterTwoTexture.loadFromFile(MONSTERTWOIMAGE);
	monsterCollisionTexture.loadFromFile(MONSTERCOLLISIONIMAGE);

	// Monster Vector Array
	std::vector<Monster *>::const_iterator monsterIterator;
	std::vector<Monster *> monsterArray;
    
    // Time management variables
    sf::Clock monsterSpawnClock;
    sf::Clock monsterSpeedClock;
    sf::Clock shieldDelayClock;
    sf::Clock shieldPopClock;

	cout << "Enter Score: ";
	cin >> Score::score;
    
    sf::Event event;
    while (Running)
    {
        // Time management
        sf::Time monsterSpawnTimer = monsterSpawnClock.getElapsedTime();
        sf::Time monsterSpeedTimer = monsterSpeedClock.getElapsedTime();
        sf::Time shieldDelayTimer = shieldDelayClock.getElapsedTime();
        sf::Time shieldPopTimer = shieldPopClock.getElapsedTime();
        
        bool attack = false;
        
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
					case sf::Keyboard::Space:
						pause = !pause;
						break;
                    default:
                        break;
                }
            }
        }

		if (!pause) {
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
			if (shieldDelayTimer.asSeconds() > 4)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					p.applyShield();
					shieldDelayClock.restart();
					shieldPopClock.restart();
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				attack = true;
			}
			if (shieldPopTimer.asSeconds() > 2.2 && shieldPopTimer.asSeconds() < 2.5)
			{
				p.loseShield();
			}
			App.clear();
			App.draw(background);
			p.draw(App);

			// Create new monster
			if (monsterSpawnTimer.asSeconds() > 3.2)
			{
				int randomNumber;
				randomNumber = rand() % 2;

				// Spawn from left side
				if (randomNumber == 0)
				{
					monsterArray.push_back(new Monster(monsterTexture, monsterTwoTexture, monsterCollisionTexture, -65, static_cast<float>(rand() % (BG_HEIGHT * 2))));
				}
				// Spawn from right side
				else if (randomNumber == 1)
				{
					monsterArray.push_back(new Monster(monsterTexture, monsterTwoTexture, monsterCollisionTexture, static_cast<float>(SCREENWIDTH * 2.1), static_cast<float>(rand() % (BG_HEIGHT * 2))));
				}

				monsterSpawnClock.restart();
			}

			int counter = 0;
			for (monsterIterator = monsterArray.begin(); monsterIterator != monsterArray.end(); monsterIterator++)
			{
				monsterArray[counter]->updateMovement(SCREENWIDTH, BG_HEIGHT);

				// If timer passes 2.5 seconds, increase monsters' speed and restart clock to 0
				if (monsterSpeedTimer.asSeconds() > 2.5)
				{
					monsterArray[counter]->movementAnimation();
					monsterArray[counter]->increaseSpeed();
					monsterSpeedClock.restart();
				}

				// Collision detection
				if (p.hitByMonster(monsterArray[counter]->getPosition().x, monsterArray[counter]->getPosition().y, monsterArray[counter]->size()))
				{
					if (p.getHit() == -1) {
						std::cout << "Player hit by Monster" << std::endl;
						p.setHit(counter);
						p.loseLife();
						txt.setString(name + "                      " + "Score: " + to_string(p.getScore()) + "                     " + "Lives: " + to_string(p.getLives()));
						monsterArray[counter]->collisionAnimation();
					}
				}
				else
				{
					if (p.getHit() == counter)
						p.setHit(-1);
				}
				monsterArray[counter]->draw(App);
				counter++;
			}
		}
            
             
        App.draw(txt);
        App.display();
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* screen_3_h */
