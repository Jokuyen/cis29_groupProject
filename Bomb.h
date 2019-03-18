#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>

class Bomb : public sf::RectangleShape
{
public:
    Bomb(sf::Texture &BombTexture);
    void moveBombToStartPosition(sf::Vector2f mousePosition);
    bool move();
    void draw(sf::RenderWindow& App);
    bool hitByMonster(float monster_x, float monster_y,  sf::Vector2f monster_size/*, bool debug*/);
    double getDistance(float monster_x, float monster_y,  sf::Vector2f monster_size);
    sf::Vector2f size() const;
    sf::Vector2f getPosition()
    {
        return sf::Vector2f(mouseX, mouseY);
    }


    //bool hitByBullet(Bullet& bullet);
protected:

private:
    //int imageIndex;
  //  sf::Vector2f position;
    float mouseY;
     float mouseX;
    sf::Sprite sprite;
};

#endif // BOMB_H
