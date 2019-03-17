//
//  Character.cpp
//  jscreens
//
//  Created by Mihika Marathe on 3/1/19 and Felicia Dewanaga on 3/7/19.
//  Copyright © 2019 Mihika Marathe and Felicia Dewanaga on 3/7/19. All rights reserved.
//
#include "Entity.h"
#include <stdio.h>


using namespace std;

/*
 Description: This is the constructor for the Entity class, it sets the texture of the sprite and the position of the sprite based on passed values. It sets the scale to a constant of 0.75x.75.
 Parameters: Texture, float width of screen, float height of screen
 
 */
Entity::Entity(sf::Texture& texture, float width, float height)
{
    sprite.setTexture(texture);
    sprite.setPosition(width / 2, height / 2);
    sprite.setScale(0.75, 0.75);
}

/*
 Description: This is the draw function, it calls the draw function of the RenderWindow class in order to draw the sprite on the window.
 Parameters: RenderWindow object on which to draw the sprite.
 
 */
void Entity::draw(sf::RenderWindow& App)
{
    App.draw(sprite);
}

/*
 Description: This is the size function, it returns the calculated size of the sprite using the scale and local bounds.
 Return: sf Vector2f containing the size.
 
 */
sf::Vector2f Entity::size() const
{
    return sf::Vector2f(sprite.getLocalBounds().width * sprite.getScale().x, sprite.getLocalBounds().height * sprite.getScale().y);
}

Entity::~Entity(){};

