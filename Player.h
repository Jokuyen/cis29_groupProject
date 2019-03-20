//
//  Player.hpp
//  jscreens
//
//  Created by Mihika Marathe on 3/1/19 and Felicia Dewanaga on 3/7/19.
//  Copyright © 2019 Mihika Marathe and Felicia Dewanaga on 3/7/19. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include "Entity.h"
using namespace std;

class Player : public Entity
{
private:
    int lives;
    bool shield;
    int score;
    int hit;
    
    // Textures
    int currentTexture;
    int currentAttackTexture;
    sf::Texture texture;
    sf::Texture shieldTexture;
    sf::Texture flippedTexture;
    sf::Texture flippedShieldTexture;
    Direction dir;
    Direction sideDir;
    
public:
    Player(sf::Texture& inputTexture, sf::Texture& inputShieldTexture, sf::Texture& inputFlippedTexture, sf::Texture& inputFlippedShieldTexture, float h, float w);
    void move(Direction d);
    void applyShield();
    void loseShield();
    void loseLife();
    int getLives();
	void increaseLife();
    int getScore();
    bool getShield();
    void setHit(int h) { hit = h; };
    int getHit() const { return hit; };
    bool attack(float monster_x, float monster_y,  sf::Vector2f monster_size);
    void incrementCurrentAttackTexture() { currentAttackTexture++; }
    double getDistance(float monster_x, float monster_y);
    bool collectCoin(float coin_x, float coin_y, float coinSize_x, float coinSize_y);
    bool hitByMonster(float monster_x, float monster_y,  sf::Vector2f monster_size);
    void setMask(sf::Texture& maskTexture);
    friend ostream& operator <<(ostream& op, Player &val);
    ~Player();
    
};


#endif /* Player_hpp */

