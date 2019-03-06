//
//  Player.cpp
//  jscreens
//
//  Created by Mihika Marathe on 3/1/19.
//  Copyright © 2019 Mihika Marathe. All rights reserved.
//

#include "Player.h"

Player::Player(sf::Texture& textone, sf::Texture& texttwo, float h, float w): Entity(textone, w, h)
{
    textureone = textone;
    texturetwo = texttwo;
    texture = 1;
    lives = 3;
    score = 0;
    shield = false;
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
