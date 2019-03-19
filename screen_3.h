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
#include <iostream>
#include <string>

using namespace std;

const char* BACKGROUNDIMAGE = "grass.png";
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

//Coin assets
const char* COIN_ONE= "coin1.png";
const char* COIN_TWO= "coin2.png";
const char* COIN_THREE= "coin3.png";
const char* COIN_FOUR= "coin4.png";
const char* COIN_FIVE= "coin5.png";
const char* COIN_SIX= "coin6.png";

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
    
    
    
    // Header line
    string name = "Gold Rush";
    sf::Text txt("", font);
    //sf::Text txt(name + "\t\t\t\t\t\tScore: " + to_string(p.getScore()) + "\t\t\t\t\t\tLives: " + to_string(p.getLives()), font);
    txt.setCharacterSize(40);
    txt.setFillColor(sf::Color::White);
    ostringstream sout;
    sout << p;
    cout << p << endl;
    txt.setString(name + sout.str());
    
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
    //cin >> Score::score;
    Score::score = 1; /////////////////////////////////////////////TEMPORARY
    
    // Coins
    std::vector<Coins*> coinArray;
    //Coins coinArray[6];
    
    sf::Texture cOne;
    cOne.loadFromFile(COIN_ONE);
    sf::Texture cTwo;
    cTwo.loadFromFile(COIN_TWO);
    sf::Texture cThree;
    cThree.loadFromFile(COIN_THREE);
    sf::Texture cFour;
    cFour.loadFromFile(COIN_FOUR);
    sf::Texture cFive;
    cFive.loadFromFile(COIN_FIVE);
    sf::Texture cSix;
    cSix.loadFromFile(COIN_SIX);

    srand(time(0));
    //sf::RenderWindow window(sf::VideoMode(2000, 2000), "Welcome!", sf::Style::Close | sf::Style::Default);
    for(int i = 0; i < 6; i++)
    {
        Coins * coinPtr = new Coins(cOne, cTwo, cThree, cFour, cFive, cSix, BG_HEIGHT, SCREENWIDTH);
        coinArray.push_back(coinPtr);
    }
    //    sf::RectangleShape coinss;
    //    coinss.setScale(100.f, 100.f);
    
    //sf::Sound coinSound;
    
    //sound.setBuffer(buffer);
    //Coins gameCoins(coinSound);
    
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
        
        if (!pause)
        {
            // Attack Mechanism
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                attack = true;
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
            
            // Shield Mechanism
            if (shieldDelayTimer.asSeconds() > 4)
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
            App.draw(background);
            p.draw(App);
            
            // Create new monster
            if (monsterSpawnTimer.asSeconds() > 3)
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
                
                // If timer passes, increase monsters' speed and restart clock to 0
                if (monsterSpeedTimer.asSeconds() > 1)
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
                    if (p.attack(monsterArray[counter]->getPosition().x, monsterArray[counter]->getPosition().y, monsterArray[counter]->size()))
                    {
                        monsterArray[counter]->setAlive(false);
                        //monsterArray.erase(monsterIterator);
                        cout << "ATTACK" << endl;
                    }
                    if (monsterArray[counter]->getAlive() == false)
                    {
                        monsterArray.erase(monsterIterator);
                        break;
                    }
                    
                }
                monsterArray[counter]->draw(App);
                counter++;
            }
            
            // Coin generation
            for (int i = 0; i < 6; i++)
            {
                coinArray[i]->draw(App);
                coinArray[i]->animate();
                //App.draw(coinArray[i]);
                if (p.collectCoin(coinArray[i]->getPosition().x, coinArray[i]->getPosition().y, coinArray[i]->size().x, coinArray[i]->size().y))
                {
                    coinArray[i]->collide();
                    txt.setString(name + "\t\t\t\tScore: " + to_string(p.getScore()) + "\t\t\t\tLives: " + to_string(p.getLives()));
                    cout << p.getScore() << endl;
                    /*
                    if (p.getScore() % 15 == 0)
                    {
                        spawnCount++;
                    }
                     */
                }
            }
            
            
            App.draw(txt);
            App.display();
        }
        
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* screen_3_h */
