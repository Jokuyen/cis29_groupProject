#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <string>

#include <SFML/Graphics.hpp>


class Explosion
{
public:
    Explosion(sf::Texture& texture);
    bool isExploding() const
    {
        return exploding;
    }
    sf::Sprite getExplosion() const
    {
        return explosion;
    }
    void startExplosion(sf::Vector2f location)
    {
        explosion.setPosition(location);
        count = 0;
        exploding = true;
    }
    sf::Vector2f getPosition() const { return explosion.getPosition(); }
    void draw(sf::RenderWindow& App);
    
private:
    sf::Texture texture;
    sf::Sprite explosion;
    bool exploding;
    int count;
};

#endif // EXPLOSION_H

