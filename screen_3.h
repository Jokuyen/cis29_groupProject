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
const char* PLAYERAHURTSOUND = "bodyimpact_jack_01.wav";

// Monster assets
const char* MONSTERIMAGE = "monster.png";
const char* MONSTERTWOIMAGE = "monsterTwo.png";
const char* MONSTERCOLLISIONIMAGE = "monsterCollision.png";
const char* MONSTERSOUND = "cyborg_hurt.wav";

// BigBoss assets
const char* BIGBOSSIMAGE = "octopus.png";
const char* BIGBOSSTWOIMAGE = "octopus2.png";
const char* BIGBOSSCOLLISIONIMAGE = "octopusCollision.png";
const char* BIGBOSSHURTIMAGE = "octopusHurt.png";

//Bomb assets
const char* BOMBIMAGE = "missile.png";
const char* EXPLOSIONIMAGE = "explosion.png";
const char* EXPLOSIONSOUND = "BOOM.wav";

//Coin assets
const char* COIN_ONE= "coin1.png";
const char* COIN_TWO= "coin2.png";
const char* COIN_THREE= "coin3.png";
const char* COIN_FOUR= "coin4.png";
const char* COIN_FIVE= "coin5.png";
const char* COIN_SIX= "coin6.png";

//Border assets
const char* BORDERIMAGE = "wall8Mask.png";

namespace Score
{
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
    theme.setVolume(30);
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
    Player playerObj(playerTexture, shieldTexture, flippedPlayerTexture, flippedShieldTexture, SCREENWIDTH, BG_HEIGHT);
    playerObj.setPosition(200,1000);
    // player sound
    sf::SoundBuffer playerhurtBuffer;
    try { // throws error if file not opened
        if(!playerhurtBuffer.loadFromFile(PLAYERAHURTSOUND))
        {
            throw FileOpenException(PLAYERAHURTSOUND);
        }
    }
    catch(exception& e)
    {
        cout << "Cannot open: " << e.what() << endl;
        exit(-1);
    }
    sf::Sound playerhurtsound;
    playerhurtsound.setBuffer(playerhurtBuffer);
    playerhurtsound.setVolume(100);
    
    //background mask
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
    playerObj.setMask(borderTexture);
    sf::Image borderImage = borderTexture.copyToImage();
    
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
    
    // Header line
    string name = "Gold Rush";
    sf::Text txt(name + "\t\t\t\tScore: " + to_string(playerObj.getScore()) + "\t\t\t\tLives: " + to_string(playerObj.getLives()), font);
    txt.setCharacterSize(25);
    txt.setFillColor(sf::Color::White);
    
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
    explosionSound.setVolume(100);
    
    // Monster
    sf::Texture monsterTexture;
    sf::Texture monsterTwoTexture;
    sf::Texture monsterCollisionTexture;
    monsterTexture.loadFromFile(MONSTERIMAGE);
    monsterTwoTexture.loadFromFile(MONSTERTWOIMAGE);
    monsterCollisionTexture.loadFromFile(MONSTERCOLLISIONIMAGE);
    float speedNumber = 0.5;
    
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
    
    Monster* bigBoss = new Monster(bigBossTexture, bigBossTwoTexture, bigBossCollisionTexture, borderImage, 2 * 2100, 2 * 300, true);
    
    // Monster sound
    /*
     sf::SoundBuffer monstersoundBuffer;
     try { // throws error if file not opened
     if(!monstersoundBuffer.loadFromFile(MONSTERSOUND))
     {
     throw FileOpenException(MONSTERSOUND);
     }
     }
     catch(exception& e)
     {
     cout << "Cannot open: " << e.what() << endl;
     exit(-1);
     }
     */
    
    //sf::Sound monstersoundd;
    
    //monstersoundd.setBuffer(monstersoundBuffer);
    //monstersoundd.setVolume(100);
    
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
    
    sf::SoundBuffer buffer;
    
    for(int i = 0; i < 6; i++)
    {
        Coins * coinPtr = new Coins(cOne, cTwo, cThree, cFour, cFive, cSix, borderTexture,  BG_HEIGHT, SCREENWIDTH);
        coinArray.push_back(coinPtr);
    }
    
    // Time management variables
    sf::Clock monsterSpawnClock;
    sf::Clock monsterSpeedClock;
    sf::Clock shieldDelayClock;
    sf::Clock shieldPopClock;
    
    
    //Border
    
    bool explode = false;
    int count = 0;
    int bigBossCountdown = 0;
    
    //View a.k.a camera
    sf::View view;
    view.reset(sf::FloatRect(0, 0, SCREENWIDTH, SCREENHEIGHT));
    sf::Vector2f viewPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);
    
    // Create Big Boss
    
    
    
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
                    case sf::Keyboard::Q: // Back to menu
						App.setView(App.getDefaultView());
                        return (7);
                        break;
                    case sf::Keyboard::Space:
                        pause = !pause;
                        break;
                    case sf::Keyboard::R:
                        testmode = false;
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
                playerObj.incrementCurrentAttackTexture();
				playerObj.attackAnimation();
            }
            else
            {
                // Player movement
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    playerObj.move(Player::Left);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    playerObj.move(Player::Right);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    playerObj.move(Player::Up);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    playerObj.move(Player::Down);
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
                    playerObj.applyShield();
                    shieldDelayClock.restart();
                    shieldPopClock.restart();
                }
            }
            if (shieldPopTimer.asSeconds() > 2.8 && shieldPopTimer.asSeconds() < 2.9)
            {
                playerObj.loseShield();
            }
            
            // View following player algorithm
            if(playerObj.getPosition().x > SCREENWIDTH / 2)
            {
                if (playerObj.getPosition().x < 2700 - SCREENWIDTH / 2)
                    viewPosition.x = playerObj.getPosition().x;
                else
                    viewPosition.x = 2700 - SCREENWIDTH / 2;
            }
            else
                viewPosition.x = SCREENWIDTH / 2;
            
            if(playerObj.getPosition().y > SCREENHEIGHT / 2)
            {
                if (playerObj.getPosition().y < 1800 - SCREENHEIGHT / 2)
                    viewPosition.y = playerObj.getPosition().y;
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
            playerObj.draw(App);
            if (bombPtr)
                bombPtr->draw(App);
            
            // Create new monster
            if (monsterSpawnTimer.asSeconds() > 5)
            {
                monsterArray.push_back(new Monster(monsterTexture, monsterTwoTexture, monsterCollisionTexture, borderImage, 2 * 250, 2 * 1700));
                monsterSpawnClock.restart();
            }
            
            int counter = 0;
            for (monsterIterator = monsterArray.begin(); monsterIterator != monsterArray.end(); monsterIterator++)
            {
                monsterArray[counter]->updateMovement(SCREENWIDTH, BG_HEIGHT);
                
                // If timer passes, increase monsters' speed and restart clock to 0
                if (monsterSpeedTimer.asSeconds() > 5)
                {
                    monsterArray[counter]->movementAnimation();
                    monsterArray[counter]->increaseSpeed(speedNumber);
                    monsterSpeedClock.restart();
                }
                
                //                // Sound of the monster
                //                sf::Sound explosionTexture;
                //                try { // throws error if file not opened
                //                    if(!explosionTexture.loadFromFile(MONSTERSOUND))
                //                    {
                //                        throw FileOpenException(EXPLOSIONIMAGE);
                //                    }
                //                }
                //                catch(exception& e)
                //                {
                //                    cout << "Cannot open: " << e.what() << endl;
                //                    exit(-1);
                //                }
                
                // Collision detection
                if (playerObj.hitByMonster(monsterArray[counter]->getPosition().x, monsterArray[counter]->getPosition().y, monsterArray[counter]->size()))
                {
                    //monstersoundd.play();
                    if (playerObj.getHit() == -1) {
                        std::cout << "Player hit by Monster" << std::endl;
                        playerObj.setHit(counter);
                        if(testmode == false)
                            playerObj.loseLife();
                        txt.setString(name + "\t\t\t\tScore: " + to_string(playerObj.getScore()) + "\t\t\t\tLives: " + to_string(playerObj.getLives()));
                        monsterArray[counter]->collisionAnimation();
                    }
                }
                else
                {
                    if (playerObj.getHit() == counter)
                        playerObj.setHit(-1);
                }
                if (attack == true)
                {
                    if(playerObj.attack(monsterArray[counter]->getPosition().x, monsterArray[counter]->getPosition().y, monsterArray[counter]->size()))
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
                coinArray[i]->draw(App);
                coinArray[i]->animate();
                //App.draw(coinArray[i]);
                if (playerObj.collectCoin(coinArray[i]->getPosition().x, coinArray[i]->getPosition().y, coinArray[i]->size().x, coinArray[i]->size().y))
                {
                    coinArray[i]->collide();
                    txt.setString(name + "\t\t\t\tScore: " + to_string(playerObj.getScore()) + "\t\t\t\tLives: " + to_string(playerObj.getLives()));
                    if (playerObj.getScore() % 10 == 0)
                    {
                        speedNumber += 0.25;
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
                    bigBoss->increaseSpeed(speedNumber);
                    bigBossCountdown = 0;
                }
                
                // Big boss collision detection
                if (attack == false)
                {
                    if (playerObj.hitByMonster(bigBoss->getPosition().x, bigBoss->getPosition().y, bigBoss->size()))
                    {
                        if (playerObj.getHit() == -1)
                        {
                            playerObj.setHit(-20);
                            if(testmode == false)
                                playerObj.loseLife();
                            txt.setString(name + "\t\t\t\tScore: " + to_string(playerObj.getScore()) + "\t\t\t\tLives: " + to_string(playerObj.getLives()));
                            bigBoss->collisionAnimation();
                        }
                    }
                    else
                    {
                        if (playerObj.getHit() == -20)
                            playerObj.setHit(-1);
                    }
                }
                
                if(attack == true)
                {
                    playerhurtsound.play();
                    if(playerObj.attack(bigBoss->getPosition().x, bigBoss->getPosition().y, bigBoss->size()))
                    {
                        if (playerObj.getHit() == -1)
                        {
                            playerObj.setHit(-20);
                            if(testmode == false)
                                playerObj.loseLife();
                            txt.setString(name + "\t\t\t\tScore: " + to_string(playerObj.getScore()) + "\t\t\t\tLives: " + to_string(playerObj.getLives()));
                            rectangle.setSize(sf::Vector2f(rectangle.getSize().x - 100, 15));
                        }
                    }
                    else
                    {
                        if (playerObj.getHit() == -20)
                            playerObj.setHit(-1);
                    }
                }
                
                if (rectangle.getSize().x < 0)
                {
                    rectangle.setFillColor(sf::Color::Transparent);
                    rectangle.setOutlineColor(sf::Color::Transparent);
                    App.draw(rectangle);
                    delete bigBoss;
                    bigBoss = nullptr;
                    if(testmode == false)
                        playerObj.increaseLife();
                }
                else
                    bigBoss->draw(App);

				App.draw(bossTxt);
				if (rectangle.getSize().x >= 0)
					App.draw(rectangle);
            }
            
            if (playerObj.getLives() == 0 && testmode == false)
            {
                App.setView(App.getDefaultView());
                Score::score = playerObj.getScore();
                return (4);
            }
            
            
            //coinArray[0].draw(App);
            App.draw(txt);
            App.display();
        }
        
    }
    
    // Never reach this point normally, but just in case, exit the application
    return (-1);
}

#endif /* screen_3_h */
