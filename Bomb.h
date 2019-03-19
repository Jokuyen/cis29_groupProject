#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>

class Bomb : public sf::RectangleShape
{
public:
    Bomb(sf::Texture &BombTexture);
    void moveBombToStartPosition(float mousePosition_x, float mousePosition_y, float viewPosition_y);
    bool move();
    void draw(sf::RenderWindow& App);
    bool hitByMonster(float monster_x, float monster_y, sf::Vector2f monster_size);
    double getDistance(float monster_x, float monster_y, sf::Vector2f monster_size);
    sf::Vector2f size() const;
    sf::Vector2f getPosition()
    {
        return sf::Vector2f(mouseX, mouseY);
    }

private:
    float mouseY;
    float mouseX;
    sf::Sprite sprite;
};

#endif // BOMB_H
