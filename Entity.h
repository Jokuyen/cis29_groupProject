
//
//  Character.h
//  jscreens
//
//  Created by Mihika Marathe on 2/25/19 and Felicia Dewanaga on 3/7/19.
//  Copyright © 2019 Mihika Marathe and Felicia Dewanaga on 3/7/19. All rights reserved.
//

#ifndef Entity_h
#define Entity_h

#include <iostream> //////////////////////////

#include <SFML/Graphics.hpp>


//static sf::Vector2f BACKGROUNDSIZE = sf::Vector2f(2048, 1536);
static sf::Vector2f BACKGROUNDSIZE = sf::Vector2f(1024.0f, 720.0f);

class Entity
{
protected:
    sf::Sprite sprite;
    sf::Image currentImage;

	static sf::Image image; // border1
	static sf::Image image2;  // border2
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
    virtual sf::Vector2f size() const;
    virtual void move(Direction d);
    void setPosition(float x, float y);
	void setImage()
	{
		currentImage = image;
	}
	void setImage2() 
	{
		std::cout << "\nsetImage2 called\n";
		currentImage = image2;
	}
};

#endif /* Character_h */








