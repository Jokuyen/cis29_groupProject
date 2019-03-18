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
#include <iostream>
#include <string>
#include "Bomb.h"
#include "Explosion.h"
#include "Border.h"

using namespace std;

const char* BACKGROUNDIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/wall8.png";
const char* THEMEMUSIC = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/American Beauty.wav";


// Player assets
const char* PLAYERIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/catSpriteSheet.png";
const char* SHIELDIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/catSpriteSheetTwo.png";
const char* FLIPPEDPLAYERIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/flippedCatSpriteSheet.png";
const char* FLIPPEDSHIELDIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/flippedCatSpriteSheetTwo.png";

// Monster assets
const char* MONSTERIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/monster.png";
const char* MONSTERTWOIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/monsterTwo.png";
const char* MONSTERCOLLISIONIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/monsterCollision.png";

// BigBoss assets
const char* BIGBOSSIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/playertempone.png";
const char* BIGBOSSTWOIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/playertemptwo.png";
const char* BIGBOSSCOLLISIONIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/monsterCollision.png";

//Bomb assets
//const char* BOMBIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/bombs.png";
const char* BOMBIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/missile.png";
const char* EXPLOSIONIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/explosion.png";
const char* EXPLOSIONSOUND = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/explosion.wav";

//Border assets
const char* BORDERIMAGE = "/Users/feliciadewanaga/Documents/computer_sci_books/C++/Adv/GoldRushGame/wall8Mask.png";

class screen_3 : public cScreen
{
public:
    screen_3(void) { }
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT);
};

int screen_3::Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT)
{
    bool Running = true;

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
    sf::RectangleShape background(sf::Vector2f( 2700, 1800));
    //background.setPosition(sf::Vector2f(0, 50));
    background.setPosition(sf::Vector2f(0, 0));
    sf::Texture backgroundTexture;
    try { // throws error if file not openedi
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

       // Big Boss
    sf::Texture bigBossTexture;
    sf::Texture bigBossTwoTexture;
    sf::Texture bigBossCollisionTexture;
    bigBossTexture.loadFromFile(BIGBOSSIMAGE);
    bigBossTwoTexture.loadFromFile(BIGBOSSTWOIMAGE);
    bigBossCollisionTexture.loadFromFile(BIGBOSSCOLLISIONIMAGE);

    // Monster Vector Array
    std::vector<Monster *>::const_iterator monsterIterator;
    std::vector<Monster *> monsterArray;


    // Time management variables
    sf::Clock monsterSpawnClock;
    sf::Clock monsterSpeedClock;
    sf::Clock shieldDelayClock;
    sf::Clock shieldPopClock;
    sf::Clock bigBossSpawnClock;


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
    //explosionBuffer.loadFromFile("../explosion.wav");
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
    //Border borderUpperLeft(borderUpperLeftTexture, 0, 0);

    bool explode = false;
    int count = 0;
    int bigBossCountdown = 0;

    //View a.k.a camera
    sf::View view;
    view.reset(sf::FloatRect(0, 0, SCREENWIDTH, SCREENHEIGHT));
    //view.setViewport(sf::FloatRect(0, 0, 0.5f, 0.5f));
    sf::Vector2f viewPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);

    // Create Big Boss
    Monster bigBoss(bigBossTexture, bigBossTwoTexture, bigBossCollisionTexture, borderTexture, 2*2100, 2*300);



    sf::Event event;
    while (Running)
    {
        // Time management
        sf::Time monsterSpawnTimer = monsterSpawnClock.getElapsedTime();
        sf::Time monsterSpeedTimer = monsterSpeedClock.getElapsedTime();
        sf::Time shieldDelayTimer = shieldDelayClock.getElapsedTime();
        sf::Time shieldPopTimer = shieldPopClock.getElapsedTime();
        sf::Time bigBossSpawnTimer = bigBossSpawnClock.getElapsedTime();

        bool attack = false;
        bool bombDrop = false;
       // bool explode = false;
        //int count = 0;

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
            //if (!p.hitByMonster(borderUpperLeft.getPosition().x, borderUpperLeft.getPosition().y, borderUpperLeft.size()))
            p.move(Player::Left);
            //txt.setPosition(txt.getPosition().x - 10.0f, txt.getPosition().y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            //if (!p.hitByMonster(borderUpperLeft.getPosition().x, borderUpperLeft.getPosition().y, borderUpperLeft.size()))
            p.move(Player::Right);
           // txt.setPosition(txt.getPosition().x + 10.0f, txt.getPosition().y);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            //if (!p.hitByMonster(borderUpperLeft.getPosition().x, borderUpperLeft.getPosition().y, borderUpperLeft.size()))
            p.move(Player::Up);
            //txt.setPosition(txt.getPosition().x, txt.getPosition().y - 10.0f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            //if (!p.hitByMonster(borderUpperLeft.getPosition().x, borderUpperLeft.getPosition().y, borderUpperLeft.size()))
            p.move(Player::Down);
           // txt.setPosition(txt.getPosition().x, txt.getPosition().y + 10.0f);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && bombPtr == nullptr)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(App);
            cout << "x:" << mousePos.x << ", y:" << mousePos.y << endl;
            //p.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            if (mousePos.x > 0 && mousePos.y > 0) {
            bombPtr = new Bomb(bombTexture);
            //App.draw(*bombPtr);
            bombPtr -> moveBombToStartPosition(sf::Vector2f(static_cast<float>(mousePos.x + viewPosition.x - SCREENWIDTH / 2), static_cast<float>(mousePos.y + viewPosition.y - SCREENHEIGHT / 2)));
            }
        }
        if (bombPtr)
                {
                    if (!bombPtr->move())
                    {
                        //bombSound.stop();
                        //delete bombPtr;
                        //bombPtr = nullptr;
                        bombDrop = true;
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

        // Attack Mechanism
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            attack = true;
        }


        if(p.getPosition().x > SCREENWIDTH / 2)
            if (p.getPosition().x < 2700 - SCREENWIDTH / 2)
               viewPosition.x = p.getPosition().x;
             else
               viewPosition.x = 2700 - SCREENWIDTH / 2;
        else
            viewPosition.x = SCREENWIDTH / 2;

        if(p.getPosition().y > SCREENHEIGHT / 2)
            if (p.getPosition().y < 1800 - SCREENHEIGHT / 2)
               viewPosition.y = p.getPosition().y;
            else
               viewPosition.y = 1800 - SCREENHEIGHT / 2;
        else
            viewPosition.y = SCREENHEIGHT / 2;

        view.setCenter(viewPosition);
        txt.setPosition(viewPosition.x - SCREENWIDTH / 2, viewPosition.y - SCREENHEIGHT / 2);

        App.setView(view);
        App.clear();
        App.draw(background);
       // borderUpperLeft.draw(App);

        p.draw(App);
        if (bombPtr)
            bombPtr->draw(App);

        //bombPtr->draw(App);

        // Create new monster
        if (monsterSpawnTimer.asSeconds() > 3.2)
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


            if(attack == true)
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

            }                    //monsterArray.erase(monsterIterator);

            if ((*monsterIterator)->getAlive())
                monsterArray[counter]->draw(App);
            counter++;
        }
        monsterArray.erase(std::remove_if(monsterArray.begin(), monsterArray.end(), [](Monster *x) {
        return !x->getAlive(); }), monsterArray.end());
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
            {explode = false;
            count = 0;
             explosionSound.stop();
            }
            /*
             if (explosionTimer.asSeconds() > 2)
             {
                 cout << "explosionTimer: " << explosionTimer.asSeconds() << endl;
                 explode = false;
                 explosionClock.restart();
             }*/


        }
        //Render big boss

        if (bigBossCountdown < 35)
        bigBossCountdown++;
        /*
        if (bigBossCountdown == 10)
             {
                 cout << "big Boss1" << endl;

cout << "big Boss" << endl;
                bigBoss.updateMovement(SCREENWIDTH, BG_HEIGHT);
             }
             */
              if (bigBossCountdown > 10)
            {
                bigBoss.updateMovement(SCREENWIDTH, BG_HEIGHT);
                bigBoss.movementAnimation();
                bigBoss.increaseSpeed();
                bigBossCountdown = 0;
            }
            bigBoss.draw(App);
        App.draw(txt);
        App.display();
    }

    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* screen_3_h */
