

//
//  Character.h
//  jscreens
//
//  Created by Mihika Marathe on 2/25/19 and Felicia Dewanaga on 3/7/19.
//  Copyright © 2019 Mihika Marathe and Felicia Dewanaga on 3/7/19. All rights reserved.
//

#ifndef Entity_h
#define Entity_h

#include <SFML/Graphics.hpp>

//static sf::Vector2f BACKGROUNDSIZE = sf::Vector2f(2048.0f, 1436.0f);
static sf::Vector2f BACKGROUNDSIZE = sf::Vector2f(2700.0f, 1800.0f);//1024.0f, 720.0f);

class Entity
{
protected:
    sf::Sprite sprite;
    sf::Image image;
    //sf::Vector2f position;
public:
    enum Direction {Up,Down,Left,Right};
    Entity(sf::Texture& texture, float width, float height);
    virtual ~Entity();
    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }
    sf::Sprite getSprite() const { return sprite; }
    void draw(sf::RenderWindow& App);
    //virtual void move(Direction);
    virtual sf::Vector2f size() const;
};

#endif /* Character_h */




