//  monster.h
//  Created by Johnny Nguyen on 02-16-19.

#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

class Monster : public Entity
{
public:
    // Constructor
    Monster(sf::Texture& monsterTexture, const int SCREENWIDTH, const int BG_HEIGHT);
    ~Monster();
    
    // Monster stats
    bool alive = true;
    int direction = 0; // 0 = Up, 1 = Down, 2 = Left, 3 = Right
    double movementSpeed = 2;
    int movementCounter = 0;
    int movementLength = 30;
    
    // Functions
    int randomNumber(int max);
    void increaseSpeed() { if (movementSpeed < 15) movementSpeed += 0.5; }
    void updateMovement(const int SCREENWIDTH, const int BG_HEIGHT);
};

#endif // MONSTER_H
