//
//  Player.hpp
//  jscreens
//
//  Created by Mihika Marathe on 3/1/19 and Felicia Dewanaga on 3/7/19.
//  Copyright © 2019 Mihika Marathe and Felicia Dewanaga on 3/7/19. All rights reserved.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>


#include "Entity.h"
//#include "Monster.h"

using namespace std;

class Player : public Entity
{
private:
    int texture;
    int lives;
    bool shield;
    int score;
    int hit;
    sf::Texture textureone;
    sf::Texture texturetwo;
    sf::Texture shieldtexture;
    
public:
    Player(sf::Texture& textone, sf::Texture& texttwo, sf::Texture& stexture, float h, float w) ;
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
    
    bool touchCoins() { score++;}
    void incrementScore() {score++;}
    
    ~Player();
    bool hitByMonster(float monster_x, float monster_y,  sf::Vector2f monster_size/*, bool debug*/);
    
    
};

#endif /* Player_hpp */



