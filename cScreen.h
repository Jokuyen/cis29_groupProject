#ifndef CSCREEN_H
#define CSCREEN_H

#include <SFML/Graphics.hpp>

const char* FONTIMAGE = "fake receipt.ttf";
class cScreen
{
public:
    virtual int Run(sf::RenderWindow &App, const int SCREENWIDTH, const int SCREENHEIGHT) = 0;
};

#endif // CSCREEN_H
