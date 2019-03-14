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
private:
    // Textures
    sf::Texture movementOneTexture;
    sf::Texture collisionTexture;
    
    bool alive = true;
    int direction = 0; // 0 = Up, 1 = Down, 2 = Left, 3 = Right
    float movementSpeed = 2;
    int movementCounter = 0;
    int movementLength = 55;
    
public:
    // Constructor
    Monster(sf::Texture& monsterTexture, sf::Texture& monsterCollisionTexture, float SCREENWIDTH, float BG_HEIGHT);
    ~Monster();
    
    // Animations
    void movementAnimation() { sprite.setTexture(movementOneTexture); }
    void collisionAnimation() { sprite.setTexture(collisionTexture); }
    
    
    // Functions
    int randomNumber(int max);
    bool getAlive();
    void setAlive(bool a);
    void increaseSpeed() { if (movementSpeed < 15) movementSpeed += 0.5; }
    void updateMovement(const int SCREENWIDTH, const int BG_HEIGHT);
};

#endif // MONSTER_H
