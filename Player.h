//
//  Player.hpp
//  jscreens
//
//  Created by Mihika Marathe on 3/1/19.
//  Copyright © 2019 Mihika Marathe. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include <stdio.h>

using namespace std;

class Player : public Entity
{
private:
    int texture;
    int lives;
    bool shield;
    int score;
    sf::Texture textureone;
    sf::Texture texturetwo;
public:
    Player(sf::Texture& textone, sf::Texture& texttwo, float h, float w);
    void move(Direction d);
    void applyShield();
    void loseLife();
    int getLives();
    int getScore();
    bool getShield();
    ~Player();
};

#endif /* Player_hpp */
