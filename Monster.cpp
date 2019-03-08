//  monster.cpp
//  Created by Johnny Nguyen on 02-16-19 and Felicia Dewanaga on 3/8/19.

#include "Monster.h"

Monster::Monster(sf::Texture& monsterTexture, const int SCREENWIDTH, const int BG_HEIGHT): Entity(monsterTexture, SCREENWIDTH/2, BG_HEIGHT/2)
{
    sprite.setOrigin(sprite.getLocalBounds().width/2.0f,sprite.getLocalBounds().height / 2.0f);
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

Monster::~Monster() {};
