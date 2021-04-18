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
		playerShape.setFillColor(sf::Color(250, 150, 0));
	}

	void draw(sf::RenderWindow& app);
	void updatePos(float x, float y);

};
