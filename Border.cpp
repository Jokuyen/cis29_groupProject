#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Border.h"
//#include <stdio.h>
using namespace std;
//#include "Invaders.h"

Border::Border(sf::Texture &BorderTexture, float x, float y)
{
    sprite.setTexture(BorderTexture);
    //setTexture(&BombTexture);
    //sprite.setOrigin(getLocalBounds().width/2.0f,getLocalBounds().height / 2.0f);

    sprite.setOrigin(sprite.getLocalBounds().width/2.0f,sprite.getLocalBounds().height / 2.0f);
    sprite.setPosition(x + sprite.getLocalBounds().width/2.0f, y + sprite.getLocalBounds().height / 2.0f);
    //sprite.setPosition(300, 200);
    //cout << "sprite:" << sprite.getPosition().x << ", "<<  sprite.getPosition().y << endl;

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
/*
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

    mouseX = mousePosition.x;
    mouseY = mousePosition.y;
    //setPosition(mousePosition.x, 0);
    sprite.setPosition(mousePosition.x, 0);
    cout << "sprite:" << sprite.getPosition().x << ", "<<  sprite.getPosition().y << endl;
    cout << "Bomb start" << endl;
}

bool Bomb::move()
{

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
*/

void Border::draw(sf::RenderWindow& App)
{
    App.draw(sprite);
}

sf::Vector2f Border::size() const
{
    return sf::Vector2f(sprite.getLocalBounds().width * sprite.getScale().x, sprite.getLocalBounds().height * sprite.getScale().y);
}
