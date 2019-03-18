#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Bomb.h"
//#include <stdio.h>
using namespace std;
//#include "Invaders.h"

Bomb::Bomb(sf::Texture &BombTexture)
{
    sprite.setTexture(BombTexture);
    //setTexture(&BombTexture);
    //sprite.setOrigin(getLocalBounds().width/2.0f,getLocalBounds().height / 2.0f);
    sprite.setScale(.085, .085);
    sprite.setOrigin(sprite.getLocalBounds().width/2.0f,sprite.getLocalBounds().height / 2.0f);
    //sprite.setPosition(300, 200);
    cout << "sprite:" << sprite.getPosition().x << ", "<<  sprite.getPosition().y << endl;

    // set texture for bomb
    /*
    sf::IntRect bombImageLocationInTexture;
    bombImageLocationInTexture.height = BombSize.y;
    bombImageLocationInTexture.width = BombSize.x;
    bombImageLocationInTexture.left = 0;
    bombImageLocationInTexture.top = imageIndex * BombTexture.getSize().y / 3;
    setTextureRect(bombImageLocationInTexture);
    */

}
/*
void Bomb::draw(sf::RenderWindow& App)
{
    App.draw(sprite);
}
*/

void Bomb::moveBombToStartPosition(sf::Vector2f mousePosition)
{
 /*
    int bomberCol = rand() % NumInvaders.y;
    int bomberRow = invaders.getMaxIndexOfVisibleInvaderByColumn(bomberCol);
    if (bomberRow != -1)
        position = sf::Vector2f(invaders.getInvaderPosition(bomberRow,bomberCol));
    else
        position = sf::Vector2f(MainWindowWidth,MainWindowHeight);
    setPosition(position);
    */

    /*float mouseX = mousePosition.x;
    float mouseY = mousePosition.y;
    sprite.setPosition(mousePosition.x, 0);
    cout << endl << "Bomb created" << endl;
    */
    mouseX = mousePosition.x;
    mouseY = mousePosition.y;
    //setPosition(mousePosition.x, 0);
    sprite.setPosition(mousePosition.x, 0);
    cout << "sprite:" << sprite.getPosition().x << ", "<<  sprite.getPosition().y << endl;
    cout << "Bomb start" << endl;
}

bool Bomb::move()
{
   /* if (position == sf::Vector2f(MainWindowWidth,MainWindowHeight))
    {
        return false;
    }*/
    //float mouseY = mousePosition.y;
    //setPosition(position);
    /*sf::IntRect bombImageLocationInTexture;
    bombImageLocationInTexture = getTextureRect();
    if (bombImageLocationInTexture.left == 0)
        bombImageLocationInTexture.left = 12;
    else
        bombImageLocationInTexture.left = 0;

    setTextureRect(bombImageLocationInTexture); */
    auto position = sprite.getPosition();
    position.y += 5.0f;
    //setPosition(position.x, position.y);
    sprite.setPosition(position.x, position.y);
    cout << "sprite:" << sprite.getPosition().x << ", "<<  sprite.getPosition().y << endl;
    //sprite.setPosition(position);
    cout << "destination:" << mouseX <<  ", "<< mouseY <<endl;
    cout << "position:" << position.x <<  ", "<< position.y <<endl;

    if (mouseY - position.y < 15)
        return false;

    return true;
}

void Bomb::draw(sf::RenderWindow& App)
{
    App.draw(sprite);
}
/*
bool Bomb::hitByBullet(Bullet& bullet)
{
    bool hit;
    if ((position.y - bullet.getPosition().y) > BombSize.y / 2.0f)
        return false;
    float diffX = fabs(position.x - bullet.getPosition().x);
    float diffY = fabs(position.y - bullet.getPosition().y);
    hit = sqrt(diffX * diffX + diffY * diffY) < (BombSize.x / 2.0f + 1.0f);
    if (hit) std::cout << "* Bomb hit by bullet" << std::endl;
    return hit;
}
*/
sf::Vector2f Bomb::size() const
{
    return sf::Vector2f(sprite.getLocalBounds().width * sprite.getScale().x, sprite.getLocalBounds().height * sprite.getScale().y);
}

bool Bomb::hitByMonster(float monster_x, float monster_y,  sf::Vector2f monster_size/*, bool debug*/)
{
    return getDistance(monster_x, monster_y, monster_size) < (size().x + monster_size.x) * 1.5f;
}

double Bomb::getDistance(float monster_x, float monster_y,  sf::Vector2f monster_size)
{
    float diffX = getPosition().x - monster_x;
    float diffY = getPosition().y - monster_y;

    return sqrt(diffX * diffX + diffY * diffY);

}

