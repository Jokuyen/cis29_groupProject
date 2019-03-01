#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>

class Monster : public sf::RectangleShape
{
public:
	Monster(const std::string& filename, const int SCREENWIDTH, const int BG_HEIGHT);
	void draw(sf::RenderWindow& App);

	enum Direction { Right, Left };
	bool move(); // Return false if unable to move

private:
	const int BG_WIDTH;
	const int BG_HEIGHT;

	sf::Texture monsterTexture;
	sf::Sprite monsterSprite;
	Direction direction = Right;
};

Monster::Monster(const std::string& filename, const int SCREENWIDTH, const int BG_HEIGHT) :
	BG_WIDTH(SCREENWIDTH), BG_HEIGHT(BG_HEIGHT)
{
	Collision::CreateTextureAndBitmask(monsterTexture, filename);

	monsterSprite.setTexture(monsterTexture);
	monsterSprite.setOrigin(0, -300);
}

void Monster::draw(sf::RenderWindow& App)
{
	App.draw(monsterSprite);
}

bool Monster::move()
{
	////////// CHANGE WINDOW RESOLUTION LATER /////////////
	if (monsterSprite.getPosition().x != BG_WIDTH - 64 && direction == Right) // Hitting right limit
	{
		monsterSprite.move(sf::Vector2f(1.f, 0.f));
	}
	else
	{
		direction = Left;
	}

	if (monsterSprite.getPosition().x != 0 && direction == Left)
	{
		monsterSprite.move(sf::Vector2f(-1.f, 0.f));
	}
	else
	{
		direction = Right;
	}

	//else if (monsterSprite.getPosition().y < monsterSize.y) // Hitting top wall
	//{
	//	monsterSprite.move(sf::Vector2f(0.f, 1.f));
	//}
	//else if (monsterSprite.getPosition().y > 1050 - 2 * monsterSize.x) // Hitting bottom wall
	//{
	//	monsterSprite.move(sf::Vector2f(0.f, -1.f));
	//}

	return true;
}

//void Monster::createMonsters()
//{
//	sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Demo Game");
//
//	sf::Event event;
//
//	sf::Texture texture;
//	if (!texture.loadFromFile("monster.png"))
//	{
//		std::cerr << "Could not load monster.png\n";
//	}
//
//	sf::Sprite sprite(texture);
//
//	while (renderWindow.isOpen()) {
//		while (renderWindow.pollEvent(event))
//		{
//			if (event.type == sf::Event::EventType::Closed)
//				renderWindow.close();
//			// Key pressed
//			if (event.type == sf::Event::KeyPressed)
//			{
//				switch (event.key.code)
//				{
//				case sf::Keyboard::Up: // Move up
//					sprite.move(sf::Vector2f(0.f, -10.f));;
//					break;
//				case sf::Keyboard::Down: // Move down
//					sprite.move(sf::Vector2f(0.f, 10.f));;
//					break;
//				case sf::Keyboard::Left: // Move left
//					sprite.move(sf::Vector2f(-10.f, 0.f));;
//					break;
//				case sf::Keyboard::Right: // Move right
//					sprite.move(sf::Vector2f(10.f, 0.f));;
//					break;
//				default:
//					break;
//				}
//			}
//		}
//
//		renderWindow.clear();
//		renderWindow.draw(monsterSprite);
//		renderWindow.display();
//	}
//}

#endif // MONSTER_H