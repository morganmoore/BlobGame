#include <iostream>
#include <cmath>
#include "player.h"

//drawing the player sphere to the screen
void Player::draw(sf::RenderWindow& app)
{
	playerShape.setRadius(radius);
	playerShape.setOrigin(radius, radius);
	playerShape.setPosition(pos.x, pos.y);
	app.draw(playerShape);
}

//using mouse potion to determine a direction vector that will be used to increment the position of the player
void Player::updatePos(float x, float y)
{
	//direction vector
	float dirX = pos.x - x;
	float dirY = pos.y - y;

	//normalize
	float hyp = sqrt(dirX * dirX + dirY * dirY);
	dirX /= hyp;
	dirY /= hyp;
	if (hyp > 300) { hyp = 300; }
	speed = (hyp / 20) * pow(radius, -0.25);

	std::cout << "HYP" << hyp << "dirX: " << dirX << " " << dirY << std::endl;
	pos.x -= dirX * speed;
	pos.y -= dirY * speed;
}

