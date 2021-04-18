#pragma once


struct Colour{int r;int g;int b;};
struct Vec2{float x;float y;};

class Entity
{
protected:
	static float mapW ;
	static float mapH;
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
	
	Vec2 getPos();
	int getRadius();
	static void setMapSize(float width, float height);
	void updateSize(int radius);
};

