//
//  Character.cpp
//  jscreens
//
//  Created by Mihika Marathe on 3/1/19 and Felicia Dewanaga on 3/7/19.
//  Copyright © 2019 Mihika Marathe and Felicia Dewanaga on 3/7/19. All rights reserved.
//

#include <stdio.h>
#include "Entity.h"

using namespace std;

Entity::Entity(sf::Texture& texture, float width, float height)
{
    sprite.setTexture(texture);
    sprite.setPosition(width / 2, height / 2);
    sprite.setScale(0.75, 0.75);
}

void Entity::draw(sf::RenderWindow& App)
{
    App.draw(sprite);
}

sf::Vector2f Entity::size() const
{
    return sf::Vector2f(sprite.getLocalBounds().width * sprite.getScale().x, sprite.getLocalBounds().height * sprite.getScale().y);
}

Entity::~Entity(){};
