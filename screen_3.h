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

#include <SFML/Audio.hpp>

#include "Monster.h"
#include "Player.h"
#include "Coins.h"
#include "Bomb.h"
#include "Explosion.h"
#include <iostream>
#include <string>

using namespace std;

const char* BACKGROUNDIMAGE = "wall8.png";
const char* THEMEMUSIC = "American Beauty.wav";

// Player assets
const char* PLAYERIMAGE = "catSpriteSheet.png";
const char* SHIELDIMAGE = "catSpriteSheetTwo.png";
const char* FLIPPEDPLAYERIMAGE = "flippedCatSpriteSheet.png";
const char* FLIPPEDSHIELDIMAGE = "flippedCatSpriteSheetTwo.png";

// Monster assets
const char* MONSTERIMAGE = "monster.png";
const char* MONSTERTWOIMAGE = "monsterTwo.png";
const char* MONSTERCOLLISIONIMAGE = "monsterCollision.png";

// BigBoss assets
const char* BIGBOSSIMAGE = "octopus.png";
const char* BIGBOSSTWOIMAGE = "octopus2.png";
const char* BIGBOSSCOLLISIONIMAGE = "octopusCollision.png";
const char* BIGBOSSHURTIMAGE = "octopusHurt.png";

//Bomb assets
const char* BOMBIMAGE = "missile.png";
const char* EXPLOSIONIMAGE = "explosion.png";
const char* EXPLOSIONSOUND = "explosion.wav";

//Border assets
const char* BORDERIMAGE = "wall8Mask.png";

namespace Score
{
	int score = 0;
}

double getRandom(int lower, int upper)
{
	double num = (rand() % (upper - lower + 1)) + lower;
	return num;
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
	bool pause = false;

    // Music
    sf::Music theme;
    try
    {
        if (!theme.openFromFile(THEMEMUSIC))
        {
            throw FileOpenException(THEMEMUSIC);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    theme.setLoop(true);
    theme.play();

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

    // Background
    //const int BG_HEIGHT = SCREENHEIGHT - 100;
    const int BG_WIDTH = 2700;
    const int BG_HEIGHT = 1800;
    sf::RectangleShape background(sf::Vector2f(BG_WIDTH, BG_HEIGHT));
    background.setPosition(sf::Vector2f(0, 0));
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
    sf::Texture playerTexture;
    try { // throws error if file not opened
        if(!playerTexture.loadFromFile(PLAYERIMAGE))
        {
            throw FileOpenException(PLAYERIMAGE);
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
    sf::Texture flippedPlayerTexture;
    try { // throws error if file not opened
        if (!flippedPlayerTexture.loadFromFile(FLIPPEDPLAYERIMAGE))
        {
            throw FileOpenException(FLIPPEDPLAYERIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Texture flippedShieldTexture;
    try { // throws error if file not opened
        if (!flippedShieldTexture.loadFromFile(FLIPPEDSHIELDIMAGE))
        {
            throw FileOpenException(FLIPPEDSHIELDIMAGE);
        }
    }
    catch (exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    Player p(playerTexture, shieldTexture, flippedPlayerTexture, flippedShieldTexture, SCREENWIDTH, BG_HEIGHT);
    p.setPosition(200,1000);

    // Header line
    string name = "Gold Rush";
    sf::Text txt(name + "\t\t\t\t\t\tScore: " + to_string(p.getScore()) + "\t\t\t\t\t\tLives: " + to_string(p.getLives()), font);
    txt.setCharacterSize(20);
    txt.setFillColor(sf::Color::White);

    // Monster
    sf::Texture monsterTexture;
    sf::Texture monsterTwoTexture;
    sf::Texture monsterCollisionTexture;
    monsterTexture.loadFromFile(MONSTERIMAGE);
    monsterTwoTexture.loadFromFile(MONSTERTWOIMAGE);
    monsterCollisionTexture.loadFromFile(MONSTERCOLLISIONIMAGE);
	int spawnCount = 1;

    // Monster Vector Array
    std::vector<Monster *>::const_iterator monsterIterator;
    std::vector<Monster *> monsterArray;

    // Big Boss
    sf::Texture bigBossTexture;
    sf::Texture bigBossTwoTexture;
    sf::Texture bigBossCollisionTexture;
    sf::Texture bigBossHurtTexture;
    bigBossTexture.loadFromFile(BIGBOSSIMAGE);
    bigBossTwoTexture.loadFromFile(BIGBOSSTWOIMAGE);
    bigBossCollisionTexture.loadFromFile(BIGBOSSCOLLISIONIMAGE);
    bigBossHurtTexture.loadFromFile(BIGBOSSHURTIMAGE);

	// Coins
	sf::RectangleShape coinArray[6];

	srand(time(0));
	sf::RectangleShape coin1(sf::Vector2f(40.0f, 40.0f));
	coinArray[0] = coin1;
	sf::RectangleShape coin2(sf::Vector2f(40.0f, 40.0f));
	coinArray[1] = coin2;
	sf::RectangleShape coin3(sf::Vector2f(40.0f, 40.0f));
	coinArray[2] = coin3;
	sf::RectangleShape coin4(sf::Vector2f(40.0f, 40.0f));
	coinArray[3] = coin4;
	sf::RectangleShape coin5(sf::Vector2f(40.0f, 40.0f));
	coinArray[4] = coin5;
	sf::RectangleShape coin6(sf::Vector2f(40.0f, 40.0f));
	coinArray[5] = coin6;

	sf::SoundBuffer buffer;
	sf::Texture coinTexture;

	if (!buffer.loadFromFile("1_Coins.wav")) {
		std::cout << "Error " << std::endl;
	}

	if (!coinTexture.loadFromFile("Coin1.png")) {
		std::cerr << "An error occured" << std::endl;
	}

	sf::Sound coinSound;

	//sound.setBuffer(buffer);
	Coins gameCoins(coinSound);
	for (int i = 0; i < 6; i++)
	{
		coinArray[i].setFillColor(sf::Color::Yellow);
		coinArray[i].setTexture(&coinTexture);
		coinArray[i].setPosition(getRandom(100, 1800), getRandom(100, 1500));
	}

	// Time management variables
	sf::Clock monsterSpawnClock;
	sf::Clock monsterSpeedClock;
	sf::Clock shieldDelayClock;
	sf::Clock shieldPopClock;

	// Bombs
    sf::Texture bombTexture;

    Bomb* bombPtr = nullptr;
    try { // throws error if file not opened
        if(!bombTexture.loadFromFile(BOMBIMAGE))
        {
            throw FileOpenException(BOMBIMAGE);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }

    // Explosion
    sf::Texture explosionTexture;
    try { // throws error if file not opened
        if(!explosionTexture.loadFromFile(EXPLOSIONIMAGE))
        {
            throw FileOpenException(EXPLOSIONIMAGE);
        }
    }
     catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    Explosion explosion(explosionTexture);
    sf::SoundBuffer explosionBuffer;
    try { // throws error if file not opened
        if(!explosionBuffer.loadFromFile(EXPLOSIONSOUND))
        {
            throw FileOpenException(EXPLOSIONSOUND);
        }
    }
     catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }

    sf::Sound explosionSound;

    explosionSound.setBuffer(explosionBuffer);

    //Border
    sf::Texture borderTexture;
    try { // throws error if file not opened
        if(!borderTexture.loadFromFile(BORDERIMAGE))
        {
            throw FileOpenException(BORDERIMAGE);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    p.setMask(borderTexture);

    bool explode = false;
    int count = 0;
    int bigBossCountdown = 0;

    //View a.k.a camera
    sf::View view;
    view.reset(sf::FloatRect(0, 0, SCREENWIDTH, SCREENHEIGHT));
    sf::Vector2f viewPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);

    // Create Big Boss
    Monster* bigBoss = new Monster(bigBossTexture, bigBossTwoTexture, bigBossCollisionTexture, borderTexture, 2*2100, 2*300, true);


    // Big Boss health bar
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(300, 15));
    rectangle.setFillColor(sf::Color::Magenta);
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(5);
    sf::Text bossTxt("Monster Health", font);
    bossTxt.setCharacterSize(30);
    bossTxt.setFillColor(sf::Color::Red);


    sf::Event event;
    while (Running)
    {
        // Time management
        sf::Time monsterSpawnTimer = monsterSpawnClock.getElapsedTime();
        sf::Time monsterSpeedTimer = monsterSpeedClock.getElapsedTime();
        sf::Time shieldDelayTimer = shieldDelayClock.getElapsedTime();
        sf::Time shieldPopTimer = shieldPopClock.getElapsedTime();

        bool attack = false;
        bool bombDrop = false;

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
						Score::score = p.getScore();
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

		if (!pause)
		{
			// Attack Mechanism
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				attack = true;
				p.incrementCurrentAttackTexture();
			}
			else
			{
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
			}

			//Bomb drop
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bombPtr == nullptr)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(App);
                if (mousePos.x > 0 && mousePos.y > 0)
                {
                    bombPtr = new Bomb(bombTexture);
                    bombPtr -> moveBombToStartPosition(static_cast<float>(mousePos.x + viewPosition.x - SCREENWIDTH / 2), static_cast<float>(mousePos.y + viewPosition.y - SCREENHEIGHT / 2), static_cast<float>(viewPosition.y - SCREENHEIGHT / 2));
                }
            }

            if (bombPtr)
            {
                if (!bombPtr->move())
                    {
                        bombDrop = true;
                }
            }

            // Shield Mechanism
			if (shieldDelayTimer.asSeconds() > 3)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					p.applyShield();
					shieldDelayClock.restart();
					shieldPopClock.restart();
				}
			}
			if (shieldPopTimer.asSeconds() > 2.8 && shieldPopTimer.asSeconds() < 2.9)
			{
				p.loseShield();
			}

			 // View following player algorithm
            if(p.getPosition().x > SCREENWIDTH / 2)
            {
                if (p.getPosition().x < 2700 - SCREENWIDTH / 2)
                    viewPosition.x = p.getPosition().x;
                else
                    viewPosition.x = 2700 - SCREENWIDTH / 2;
            }
            else
                viewPosition.x = SCREENWIDTH / 2;

            if(p.getPosition().y > SCREENHEIGHT / 2)
            {
                if (p.getPosition().y < 1800 - SCREENHEIGHT / 2)
                    viewPosition.y = p.getPosition().y;
                else
                    viewPosition.y = 1800 - SCREENHEIGHT / 2;
            }
            else
                viewPosition.y = SCREENHEIGHT / 2;

            view.setCenter(viewPosition);
            txt.setPosition(viewPosition.x - SCREENWIDTH / 2, viewPosition.y - SCREENHEIGHT / 2);
            bossTxt.setPosition(viewPosition.x - SCREENWIDTH / 2, viewPosition.y + SCREENHEIGHT / 2 - 50 );
            rectangle.setPosition(viewPosition.x - SCREENWIDTH / 2 + 400, viewPosition.y + SCREENHEIGHT / 2 - 30);

            App.setView(view);
			App.clear();
			App.draw(background);
			p.draw(App);
			if (bombPtr)
                bombPtr->draw(App);

             // Create new monster
			if (monsterSpawnTimer.asSeconds() > 8)
			{
				for (int i = 0; i < spawnCount; i++)
				{
					int randomNumber;
					randomNumber = rand() % 2;

					// Spawn from left side
					if (randomNumber == 0)
					{
						monsterArray.push_back(new Monster(monsterTexture, monsterTwoTexture, monsterCollisionTexture, borderTexture, 2*250, 2*(750+static_cast<float>(rand() % 1000))));
					}
					// Spawn from right side
					else if (randomNumber == 1)
					{
						 monsterArray.push_back(new Monster(monsterTexture, monsterTwoTexture, monsterCollisionTexture, borderTexture, 2*1200, 2*(800 + static_cast<float>(rand() % 1000))));
					}
				}
				monsterSpawnClock.restart();
			}

			int counter = 0;
			for (monsterIterator = monsterArray.begin(); monsterIterator != monsterArray.end(); monsterIterator++)
			{
				monsterArray[counter]->updateMovement(SCREENWIDTH, BG_HEIGHT);

				// If timer passes, increase monsters' speed and restart clock to 0
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
				if (attack == true)
				{
					if(p.attack(monsterArray[counter]->getPosition().x, monsterArray[counter]->getPosition().y, monsterArray[counter]->size()))
                    {
                        monsterArray[counter]->setAlive(false) ;
                        cout << "ATTACK" << endl;
                        break;
                    }
				}


                if(bombDrop == true)
                {
                    if(bombPtr->hitByMonster(monsterArray[counter]->getPosition().x, monsterArray[counter]->getPosition().y, monsterArray[counter]->size()))
                    {
                        monsterArray[counter]->setAlive(false) ;
                    }
                }

                if ((*monsterIterator)->getAlive())
                    monsterArray[counter]->draw(App);
                counter++;
            }
            monsterArray.erase(std::remove_if(monsterArray.begin(), monsterArray.end(), [](Monster *x) {return !x->getAlive(); }), monsterArray.end());

			// Coin generation
			for (int i = 0; i < 6; i++)
			{
				App.draw(coinArray[i]);
				if (p.collectCoin(coinArray[i].getPosition().x, coinArray[i].getPosition().y, 40, 40))
				{
					coinArray[i].setPosition(getRandom(100, 1800), getRandom(100, 1500));
					txt.setString(name + "                      " + "Score: " + to_string(p.getScore()) + "                     " + "Lives: " + to_string(p.getLives()));
					cout << p.getScore() << endl;
					if (p.getScore() % 15 == 0)
					{
						spawnCount++;
					}
				}
			}

        if(bombDrop == true)
        {
            explosionSound.play();
            explosion.startExplosion(bombPtr->getPosition());
            delete bombPtr;
            bombPtr = nullptr;
            bombDrop = false;
            explode = true;
        }

        if (explode)
        {
            explosion.draw(App);
            count++;
            if (count > 10)
            {
                explode = false;
                count = 0;
                explosionSound.stop();
            }

        }

        //Render big boss
        if (bigBoss != nullptr)
        {
            if (bigBossCountdown < 35)
                 bigBossCountdown++;
            if (bigBossCountdown > 10)
            {
                bigBoss->updateMovement(SCREENWIDTH, BG_HEIGHT);
                bigBoss->movementAnimation();
                bigBoss->increaseSpeed();
                bigBossCountdown = 0;
            }

            // Big boss collision detection
            if (attack == false)
            {
                if (p.hitByMonster(bigBoss->getPosition().x, bigBoss->getPosition().y, bigBoss->size()))
                {
                    if (p.getHit() == -1)
                    {
                        p.setHit(-20);
                        p.loseLife();
                        txt.setString(name + "                      " + "Score: " + to_string(p.getScore()) + "                     " + "Lives: " + to_string(p.getLives()));
                        bigBoss->collisionAnimation();
                    }
                }
                else
                {
                    if (p.getHit() == -20)
                        p.setHit(-1);
                }
            }

            if(attack == true)
            {
                if(p.attack(bigBoss->getPosition().x, bigBoss->getPosition().y, bigBoss->size()))
                {
                    if (p.getHit() == -1)
                    {
                        p.setHit(-20);
                        p.loseLife();
                        txt.setString(name + "                      " + "Score: " + to_string(p.getScore()) + "                     " + "Lives: " + to_string(p.getLives()));
                        rectangle.setSize(sf::Vector2f(rectangle.getSize().x - 100, 15));
                    }
                }
                else
                {
                    if (p.getHit() == -20)
                        p.setHit(-1);
                }
            }

            if (rectangle.getSize().x < 0)
            {
                rectangle.setFillColor(sf::Color::Transparent);
                rectangle.setOutlineColor(sf::Color::Transparent);
                App.draw(rectangle);
                delete bigBoss;
                bigBoss = nullptr;
            }
            else
            bigBoss->draw(App);
        }



			App.draw(txt);
			App.draw(bossTxt);
            if (rectangle.getSize().x >= 0)
                App.draw(rectangle);
			App.display();
		}

    }

    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* screen_3_h */
