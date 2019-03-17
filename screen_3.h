//
//  screen_3.h
//  jscreens
//
//  Created by Mihika Marathe, Felicia Dewanaga, Johnny Nguyen, Manxin Zhang, Alan Rodriguez.
//  Copyright © 2019 Mihika Marathe, Felicia Dewanaga, Johnny Nguyen, Manxin Zhang, Alan Rodriguez.
//  All rights reserved.
//

#ifndef SCREEN_3_H
#define SCREEN_3_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Monster.h"
#include "Player.h"
#include "Coins.h"
#include <iostream>
#include <string>
#include "test.h"
#include "map.h"
using namespace std;

const char* BACKGROUNDIMAGE = "grass.png";

// Monster assets
const char* MONSTERIMAGE = "monster.png";
const char* MONSTERTWOIMAGE = "monsterTwo.png";
const char* MONSTERCOLLISIONIMAGE = "monsterCollision.png";

// Player assets
const char* PLAYERIMAGEONE = "adventurer-run-00.png";
const char* PLAYERIMAGETWO = "adventurer-run-02.png";
const char* SHIELDIMAGE = "adventurer-smrslt-02.png";

// Coin assets
const char* CoinSound = "1_Coins.wav";

double getRandom(int lower, int upper) {
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
    ///
    /// TILE MAP
    ///
    
    //sf::RenderWindow window(sf::VideoMode(2000, 2000), "Tilemap");
    
    const int level[] = {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
        
    };
    
    TileMap map;
    
    if (!map.load("Pico_RPG_Forest_Tileset_Preview.png", sf::Vector2u(200, 200), level, 16, 8)) {
        return -1;
    }
    
    
    
    
    
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

    //bool pause = false;

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
    
    cout << "last iteration\n";
    
    simple mysimple(89);
    
    mysimple.displayData();
    
    Player p(playerTextureOne, playerTextureTwo, shieldTexture, SCREENWIDTH, BG_HEIGHT);
    


    // Header line
    string name = "Name";
    sf::Text txt(name + " " + "Score: " + to_string(p.getScore()) + " " + "Lives:" + to_string(p.getLives()), font);
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
    
    ///
    /// Alan's Portion
    ///
    
    srand(time(0));
    //sf::RenderWindow window(sf::VideoMode(2000, 2000), "Welcome!", sf::Style::Close | sf::Style::Default);
    sf::RectangleShape coinss(sf::Vector2f(30.0f, 30.0f));
    sf::RectangleShape coinss2(sf::Vector2f(30.0f, 30.0f));
    sf::RectangleShape coinss3(sf::Vector2f(30.0f, 30.0f));
    
    sf::Sprite myArray[10];
    
    for (int i = 0; i < 10; i++) {
        myArray[i].setScale(3.0f, 3.0f);
    }
    
    for (int i = 0; i < 10; i++) {
        myArray[i].setPosition(getRandom(0, 2000), getRandom(0, 2000));
    }
    
    
    
    //    sf::RectangleShape coinss;
    //    coinss.setScale(100.f, 100.f);
    
    coinss.setPosition(getRandom(100, 1800), getRandom(100, 1800));
    coinss2.setPosition(getRandom(100, 1800), getRandom(100, 1800));
    coinss3.setPosition(getRandom(100, 1800), getRandom(100, 1800));
    sf::SoundBuffer buffer;
    sf::Texture texture;
    
    if (!buffer.loadFromFile("1_Coins.wav")) {
        std::cout << "Error " << std:: endl;
    }
    
    if (!texture.loadFromFile("Coin1.png")) {
        std::cerr << "An eror oucred" << std::endl;
    }
    
    sf::Sound sound;
    
    sound.setBuffer(buffer);
    Coins gameCoins(sound);
    
    coinss.setFillColor(sf::Color::Yellow);
    coinss2.setFillColor(sf::Color::Yellow);
    coinss3.setFillColor(sf::Color::Yellow);
    
    coinss.setTexture(&texture);
    coinss2.setTexture(&texture);
    coinss3.setTexture(&texture);

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
            
            /////// Collision with coin
            
            cout << "playerX: " << p.getPosition().x << endl;
            cout << "CoinsX: " << coinss.getPosition().x << endl << endl;
            
            if (p.getPosition().x == coinss.getPosition().x | p.getPosition().y == coinss.getPosition().y) {
                p.incrementScore();
            }
            
            monsterArray[counter]->draw(App);
            counter++;
        }
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(App);
            coinss.setPosition( static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
            coinss2.setPosition( static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
            coinss3.setPosition( static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
            gameCoins.playsound();
            
        }

        
        
        App.draw(coinss);
        App.draw(coinss2);
        App.draw(coinss3);
        
        App.draw(myArray[0]);
        App.draw(myArray[1]);
        App.draw(myArray[2]);
        App.draw(myArray[3]);
        App.draw(myArray[4]);
        App.draw(myArray[5]);
        App.draw(txt);
        
        
        App.display();
    }

    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* screen_3_h */

