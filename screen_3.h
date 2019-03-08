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
    Player p(playerTextureOne, playerTextureTwo, SCREENWIDTH, BG_HEIGHT);


    string name = "Name";
    sf::Text txt(name + "                   " + "Score: " + to_string(p.getScore()) + "                 " + "Lives: " + to_string(p.getLives()), font);
    txt.setCharacterSize(20);
	txt.setFillColor(sf::Color::White);

    sf::Clock clock;

    sf::Event event;
    while (Running)
    {
        // Time management
        sf::Time timer = clock.getElapsedTime();
        //std::cout << timer.asSeconds() << std::endl;

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
                        //instructions
                    case sf::Keyboard::Backspace: // Back to screen 2
                        return (2);
                        break;
                        //quit
                    case sf::Keyboard::Q: // Back to screen 0
                        return (0);
                        break;
                    case sf::Keyboard::Return: // Return to screen_1
                        return (4);
                        break;
                    case sf::Keyboard::S:
                        p.applyShield();
                        break;
                    case sf::Keyboard::Right:
                        p.move(Player::Right);
                        break;
                    case sf::Keyboard::Left:
                        p.move(Player::Left);
                        break;
                    case sf::Keyboard::Up:
                        p.move(Player::Up);
                        break;
                    case sf::Keyboard::Down:
                        p.move(Player::Down);
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


        App.clear();
        //App.draw(txt);
        App.draw(background);
        p.draw(App);


        // Draw enemies

        //cout << monsterArray.size() << endl;
        int counter = 0;
        for (monsterIterator = monsterArray.begin(); monsterIterator != monsterArray.end(); monsterIterator++)
        {
            if(p.getPosition() == monsterArray[counter].getPosition())
            {
                //std::cout << p.getPosition() << "     " << monsterArray[counter].getPosition() << std::endl;
                p.loseLife();
            }
            monsterArray[counter].updateMovement(SCREENWIDTH, BG_HEIGHT);

            // If timer passes 2.5 seconds, increase monsters' speed and restart clock to 0
            if (timer.asSeconds() > 2.5)
            {
                monsterArray[counter].increaseSpeed();
                clock.restart();
            }

            monsterArray[counter].draw(App);

            /*
			if (Collision::PixelPerfectTest(monsterArray[counter].getSprite(), p.getSprite()))
			{
				std::cout << "Collision" << std::endl;
			}
             */
            if (p.hitByMonster(monsterArray[counter].getPosition().x, monsterArray[counter].getPosition().y, monsterArray[counter].size()))
            {
                if (p.getHit() == -1) {
                    std::cout << "Player hit by Monster" << std::endl;
                    p.setHit(counter);
                    p.loseLife();
                    txt.setString(name + "                      " + "Score: " + to_string(p.getScore()) + "                     " + "Lives: " + to_string(p.getLives()));
                }
            }
			else
			{
			    if (p.getHit() == counter)
                    p.setHit(-1);
				//std::cout << "No Collision" << std::endl;
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
