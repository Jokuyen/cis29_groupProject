//
//  Monster.cpp
//  jscreens
//
//  Created by Johnny Nguyen on 02/16/19 and Felicia Dewanaga on 3/8/19.
//  Copyright � 2019 Johnny Nguyen and Felicia Dewanaga on 3/8/19. All rights reserved.
//

#include "Monster.h"

/*
 Description: This is the constructor for the monster, it sets the movement texture, the collision texture, and the origin. It also calls the constructor of the parent class, Entity, to set the original texture and the starting position.
 */

Monster::Monster(sf::Texture& monsterTexture, sf::Texture& monsterTwoTexture, sf::Texture& monsterCollisionTexture, float SCREENWIDTH, float BG_HEIGHT): Entity(monsterTexture, SCREENWIDTH, BG_HEIGHT)
{
    movementOneTexture = monsterTexture;
    movementTwoTexture = monsterTwoTexture;
    collisionTexture = monsterCollisionTexture;
    sprite.setOrigin(sprite.getLocalBounds().width / 2.0f, sprite.getLocalBounds().height / 2.0f);
}

/*
 Description: This method updates the sprite with a new texture
 */
void Monster::movementAnimation()
{
    if (sprite.getTexture() == &movementOneTexture)
    {
        sprite.setTexture(movementTwoTexture);
    }
    else
    {
        sprite.setTexture(movementOneTexture);
    }
}

/*
 Description: This method handles the movement of the monster. It uses a random number calculator to determine the direction and moves by the set speed. There are statements in place to make sure a monster does not move out of the boundaries and reacts correctly.
 Parameters: width of the screen, height of the screen
 */
void Monster::updateMovement(const int SCREENWIDTH, const int BG_HEIGHT)
{
    if (direction == 0) // Up
    {
        sprite.move(0, -movementSpeed);
    }
    else if (direction == 1) // Down
    {
        sprite.move(0, movementSpeed);
    }
    else if (direction == 2) // Left
    {
        sprite.move(-movementSpeed, 0);
    }
    else if (direction == 3) // Right
    {
        sprite.move(movementSpeed, 0);
    }
    else
    {
        // No movement
    }
    
    // Prevent monsters from leaving the window
    if (sprite.getPosition().y < 85) // Hitting top wall
    {
        direction = 1;
    }
    else if (sprite.getPosition().y > BG_HEIGHT + 15) // Hitting bottom wall
    {
        direction = 0;
    }
    else if (sprite.getPosition().x < 35) // Hitting left wall
    {
        direction = 3;
    }
    else if (sprite.getPosition().x > SCREENWIDTH - 20) // Hitting right wall
    {
        direction = 2;
    }
    
    movementCounter++;
    
    if (movementCounter >= movementLength)
    {
        /* If randomNumber(5), and since we only have 4 numbers for direction,
         there will be a 4/5 chance that the monster will move. */
        direction = randomNumber(6);
        movementCounter = 0;
    }
}

/*
 Description: This method returns a random number from 0 to max.
 Paramaters: integer max
 Return: integer generated
 */
int Monster::randomNumber(int max)
{
    
    int randomNumber;
    randomNumber = rand() % (max + 1);
    return randomNumber;
}

/*
 Description: This method returns the value of the alive member.
 Return: boolean alive
 */
bool Monster::getAlive()
{
    return alive;
}

/*
 Description: This function sets the member alive to the passed value.
 Parameter: bool to set alive to
 */
void Monster::setAlive(bool a)
{
    alive = a;
}

Monster::~Monster() {};

