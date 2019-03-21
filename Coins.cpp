
#include "Coins.h"


/*
 Description: This is the constructor for the coin class. It initializes members of Entitiy along with multiple textures for animation purposes. There is also an int to keep track of the animation.
 
 */
Coins::Coins(sf::Texture& textOne, sf::Texture& textTwo, sf::Texture& textThree, sf::Texture& textFour, sf::Texture& textFive, sf::Texture& textSix, float h, float w) : Entity(textOne, w, h)
{
    textureArr[0] = textOne;
    textureArr[1] = textTwo;
    textureArr[2] = textThree;
    textureArr[3] = textFour;
    textureArr[4] = textFive;
    textureArr[5] = textSix;
    
    collide();
    sprite.setScale(1.25, 1.25);
    
    currentTexture = 0;

}

/*
 Description: This function returns a random double between the lower and upper bounds passed to it
 Parameters: lower and upper bounds
 Return: random double within the range
 
 */
double Coins::getRandom(int lower, int upper)
{
    double num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

/*
 Description: This function reassigns the position of a coin after it has been collected.
 
 */
void Coins::collide()
{
    double xPos = getRandom(0, 1300);
    double yPos = getRandom(700, 1600);
    if(image.getPixel(xPos, yPos) == sf::Color::Black)
    {
        collide();
    }
    else
        sprite.setPosition(xPos, yPos);
}

/*
 Description: This function animates the coin. It switches between 6 images to make it look as if it is spinning.
 
 */
void Coins::animate()
{
    if(currentTexture < 5)
        currentTexture += 1;
    else
        currentTexture = 0;
    sprite.setTexture(textureArr[currentTexture]);
}

Coins::~Coins(){};
