

#ifndef COINS_H
#define COINS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

class Coins {
    sf::Sound mySound;
    
public:
    
    Coins(sf::Sound s) : mySound(s) {
        sf::SoundBuffer buffer;
        
        if (!buffer.loadFromFile("1_Coins.wav")) {
            std::cout << "Error " << std:: endl;
        }
        
        sf::Sound sound;
        
        sound.setBuffer(buffer);
        
        //mySound = sound;
    }
    
    void playsound() { mySound.play();}
    //    void spawnCoins() {
    //        sf::Sprite sprit(_data)
    //    }
    
    //void move(Direction d);
};



#endif
