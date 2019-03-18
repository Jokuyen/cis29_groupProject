//
//  Player.hpp
//  jscreens
//
//  Created by Mihika Marathe on 3/1/19 and Felicia Dewanaga on 3/7/19.
//  Copyright © 2019 Mihika Marathe and Felicia Dewanaga on 3/7/19. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>


#include "Entity.h"
//#include "Monster.h"

using namespace std;

class Player : public Entity
{
private:
    int lives;
    bool shield;
    int score;
    int hit;

    // Textures
    int currentTexture;
    sf::Texture texture;
    sf::Texture shieldTexture;
    sf::Texture flippedTexture;
    sf::Texture flippedShieldTexture;
    Direction dir;

public:
    Player(sf::Texture& inputTexture, sf::Texture& inputShieldTexture, sf::Texture& inputFlippedTexture, sf::Texture& inputFlippedShieldTexture, float h, float w);
    void move(Direction d);
    void applyShield();
    void loseShield();
    void loseLife();
    int getLives();
    int getScore();
    bool getShield();
    void setHit(int h) { hit = h; };
    int getHit() const { return hit; };
    bool attack(float monster_x, float monster_y,  sf::Vector2f monster_size);
    double getDistance(float monster_x, float monster_y,  sf::Vector2f monster_size);

    ~Player();
    bool hitByMonster(float monster_x, float monster_y,  sf::Vector2f monster_size/*, bool debug*/);
    void setPosition(float x, float y);
    void setMask(sf::Texture& maskTexture);
};

#endif /* Player_hpp */

