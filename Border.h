#ifndef BORDER_H
#define BORDER_H

#include <SFML/Graphics.hpp>

class Border : public sf::RectangleShape
{
public:
   Border(sf::Texture &BorderTexture, float x, float y);
   void draw(sf::RenderWindow& App);
   sf::Vector2f size() const;
   sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }


protected:

private:
    //int imageIndex;
  //  sf::Vector2f position;

    sf::Sprite sprite;
};

#endif // BORDER_H

