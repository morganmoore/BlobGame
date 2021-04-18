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
	float speed = 2.0f;


	//direction vector
	float dirX = pos.x - x;
	float dirY = pos.y - y;

	//normalize
	float hyp = sqrt(dirX * dirX + dirY * dirY);
	dirX /= hyp;
	dirY /= hyp;
	if (hyp > 300) { hyp = 300; }
	speed = (hyp / 25) * pow(radius, -0.25);

	std::cout << "HYP" << hyp << "dirX: " << dirX << " " << dirY << std::endl;
	pos.x -= dirX * speed;
	pos.y -= dirY * speed;
}

/*
void Player::updateVel(float x, float y)
{
	if ((abs(x) -0.2)>-0.1 && (abs(y) - 0.2)>- 0.1)
	{
		float tmpVel = sqrt(pow(abs(x), 2) / 2);
		float tmpMax = sqrt(pow(maxSpeed, 2) / 2);

		if(abs(vel.x)< tmpMax-tmpVel){vel.x += (tmpVel * x) / abs(x);}
		else if(abs(vel.x) > tmpMax + tmpVel){ vel.x -= (tmpVel * x) / abs(x); }
		if (abs(vel.y) < tmpMax - tmpVel) { vel.y += (tmpVel * y) / abs(y); }
		else if (abs(vel.y) > tmpMax + tmpVel) { vel.y -= (tmpVel * y) / abs(y); }
		//vel.x += (tmpVel *x)/abs(x);
		//vel.y += (tmpVel *y)/abs(y);
		
		vel.x = std::max(-tmpMax, std::min(vel.x, tmpMax));
		vel.y = std::max(-tmpMax, std::min(vel.y, tmpMax));
	}
	else
	{
		if (x == 0) { vel.x /= 1.1f; }
		else { vel.x += x; }
		if (y == 0) { vel.y /= 1.1f; }
		else { vel.y += y; }
		vel.x = std::max(-maxSpeed, std::min(vel.x, maxSpeed));
		vel.y = std::max(-maxSpeed, std::min(vel.y, maxSpeed));
	}
	
	std::cout << "SPEEEEEEEEEEEEEEEEEED             " <<sqrt(pow(vel.x, 2) + pow(vel.y, 2)) <<" "<< x<< "  "<< y << std::endl;
	
	

	pos.x += vel.x;
	pos.y += vel.y;

	pos.x = std::max(500.0f, std::min(pos.x, 2500.0f));
	pos.y = std::max(500.0f, std::min(pos.y, 2500.0f));
	
}

void Player::updatePos(float x, float y)
{
	float speed = 2.0f;
	
	
	//direction vector
	float dirX = pos.x - x;
	float dirY = pos.y - y;

	//normalize
	float hyp = sqrt(dirX * dirX + dirY * dirY);
	dirX /= hyp;
	dirY /= hyp;
	if (hyp > 300) { hyp = 300; }
	currentSpeed = (hyp/25) * pow(size, -0.25);
	
	std::cout << "HYP" << hyp << "dirX: " << dirX<< " "<< dirY<< std::endl;
	pos.x -= dirX* currentSpeed;
	pos.y -= dirY* currentSpeed;
}

void Player::updateSize(int radius)
{
	float newArea = (3.14 * pow(size, 2)) + (3.14 * pow(radius, 2));
	size = sqrt(newArea / 3.14);
}

Position Player::getPos()
{
	return pos;
}

int Player::getSize()
{
	return size; 
}


*/