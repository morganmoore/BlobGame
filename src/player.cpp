#include <iostream>
#include <cmath>
#include "player.h"


void Player::draw(sf::RenderWindow& app)
{
	playerShape.setRadius(radius);
	playerShape.setOrigin(radius, radius);
	//std::cout << "PSZ: " << psz << std::endl;
	playerShape.setFillColor(sf::Color(250, 150, 0));
	playerShape.setPosition(pos.x, pos.y);
	app.draw(playerShape);
}

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

