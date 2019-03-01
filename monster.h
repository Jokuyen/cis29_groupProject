//
//  monster.h
// 
//
//  Created by Johnny Nguyen on 02-16-19.
//  Copyright © 2019 Johnny Nguyen. All rights reserved.
//

#ifndef MONSTER_H
#define MONSTER_H

#include "entity.h"

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

class Monster : public Entity
{
public:
	// Constructor
	Monster(sf::Texture* monsterTexture, const int SCREENWIDTH, const int BG_HEIGHT);

	// Monster stats
	int direction = 0; // 0 = Up, 1 = Down, 2 = Left, 3 = Right
	double movementSpeed = 2;
	int movementCounter = 0; 
	int movementLength = 30;

	// Functions
	void draw(sf::RenderWindow& App);
	
	void increaseSpeed() { if (movementSpeed < 15) movementSpeed += 0.5; }
	int randomNumber(int max);
	void updateMovement(const int SCREENWIDTH, const int BG_HEIGHT);
};

Monster::Monster(sf::Texture* monsterTexture, const int SCREENWIDTH, const int BG_HEIGHT)
{
	sprite.setTexture(*monsterTexture);
	sprite.setPosition(SCREENWIDTH / 2, BG_HEIGHT / 2);
}

void Monster::draw(sf::RenderWindow& App)
{
	App.draw(sprite);
}

void Monster::updateMovement(const int SCREENWIDTH, const int BG_HEIGHT)
{
	if (direction == 0) // Up
	{
		sprite.move(0, -movementSpeed);
	}
	else if (direction == 1) // Down
	{
		sprite.move(0, movementSpeed);
	}
	else if (direction == 2) // Left
	{
		sprite.move(-movementSpeed, 0);
	}
	else if (direction == 3) // Right
	{
		sprite.move(movementSpeed, 0);
	}
	else
	{
		// No movement
	}

	// Prevent monsters from leaving the window
	if (sprite.getPosition().y < 50) // Hitting top wall
	{
		direction = 1;
	}
	else if (sprite.getPosition().y > BG_HEIGHT - 40) // Hitting bottom wall
	{
		direction = 0;
	}
	else if (sprite.getPosition().x < 0) // Hitting left wall
	{
		direction = 3;
	}
	else if (sprite.getPosition().x > SCREENWIDTH - 100) // Hitting right wall
	{
		direction = 2;
	}


	movementCounter++;

	if (movementCounter >= movementLength)
	{
		/* If randomNumber(5), and since we only have 4 numbers for direction, 
		there will be a 4/5 chance that the monster will move. */
		direction = randomNumber(5); 
		movementCounter = 0;
	}

}

int Monster::randomNumber(int max)
{
	// Output random number from 0 to max
	int randomNumber;
	randomNumber = rand() % (max + 1);
	return randomNumber;
}

#endif // MONSTER_H