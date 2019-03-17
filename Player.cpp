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
Player::Player(sf::Texture& inputTexture, sf::Texture& inputShieldTexture, sf::Texture& inputFlippedTexture, sf::Texture& inputFlippedShieldTexture, float h, float w): Entity(inputTexture, w, h)
{
    lives = 20;
    score = 0;
    hit = -1;
    currentTexture = 1;
    dir = Right;
    
    texture = inputTexture;
    flippedTexture = inputFlippedTexture;
    
    shield = false;
    shieldTexture = inputShieldTexture;
    flippedShieldTexture = inputFlippedShieldTexture;
    
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(10, 10, 24, 30));
    sprite.setScale(4, 4);
    sprite.setOrigin(sprite.getLocalBounds().width/2.0f,sprite.getLocalBounds().height / 2.0f);
}


/*
 Description: This function handles the movement of the player. It changes the texture each move to animate the player. It moves the player 10.0f in the direction entered. There are statements in place to handle the boundaries of the screen.
 Parameters: Direction to move the sprite.
 
 */
void Player::move(Direction d)
{
    switch (d)
    {
        case Up:
            dir = Up;
            if (shield == false)
            {
                sprite.setTexture(texture);
            }
            else
            {
                sprite.setTexture(shieldTexture);
            }
            
            if (currentTexture == 1)
            {
                // 3rd row, 4th cat
                sprite.setTextureRect(sf::IntRect(160, 110, 24, 30));
                currentTexture = 2;
            }
            else
            {
                // 6th row, 3rd cat
                sprite.setTextureRect(sf::IntRect(110, 260, 24, 30));
                currentTexture = 1;
            }
            
            if (sprite.getPosition().y < 105.0f)
                break;
            else
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 10.0f);
            break;
        case Down:
            dir = Down;
            if (shield == false)
            {
                sprite.setTexture(texture);
            }
            else
            {
                sprite.setTexture(shieldTexture);
            }
            
            // 1st row of sprite sheet
            if (currentTexture == 1)
            {
                // 1st cat
                sprite.setTextureRect(sf::IntRect(10, 10, 24, 30));
                currentTexture = 2;
            }
            else if (currentTexture == 2)
            {
                // 4th cat
                sprite.setTextureRect(sf::IntRect(160, 10, 24, 30));
                currentTexture = 3;
            }
            else if (currentTexture == 3)
            {
                // 5th cat
                sprite.setTextureRect(sf::IntRect(210, 10, 24, 30));
                currentTexture = 1;
            }
            
            if ((sprite.getPosition().y + 20) > BACKGROUNDSIZE.y)
                break;
            else
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 10.0f);
            break;
        case Right:
            dir = Right;
            if (shield == false)
            {
                sprite.setTexture(texture);
            }
            else
            {
                sprite.setTexture(shieldTexture);
            }
            
            // 1st row of sprite sheet
            if (currentTexture == 1)
            {
                // 1st cat
                sprite.setTextureRect(sf::IntRect(10, 10, 24, 30));
                currentTexture = 2;
            }
            else if (currentTexture == 2)
            {
                // 4th cat
                sprite.setTextureRect(sf::IntRect(160, 10, 24, 30));
                currentTexture = 3;
            }
            else if (currentTexture == 3)
            {
                // 5th cat
                sprite.setTextureRect(sf::IntRect(210, 10, 24, 30));
                currentTexture = 1;
            }
            
            if (sprite.getPosition().x > BACKGROUNDSIZE.x-size().x/2)
                break;
            else
                sprite.setPosition(sprite.getPosition().x + 10.0f, sprite.getPosition().y);
            break;
        case Left:
            dir = Left;
            if (shield == false)
            {
                sprite.setTexture(flippedTexture);
            }
            else
            {
                sprite.setTexture(flippedShieldTexture);
            }
            
            // 1st row of sprite sheet
            if (currentTexture == 1)
            {
                // 10th cat
                sprite.setTextureRect(sf::IntRect(465, 10, 24, 30));
                currentTexture = 2;
            }
            else if (currentTexture == 2)
            {
                // 7th cat
                sprite.setTextureRect(sf::IntRect(315, 10, 24, 30));
                currentTexture = 3;
            }
            else if (currentTexture == 3)
            {
                // 6th cat
                sprite.setTextureRect(sf::IntRect(265, 10, 24, 30));
                currentTexture = 1;
            }
            
            if (sprite.getPosition().x < size().x / 2)
                break;
            else
                sprite.setPosition(sprite.getPosition().x - 10.0f, sprite.getPosition().y);
            break;
        default:
            ;
    };
}

/*
 Description: This function changes the status of the shield to true and sets the shield texture.
 
 */
void Player::applyShield()
{
    shield = true;
    
    if (sprite.getTexture() == &texture)
    {
        sprite.setTexture(shieldTexture);
    }
    else if (sprite.getTexture() == &flippedTexture)
    {
        sprite.setTexture(flippedShieldTexture);
    }
    
    cout << "shieldAPP" << endl;
}

/*
 Description: This function disables the shield(sets to false) and sets the texture back to regular.
 
 */
void Player::loseShield()
{
    shield = false;
    
    if (sprite.getTexture() == &shieldTexture)
    {
        sprite.setTexture(texture);
    }
    else if (sprite.getTexture() == &flippedShieldTexture)
    {
        sprite.setTexture(flippedTexture);
    }
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
        loseShield();
    }
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
bool Player::hitByMonster(float monster_x, float monster_y, sf::Vector2f monster_size/*, bool debug*/)
{
	return getDistance(monster_x, monster_y) < (size().x + monster_size.x) / 2.0f;
}

double Player::getDistance(float monster_x, float monster_y)
{
	float diffX = getPosition().x - monster_x;
	float diffY = getPosition().y - monster_y;

	return sqrt(diffX * diffX + diffY * diffY);

}

bool Player::attack(float monster_x, float monster_y, sf::Vector2f monster_size)
{
    float startx = getPosition().x-(size().x/2);
    float endx = getPosition().x+(size().x/2);
    float starty = getPosition().y-(size().y/2);
    float endy = getPosition().y+(size().y/2);
    double dist = getDistance(monster_x, monster_y);
    
    switch (dir)
    {
        case Up:
            if((dist < 300) && (monster_x >= startx && monster_x <= endx) && (monster_y <= endy))
            {
                return true;
            }
            break;
        case Down:
			// 5th row, 10th cat
			sprite.setTextureRect(sf::IntRect(463, 210, 24, 30));
            if((dist < 300) && (monster_x >= startx && monster_x <= endx) && (monster_y >= endy))
            {
                return true;
            }
            break;
        case Right:
			// 4th row, 7th cat
			sprite.setTextureRect(sf::IntRect(313, 160, 24, 30));
            if((dist < 300) && (monster_y >= starty && monster_y <= endy) && (monster_x >= endx))
            {
                return true;
            }
            break;
        case Left:
            if((dist < 300) && (monster_y >= starty && monster_y <= endy) && (monster_x <= startx))
            {
                return true;
            }
            break;
        default:
            return false;
    };
    return false;
}

bool Player::collectCoin(float coin_x, float coin_y, float coinSize_x, float coinSize_y)
{
	if (getDistance(coin_x, coin_y) < (size().x + coinSize_x) / 2.0f)
	{
		score++;
		return true;
	}
	return false;
}
