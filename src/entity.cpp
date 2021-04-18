#include "entity.h"
#include <cmath>

float Entity::mapW = 2000.f;
float Entity::mapH = 2300.f;

Vec2 Entity::getPos()
{
	return pos;
}

int Entity::getRadius()
{
	return radius;
}

//calculate total area of player and consumed enemy and find new radius
void Entity::updateSize(int consumedRadius)
{
	float newArea = (3.14 * pow(radius, 2)) + (3.14 * pow(consumedRadius, 2));
	radius = sqrt(newArea / 3.14);
}
