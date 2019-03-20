#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Bomb.h"
using namespace std;


Bomb::Bomb(sf::Texture &BombTexture)
{
    sprite.setTexture(BombTexture);
    sprite.setScale(.085, .085);
    sprite.setOrigin(sprite.getLocalBounds().width/2.0f,sprite.getLocalBounds().height / 2.0f);
}

void Bomb::moveBombToStartPosition(float mousePosition_x, float mousePosition_y, float viewPosition_y)
{
    mouseX = mousePosition_x;
    mouseY = mousePosition_y;
    sprite.setPosition(mousePosition_x, viewPosition_y);
}

bool Bomb::move()
{
    cout << mouseX << mouseY << endl;
    auto position = sprite.getPosition();
    position.y += 5.0f;
    sprite.setPosition(position.x, position.y);
    if (mouseY - position.y < 15)
        return false;
    return true;
}

void Bomb::draw(sf::RenderWindow& App)
{
    App.draw(sprite);
}

sf::Vector2f Bomb::size() const
{
    return sf::Vector2f(sprite.getLocalBounds().width * sprite.getScale().x, sprite.getLocalBounds().height * sprite.getScale().y);
}

bool Bomb::hitByMonster(float monster_x, float monster_y,  sf::Vector2f monster_size)
{
    return getDistance(monster_x, monster_y, monster_size) < (size().x + monster_size.x) * 1.5f;
}

double Bomb::getDistance(float monster_x, float monster_y,  sf::Vector2f monster_size)
{
    float diffX = getPosition().x - monster_x;
    float diffY = getPosition().y - monster_y;
    
    return sqrt(diffX * diffX + diffY * diffY);
    
}
