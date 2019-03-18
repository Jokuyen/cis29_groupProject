#include <cstdlib>
#include <iostream>
#include "Explosion.h"

Explosion::Explosion(sf::Texture& texture)
: exploding(false), count(0)
{

    //texture.loadFromFile(filename);
    explosion.setTexture(texture);
    explosion.setScale(0.3, 0.3);
    explosion.setOrigin(explosion.getLocalBounds().width/2.0f,explosion.getLocalBounds().height / 2.0f);
}
/*
void Explosion::update()
{
    ++count;
    if (count > 200)
    {
        exploding = false;
    }
    //explosion.rotate(90.0f);
}
*/
void Explosion::draw(sf::RenderWindow& App)
{
    App.draw(explosion);
}
