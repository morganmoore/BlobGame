#pragma once

#include "entity.h"
#include <SFML/Graphics.hpp>


class Enemy : public Entity
{
	sf::CircleShape enemyShape;
	Vec2 vel = { 0,0 };
	float speedIncrement = 1.0f;
	float awareDist = 20.0f;
	float distFromPlayer;

public:
	Enemy(int radius1, Vec2 pos1, Colour colour1)
		:Entity(radius1, pos1, colour1)
	{
		enemyShape.setRadius(radius1);
	}

	void updatePos();
	void draw(sf::RenderWindow& app);
	void updateVelX(int posNeg);
	void updateVelY(int posNeg);
	float getSpeedIncrement();
	void checkOutsideMap();

};











