//
//  Player.cpp
//  jscreens
//
//  Created by Mihika Marathe on 3/1/19 and Felicia Dewanaga on 3/7/19.
//  Copyright © 2019 Mihika Marathe and Felicia Dewanaga on 3/7/19. All rights reserved.
//

#include "Player.h"
#include <cmath>

/*
 Description: This is the constructor for the player. It sets the textures for the animation, the shield texture, sets the number of lives, the score, the status of the shield, the origin, and number of hits.
 Parameters: RenderWindow object on which to draw the sprite.
 
 */
Player::Player(sf::Texture& textone, sf::Texture& texttwo, sf::Texture& stexture, float h, float w): Entity(textone, w, h)
{
    textureone = textone;
    texturetwo = texttwo;
    shieldtexture = stexture;
    texture = 1;
    lives = 20;
    score = 0;
    shield = false;
    sprite.setOrigin(sprite.getLocalBounds().width/2.0f,sprite.getLocalBounds().height / 2.0f);
    hit = -1;
}


/*
 Description: This function handles the movement of the player. It changes the texture each move to animate the player. It moves the player 10.0f in the direction entered. There are statements in place to handle the boundaries of the screen.
 Parameters: Direction to move the sprite.
 
 */
void Player::move(Direction d)
{
    if(shield == false)
    {
        if(texture == 1)
        {
            sprite.setTexture(texturetwo);
            texture = 2;
        }
        else
        {
            sprite.setTexture(textureone);
            texture = 1;
        }
    }
    switch (d)
    {
        case Up:
            if (sprite.getPosition().y < 80.0f)
                break;
            else
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 10.0f);
            break;
        case Down:
            if (sprite.getPosition().y > BACKGROUNDSIZE.y)
                break;
            else
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 10.0f);
            break;
        case Left:
            if (sprite.getPosition().x < size().x/2)
                break;
            else
                sprite.setPosition(sprite.getPosition().x - 10.0f,sprite.getPosition().y);
            break;
        case Right:
            if (sprite.getPosition().x > BACKGROUNDSIZE.x-size().x/2)
                break;
            else
                sprite.setPosition(sprite.getPosition().x + 10.0f, sprite.getPosition().y);
            break;
        default:
            ;
    };
    //shield = false;
    
}

/*
 Description: This function changes the status of the shield to true and sets the shield texture.
 
 */
void Player::applyShield()
{
    shield = true;
    sprite.setTexture(shieldtexture);
    cout << "shieldAPP" << endl;
}

/*
 Description: This function disables the shield(sets to false) and sets the texture back to regular.
 
 */
void Player::loseShield()
{
    shield = false;
    sprite.setTexture(texturetwo);
}

/*
 Description: This function subtracts a life if the shield is not active. If the shield is active, it deactivates it and does not subtract a life.
 
 */
void Player::loseLife()
{
    //cout << "IN";
    if(shield == false)
    {
        lives--;
    }
    else
    {
        cout << "shield" << endl;
    }
    sprite.setTexture(texturetwo);
    shield = false;
}

/*
 Description: This returns the number of lives the player has.
 Return: int number of lives.
 
 */
int Player::getLives()
{
    return lives;
}

/*
 Description: This function returns the score of the player.
 Return: int score
 */
int Player::getScore()
{
    return score;
}

/*
 Description: This function returns the status of the shield.
 Return: bool shield
 */
bool Player::getShield()
{
    return shield;
}


Player::~Player(){};

/*
 Description: This function handles the collision of the player and a monster. It determines whether or not they collide by finding the distance between the two,
 Parameters: float x_position of monster, float y_position of monster, sf::Vector2f size of the monster
 Return: bool whether there was a collision or not
 */
bool Player::hitByMonster(float monster_x, float monster_y,  sf::Vector2f monster_size/*, bool debug*/)
{
    
    float diffX = getPosition().x - monster_x;
    float diffY = getPosition().y - monster_y;
    
    /*
     if (debug) {
     std::cout <<  "player position = (" << getPosition().x << ", " << getPosition().y << ")" << std::endl;
     std::cout <<  "monster position = (" << monster_x << ", " << monster_y << ")" << std::endl;
     std::cout << "dist=" << std::sqrt(diffX * diffX + diffY * diffY) << " < " <<  (size().x + monster_size.x) / 2.0f << std::endl;
     std::cout <<  "player size = " << size().x << "  monster size = " << monster_size.x << " " << std::endl;
     }
     */
    return std::sqrt(diffX * diffX + diffY * diffY) < (size().x + monster_size.x) / 2.0f;
    
    
}

