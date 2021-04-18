#pragma once


struct Colour
{
	int r;
	int g;
	int b;

};

struct Vec2
{
	float x;
	float y;

};



class Entity
{
protected:
	
	float radius = 15;
	float speed;
	Colour colour = { 0,0,0 };
	Vec2 pos = { 0,0 };
	Vec2 vel = { 0.0f, 0.0f };
	 
public:
	Entity(float radius, Vec2 pos1, Colour colour1)
	{
		this->radius = radius;
		this->pos = pos1;
		this->colour = colour1;
	}
	static float mapW;
	static float mapH;
	Vec2 getPos();
	int getRadius();
	void updateSize(int radius);

};

