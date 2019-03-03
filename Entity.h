//
//  Character.h
//  jscreens
//
//  Created by Mihika Marathe on 2/25/19.
//  Copyright © 2019 Mihika Marathe. All rights reserved.
//

#ifndef Entity_h
#define Entity_h

#include <SFML/Graphics.hpp>

static sf::Vector2f BackgroundSize = sf::Vector2f(1650.0f, 1000.0f);

class Entity
{
protected:
    sf::Sprite sprite;
    sf::Vector2f position;
public:
    enum Direction {Up,Down,Left,Right};
    Entity(sf::Texture& texture, float width, float height);
    virtual ~Entity();
    sf::Vector2f getPosition() const
    {
        return position;
    }
    sf::Sprite getSprite() const { return sprite; }
    void draw(sf::RenderWindow& App);
    //virtual void move(Direction);

};

#endif /* Character_h */
