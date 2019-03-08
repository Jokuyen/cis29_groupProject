//
//  Player.cpp
//  jscreens
//
//  Created by Mihika Marathe on 3/1/19 and Felicia Dewanaga on 3/7/19.
//  Copyright © 2019 Mihika Marathe and Felicia Dewanaga on 3/7/19. All rights reserved.
//

#include "Player.h"
#include <cmath>

Player::Player(sf::Texture& textone, sf::Texture& texttwo, float h, float w): Entity(textone, w, h)
{
    textureone = textone;
    texturetwo = texttwo;
    texture = 1;
    lives = 20;
    score = 0;
    shield = false;
    sprite.setOrigin(sprite.getLocalBounds().width/2.0f,sprite.getLocalBounds().height / 2.0f);
    hit = -1;
}

void Player::move(Direction d)
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
    switch (d)
    {
        case Up:
            if (sprite.getPosition().y < 80.0f)
                break;
            else
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 30.0f);
            /*
            if (sprite.getPosition().y < 50.0f)
                sprite.setPosition(sprite.getPosition().x, BackgroundSize.y - 1.0f);
             */
            break;
        case Down:
            if (sprite.getPosition().y > BackgroundSize.y-50.0f)
                break;
            else
                sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 30.0f);
            /*
            if (sprite.getPosition().y > BackgroundSize.y)
                sprite.setPosition(sprite.getPosition().x, 1.0f+50);
             */
            break;
        case Left:
            if (sprite.getPosition().x < 0.0f)
                break;
            else
                sprite.setPosition(sprite.getPosition().x - 30.0f,sprite.getPosition().y);
            /*
            if (sprite.getPosition().x < 0.0f)
                sprite.setPosition(BackgroundSize.x - 1.0f,sprite.getPosition().y);
             */
            break;
        case Right:
            if (sprite.getPosition().x > BackgroundSize.x-100)
                break;
            else
                sprite.setPosition(sprite.getPosition().x + 30.0f, sprite.getPosition().y);
            /*
            if (sprite.getPosition().x > BackgroundSize.x)
                sprite.setPosition(1.0f,sprite.getPosition().y);
             */
            break;
        default:
            ;
    };

}

void Player::applyShield()
{
    shield = true;
    cout << "shieldAPP" << endl;
}


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
    shield = false;
}

int Player::getLives()
{
    return lives;
}

int Player::getScore()
{
    return score;
}

bool Player::getShield()
{
    return shield;
}

Player::~Player(){};


bool Player::hitByMonster(float monster_x, float monster_y,  sf::Vector2f monster_size, bool debug)
{

    float diffX = getPosition().x - monster_x;
    float diffY = getPosition().y - monster_y;

    if (debug) {
        std::cout <<  "player position = (" << getPosition().x << ", " << getPosition().y << ")" << std::endl;
        std::cout <<  "monster position = (" << monster_x << ", " << monster_y << ")" << std::endl;
        std::cout << "dist=" << std::sqrt(diffX * diffX + diffY * diffY) << " < " <<  (size().x + monster_size.x) / 2.0f << std::endl;
        std::cout <<  "player size = " << size().x << "  monster size = " << monster_size.x << " " << std::endl;
    }
    return std::sqrt(diffX * diffX + diffY * diffY) < (size().x + monster_size.x) / 2.0f;


}
