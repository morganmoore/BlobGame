#pragma once

#include "entity.h"
#include <SFML/Graphics.hpp>


class Player : public Entity
{
	std::string name;
	sf::CircleShape playerShape;
public:
	Player(int size1, Vec2 pos1, Colour colour1, float radius1, std::string name1)
		:Entity(size1, pos1, colour1)
	{
		this->name = name1;
		this->playerShape.setRadius(radius1);
	}



	void draw(sf::RenderWindow& app);
	void updatePos(float x, float y);

};
/*
class Player 
{

	float size = 15;
	float maxSpeed = 5.0f;
	float baseSpeed = 4.0f;
	float currentSpeed;
	Colour colour = { 0,0,0 };
	Position pos = { 0,0 };
	Velocity vel = { 0.0f, 0.0f };
public:
	Player(int size1, Position pos1, Velocity vel1, Colour colour1)
	{
		this->size = size1;
		this->pos = pos1;
		this->vel = vel1;
		colour = colour1;
	}

	

	void updateVel(float x, float y);
	void updatePos(float x, float y);
	void updateSize(int radius);
	Position getPos();
	int getSize();
	
};
*/